/*****************************************************************************
 * FILE NAME    : BuildTreeContainer.cpp
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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTreeContainer.h"

/*****************************************************************************!
 * Function : BuildTreeContainer
 *****************************************************************************/
BuildTreeContainer::BuildTreeContainer
(BuildTree* InBuildTree) : QWidget()
{
  QPalette pal;
  buildTree = InBuildTree;
  buildTree->setParent(this);
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTreeContainer
 *****************************************************************************/
BuildTreeContainer::~BuildTreeContainer
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeContainer::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeContainer::CreateSubWindows()
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
BuildTreeContainer::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeContainer::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   buildTreeX, buildTreeY, buildTreeW, buildTreeH;
  int                                   toolBarW, toolBarH, toolBarX, toolBarY;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  buildTreeX = 0;
  buildTreeY = 0;
  buildTreeW = width;
  buildTreeH = height - 32;

  toolBarX = 0;
  toolBarH = 32;
  toolBarW = width;
  toolBarY = height - 32;
  
  buildTree->move(buildTreeX, buildTreeY);
  buildTree->resize(buildTreeW, buildTreeH);

  toolBar->move(toolBarX, toolBarY);
  toolBar->resize(toolBarW, toolBarH);
}

/*****************************************************************************!
 * Function : SlotCollapseButtonPushed
 *****************************************************************************/
void
BuildTreeContainer::SlotCollapseButtonPushed(void)
{
  emit SignalCollapseTree();
  if ( buildTree->GetExpanded() ) {
    CollapseButton->setText("CO");
    return;
  }
  CollapseButton->setText("EX");
}

/*****************************************************************************!
 * Function : SlotChangedItemsButtonPushed
 *****************************************************************************/
void
BuildTreeContainer::SlotChangedItemsButtonPushed(void)
{
  emit SignalChangedItemsDisplay();
  if ( buildTree->GetDisplayAllItems() ) {
    ChangedItemsButton->setText("CH");
    return;
  }
  ChangedItemsButton->setText("ALL");
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BuildTreeContainer::CreateConnections(void)
{
  connect(this, BuildTreeContainer::SignalCollapseTree, buildTree, BuildTree::SlotToggleTreeView);
  connect(this, BuildTreeContainer::SignalChangedItemsDisplay, buildTree, BuildTree::SlotToggleChangedItems);
}
