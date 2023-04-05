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
#include "trace.h"

/*****************************************************************************!
 * Function : DependencyTreeWidgetItem
 *****************************************************************************/
DependencyTreeWidgetItem::DependencyTreeWidgetItem
(QStringList InNames, QFileInfo InInfo) : QTreeWidgetItem(InNames)
{
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
  buildLine = new BuildLine();
  buildLine->ParseLine(InOutputLine);
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
