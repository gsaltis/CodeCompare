/*****************************************************************************
 * FILE NAME    : BuildElement.cpp
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
#include "BuildElement.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildElement
 *****************************************************************************/
BuildElement::BuildElement
(QString InName) : QWidget()
{
  name = QString(InName);
  buildLine = NULL;
}

/*****************************************************************************!
 * Function : ~BuildElement
 *****************************************************************************/
BuildElement::~BuildElement
()
{
}

/*****************************************************************************!
 * Function : Dump
 *****************************************************************************/
void
BuildElement::Dump
(int InIndex)
{
  QString                               indentString;
  indentString.fill(' ', InIndex);
  printf("%s%s\n", indentString.toStdString().c_str(), name.toStdString().c_str());
}

/*****************************************************************************!
 * Function : GetName
 *****************************************************************************/
QString
BuildElement::GetName
()
{
  return name;
}

/*****************************************************************************!
 * Function : GetBuildLine
 *****************************************************************************/
BuildLine*
BuildElement::GetBuildLine(void)
{
  return buildLine;  
}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildElement::SetBuildLine
(BuildLine* InBuildLine)
{
  TRACE_FUNCTION_START();
  buildLine = InBuildLine;
  TRACE_FUNCTION_END();
}
