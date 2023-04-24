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
  QChar                                 c2;
  QChar                                 c;
  int                                   start;
  int                                   point;
  QString                               line;
  QString                               startPointString;
  QString                               endPointString;
  int                                   n;
  
  line = InLines[InCurrentLine];
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
      return;
    }
  } while (true);

  startPointString = line.sliced(start, point);
  if ( point >= n ) {
    return;
  }
  startLine = startPointString.toInt();
  endLine = startLine; 
  c2 = line[point];
  if ( c2 == ',' ) {
    point++;
    do {
      c = line[point];
      if ( ! c.isDigit() ) {
        break;
      }
      point++;
      if ( point == n ) {
        return;
      }
    } while (true);
    c2 = line[point];
    endPointString = line.sliced(start, point);
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
      return;
  }
  if ( type == Delete ) {
    return;
  }
  for ( int i = startLine; i <= endLine ; i++ ) {
    changeLines << InLines[InCurrentLine];
    InCurrentLine++;
  }
  if ( InLines[InCurrentLine] == '.' ) {
    InCurrentLine++;
  }
  return;
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
  return endLine - startLine + 1;
}
