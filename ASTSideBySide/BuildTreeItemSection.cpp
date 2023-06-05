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
#include "BuildTreeItemSubSection.h"
#include "BuildTreeItemComponent.h"

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
    if ( item->GetType() == BuildTreeItem::SubSection ) {
      BuildTreeItemSubSection*          subSection = (BuildTreeItemSubSection*)item;
      if ( subSection->ElementExists(InName) ) {
        return true;
      }
      continue;
    }
    if ( item->text(0) == InName ) {
      return true;
    }
  }
  return false;
}

/*****************************************************************************!
 * Function : AnyChanged
 *****************************************************************************/
bool
BuildTreeItemSection::AnyChanged
()
{
  int                                   i, n;
  BuildTreeItem*                        item;
  BuildTreeItem::Type                   type;
  BuildTreeItemComponent*               componentItem;

  n = childCount();
  for (i = 0; i < n; i++) {
    item = (BuildTreeItem*)child(i);
    type = item->GetType();
    if ( type != BuildTreeItem::Type::Component ) {
      continue;
    }
    componentItem = (BuildTreeItemComponent*)item;
    if ( componentItem->GetChanged() ) {
      return true;
    }
  }
  return false;
}

