/*****************************************************************************
 * FILE NAME    : FileTreeFile.cpp
 * DATE         : April 28 2023
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
#include "FileTreeFile.h"
#include "main.h"

/*****************************************************************************!
 * Function : FileTreeFile
 *****************************************************************************/
FileTreeFile::FileTreeFile
(QString InAbsoluteFileName1, QString InAbsoluteFileName2) : FileTreeElement(InAbsoluteFileName1, InAbsoluteFileName2)
{
}

/*****************************************************************************!
 * Function : ~FileTreeFile
 *****************************************************************************/
FileTreeFile::~FileTreeFile
()
{
}

/*****************************************************************************!
 * Function : Read
 *****************************************************************************/
void
FileTreeFile::Read
()
{
  if ( FilesHaveBeenRead ) {
    return;
  }
  do
  {
    if ( ! ReadFileContents(AbsoluteFileName1, FileLines1) ) {
      break;
    }
    if ( ! ReadFileContents(AbsoluteFileName2, FileLines2) ) {
      break;
    }
    FilesHaveBeenRead = true;
  }
  while(false);
}

/*****************************************************************************!
 * Function : GetIsSourceFile
 *****************************************************************************/
bool
FileTreeFile::GetIsSourceFile
()
{
  return IsSourceFile;
}

/*****************************************************************************!
 * Function : ReadFileContents
 *****************************************************************************/
bool
FileTreeFile::ReadFileContents
(QString InFilename, QStringList& InFileLines)
{
  QFile                                 file(InFilename);
  QByteArray                            ba;
  QString                               fileContents;

  if ( ! file.open(QIODeviceBase::ReadOnly) ) {
    return false;
  }

  ba = file.readAll();
  file.close();
  if ( ba.isEmpty() ) {
    return false;
  }

  fileContents = QString(ba);
  InFileLines = fileContents.split("\n");
  return true;
}

/*****************************************************************************!
 * Function : FileContentsDiff
 *****************************************************************************/
FileContentsDiff
FileTreeFile::GetDiffs
()
{
  return Diffs;
}

/*****************************************************************************!
 * Function : GetFileLines1
 *****************************************************************************/
QStringList
FileTreeFile::GetFileLines1
()
{
  return FileLines1;
}

/*****************************************************************************!
 * Function : GetFileLines2
 *****************************************************************************/
QStringList
FileTreeFile::GetFileLines2
()
{
  return FileLines2;
}

/*****************************************************************************!
 * Function : GetFilesDiffer
 *****************************************************************************/
bool
FileTreeFile::GetFilesDiffer
()
{
  return FilesDiffer;
}

/*****************************************************************************!
 * Function : GetFilesHaveBeenRead
 *****************************************************************************/
bool
FileTreeFile::GetFilesHaveBeenRead
()
{
  return FilesHaveBeenRead;
}

/*****************************************************************************!
 * Function : DiffFiles
 *****************************************************************************/
void
FileTreeFile::DiffFiles
()
{
  QFileInfo                             fileInfo1(AbsoluteFileName1);
  QFileInfo                             fileInfo2(AbsoluteFileName2);
  QProcess                              diffProcess;
  QString                               stdOutput;
  QStringList                           args;
  QString                               program = mainSystemConfig->GetDiff();

  args << AbsoluteFileName1 << AbsoluteFileName2;
  diffProcess.start(program, args);
  diffProcess.waitForFinished();
  stdOutput = QString(diffProcess.readAllStandardOutput().trimmed());
  if ( !stdOutput.isEmpty() ) {
    // ParseDiffLines(stdOutput);
    FilesDiffer = true;
  } else {
    FilesDiffer = false;
  }
}

/*****************************************************************************!
 * Function : SetFilesDiffer
 *****************************************************************************/
void
FileTreeFile::SetFilesDiffer
(bool InFilesDiffer)
{
  FilesDiffer = InFilesDiffer;
}

