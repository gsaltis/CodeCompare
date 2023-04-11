/*****************************************************************************
 * FILE NAME    : DependencyTreeWidgetItem.cpp
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
#include "DependencyTreeWidgetItem.h"
#include "BuildCompileLine.h"
#include "BuildLNLine.h"
#include "BuildARLine.h"
#include "BuildRanlibLine.h"
#include "BuildUnknownLine.h"
#include "BuildForLine.h"
#include "BuildEchoLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : DependencyTreeWidgetItem
 *****************************************************************************/
DependencyTreeWidgetItem::DependencyTreeWidgetItem
(QStringList InNames, QFileInfo InInfo, BuildSystem* InBuildSystem) : QTreeWidgetItem(InNames)
{
  buildSystem = InBuildSystem;
  buildLine = NULL;
  buildLines = new BuildLineSet();
  fileInfo = QFileInfo(InInfo);
}

/*****************************************************************************!
 * Function : ~DependencyTreeWidgetItem
 *****************************************************************************/
DependencyTreeWidgetItem::~DependencyTreeWidgetItem
()
{
}

/*****************************************************************************!
 * Function : GetFileInfo
 *****************************************************************************/
QFileInfo
DependencyTreeWidgetItem::GetFileInfo(void)
{
  
  return fileInfo;
}

/*****************************************************************************!
 * Function : SetFileInfo
 *****************************************************************************/
void
DependencyTreeWidgetItem::SetFileInfo
(QFileInfo InFileInfo)
{
  
  fileInfo = InFileInfo;
}

/*****************************************************************************!
 * Function : ParseMakefileOutput
 *****************************************************************************/
void
DependencyTreeWidgetItem::ParseMakefileOutput
(QString InMakeOutput)
{
  QStringList                           lines;
  int                                   linesCount;
  BuildLine*                            line;
  
  lines = InMakeOutput.split("\n", Qt::SkipEmptyParts);
  linesCount = lines.count();

  for ( int i = 0 ; i < linesCount ; i++ ) {
    line = ParseMakefileOutputLine(lines[i]);
    if ( NULL == line ) {
      continue;
    }
    if ( line->GetType() == BuildLine::TypeCompile ) {
      QString t = ((BuildCompileLine*)line)->GetTarget();
    }
    buildLines->AppendLine(line);
  }
  buildLine = buildLines->GetLineByIndex(0);
}

/*****************************************************************************!
 * Function : ParseMakefileOutputLine
 *****************************************************************************/
BuildLine*
DependencyTreeWidgetItem::ParseMakefileOutputLine
(QString InOutputLine)
{
  QStringList                           elements;
  BuildLine*                            outputLine;
  QStringList                           sources;
  BuildElementSet*                      buildSet;
  BuildElement*                         buildElement;
  QString                               targetString;
  BuildUnknownLine*                     unknownBuildLine;
  
  outputLine = NULL;

  if ( InOutputLine.startsWith("#") ) {
    return NULL;
  }
  elements = BuildLine::GetLineElements(InOutputLine);

  
  if ( 0 == elements.count() ) {
    return outputLine;
  }

  //!
  if ( elements[0] == "gcc" ) {
    BuildCompileLine*                   compileBuildLine;
    
    compileBuildLine = new BuildCompileLine();
    compileBuildLine->ParseLine(InOutputLine);
    outputLine = compileBuildLine;
    targetString = compileBuildLine->GetTarget();
    sources = compileBuildLine->GetSources();
    buildSet = new BuildElementSet(targetString);
    buildSet->SetBuildLine(compileBuildLine);
    buildSystem->BuildElementSetAdd(buildSet);
    
    for ( int i = 0 ;  i < sources.count(); i++ ) {
      QString                           source;
      buildElement = new BuildElement(sources[i]);
      buildSet->AddElement(buildElement);
      buildSet->SetBuildLine(compileBuildLine);
    }
    return outputLine;
  }

  //!
  if ( elements[0] == "ln" ) {
    BuildLNLine*                        line;
    line = new BuildLNLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }

  //!
  if ( elements[0] == "ranlib" ) {
    BuildRanlibLine*                    line;
    line = new BuildRanlibLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }

  //!
  if ( elements[0] == "ar" ) {
    BuildARLine*                        line;
    line = new BuildARLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    targetString = line->GetTarget();
    sources = line->GetSources();
    buildSet = new BuildElementSet(targetString);
    buildSystem->BuildElementSetAdd(buildSet);
    for ( int i = 0 ;  i < sources.count(); i++ ) {
      QString                           source;
      buildElement = new BuildElement(sources[i]);
      buildSet->AddElement(buildElement);
      buildSet->SetBuildLine(line);
    }
    return outputLine;
  }

  //!
  if ( elements[0] == "for" ) {
    BuildForLine*                       line;
    line = new BuildForLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }

  //!
  if ( elements[0] == "echo" ) {
    BuildEchoLine*                      line;
    line = new BuildEchoLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }
  
  unknownBuildLine = new BuildUnknownLine();
  unknownBuildLine->ParseLine(InOutputLine);
  outputLine = unknownBuildLine;
  return outputLine;
}

/*****************************************************************************!
 * Function : PerformMake
 *****************************************************************************/
void
DependencyTreeWidgetItem::PerformMake
()
{
  QString                               text;
  QString                               fullPath;
  QProcess                              makeProcess;
  QStringList                           args;
  QString                               program;
  QString                               outputString;
  QString                               libdlPath;
  QFileInfo                             libdlFileInfo;
  bool                                  alreadyHasLIBDL;
  
  fullPath = fileInfo.absoluteFilePath();

  // Create libdl.a since some of the targets rely on -ldl
  libdlPath = fullPath + QString("/libdl.a");
  libdlFileInfo.setFile(libdlPath);
  alreadyHasLIBDL = libdlFileInfo.exists();
  QFile file(libdlPath);
  if ( ! alreadyHasLIBDL ) {
    file.open(QIODeviceBase::ReadWrite);
  }

  makeProcess.setWorkingDirectory(fullPath);
  args << "-n";
  args << "all";
  program = "D:\\Qt\\Tools\\mingw900_64\\bin\\make.exe";

  makeProcess.start(program, args);
  makeProcess.waitForFinished();
  outputString = QString(makeProcess.readAllStandardOutput());
  ParseMakefileOutput(outputString);
  if ( ! alreadyHasLIBDL ) {
    file.remove(); 
    file.close();
  }
}

/*****************************************************************************!
 * Function : GetBuildLine
 *****************************************************************************/
BuildLine*
DependencyTreeWidgetItem::GetBuildLine(void)
{
  return buildLine;
}

/*****************************************************************************!
 * Function : GetBuildLines
 *****************************************************************************/
BuildLineSet*
DependencyTreeWidgetItem::GetBuildLines
(void)
{
  return buildLines;
}
