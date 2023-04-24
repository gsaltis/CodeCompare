/*****************************************************************************
 * FILE NAME    : SourceFileCompareStatsWindow.cpp
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
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SourceFileCompareStatsWindow.h"

/*****************************************************************************!
 * Function : SourceFileCompareStatsWindow
 *****************************************************************************/
SourceFileCompareStatsWindow::SourceFileCompareStatsWindow
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(240, 240, 240)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
  setFrameShadow(QFrame::Sunken);
  setFrameShape(QFrame::Box);
}

/*****************************************************************************!
 * Function : ~SourceFileCompareStatsWindow
 *****************************************************************************/
SourceFileCompareStatsWindow::~SourceFileCompareStatsWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SourceFileCompareStatsWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SourceFileCompareStatsWindow::CreateSubWindows()
{
  QLabel*                               label;
  QFont                                 font = QFont("", 10, QFont::Bold);
  int                                   y = 15;
  int                                   labelWidth = 140;
  
  //! Create label  
  label = new QLabel();
  label->setParent(this);
  label->move(10, y);
  label->resize(labelWidth, 20);
  label->setText("File Count :");
  label->setAlignment(Qt::AlignRight);
  label->setFont(font);

  //! Create label
  fileCountLabel = new QLabel();
  fileCountLabel->setParent(this);
  fileCountLabel->move(labelWidth + 15, y);
  fileCountLabel->resize(100, 20);
  fileCountLabel->setText("lkj");
  fileCountLabel->setAlignment(Qt::AlignLeft);
  y += 25;

  //! Create label  
  label = new QLabel();
  label->setParent(this);
  label->move(10, y);
  label->resize(labelWidth, 20);
  label->setText("File Differ Count :");
  label->setAlignment(Qt::AlignRight);
  label->setFont(font);

  //! Create label
  fileDifferCountLabel = new QLabel();
  fileDifferCountLabel->setParent(this);
  fileDifferCountLabel->move(labelWidth + 15, y);
  fileDifferCountLabel->resize(100, 20);
  fileDifferCountLabel->setText("lkj");
  fileDifferCountLabel->setAlignment(Qt::AlignLeft);
  y += 25;

  //! Create label  
  label = new QLabel();
  label->setParent(this);
  label->move(10, y);
  label->resize(labelWidth, 20);
  label->setText("Source File Count :");
  label->setAlignment(Qt::AlignRight);
  label->setFont(font);

  //! Create label
  fileSourceCountLabel = new QLabel();
  fileSourceCountLabel->setParent(this);
  fileSourceCountLabel->move(labelWidth + 15, y);
  fileSourceCountLabel->resize(100, 20);
  fileSourceCountLabel->setText("lkj");
  fileSourceCountLabel->setAlignment(Qt::AlignLeft);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SourceFileCompareStatsWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SourceFileCompareStatsWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   fileCountLabelX, fileCountLabelY;
  int                                   fileCountLabelW, fileCountLabelH;
  int                                   fileDifferCountLabelX, fileDifferCountLabelY;
  int                                   fileDifferCountLabelW, fileDifferCountLabelH;
  int                                   fileSourceCountLabelX, fileSourceCountLabelY;
  int                                   fileSourceCountLabelW, fileSourceCountLabelH;
  
  size = InEvent->size();
  width = size.width();

  fileCountLabelX = fileCountLabel->pos().x();
  fileCountLabelY = fileCountLabel->pos().y();
  fileCountLabelH = fileCountLabel->size().height();
  fileCountLabelW = width - (fileCountLabelX + 10);
  fileCountLabel->move(fileCountLabelX, fileCountLabelY);
  fileCountLabel->resize(fileCountLabelW, fileCountLabelH);

  fileDifferCountLabelX = fileDifferCountLabel->pos().x();
  fileDifferCountLabelY = fileDifferCountLabel->pos().y();
  fileDifferCountLabelH = fileDifferCountLabel->size().height();
  fileDifferCountLabelW = width - (fileDifferCountLabelX + 10);
  fileDifferCountLabel->move(fileDifferCountLabelX, fileDifferCountLabelY);
  fileDifferCountLabel->resize(fileDifferCountLabelW, fileDifferCountLabelH);

  fileSourceCountLabelX = fileSourceCountLabel->pos().x();
  fileSourceCountLabelY = fileSourceCountLabel->pos().y();
  fileSourceCountLabelH = fileSourceCountLabel->size().height();
  fileSourceCountLabelW = width - (fileSourceCountLabelX + 10);
  fileSourceCountLabel->move(fileSourceCountLabelX, fileSourceCountLabelY);
  fileSourceCountLabel->resize(fileSourceCountLabelW, fileSourceCountLabelH);
}

/*****************************************************************************!
 * Function : SetFileCount
 *****************************************************************************/
void
SourceFileCompareStatsWindow::SetFileCount
(int InFileCount)
{
  fileCountLabel->setText(QString("%1").arg(InFileCount));
}

/*****************************************************************************!
 * Function : SetFileDifferCount
 *****************************************************************************/
void
SourceFileCompareStatsWindow::SetFileDifferCount
(int InFileDifferCount)
{
  fileDifferCountLabel->setText(QString("%1").arg(InFileDifferCount));
}

/*****************************************************************************!
 * Function : SetFileDifferCount
 *****************************************************************************/
void
SourceFileCompareStatsWindow::SetFileSourceCount
(int InFileSourceCount)
{
  fileSourceCountLabel->setText(QString("%1").arg(InFileSourceCount));
}

/*****************************************************************************!
 * Function : GetFileItem
 *****************************************************************************/
FileTreeWidgetItem*
SourceFileCompareStatsWindow::GetFileItem(void)
{
  return fileItem;  
}

/*****************************************************************************!
 * Function : SetFileItem
 *****************************************************************************/
void
SourceFileCompareStatsWindow::SetFileItem
(FileTreeWidgetItem* InFileItem)
{
  fileItem = InFileItem;  
}
