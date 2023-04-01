/*****************************************************************************
 * FILE NAME    : CodeWindow.cpp
 * DATE         : March 22 2023
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
#include "CodeWindow.h"
#include "trace.h"

/*****************************************************************************!
 * Function : CodeWindow
 *****************************************************************************/
CodeWindow::CodeWindow
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShape(QFrame::Panel);
  setFrameShadow(QFrame::Sunken);
  setLineWidth(2);
  initialize();
}

/*****************************************************************************!
 * Function : ~CodeWindow
 *****************************************************************************/
CodeWindow::~CodeWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
CodeWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
CodeWindow::CreateSubWindows()
{
  header = new WindowHeader();  
  header->setParent(this);
  dirTreeWindow = new DirectoryTreeWindow();
  dirTreeWindow->setParent(this);
  dirTreeWindow->hide();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
CodeWindow::InitializeSubWindows()
{
  header = NULL;  
  dirTreeWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
CodeWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   dirTreeWindowX, dirTreeWindowY;
  int                                   dirTreeWindowW, dirTreeWindowH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
  if ( header ) {
    header->move(2, 0);
    header->resize(width - 2, WINDOW_HEADER_HEIGHT);
  }

  dirTreeWindowX = 5;
  dirTreeWindowY = WINDOW_HEADER_HEIGHT + 3;
  dirTreeWindowW = width - (3 + 5);
  dirTreeWindowH = (height - (WINDOW_HEADER_HEIGHT + (3 * 2)));
  if ( dirTreeWindow ) {
    dirTreeWindow->move(dirTreeWindowX, dirTreeWindowY);
    dirTreeWindow->resize(dirTreeWindowW, dirTreeWindowH);
  }
}

/*****************************************************************************!
 * Function : SetTitle
 *****************************************************************************/
void
CodeWindow::SetTitle
(QString InTitle)
{
  header->SetText(InTitle);
}

/*****************************************************************************!
 * Function : AddDirectory
 *****************************************************************************/
void
CodeWindow::AddDirectory
(QString InDirectoryName)
{
  directoryName = InDirectoryName;
  dirTreeWindow->show();
  header->SetText(InDirectoryName);
  dirTreeWindow->PopulateDirectory(InDirectoryName);
}

