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
#include "BuildForLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : DependencyTreeWidgetItem
 *****************************************************************************/
DependencyTreeWidgetItem::DependencyTreeWidgetItem
(QStringList InNames, QFileInfo InInfo) : QTreeWidgetItem(InNames)
{
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
  
  outputLine = NULL;
  elements = BuildLine::GetLineElements(InOutputLine);
  if ( 0 == elements.count() ) {
    return outputLine;
  }
  if ( elements[0] == "gcc" ) {
    BuildCompileLine*                   compileBuildLine;
    
    compileBuildLine = new BuildCompileLine();
    compileBuildLine->ParseLine(InOutputLine);
    outputLine = compileBuildLine;
    return outputLine;
  }
  if ( elements[0] == "ln" ) {
    BuildLNLine*                        line;
    line = new BuildLNLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }
  if ( elements[0] == "for" ) {
    BuildForLine*                       line;
    line = new BuildForLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }
  BuildUnknownLine*                     unknownBuildLine;

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

/*****************************************************************************!
 * Function : GetBuildLines
 *****************************************************************************/
BuildLineSet*
DependencyTreeWidgetItem::GetBuildLines
(void)
{
  return buildLines;
}
