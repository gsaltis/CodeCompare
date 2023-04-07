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
#include "BuildUnknownLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : DependencyTreeWidgetItem
 *****************************************************************************/
DependencyTreeWidgetItem::DependencyTreeWidgetItem
(QStringList InNames, QFileInfo InInfo) : QTreeWidgetItem(InNames)
{
  buildLine = NULL;
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

  lines = InMakeOutput.split("\n");
  linesCount = lines.count();

  ParseMakefileOutputLine(lines[linesCount-2]);
}

/*****************************************************************************!
 * Function : ParseMakefileOutputLine
 *****************************************************************************/
void
DependencyTreeWidgetItem::ParseMakefileOutputLine
(QString InOutputLine)
{
  QStringList                           elements;
  
  buildLine = NULL;
  elements = BuildLine::GetLineElements(InOutputLine);
  if ( 0 == elements.count() ) {
    return;
  }
  if ( elements[0] == "gcc" ) {
    BuildCompileLine*                   compileBuildLine;
    
    compileBuildLine = new BuildCompileLine();
    compileBuildLine->ParseLine(InOutputLine);
    buildLine = compileBuildLine;
    return;
  }
  if ( elements[0] == "ln" ) {
    BuildLNLine*                        line;
    line = new BuildLNLine();
    line->ParseLine(InOutputLine);
    buildLine = line;
    return;
  }
  BuildUnknownLine*                     unknownBuildLine;

  unknownBuildLine = new BuildUnknownLine();
  unknownBuildLine->ParseLine(InOutputLine);
  buildLine = unknownBuildLine;
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
  
  fullPath = fileInfo.absoluteFilePath();
  
  makeProcess.setWorkingDirectory(fullPath);
  args << "-n";
  program = "D:\\Qt\\Tools\\mingw900_64\\bin\\make.exe";

  makeProcess.start(program, args);
  makeProcess.waitForFinished();
  outputString = QString(makeProcess.readAllStandardOutput());
  ParseMakefileOutput(outputString);
}

/*****************************************************************************!
 * Function : GetBuildLine
 *****************************************************************************/
BuildLine*
DependencyTreeWidgetItem::GetBuildLine(void)
{
  return buildLine;
}