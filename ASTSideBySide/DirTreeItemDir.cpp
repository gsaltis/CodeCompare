/*****************************************************************************
 * FILE NAME    : DirTreeItemDir.cpp
 * DATE         : May 12 2023
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
#include "DirTreeItemDir.h"

/*****************************************************************************!
 * Function : DirTreeItem
 *****************************************************************************/
DirTreeItemDir::DirTreeItemDir
() : DirTreeItem()
{
  type = Dir;
  initialize();
}

/*****************************************************************************!
 * Function : ~DirTreeItemDir
 *****************************************************************************/
DirTreeItemDir::~DirTreeItemDir
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
DirTreeItemDir::initialize()
{
  QFont                                 f = font(0);
  f.setBold(true);
  setFont(0, f);
  setFont(1, f);
  setForeground(0, QBrush(QColor(128, 64, 140)));
}

/*****************************************************************************!
 * Function : CollapseChildren
 *****************************************************************************/
void
DirTreeItemDir::CollapseChildren(void)
{
  int                                   n = childCount();

  for ( int i = 0; i < n; i++) {
    DirTreeItem*                        item = (DirTreeItem*)child(i);
    if ( item->GetType() == DirTreeItem::Dir ) {
      DirTreeItemDir* dirItem = (DirTreeItemDir*)item;
      dirItem->CollapseChildren();
    }
  }
  treeWidget()->collapseItem(this);
}

/*****************************************************************************!
 * Function : ExpandChildren
 *****************************************************************************/
void
DirTreeItemDir::ExpandChildren(void)
{
  int                                   n = childCount();

  for ( int i = 0; i < n; i++) {
    DirTreeItem*                        item = (DirTreeItem*)child(i);
    if ( item->GetType() == DirTreeItem::Dir ) {
      DirTreeItemDir* dirItem = (DirTreeItemDir*)item;
      dirItem->ExpandChildren();
    }
  }
  treeWidget()->expandItem(this);
}

