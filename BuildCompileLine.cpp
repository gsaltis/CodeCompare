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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildCompileLine.h"
#include "main.h"
#include "trace.h"

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
    QString             st = d.toNativeSeparators(filePath + QString("/") + sources[i]);
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
 * Function : BuildAST
 *****************************************************************************/
void
BuildCompileLine::BuildAST
(CodeTrack* InCodeTrack)
{
  QString                               clangExe;
  QStringList                           clangHeaderOptions;
  QStringList                           clangOptions;
  QStringList                           clangCodeGatherOptions;
  QStringList                           clangIncludePaths;
  QString                               excludeLine;
  QStringList                           excludeLines;
  QDir                                  d;
  QStringList                           lineArgs;
  QStringList                           args;
  QString                               st = d.toNativeSeparators(filePath + QString("/") + sources[0]);
  QFileInfo                             f(st);
  QString                               filename = d.toNativeSeparators(f.canonicalFilePath());
  QProcess                              process;
  QString                               buildPath;
  QString                               jsonFilename;

  buildPath = mainSystemConfig->GetBuildDirectoryName() + QString("/") + InCodeTrack->RemoveLeadingBasePath(filename);
  jsonFilename = QString("%1/AST-%2.json").arg(buildPath).arg(InCodeTrack->GetIndex());

  if ( filename.isEmpty() ) {
    return;
  }
#if 1
  if (! d.exists(jsonFilename) ) {
    clangExe = mainSystemConfig->GetClangExecutable();
    clangOptions = mainSystemConfig->GetClangOptions();
    clangIncludePaths = mainSystemConfig->GetClangIncludePaths();
    clangCodeGatherOptions = mainSystemConfig->GetClangCodeGatherOptions();
    excludeLines = mainSystemConfig->GetClangHeaderExcludePaths();
    
    lineArgs = GetFlags();
    args << clangOptions;
    args << clangIncludePaths;
    args << clangHeaderOptions;
    args << clangCodeGatherOptions;
    args << lineArgs;
    args << filename;
    process.setStandardOutputFile(jsonFilename);
    process.start(clangExe, args);
    process.waitForFinished();
  }
#endif
}
