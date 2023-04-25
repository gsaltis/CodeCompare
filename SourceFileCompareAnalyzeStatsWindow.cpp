/*****************************************************************************
 * FILE NAME    : SourceFileCompareAnalyzeStatsWindow.cpp
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
#include "SourceFileCompareAnalyzeStatsWindow.h"
#include "trace.h"

/*****************************************************************************!
 * Function : SourceFileCompareAnalyzeStatsWindow
 *****************************************************************************/
SourceFileCompareAnalyzeStatsWindow::SourceFileCompareAnalyzeStatsWindow
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
 * Function : ~SourceFileCompareAnalyzeStatsWindow
 *****************************************************************************/
SourceFileCompareAnalyzeStatsWindow::~SourceFileCompareAnalyzeStatsWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SourceFileCompareAnalyzeStatsWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SourceFileCompareAnalyzeStatsWindow::CreateSubWindows()
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
  fileSourceCountLabel->resize(130, 20);
  fileSourceCountLabel->setText("lkj");
  fileSourceCountLabel->setAlignment(Qt::AlignLeft);

  //! Create label
  fileCurrentSourceCountLabel = new QLabel();
  fileCurrentSourceCountLabel->setParent(this);
  fileCurrentSourceCountLabel->move(labelWidth + 15, y);
  fileCurrentSourceCountLabel->resize(100, 20);
  fileCurrentSourceCountLabel->setText("");
  fileCurrentSourceCountLabel->setAlignment(Qt::AlignLeft);

  y += 25;

  //! Create label  
  LabelFileName1 = new QLabel();
  LabelFileName1->setParent(this);
  LabelFileName1->move(10, y);
  LabelFileName1->resize(100, 20);
  LabelFileName1->setText("sdf");
  LabelFileName1->setAlignment(Qt::AlignLeft);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SourceFileCompareAnalyzeStatsWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SourceFileCompareAnalyzeStatsWindow::resizeEvent
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
  int                                   fileCurrentSourceCountLabelX, fileCurrentSourceCountLabelY;
  int                                   fileCurrentSourceCountLabelW, fileCurrentSourceCountLabelH;

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
  fileSourceCountLabelW = (width - (fileSourceCountLabelX + 10) / 2);
  fileSourceCountLabel->move(fileSourceCountLabelX, fileSourceCountLabelY);
  fileSourceCountLabel->resize(fileSourceCountLabelW, fileSourceCountLabelH);

  LabelFileName1->resize(width - 20, 20);

  fileCurrentSourceCountLabelX = (width - (fileSourceCountLabelX + 10) / 2);
  fileCurrentSourceCountLabelY = fileCurrentSourceCountLabel->pos().y();
  fileCurrentSourceCountLabelH = fileCurrentSourceCountLabel->size().height();
  fileCurrentSourceCountLabelW = (width - (fileCurrentSourceCountLabelX + 10) / 2);
  fileCurrentSourceCountLabel->move(fileCurrentSourceCountLabelX, fileCurrentSourceCountLabelY);
  fileCurrentSourceCountLabel->resize(fileCurrentSourceCountLabelW, fileCurrentSourceCountLabelH);
}

/*****************************************************************************!
 * Function : SetFileItem
 *****************************************************************************/
void
SourceFileCompareAnalyzeStatsWindow::SetFileItem
(FileTreeWidgetItem* InFileItem)
{
  QString                               fileName1;
  fileItem = InFileItem;
  if ( fileItem ) {
    fileName1 = fileItem->GetAbsoluteFileName1();
    LabelFileName1->setText(fileName1);
    return;
  }
  LabelFileName1->setText("");
}

/*****************************************************************************!
 * Function : SetFileCount
 *****************************************************************************/
void
SourceFileCompareAnalyzeStatsWindow::SetFileCount
(int InFileCount)
{
  fileCountLabel->setText(QString("%1").arg(InFileCount));
}

/*****************************************************************************!
 * Function : SetFileDifferCount
 *****************************************************************************/
void
SourceFileCompareAnalyzeStatsWindow::SetFileDifferCount
(int InFileDifferCount)
{
  differSourceCount = InFileDifferCount;
  fileDifferCountLabel->setText(QString("%1 of %2")
                                .arg(differSourceCount)
                                .arg(currentSourceCount));
}

/*****************************************************************************!
 * Function : SetFileSourceCount
 *****************************************************************************/
void
SourceFileCompareAnalyzeStatsWindow::SetFileSourceCount
(int InFileSourceCount)
{
  fileSourceCountLabel->setText(QString("%1").arg(InFileSourceCount));
}

/*****************************************************************************!
 * Function : SetFileCurrentSourceCount
 *****************************************************************************/
void
SourceFileCompareAnalyzeStatsWindow::SetFileCurrentSourceCount
(int InFileCurrentSourceCount)
{
  currentSourceCount = InFileCurrentSourceCount;
  fileDifferCountLabel->setText(QString("%1 of %2")
                                .arg(differSourceCount)
                                .arg(currentSourceCount));
}

