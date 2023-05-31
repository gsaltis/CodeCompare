/*****************************************************************************
 * FILE NAME    : BuildTreeItem.cpp
 * DATE         : May 24 2023
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
#include "BuildTreeItem.h"

/*****************************************************************************!
 * Function : BuildTreeItem
 *****************************************************************************/
BuildTreeItem::BuildTreeItem
() : QTreeWidgetItem()
{
}

/*****************************************************************************!
 * Function : ~BuildTreeItem
 *****************************************************************************/
BuildTreeItem::~BuildTreeItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeItem::initialize()
{
  type = None;
}

/*****************************************************************************!
 * Function : GetType
 *****************************************************************************/
BuildTreeItem::Type
BuildTreeItem::GetType
()
{
  return type;
}

/*****************************************************************************!
 * Function : Contains
 *****************************************************************************/
bool
BuildTreeItem::Contains
(QString InName)
{
  QTreeWidgetItem*                      item;
  int                                   i, n;

  n = childCount();

  for (i = 0; i < n; i++) {
    item = child(i);
    if ( item->text(0) == InName ) {
      return true;
    }
  }
  return false;
}

/*****************************************************************************!
 * Function : CollapseChildren
 *****************************************************************************/
void
BuildTreeItem::CollapseChildren(void)
{
  int                                   n = childCount();

  for ( int i = 0; i < n; i++) {
    BuildTreeItem*                      item = (BuildTreeItem*)child(i);
    BuildTreeItem* buildItem = (BuildTreeItem*)item;
    buildItem->CollapseChildren();
  }
  treeWidget()->collapseItem(this);
}

/*****************************************************************************!
 * Function : ExpandChildren
 *****************************************************************************/
void
BuildTreeItem::ExpandChildren(void)
{
  int                                   n = childCount();

  for ( int i = 0; i < n; i++) {
    BuildTreeItem*                        item = (BuildTreeItem*)child(i);
    BuildTreeItem* buildItem = (BuildTreeItem*)item;
    buildItem->ExpandChildren();
  }
  treeWidget()->expandItem(this);
}

