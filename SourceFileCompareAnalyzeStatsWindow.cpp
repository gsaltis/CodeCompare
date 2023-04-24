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
  int                                   y;

  y = 80;
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

  size = InEvent->size();
  width = size.width();
  (void)width;
  LabelFileName1->resize(width - 20, 20);
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
  fileName1 = fileItem->GetAbsoluteFileName1();
  LabelFileName1->setText(fileName1);
}
