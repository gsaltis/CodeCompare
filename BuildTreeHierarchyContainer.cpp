/*****************************************************************************
 * FILE NAME    : BuildTreeHierarchyContainer.cpp
 * DATE         : April 14 2023
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
#include "BuildTreeHierarchyContainer.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildTreeHierarchyContainer
 *****************************************************************************/
BuildTreeHierarchyContainer::BuildTreeHierarchyContainer
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTreeHierarchyContainer
 *****************************************************************************/
BuildTreeHierarchyContainer::~BuildTreeHierarchyContainer
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeHierarchyContainer::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeHierarchyContainer::CreateSubWindows()
{
  buildTreeHierarchyTableWindow = new BuildTreeHierarchyTable();  
  buildTreeHierarchyTableWindow->setParent(this);
  buildTreeHierarchyTableWindow->move(0, 0);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTreeHierarchyContainer::InitializeSubWindows()
{
  buildTreeHierarchyTableWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeHierarchyContainer::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  if ( buildTreeHierarchyTableWindow ) {
    buildTreeHierarchyTableWindow->resize(width, height);
  }
}

/*****************************************************************************!
 * Function : SlotTreeItemSelected
 *****************************************************************************/
void
BuildTreeHierarchyContainer::SlotTreeItemSelected
(BuildLine* InLine, QString InFilename)
{
  emit SignalTreeItemSelected(InLine, InFilename);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BuildTreeHierarchyContainer::CreateConnections(void)
{
  connect(this,
          SIGNAL(SignalTreeItemSelected(BuildLine*, QString)),
          buildTreeHierarchyTableWindow,
          SLOT(SlotTreeItemSelected(BuildLine*, QString)));
}
