/*****************************************************************************
 * FILE NAME    : BuildLine.cpp
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
#include "BuildLine.h"

/*****************************************************************************!
 * Function : BuildLine
 *****************************************************************************/
BuildLine::BuildLine
() : QWidget()
{
  buildType = TypeNone;
}

/*****************************************************************************!
 * Function : ~BuildLine
 *****************************************************************************/
BuildLine::~BuildLine
()
{
}

/*****************************************************************************!
 * Function : GetType
 *****************************************************************************/
BuildLine::Type
BuildLine::GetType
()
{
  return buildType;
}
  
/*****************************************************************************!
 * Function : GetText
 *****************************************************************************/
QString
BuildLine::GetText
(void)
{
  return QString(lineText);
}

/*****************************************************************************!
 * Function : GetLineElements
 *****************************************************************************/
QStringList
BuildLine::GetLineElements
(QString InBuildLine)
{
  QStringList                           elements;

  elements = InBuildLine.split(QRegularExpression("\\s+|\n"));
  return elements;
}