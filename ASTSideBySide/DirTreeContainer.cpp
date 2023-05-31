/*****************************************************************************
 * FILE NAME    : DirTreeContainer.cpp
 * DATE         : May 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirTreeContainer.h"
#include "trace.h"

/*****************************************************************************!
 * Function : DirTreeContainer
 *****************************************************************************/
DirTreeContainer::DirTreeContainer
(DirTree* InDirTree) : QWidget()
{
  dirTree = InDirTree;
  dirTree->setParent(this);
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~DirTreeContainer
 *****************************************************************************/
DirTreeContainer::~DirTreeContainer
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
DirTreeContainer::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
DirTreeContainer::CreateSubWindows()
{
  toolBar = new QFrame(this);
  toolBar->setFrameShadow(QFrame::Sunken);
  toolBar->setFrameStyle(QFrame::Panel);
  toolBar->setStyleSheet("QFrame { border : 1px solid #CCC}");

  //! Create the CollapseButton button  
  CollapseButton = new QPushButton();
  CollapseButton->setParent(toolBar);
  CollapseButton->setText("Ex");
  CollapseButton->move(1, 1);
  CollapseButton->resize(30,30);
  connect(CollapseButton, SIGNAL(pressed()), this, SLOT(SlotCollapseButtonPushed()));

  ChangedItemsButton = new QPushButton();
  ChangedItemsButton->setParent(toolBar);
  ChangedItemsButton->setText("Ch");
  ChangedItemsButton->move(33, 1);
  ChangedItemsButton->resize(30,30);
  connect(ChangedItemsButton, SIGNAL(pressed()), this, SLOT(SlotChangedItemsButtonPushed()));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
DirTreeContainer::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
DirTreeContainer::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   dirTreeW, dirTreeH, dirTreeX, dirTreeY;
  int                                   toolBarW, toolBarH, toolBarX, toolBarY;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  dirTreeW = width;
  dirTreeH = height - 32;
  dirTreeX = 0;
  dirTreeY = 0;

  toolBarX = 0;
  toolBarH = 32;
  toolBarW = width;
  toolBarY = height - 32;
  
  dirTree->move(dirTreeX, dirTreeY);
  dirTree->resize(dirTreeW, dirTreeH);

  toolBar->move(toolBarX, toolBarY);
  toolBar->resize(toolBarW, toolBarH);
}

/*****************************************************************************!
 * Function : SlotCollapseButtonPushed
 *****************************************************************************/
void
DirTreeContainer::SlotCollapseButtonPushed(void)
{
  emit SignalCollapseTree();
  if ( dirTree->GetExpanded() ) {
    CollapseButton->setText("CO");
    return;
  }
  CollapseButton->setText("EX");
}

/*****************************************************************************!
 * Function : SlotChangedItemsButtonPushed
 *****************************************************************************/
void
DirTreeContainer::SlotChangedItemsButtonPushed(void)
{
  emit SignalChangedItemsDisplay();
  if ( dirTree->GetDisplayAllItems() ) {
    ChangedItemsButton->setText("CH");
    return;
  }
  ChangedItemsButton->setText("ALL");
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
DirTreeContainer::CreateConnections(void)
{
  connect(this, DirTreeContainer::SignalCollapseTree, dirTree, DirTree::SlotToggleTreeView);
  connect(this, DirTreeContainer::SignalChangedItemsDisplay, dirTree, DirTree::SlotToggleChangedItems);
}
