/*****************************************************************************
 * FILE NAME    : BuildEchoLine.cpp
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
#include "BuildEchoLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildEchoLine
 *****************************************************************************/
BuildEchoLine::BuildEchoLine
() : BuildLine()
{
  buildType = TypeEcho;
}

/*****************************************************************************!
 * Function : ~BuildEchoLine
 *****************************************************************************/
BuildEchoLine::~BuildEchoLine
()
{
}

/*****************************************************************************!
 * Function : ParseLine
 *****************************************************************************/
void
BuildEchoLine::ParseLine
(QString InBuildEchoLine)
{
  QStringList                           elements;
  
  lineText = QString(InBuildEchoLine);
  echoLine = lineText.remove(QRegularExpression("^echo\\s+"));
  action = QString("echo");
}

/*****************************************************************************!
 * Function : GetEchoLine
 *****************************************************************************/
QString
BuildEchoLine::GetEchoLine(void)
{
  return echoLine;
}

/*****************************************************************************!
 * Function : GetAction
 *****************************************************************************/
QString
BuildEchoLine::GetAction(void)
{
  return action;
}

