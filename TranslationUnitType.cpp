/*****************************************************************************
 * FILE NAME    : TranslationUnitType.cpp
 * DATE         : May 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
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
#include "TranslationUnitType.h"
#include "trace.h"

/*****************************************************************************!
 * Function : TranslationUnitType
 *****************************************************************************/
TranslationUnitType::TranslationUnitType
(QString InName, int InLineStart, int InLineEnd) : QWidget()
{
  name = InName;
  lineStart = InLineStart;
  lineEnd = InLineEnd;
  type = None;
}

/*****************************************************************************!
 * Function : ~TranslationUnitType
 *****************************************************************************/
TranslationUnitType::~TranslationUnitType
()
{
}

/*****************************************************************************!
 * Function : GetName
 *****************************************************************************/
QString
TranslationUnitType::GetName
()
{
  return name;
}

/*****************************************************************************!
 * Function : HasChangeLines
 *****************************************************************************/
bool
TranslationUnitType::HasTargetChangeLines
(FileContentsDiff* InDiffs)
{
  int                                   a, b;

  for ( int i = 0 ; i < InDiffs->count(); i++ ) {
    FileSectionDiff f = InDiffs->at(i);
    a = f.GetTargetStartLine();
    b = f.GetTargetEndLine();

    if ( a < lineStart ) {
      continue;
    }
    if ( b < lineStart ) {
      continue;
    }

    if ( a > lineEnd ) {
      continue;
    }

    if ( b > lineEnd ) {
      continue;
    }
    return true;
  }
  return false;
}

/*****************************************************************************!
 * Function : GetLineStart
 *****************************************************************************/
int
TranslationUnitType::GetLineStart(void)
{
  return lineStart;
}

/*****************************************************************************!
 * Function : GetLineEnd
 *****************************************************************************/
int
TranslationUnitType::GetLineEnd(void)
{
  return lineEnd;
}
