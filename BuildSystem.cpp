/*****************************************************************************
 * FILE NAME    : BuildSystem.cpp
 * DATE         : April 10 2023
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
#include "BuildSystem.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildSystem
 *****************************************************************************/
BuildSystem::BuildSystem
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~BuildSystem
 *****************************************************************************/
BuildSystem::~BuildSystem
()
{
}

/*****************************************************************************!
 * Function : BuildElementSetAdd
 *****************************************************************************/
void
BuildSystem::BuildElementSetAdd
(BuildElementSet* InSet)
{
  if ( NULL == InSet ) {
    return;
  }

  targets << InSet;
}

/*****************************************************************************!
 * Function : Dump
 *****************************************************************************/
void
BuildSystem::Dump
()
{
  for ( int i = 0 ; i < targets.count(); i++ ) {
    targets[i]->Dump(0);
  }
}

/*****************************************************************************!
 * Function : GetTopLevelElements
 *****************************************************************************/
void
BuildSystem::GetTopLevelElements(void)
{
  QString                               targetName;
  for ( int i = 0 ; i < targets.count(); i++ ) {
    targetName = targets[i]->GetTarget();

    if ( ! IsSourceElement(targetName) ) {
      printf("%s\n", targetName.toStdString().c_str());
    }
  }
}

/*****************************************************************************!
 * Function : IsSourceElement
 *****************************************************************************/
bool
BuildSystem::IsSourceElement
(QString InName)
{
  for ( int i =  0 ; i < targets.count(); i++ ) {
    if ( targets[i]->IsSourceElement(InName) ) {
      return true;
    }
  }
  return false;
}

/*****************************************************************************!
 * Function : GetCount
 *****************************************************************************/
int
BuildSystem::GetCount(void)
{
  return targets.count();
}

/*****************************************************************************!
 * Function : GetTopLevelNames
 *****************************************************************************/
QStringList
BuildSystem::GetTopLevelNames(void)
{
  QStringList                           returnNames;
  QString                               targetName;
  int                                   i, n;

  n = targets.count();
  for (i = 0; i < n; i++) {
    targetName = targets[i]->GetTarget();
    if ( IsSourceElement(targetName) ) {
      continue;
    }
    returnNames << targetName;
  }
  return returnNames;
}

/*****************************************************************************!
 * Function : GetBuildElementByName
 *****************************************************************************/
BuildElementSet*
BuildSystem::GetBuildElementByName
(QString InName)
{
  BuildElementSet*                      set;
  int                                   i, n;

  n = targets.count();

  for (i = 0; i < n; i++) {
    set = targets[i];
    if ( set->GetTarget() == InName ) {
      return set;
    }
  }
  return NULL;
}
