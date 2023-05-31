/*****************************************************************************
 * FILE NAME    : BuildTreeItemComponent.cpp
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
#include "BuildTreeItemComponent.h"

/*****************************************************************************!
 * Function : BuildTreeItemComponent
 *****************************************************************************/
BuildTreeItemComponent::BuildTreeItemComponent
(QString InTrackName) : BuildTreeItem()
{
  initialize();
  trackName = InTrackName;
}

/*****************************************************************************!
 * Function : ~BuildTreeItemComponent
 *****************************************************************************/
BuildTreeItemComponent::~BuildTreeItemComponent
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeItemComponent::initialize()
{
  type = Component;
}

/*****************************************************************************!
 * Function : GetTrackName
 *****************************************************************************/
QString
BuildTreeItemComponent::GetTrackName
()
{
  return trackName;
}
