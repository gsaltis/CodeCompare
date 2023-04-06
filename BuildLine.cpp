/*****************************************************************************
 * FILE NAME    : BuildLine.cpp
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
#include "BuildLine.h"

/*****************************************************************************!
 * Function : BuildLine
 *****************************************************************************/
BuildLine::BuildLine
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~BuildLine
 *****************************************************************************/
BuildLine::~BuildLine
()
{
}

/*****************************************************************************!
 * Function : ParseLine
 *****************************************************************************/
void
BuildLine::ParseLine
(QString InBuildLine)
{
  QStringList                           elements;
  int                                   n;
  QString                               s;
  QString                               sc;
  QString                               flag;
  QString                               inc;
  QString                               libpath;
  QString                               lib;

  lineText = QString(InBuildLine);
  
  elements = InBuildLine.split(QRegularExpression("\\s+|\n"));
  n = elements.count();

  for ( int i = 0; i < n ; i++ ) {
    if ( i == 0 ) {
      action = QString(elements[i]);
      continue;
    }

    s = elements[i];
    if ( s.isEmpty() ) {
      continue;
    }
    sc = s[0];

    if ( sc == QChar('-') ) {
      flag = s.sliced(0, 2);
      if ( flag == "-I" ) {
        inc = s.sliced(2);
        includePaths << inc;
        continue;
      }
      if ( flag == "-l" ) {
        lib = s.sliced(2);
        libs << lib;
        continue;
      }
      if ( flag == "-L" ) {
        libpath = s.sliced(2);
        libPaths << libpath;
        continue;
      }

      if ( flag == "-o" ) {
        i++;
        target = QString(elements[i]);
        
        continue;
      }

      flags << s;
      continue;
    }
    sources << s;
  }
}

/*****************************************************************************!
 * Function : GetTarget
 *****************************************************************************/
QString
BuildLine::GetTarget(void)
{
  return target;
}

/*****************************************************************************!
 * Function : GetAction
 *****************************************************************************/
QString
BuildLine::GetAction(void)
{
  return action;
}

/*****************************************************************************!
 * Function : GetSources
 *****************************************************************************/
QStringList
BuildLine::GetSources
(void)
{
  return sources;
}

/*****************************************************************************!
 * Function : GetIncludePaths
 *****************************************************************************/
QStringList
BuildLine::GetIncludePaths
(void)
{
  return includePaths;
}

/*****************************************************************************!
 * Function : GetLibraries
 *****************************************************************************/
QStringList
BuildLine::GetLibraries
(void)
{
  return libs;
}

/*****************************************************************************!
 * Function : GetLibraryPaths
 *****************************************************************************/
QStringList
BuildLine::GetLibraryPaths
(void)
{
  return libPaths;
}

/*****************************************************************************!
 * Function : GetFlags
 *****************************************************************************/
QStringList
BuildLine::GetFlags
(void)
{
  return flags;
}

/*****************************************************************************!
 * Function : GetText
 *****************************************************************************/
QString
BuildLine::GetText
(void)
{
  return QString(lineText);
}
