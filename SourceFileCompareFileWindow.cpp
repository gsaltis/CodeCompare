/*****************************************************************************
 * FILE NAME    : SourceFileCompareFileWindow.cpp
 * DATE         : April 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SourceFileCompareFileWindow.h"
#include "trace.h"

/*****************************************************************************!
 * Function : SourceFileCompareFileWindow
 *****************************************************************************/
SourceFileCompareFileWindow::SourceFileCompareFileWindow
() : SourceFileCompareStatsWindow()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~SourceFileCompareFileWindow
 *****************************************************************************/
SourceFileCompareFileWindow::~SourceFileCompareFileWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SourceFileCompareFileWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SourceFileCompareFileWindow::CreateSubWindows()
{
  int                           labelX, labelY, labelW, labelH;
  QLabel*                       label;
  QFont                                 font = QFont("", 10, QFont::Bold);
  
  labelX                        = 10;
  labelW                        = 100;
  labelH                        = 20;
  labelY                        = 20;
  
  fileLabel1 = new QLabel(this);
  fileLabel1->move(labelX, labelY);
  fileLabel1->resize(labelW, labelH);
  fileLabel1->setAlignment(Qt::AlignLeft);

  labelY += 25;

  fileLabel2 = new QLabel(this);
  fileLabel2->move(labelX, labelY);
  fileLabel2->resize(labelW, labelH);
  fileLabel2->setAlignment(Qt::AlignLeft);
  labelY += 25;
  
  //! Create label  
  label = new QLabel();
  label->setParent(this);
  label->move(labelX, labelY);
  label->resize(labelW, 20);
  label->setText("Adds :");
  label->setAlignment(Qt::AlignRight);
  label->setFont(font);

  addCountLabel = new QLabel();
  addCountLabel->setParent(this);
  addCountLabel->move(labelW + 15, labelY);
  addCountLabel->resize(labelW, 20);
  addCountLabel->setText("");
  addCountLabel->setAlignment(Qt::AlignLeft);
  labelY += 25;

  //! Create label  
  label = new QLabel();
  label->setParent(this);
  label->move(labelX, labelY);
  label->resize(labelW, 20);
  label->setText("Change :");
  label->setAlignment(Qt::AlignRight);
  label->setFont(font);

  changeCountLabel = new QLabel();
  changeCountLabel->setParent(this);
  changeCountLabel->move(labelW + 15, labelY);
  changeCountLabel->resize(labelW, 20);
  changeCountLabel->setText("");
  changeCountLabel->setAlignment(Qt::AlignLeft);
  labelY += 25;

  //! Create label  
  label = new QLabel();
  label->setParent(this);
  label->move(labelX, labelY);
  label->resize(labelW, 20);
  label->setText("Delete :");
  label->setAlignment(Qt::AlignRight);
  label->setFont(font);

  deleteCountLabel = new QLabel();
  deleteCountLabel->setParent(this);
  deleteCountLabel->move(labelW + 15, labelY);
  deleteCountLabel->resize(labelW, 20);
  deleteCountLabel->setText("");
  deleteCountLabel->setAlignment(Qt::AlignLeft);
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SourceFileCompareFileWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SourceFileCompareFileWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   fileLabel1X, fileLabel1Y;
  int                                   fileLabel1W, fileLabel1H;
  int                                   fileLabel2X, fileLabel2Y;
  int                                   fileLabel2W, fileLabel2H;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  fileLabel1X = fileLabel1->pos().x();
  fileLabel1Y = fileLabel1->pos().y();
  fileLabel1H = fileLabel1->size().height();
  fileLabel1W = width - (fileLabel1X * 2);
  fileLabel1->move(fileLabel1X, fileLabel1Y);
  fileLabel1->resize(fileLabel1W, fileLabel1H);
  
  fileLabel2X = fileLabel2->pos().x();
  fileLabel2Y = fileLabel2->pos().y();
  fileLabel2H = fileLabel2->size().height();
  fileLabel2W = width - (fileLabel2X * 2);
  fileLabel2->move(fileLabel2X, fileLabel2Y);
  fileLabel2->resize(fileLabel2W, fileLabel2H);
  
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : SetFileTreeItemNames
 *****************************************************************************/
void
SourceFileCompareFileWindow::SetFileTreeItemNames
(FileTreeElement* InItem)
{
  fileItem = InItem;

  if ( NULL == fileItem ) {
    return;
  }
  fileLabel1->setText(InItem->GetCodeTrack1()->RemoveLeadingBasePath(fileItem->GetAbsoluteFileName1()));
  QString st = fileItem->GetAbsoluteFileName2();
  fileLabel2->setText(InItem->GetCodeTrack2()->RemoveLeadingBasePath(st));
  SetCounts(fileItem->GetChangeLinesCount());
}

/*****************************************************************************!
 * Function : SetCounts
 *****************************************************************************/
void
SourceFileCompareFileWindow::SetCounts
(QList<int> InValues)
{
  addCountLabel->setText(QString("%1").arg(InValues[0]));
  changeCountLabel->setText(QString("%1").arg(InValues[1]));
  deleteCountLabel->setText(QString("%1").arg(InValues[2]));
}
