/*****************************************************************************
 * FILE NAME    : BuildTree.cpp
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
#include "BuildTree.h"
#include "BuildTreeItem.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildTree
 *****************************************************************************/
BuildTree::BuildTree
(QString InFilePath1, QString InFilePath2) : CommonFileTree(InFilePath1, InFilePath2)
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setColumnCount(2);
  
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTree
 *****************************************************************************/
BuildTree::~BuildTree
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTree::initialize()
{
  expanded = false;
  displayAllItems = true;
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTree::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTree::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTree::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : SlotToggleTreeView
 *****************************************************************************/
void
BuildTree::SlotToggleTreeView(void)
{
  int                                   i;
  int                                   n;

  n = topLevelItemCount();
  if ( expanded ) {
    expanded = false;
    for (i = 0; i < n; i++) {
      BuildTreeItem*                    item;
      item = (BuildTreeItem*)topLevelItem(i);
      item->CollapseChildren();
    }
    return;
  }
  for (i = 0; i < n; i++) {
    BuildTreeItem*                    item;
    item = (BuildTreeItem*)topLevelItem(i);
    item->ExpandChildren();
  }
  expanded = true;
}

/*****************************************************************************!
 * Function : SlotToggleChangedItems
 *****************************************************************************/
void
BuildTree::SlotToggleChangedItems
()
{
  if ( displayAllItems ) {
    displayAllItems = false;
    return;
  }

  displayAllItems = true;
}

