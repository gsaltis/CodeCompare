/*****************************************************************************
 * FILE NAME    : DirectoryReadEntry.cpp
 * DATE         : March 23 2023
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
#include "DirectoryReadEntry.h"

/*****************************************************************************!
 * Function : DirectoryReadEntry
 *****************************************************************************/
DirectoryReadEntry::DirectoryReadEntry
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 0)));
  setPalette(pal);
  setAutoFillBackground(true);
  
  initialize();
}

/*****************************************************************************!
 * Function : ~DirectoryReadEntry
 *****************************************************************************/
DirectoryReadEntry::~DirectoryReadEntry
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
DirectoryReadEntry::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  ActionbrowseButtonPushed = new QAction("browseButtonPushed", this);
  connect(ActionbrowseButtonPushed, SIGNAL(triggered()), this, SLOT(SlotbrowseButtonPushed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
DirectoryReadEntry::CreateSubWindows()
{
    //! Create directoryNameEdit LineEdit
  directoryNameEdit = new QLineEdit();
  directoryNameEdit->setParent(this);
  directoryNameEdit->move(0,0);
  directoryNameEdit->resize(100,20);

  //! Create the browseButton button
  browseButton = new QPushButton();
  browseButton->setParent(this);
  browseButton->setText("...");
  browseButton->move(0, 0);
  browseButton->resize(20, 16);
  connect(browseButton, SIGNAL(pressed()), this, SLOT(SlotbrowseButtonPushed()));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
DirectoryReadEntry::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
DirectoryReadEntry::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   buttonWidth;
  int                                   w;
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  buttonWidth = height;
  
  w = width - buttonWidth - 4;
  directoryNameEdit->resize(w, height);

  browseButton->move(width - (buttonWidth + 2) , 0);
  browseButton->resize(height, height);
}

/*****************************************************************************!
 * Function : SlotbrowseButtonPushed
 *****************************************************************************/
void
DirectoryReadEntry::SlotbrowseButtonPushed(void)
{
  
}
