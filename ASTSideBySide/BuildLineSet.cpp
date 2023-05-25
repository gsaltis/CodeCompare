/*****************************************************************************
 * FILE NAME    : BuildLineSet.cpp
 * DATE         : April 07 2023
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
#include "BuildLineSet.h"
#include "BuildCompileLine.h"
#include "BuildARLine.h"
#include "main.h"

/*****************************************************************************!
 * Function : BuildLineSet
 *****************************************************************************/
BuildLineSet::BuildLineSet
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~BuildLineSet
 *****************************************************************************/
BuildLineSet::~BuildLineSet
()
{
}

/*****************************************************************************!
 * Function : GetLineCount
 *****************************************************************************/
int
BuildLineSet::GetLineCount
()
{
  return lines.count();
}

/*****************************************************************************!
 * Function : GetLineByIndex
 *****************************************************************************/
BuildLine*
BuildLineSet::GetLineByIndex
(int InIndex)
{
  if ( InIndex >= lines.count() ) {
    return NULL;
  }
  return lines[InIndex];
}

/*****************************************************************************!
 * Function : AppendLine
 *****************************************************************************/
void
BuildLineSet::AppendLine
(BuildLine* InLine)
{
  lines << InLine;
}


/*****************************************************************************!
 * Function : Dump
 *****************************************************************************/
void
BuildLineSet::Dump(void)
{
  BuildLine*                            line;

  foreach (line, lines) {
    if ( line->GetType() == BuildLine::TypeCompile ) {
      BuildCompileLine*                 compileLine = (BuildCompileLine*)line;
      if ( compileLine->GetIsTargetObject() ) {
        line->Dump();
      }
    }
  }
}

/*****************************************************************************!
 * Function : GetLineByTargetName
 *****************************************************************************/
BuildLine*
BuildLineSet::GetLineByTargetName
(QString InName)
{
  BuildLine*                            line;
  BuildLine::Type                       lineType;
  
  foreach (line, lines) {
    lineType = line->GetType();
    if ( ! ( lineType == BuildLine::TypeCompile ||
             lineType == BuildLine::TypeAR ) ) {
      continue;
    }

    if ( lineType == BuildLine::TypeCompile ) {
      BuildCompileLine*                 compileLine;
      compileLine = (BuildCompileLine*)line;
      if ( InName == compileLine->GetTarget() ) {
        return line;
      }
    }
    if ( lineType == BuildLine::TypeAR ) {
      BuildARLine*                      arLine;
      arLine = (BuildARLine*)line;
      if ( arLine->GetTarget() == InName ) {
        return line;
      }
    }
  }
  return NULL;
}

#if 0
/*****************************************************************************!
 * Function : BuildAST
 *****************************************************************************/
void
BuildLineSet::BuildAST
(CodeTrack* InCodeTrack)
{
  BuildLine*                            line;
  int                                   i, n;
  n = 0;
  
  foreach (line, lines) {
    if ( line->GetType() == BuildLine::TypeCompile ) {
      BuildCompileLine*                 compileLine = (BuildCompileLine*)line;
      if ( ! compileLine->GetIsTargetObject() ) {
        continue;
      }
      n++;
    }
  }
  i = 1;
  foreach (line, lines) {
    if ( line->GetType() == BuildLine::TypeCompile ) {
      BuildCompileLine*                 compileLine = (BuildCompileLine*)line;
      if ( ! compileLine->GetIsTargetObject() ) {
        continue;
      }
      // printf("%4d of %4d : ", i, n);
      i++;
      compileLine->BuildAST(InCodeTrack);
    }
  }
}
#endif
