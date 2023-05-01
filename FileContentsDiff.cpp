/*****************************************************************************
 * FILE NAME    : FileContentsDiff.cpp
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
#include "FileContentsDiff.h"
#include "trace.h"

/*****************************************************************************!
 * Function : FileContentsDiff
 *****************************************************************************/
FileContentsDiff::FileContentsDiff
() : QList<FileSectionDiff> ()
{
}

/*****************************************************************************!
 * Function : ~FileContentsDiff
 *****************************************************************************/
FileContentsDiff::~FileContentsDiff
()
{
}

/*****************************************************************************!
 * Function : ParseLines
 *****************************************************************************/
void
FileContentsDiff::ParseLines
(QString InDiffString)
{
  QString                               line;
  QStringList                           strings;
  int                                   i;

  if ( InDiffString.isEmpty() ) {
    return;
  }

  strings = InDiffString.split("\r\n");
  strings.removeAll("\\ No newline at end of file");
  i = 0;
  while ( i < strings.count() ) {
    FileSectionDiff                     s(strings, i);
    append(s);
  }
}

/*****************************************************************************!
 * Function : GetCounts
 *****************************************************************************/
QList<int>
FileContentsDiff::GetCounts(void)
{
  int                                   changes;
  int                                   deletes;
  int                                   adds;
  QList<int>                            counts;

  adds = deletes = changes = 0;
  for ( QList<FileSectionDiff>::iterator i = begin();
        i != end();
        i++ ) {
    
    FileSectionDiff::Type               type = (*i).GetType();
    switch (type) {
      case FileSectionDiff::Add : {
        adds++;
        break;
      }
      case FileSectionDiff::Delete : {
        deletes++;
        break;
      }
      case FileSectionDiff::Change : {
        changes++;
        break;
      }
      default :
        break;
    }
  }
  counts << adds << changes << deletes;
  return counts;
}

    
        
      
