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
  hasChanged = false;
}

/*****************************************************************************!
 * Function : TranslationUnitType
 *****************************************************************************/
TranslationUnitType::TranslationUnitType
(TranslationUnitType::Type InType, QString InName, int InLineStart, int InLineEnd) : QWidget()
{
  name = InName;
  lineStart = InLineStart;
  lineEnd = InLineEnd;
  type = InType;
  hasChanged = false;
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

/*****************************************************************************!
 * Function : Write
 *****************************************************************************/
void
TranslationUnitType::Write
(QFile *InFile, bool InLastItem)
{
  QString                               st;

  st =
    QString("  { \"name\" : \"%1\", \"type\" : %2, \"linestart\" : %3, \"lineend\" : %4, \"changed\" : %5 }").
    arg(name).
    arg(type).
    arg(lineStart).
    arg(lineEnd).
    arg(hasChanged ? "true" : "false");

  if ( !InLastItem ) {
    st += QString(",");
  }
  st += QString("\n");
  InFile->write(st.toLatin1());
}

/*****************************************************************************!
 * Function : GetHasChanged
 *****************************************************************************/
bool
TranslationUnitType::GetHasChanged(void)
{
  return hasChanged;  
}

/*****************************************************************************!
 * Function : SetHasChanged
 *****************************************************************************/
void
TranslationUnitType::SetHasChanged
(bool InHasChanged)
{
  hasChanged = InHasChanged;  
}

/*****************************************************************************!
 * Function : KindToTUType
 *****************************************************************************/
TranslationUnitType::Type
TranslationUnitType::KindToTUType
(QString InKind)
{
  if ( InKind == "VarDecl" ) {
    return TranslationUnitType::Variable;
  }
  if ( InKind == "RecordDecl" ) {
    return TranslationUnitType::Record;
  }
  if ( InKind == "TypedefDecl" ) {
    return TranslationUnitType::TypeDef;
  }
  if ( InKind == "FunctionDecl" ) {
    return TranslationUnitType::Function;
  }
  return TranslationUnitType::None;
}
