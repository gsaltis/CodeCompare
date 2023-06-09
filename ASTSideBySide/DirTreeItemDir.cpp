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

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirTreeItemDir.h"
#include "trace.h"

/*****************************************************************************!
 * Function : DirTreeItem
 *****************************************************************************/
DirTreeItemDir::DirTreeItemDir
() : DirTreeItem()
{
  type = Dir;
  changed = false;
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

/*****************************************************************************!
 * Function : FindItem
 *****************************************************************************/
DirTreeItem*
DirTreeItemDir::FindItem
(QString InText)
{
  DirTreeItem*                          item;
  int                                   i, n;

  n = childCount();

  for (i = 0; i < n; i++) {
    item = (DirTreeItem*)child(i);
    if ( item->text(0) == InText) {
      return item;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : GetChanged
 *****************************************************************************/
bool
DirTreeItemDir::GetChanged(void)
{
  
  return changed;
}

/*****************************************************************************!
 * Function : SetChanged
 *****************************************************************************/
void
DirTreeItemDir::SetChanged
(bool InChanged)
{
  changed = InChanged;
}
