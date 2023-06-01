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

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTreeItemComponent.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildTreeItemComponent
 *****************************************************************************/
BuildTreeItemComponent::BuildTreeItemComponent
(QString InFullFileName) : BuildTreeItem()
{
  initialize();
  fullFileName = InFullFileName;
  SetChanged();
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
  QFont                                 f = font(0);
  f.setBold(true);
  setFont(0, f);
  setFont(1, f);
  setForeground(0, QBrush(QColor(87, 114, 174)));
  changed = false;
  type = Component;
}

/*****************************************************************************!
 * Function : GetFullFileName
 *****************************************************************************/
QString
BuildTreeItemComponent::GetFullFileName
()
{
  return fullFileName;
}

/*****************************************************************************!
 * Function : SetChanged
 *****************************************************************************/
void
BuildTreeItemComponent::SetChanged
()
{
  QString                               diffFileName;

  diffFileName = fullFileName + QString(".diff");
  QFileInfo                             file(diffFileName);

  if ( file.exists() ) {
    changed = true;
    setForeground(0, QBrush(QColor(0, 192, 0)));
    setForeground(1, QBrush(QColor(0, 192, 0)));
  }
}

/*****************************************************************************!
 * Function : GetChanged
 *****************************************************************************/
bool
BuildTreeItemComponent::GetChanged
()
{
  return changed;
}
