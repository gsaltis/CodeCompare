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
#include <QProcess>
#include <stdio.h>
#include <sys/stat.h>

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildCompileLine.h"
#include "main.h"
#include "trace.h"
#include "JSONAST.h"
#include "FileTreeFile.h"

/*****************************************************************************!
 * Function : BuildCompileLine
 *****************************************************************************/
BuildCompileLine::BuildCompileLine
(QString InFullFilePath) : BuildLine()
{
  buildType = TypeCompile;
  fullFilePath = InFullFilePath;
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
  QString                               st;
  QString                               st2;
  QString                               st3;
  QString                               st4;
  QDir                                  d;
  CompileSourceLine*                    sourceLine;
  
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
    st = fullFilePath + "/" + s;
    st2 = d.toNativeSeparators(st);
    QFileInfo                   fileInfo(st2);
    st3 = fileInfo.canonicalFilePath();
    st4 = d.toNativeSeparators(st3);
    sourceFullFilenames << st4;

    sourceLine = new CompileSourceLine();
    sourceLine->Set(s, st4);
    sources << sourceLine;
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
QList<CompileSourceLine*>
BuildCompileLine::GetSources
(void)
{
  return sources;
}

/*****************************************************************************!
 * Function : GetSourceFullFilenames
 *****************************************************************************/
QStringList
BuildCompileLine::GetSourceFullFilenames
(void)
{
  return sourceFullFilenames;
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

/*****************************************************************************!
 * Function : Dump
 *****************************************************************************/
void
BuildCompileLine::Dump(void)
{
  printf("%7s(%2d) %s %s ",
         BuildLine::GetTypeString(buildType).toStdString().c_str(),
         buildType,
         filePath.toStdString().c_str(),
         target.toStdString().c_str());
  for ( int i = 0 ; i < sources.count(); i++ ) {
    QDir                d;
    QString             st = d.toNativeSeparators(filePath + QString("/") + sources[i]->GetSourceFileName());
    QFileInfo           f(st);
    printf(" %s", f.canonicalFilePath().toStdString().c_str());
  }
  printf("\n");
}

/*****************************************************************************!
 * Function : GetIsTargetObject
 *****************************************************************************/
bool
BuildCompileLine::GetIsTargetObject
(void)
{
  if ( target.endsWith(".o") ) {
    return true;
  }
  return false;
}

/*****************************************************************************!
 * Function : GetFullFilePath
 *****************************************************************************/
QString
BuildCompileLine::GetFullFilePath(void)
{
  return fullFilePath;  
}

/*****************************************************************************!
 * Function : SetFullFilePath
 *****************************************************************************/
void
BuildCompileLine::SetFullFilePath
(QString InFullFilePath)
{
  fullFilePath = InFullFilePath;  
}

/*****************************************************************************!
 * Function : GetFullFileName
 *****************************************************************************/
QString
BuildCompileLine::GetFullFileName
()
{
  QString                               fullFileName;
  QDir                                  d;
  
  fullFileName =  sources[0]->GetFullSourceFileName();
  return d.toNativeSeparators(fullFileName);
}
