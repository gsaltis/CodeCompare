/*****************************************************************************
 * FILE NAME    : BuildRanlibLine.cpp
 * DATE         : April 03 2023
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
#include "BuildRanlibLine.h"

/*****************************************************************************!
 * Function : BuildRanlibLine
 *****************************************************************************/
BuildRanlibLine::BuildRanlibLine
() : BuildLine()
{
  buildType = TypeRanlib;
}

/*****************************************************************************!
 * Function : ~BuildRanlibLine
 *****************************************************************************/
BuildRanlibLine::~BuildRanlibLine
()
{
}

/*****************************************************************************!
 * Function : ParseLine
 *****************************************************************************/
void
BuildRanlibLine::ParseLine
(QString InBuildRanlibLine)
{
  QStringList                           elements;
  int                                   n;
  QString                               s;
  
  lineText = QString(InBuildRanlibLine);
  elements = InBuildRanlibLine.split(QRegularExpression("\\s+|\n"));
  n = elements.count();
  if ( n < 2 ) {
    return;
  }
  action = QString(elements[0]);
  target = QString(elements[1]);
}

/*****************************************************************************!
 * Function : GetTarget
 *****************************************************************************/
QString
BuildRanlibLine::GetTarget(void)
{
  return target;
}

/*****************************************************************************!
 * Function : GetAction
 *****************************************************************************/
QString
BuildRanlibLine::GetAction(void)
{
  return action;
}

