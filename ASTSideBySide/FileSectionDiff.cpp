 /*****************************************************************************
 * FILE NAME    : FileSectionDiff.cpp
 * DATE         : April 22 2023
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
#include "FileSectionDiff.h"
#include "trace.h"

/*****************************************************************************!
 * Function : FileSectionDiff
 *****************************************************************************/
FileSectionDiff::FileSectionDiff
(QStringList InLines, int &InCurrentLine)
{
  type = None;
  ParseLine(InLines, InCurrentLine);
}

/*****************************************************************************!
 * Function : ~FileSectionDiff
 *****************************************************************************/
FileSectionDiff::~FileSectionDiff
()
{
}

/*****************************************************************************!
 * Function : ParseLine
 *****************************************************************************/
void
FileSectionDiff::ParseLine
(QStringList InLines, int &InCurrentLine)
{
  QString                               line;
  QStringList                           s;
  int                                   n1;
  QString                               command;
  int                                   first1, last1, first2, last2;
  int                                   lineCount1, lineCount2;
  QStringList                           leftRangeLine, rightRangeLine;

  line = InLines[InCurrentLine];
  line = line.trimmed();
  s = line.split(QRegularExpression("[a-z]"));
  n1 = s[0].length();
  command = line.sliced(n1, 1);
  first1 = last1 = first2 = last2 = lineCount1 = lineCount2 = 0;

  //!
  if ( command == "a" ) {
    first1 = last1 = s[0].toInt();
    rightRangeLine = s[1].split(",");
    last2 = first2 = rightRangeLine[0].toInt();
    if ( rightRangeLine.length() == 2 ) {
      last2 = rightRangeLine[1].toInt();
    }
    lineCount2 = (last2 - first2) + 1;
  }

  //!
  if ( command == "d" ) {
    leftRangeLine = s[0].split(",");
    last1 = first1 = leftRangeLine[0].toInt();
    if ( leftRangeLine.length() == 2 ) {
      last1 = leftRangeLine[1].toInt();
    }
    lineCount1 = (last1 - first1) + 1;
    first2 = last2 = s[1].toInt();
  }

  //!
  if ( command == "c" ) {
    leftRangeLine = s[0].split(",");
    last1 = first1 = leftRangeLine[0].toInt();
    if ( leftRangeLine.length() == 2 ) {
      last1 = leftRangeLine[1].toInt();
    }
    lineCount1 = (last1 - first1) + 1;

    rightRangeLine = s[1].split(",");
    last2 = first2 = rightRangeLine[0].toInt();
    if ( rightRangeLine.length() == 2 ) {
      last2 = rightRangeLine[1].toInt();
    }
    lineCount2 = (last2 - first2) + 1;    
  }

  sourceStartLine = first1;
  sourceEndLine = last1;
  targetStartLine = first2;
  targetEndLine = last2;
  
  InCurrentLine++;
  if ( command == "c" ) {
    type = Change;
    for ( int i = 0; i < lineCount1; i++ ) {
      line = InLines[InCurrentLine];
      line = line.trimmed();
      sourceChangeLines << line;
      InCurrentLine++;
    }
    line = InLines[InCurrentLine];
    line = line.trimmed();
    InCurrentLine++;
    for ( int i = 0; i < lineCount2; i++ ) {
      line = InLines[InCurrentLine];
      line = line.trimmed();
      targetChangeLines << line;
      InCurrentLine++;
    }
    return;
  }
  if ( command == "d" ) {
    type = Delete;
    for ( int i = 0; i < lineCount1; i++ ) {
      line = InLines[InCurrentLine];
      line = line.trimmed();
      sourceChangeLines << line;
      InCurrentLine++;
    }
    return;
  }
  if ( command == "a" ) {
    type = Delete;
    for ( int i = 0; i < lineCount2; i++ ) {
      line = InLines[InCurrentLine];
      line = line.trimmed();
      targetChangeLines << line;
      InCurrentLine++;
    }
    return;
  }
}

/*****************************************************************************!
 * Function : FileSectionDiff
 *****************************************************************************/
FileSectionDiff::FileSectionDiff
(FileSectionDiff* InDiff)
{
  sourceStartLine       = InDiff->GetStartLine();
  sourceEndLine         = InDiff->GetEndLine();
  targetStartLine       = InDiff->GetTargetStartLine();
  targetEndLine         = InDiff->GetTargetEndLine();
  type                  = InDiff->GetType();
  sourceChangeLines     = InDiff->GetSourceChangeLines();
  targetChangeLines     = InDiff->GetTargetChangeLines();
}
  
/*****************************************************************************!
 * Function : GetType
 *****************************************************************************/
FileSectionDiff::Type
FileSectionDiff::GetType
()
{
  return type;
}

/*****************************************************************************!
 * Function : GetTypeString
 *****************************************************************************/
QString
FileSectionDiff::GetTypeString
()
{
  switch (type) {
    case None : {
      return "None";
    }
    case Change : {
      return "Change";
    }
    case Delete : {
      return "Delete";
    }
    case Add : {
      return "Add";
    }
  }
  return "Unknown";
}

/*****************************************************************************!
 * Function : GetLinesChangedCount
 *****************************************************************************/
int
FileSectionDiff::GetLinesChangedCount
()
{
  return sourceEndLine - sourceStartLine + 1;
}

/*****************************************************************************!
 * Function : GetStartLine 
 *****************************************************************************/
int
FileSectionDiff::GetStartLine
()
{
  return sourceStartLine;
}

/*****************************************************************************!
 * Function : GetEndLine 
 *****************************************************************************/
int
FileSectionDiff::GetEndLine
()
{
  return sourceEndLine;
}

/*****************************************************************************!
 * Function : GetTargetLinesChangedCount
 *****************************************************************************/
int
FileSectionDiff::GetTargetLinesChangedCount
()
{
  return targetEndLine - targetStartLine + 1;
}

/*****************************************************************************!
 * Function : GetTargetStartLine 
 *****************************************************************************/
int
FileSectionDiff::GetTargetStartLine
()
{
  return targetStartLine;
}

/*****************************************************************************!
 * Function : GetTargetEndLine 
 *****************************************************************************/
int
FileSectionDiff::GetTargetEndLine
()
{
  return targetEndLine;
}

/*****************************************************************************!
 * Function : GetSourceChangeLines
 *****************************************************************************/
QStringList
FileSectionDiff::GetSourceChangeLines
()
{
  return sourceChangeLines;
}

/*****************************************************************************!
 * Function : GetTargetChangeLines
 *****************************************************************************/
QStringList
FileSectionDiff::GetTargetChangeLines
()
{
  return targetChangeLines;
}

