/*****************************************************************************
 * FILE NAME    : BuildTreeItemSubSection.cpp
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
#include "BuildTreeItemSubSection.h"

/*****************************************************************************!
 * Function : BuildTreeItemSubSection
 *****************************************************************************/
BuildTreeItemSubSection::BuildTreeItemSubSection
(QString InName) : BuildTreeItem()
{
  setText(0, InName);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTreeItemSubSection
 *****************************************************************************/
BuildTreeItemSubSection::~BuildTreeItemSubSection
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeItemSubSection::initialize()
{
  type = SubSection;
}

/*****************************************************************************!
 * Function : ElementExists
 *****************************************************************************/
bool
BuildTreeItemSubSection::ElementExists
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
