/*****************************************************************************
 * FILE NAME    : BuildElementSet.cpp
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
#include "BuildElementSet.h"

/*****************************************************************************!
 * Function : BuildElementSet
 *****************************************************************************/
BuildElementSet::BuildElementSet
(QString InElementName) : QWidget()
{
  target = QString(InElementName);
}

/*****************************************************************************!
 * Function : ~BuildElementSet
 *****************************************************************************/
BuildElementSet::~BuildElementSet
()
{
}

/*****************************************************************************!
 * Function : AddElement
 *****************************************************************************/
void
BuildElementSet::AddElement
(BuildElement* InElement)
{
  if ( NULL == InElement ) {
    return;
  }
  
  elements << InElement;
}

/*****************************************************************************!
 * Function : GetTarget
 *****************************************************************************/
QString
BuildElementSet::GetTarget(void)
{
  
  return target;
}

/*****************************************************************************!
 * Function : SetTarget
 *****************************************************************************/
void
BuildElementSet::SetTarget
(QString InTarget)
{
  
  target = InTarget;
}

/*****************************************************************************!
 * Function : Dump
 *****************************************************************************/
void
BuildElementSet::Dump(int InIndent)
{
  QString                               indentString;
  indentString.fill(' ', InIndent);

  printf("%s%s\n",
         indentString.toStdString().c_str(), 
         target.toStdString().c_str());

  for ( int i = 0 ; i < elements.count() ; i++ ) {
    elements[i]->Dump(InIndent + 2);
  }
}

/*****************************************************************************!
 * Function : IsSourceElement
 *****************************************************************************/
bool
BuildElementSet::IsSourceElement
(QString InName)
{
  for ( int i = 0 ; i < elements.count() ; i++ ) {
    if ( elements[i]->GetName() == InName ) {
      return true;
    }
  }
  return false;
}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildElementSet::SetBuildLine
(BuildLine* InBuildLine)
{
  buildLine = InBuildLine;
}

/*****************************************************************************!
 * Function : GetElementCount
 *****************************************************************************/
int
BuildElementSet::GetElementCount(void)
{
  return elements.count();
}

/*****************************************************************************!
 * Function : GetElementByIndex
 *****************************************************************************/
BuildElement*
BuildElementSet::GetElementByIndex
(int InIndex)
{
  if ( InIndex >= elements.count() ) {
    return NULL;
  }
  return elements[InIndex];
}
