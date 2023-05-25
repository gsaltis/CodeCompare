/*****************************************************************************
 * FILE NAME    : BuildARLine.cpp
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
#include "BuildARLine.h"

/*****************************************************************************!
 * Function : BuildARLine
 *****************************************************************************/
BuildARLine::BuildARLine
() : BuildLine()
{
  buildType = TypeAR;
}

/*****************************************************************************!
 * Function : ~BuildARLine
 *****************************************************************************/
BuildARLine::~BuildARLine
()
{
}

/*****************************************************************************!
 * Function : ParseLine
 *****************************************************************************/
void
BuildARLine::ParseLine
(QString InBuildARLine)
{
  QStringList                           elements;
  int                                   n;
  QString                               s;
  
  lineText = QString(InBuildARLine);
  elements = InBuildARLine.split(QRegularExpression("\\s+|\n"));
  n = elements.count();
  if ( n < 4 ) {
    return;
  }
  action = QString(elements[0]);
  flags = QString(elements[1]);
  target = QString(elements[2]);
    
  for ( int i = 3; i < n ; i++ ) {
    s = elements[i];
    if ( s.isEmpty() ) {
      continue;
    }
    sources << QString(s);
  }
}

/*****************************************************************************!
 * Function : GetTarget
 *****************************************************************************/
QString
BuildARLine::GetTarget(void)
{
  return target;
}

/*****************************************************************************!
 * Function : GetAction
 *****************************************************************************/
QString
BuildARLine::GetAction(void)
{
  return action;
}

/*****************************************************************************!
 * Function : GetSources
 *****************************************************************************/
QStringList
BuildARLine::GetSources(void)
{
  return sources;
}

/*****************************************************************************!
 * Function : GetFlags
 *****************************************************************************/
QString
BuildARLine::GetFlags
(void)
{
  return flags;
}

