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

#undef TRACE_USE
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

  TRACE_FUNCTION_INT(InLines.count());
  line = InLines[InCurrentLine];
  line = line.trimmed();
  TRACE_FUNCTION_QSTRING(line);
  s = line.split(QRegularExpression("[a-z]"));
  n1 = s[0].length();
  command = line.sliced(n1, 1);
  TRACE_FUNCTION_QSTRING(command);
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
    TRACE_FUNCTION_LOCATION();
    leftRangeLine = s[0].split(",");
    TRACE_FUNCTION_INT(leftRangeLine.length());
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

  TRACE_FUNCTION_QSTRING(command);
  TRACE_FUNCTION_INT(first1);
  TRACE_FUNCTION_INT(last1);
  TRACE_FUNCTION_INT(first2);
  TRACE_FUNCTION_INT(last2);
  TRACE_FUNCTION_INT(lineCount1);
  TRACE_FUNCTION_INT(lineCount2);

  sourceStartLine = first1;
  sourceEndLine = last1;
  sourceLineCount = lineCount1;
  targetStartLine = first2;
  targetEndLine = last2;
  targetLineCount = lineCount2;
  
  InCurrentLine++;
  if ( command == "c" ) {
    type = Change;
    for ( int i = 0; i < lineCount1; i++ ) {
      line = InLines[InCurrentLine];
      line = line.trimmed();
      TRACE_FUNCTION_QSTRING(line);
      sourceChangeLines << line;
      InCurrentLine++;
    }
    line = InLines[InCurrentLine];
    line = line.trimmed();
    InCurrentLine++;
    TRACE_FUNCTION_QSTRING(line);
    TRACE_FUNCTION_INT(InCurrentLine);
    for ( int i = 0; i < lineCount2; i++ ) {
      line = InLines[InCurrentLine];
      line = line.trimmed();
      targetChangeLines << line;
      TRACE_FUNCTION_QSTRING(line);
      InCurrentLine++;
    }
    TRACE_FUNCTION_INT(InCurrentLine);
    return;
  }
  if ( command == "d" ) {
    type = Delete;
    for ( int i = 0; i < lineCount1; i++ ) {
      line = InLines[InCurrentLine];
      line = line.trimmed();
      TRACE_FUNCTION_QSTRING(line);
      sourceChangeLines << line;
      InCurrentLine++;
    }
    TRACE_FUNCTION_INT(InCurrentLine);
    return;
  }
  if ( command == "a" ) {
    type = Delete;
    for ( int i = 0; i < lineCount2; i++ ) {
      line = InLines[InCurrentLine];
      line = line.trimmed();
      TRACE_FUNCTION_QSTRING(line);
      targetChangeLines << line;
      InCurrentLine++;
    }
    TRACE_FUNCTION_INT(InCurrentLine);
    return;
  }
  TRACE_FUNCTION_QSTRING(line);
  exit(0);
#if 0
  QChar                                 c2;
  QChar                                 c;
  int                                   start;
  int                                   point;
  QString                               line;
  QString                               startPointString;
  QString                               endPointString;
  int                                   n;

  
  TRACE_FUNCTION_START();
  TRACE_FUNCTION_INT(InLines.count());
  TRACE_FUNCTION_INT(InCurrentLine);

  line = line.trimmed();
  TRACE_FUNCTION_QSTRING(line);
  InCurrentLine++;
  start = 0;
  point = 0;

  n = line.length();
  do {
    c = line[point];
    if ( ! c.isDigit() ) {
      break;
    }
    point++;
    if ( point == n ) {
      TRACE_FUNCTION_END();
      return;
    }
  } while (true);

  startPointString = line.sliced(start, point - start);
  if ( point >= n ) {
    TRACE_FUNCTION_END();
    return;
  }
  startLine = startPointString.toInt();
  endLine = startLine; 
  c2 = line[point];
  if ( c2 == ',' ) {
    point++;
    start = point;
    
    do {
      c = line[point];
      if ( ! c.isDigit() ) {
        break;
      }
      point++;
      if ( point == n ) {
        break;
      }
    } while (true);
    c2 = line[point];
    endPointString = line.sliced(start, point - start);
    endLine = endPointString.toInt();
  }
  switch (c2.toLatin1()) {
    case 'c' :
      type = Change;
      break;
    case 'd' :
      type = Delete;
      break;
    case 'a' :
      type = Add;
      break;
    default :
      TRACE_FUNCTION_END();
      return;
  }
  if ( type == Delete ) {
    TRACE_FUNCTION_END();
    return;
  }
  TRACE_FUNCTION_INT(startLine);
  TRACE_FUNCTION_INT(endLine);
  TRACE_FUNCTION_INT(InCurrentLine);
  for ( int i = startLine; i <= endLine ; i++ ) {
    TRACE_FUNCTION_QSTRING(InLines[InCurrentLine]);
    changeLines << InLines[InCurrentLine];
    InCurrentLine++;
  }
  if ( InLines[InCurrentLine] == "." ) {
    TRACE_FUNCTION_LOCATION();
    InCurrentLine++;
  }
  TRACE_FUNCTION_INT(InCurrentLine);
  TRACE_FUNCTION_END();
  return;
#endif  
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

