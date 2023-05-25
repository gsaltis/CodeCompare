/*****************************************************************************
 * FILE NAME    : BuildTreeItemSection.cpp
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
#include "BuildTreeItemSection.h"

/*****************************************************************************!
 * Function : BuildTreeItemSection
 *****************************************************************************/
BuildTreeItemSection::BuildTreeItemSection
(QString InName) : BuildTreeItem()
{
  setText(0, InName);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTreeItemSection
 *****************************************************************************/
BuildTreeItemSection::~BuildTreeItemSection
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeItemSection::initialize()
{
  type = Section;
}

/*****************************************************************************!
 * Function : ElementExists
 *****************************************************************************/
bool
BuildTreeItemSection::ElementExists
(QString InName)
{
  int                                   i, n;
  BuildTreeItem*                        item;
  
  n = childCount();

  for (i = 0; i < n; i++) {
    item = (BuildTreeItem*)child(i);
    if ( item->text(0) == InName ) {
      return true;
    }
  }
  return false;
}
