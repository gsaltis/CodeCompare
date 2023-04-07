/*****************************************************************************
 * FILE NAME    : BuildCompileLine.cpp
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
#include "BuildCompileLine.h"

/*****************************************************************************!
 * Function : BuildCompileLine
 *****************************************************************************/
BuildCompileLine::BuildCompileLine
() : BuildLine()
{
  buildType = TypeCompile;
}

/*****************************************************************************!
 * Function : ~BuildCompileLine
 *****************************************************************************/
BuildCompileLine::~BuildCompileLine
()
{
}

/*****************************************************************************!
 * Function : ParseLine
 *****************************************************************************/
void
BuildCompileLine::ParseLine
(QString InBuildCompileLine)
{
  QStringList                           elements;
  int                                   n;
  QString                               s;
  QString                               sc;
  QString                               flag;
  QString                               inc;
  QString                               libpath;
  QString                               lib;

  lineText = QString(InBuildCompileLine);
  
  elements = InBuildCompileLine.split(QRegularExpression("\\s+|\n"));
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
BuildCompileLine::GetTarget(void)
{
  return target;
}

/*****************************************************************************!
 * Function : GetAction
 *****************************************************************************/
QString
BuildCompileLine::GetAction(void)
{
  return action;
}

/*****************************************************************************!
 * Function : GetSources
 *****************************************************************************/
QStringList
BuildCompileLine::GetSources
(void)
{
  return sources;
}

/*****************************************************************************!
 * Function : GetIncludePaths
 *****************************************************************************/
QStringList
BuildCompileLine::GetIncludePaths
(void)
{
  return includePaths;
}

/*****************************************************************************!
 * Function : GetLibraries
 *****************************************************************************/
QStringList
BuildCompileLine::GetLibraries
(void)
{
  return libs;
}

/*****************************************************************************!
 * Function : GetLibraryPaths
 *****************************************************************************/
QStringList
BuildCompileLine::GetLibraryPaths
(void)
{
  return libPaths;
}

/*****************************************************************************!
 * Function : GetFlags
 *****************************************************************************/
QStringList
BuildCompileLine::GetFlags
(void)
{
  return flags;
}

