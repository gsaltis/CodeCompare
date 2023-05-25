/*****************************************************************************
 * FILE NAME    : BuildForLine.cpp
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
#include "BuildForLine.h"

/*****************************************************************************!
 * Function : BuildForLine
 *****************************************************************************/
BuildForLine::BuildForLine
() : BuildLine()
{
  buildType = TypeFor;
}

/*****************************************************************************!
 * Function : ~BuildForLine
 *****************************************************************************/
BuildForLine::~BuildForLine
()
{
}

/*****************************************************************************!
 * Function : ParseLine
 *****************************************************************************/
void
BuildForLine::ParseLine
(QString InBuildForLine)
{
  QStringList                           elements;
  int                                   n, m;
  QString                               s;
  QString                               st;
  
  lineText = QString(InBuildForLine);
  elements = InBuildForLine.split(QRegularExpression("\\s+|\n"));
  n = elements.count();

  if ( n < 4 ) {
    return;
  }
  if ( elements[0] != QString("for") || elements[2] != QString("in") ) {
    return;
  }
  action = QString(elements[0]);

  for ( int i = 3; i < n ; i++ ) {
    s = elements[i];
    if ( s == QString(";") ) {
      break;
    }
    st = s.last(1);
    if ( st == QString(";") ) {
      m = s.length();
      s = s.sliced(m-1);
      targets << s;
      break;
    }
    targets << s;
  }
}

/*****************************************************************************!
 * Function : GetTarget
 *****************************************************************************/
QStringList
BuildForLine::GetTargets(void)
{
  return targets;
}

/*****************************************************************************!
 * Function : GetAction
 *****************************************************************************/
QString
BuildForLine::GetAction(void)
{
  return action;
}
