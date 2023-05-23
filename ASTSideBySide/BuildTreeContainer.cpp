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
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeContainer::CreateSubWindows()
{
  
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
  int                                   buildTreeX, buildTreeY;
  int                                   buildTreeW, buildTreeH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  buildTreeX = 0;
  buildTreeY = 0;

  buildTreeW = width;
  buildTreeH = height - 32;

  buildTree->move(buildTreeX, buildTreeY);
  buildTree->resize(buildTreeW, buildTreeH);
}
