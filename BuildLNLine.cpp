/*****************************************************************************
 * FILE NAME    : BuildLNLine.cpp
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
#include "BuildLNLine.h"

/*****************************************************************************!
 * Function : BuildLNLine
 *****************************************************************************/
BuildLNLine::BuildLNLine
() : BuildLine()
{
  buildType = TypeLN;
}

/*****************************************************************************!
 * Function : ~BuildLNLine
 *****************************************************************************/
BuildLNLine::~BuildLNLine
()
{
}

/*****************************************************************************!
 * Function : ParseLine
 *****************************************************************************/
void
BuildLNLine::ParseLine
(QString InBuildLNLine)
{
  QStringList                           elements;
  int                                   n;
  bool                                  haveTarget = false;
  QString                               s;
  QChar                                 sc;
  
  lineText = QString(InBuildLNLine);
  elements = InBuildLNLine.split(QRegularExpression("\\s+|\n"));
  n = elements.count();
  
  for ( int i = 0; i < n ; i++ ) {
    if ( i == 0 ) {
      action = QString(elements[i]);
      continue;
    }

    s = elements[i];
    if ( s.isEmpty() ) {
      continue;
    }
    sc = s[0];

    if ( sc == QChar('-') ) {
      flags << QString(s);
      continue;
    }
    if ( ! haveTarget ) {
      target = QString(s);
      haveTarget = true;
      continue;
    }
    linkName = QString(s);
  }
}

/*****************************************************************************!
 * Function : GetTarget
 *****************************************************************************/
QString
BuildLNLine::GetTarget(void)
{
  return target;
}

/*****************************************************************************!
 * Function : GetAction
 *****************************************************************************/
QString
BuildLNLine::GetAction(void)
{
  return action;
}

/*****************************************************************************!
 * Function : GetLinkName
 *****************************************************************************/
QString
BuildLNLine::GetLinkName
(void)
{
  return linkName;
}

/*****************************************************************************!
 * Function : GetFlags
 *****************************************************************************/
QStringList
BuildLNLine::GetFlags
(void)
{
  return flags;
}

