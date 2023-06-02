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

  statusBar = new QFrame(this);
  statusBar->setFrameShadow(QFrame::Sunken);
  statusBar->setFrameStyle(QFrame::Panel);
  statusBar->setStyleSheet("QFrame { border : 1px solid #CCC}");

  FilesCountLabel = new QLabel(statusBar);
  FilesCountLabel->move(5, 1);
  FilesCountLabel->resize(60, 18);
  FilesCountLabel->setText(QString("%1 / %2").arg(0).arg(0));
  FilesCountLabel->setStyleSheet("QLabel { border : 0px solid #00000000}");
    
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

  ShowChangedLinesButton = new QPushButton();
  ShowChangedLinesButton->setParent(toolBar);
  ShowChangedLinesButton->setText("LI");
  ShowChangedLinesButton->move(65, 1);
  ShowChangedLinesButton->resize(30,30);
  connect(ShowChangedLinesButton, SIGNAL(pressed()), this, SLOT(SlotShowChangedLinesButtonPushed()));
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
  int                                   statusBarW, statusBarH, statusBarX, statusBarY;
  int                                   FilesCountLabelW, FilesCountLabelH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  toolBarH = 32;
  statusBarH = 20;
  buildTreeH = height - (toolBarH + statusBarH);
  
  buildTreeX = 0;
  buildTreeY = 0;
  buildTreeW = width;

  toolBarX = 0;
  toolBarW = width;
  toolBarY = height - toolBarH;
  
  statusBarX = 0;
  statusBarW = width;
  statusBarY = height - (toolBarH + statusBarH);

  FilesCountLabelW = width - 10;
  FilesCountLabelH = 18;

  FilesCountLabel->resize(FilesCountLabelW, FilesCountLabelH);
  
  buildTree->move(buildTreeX, buildTreeY);
  buildTree->resize(buildTreeW, buildTreeH);

  toolBar->move(toolBarX, toolBarY);
  toolBar->resize(toolBarW, toolBarH);

  statusBar->move(statusBarX, statusBarY);
  statusBar->resize(statusBarW, statusBarH);
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
 * Function : SlotShowChangedLinesButtonPushed
 *****************************************************************************/
void
BuildTreeContainer::SlotShowChangedLinesButtonPushed
(void)
{

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

/*****************************************************************************!
 * Function : SlotSetFileCounts
 *****************************************************************************/
void
BuildTreeContainer::SlotSetFileCounts
(int InTotalFiles, int InChangedFiles)
{
  FilesCountLabel->setText(QString("Files : Total:%1 | Changed:%2").arg(InTotalFiles).arg(InChangedFiles));
}
