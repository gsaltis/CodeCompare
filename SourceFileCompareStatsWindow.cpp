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
  size = InEvent->size();
  width = size.width();
  (void)width;
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
