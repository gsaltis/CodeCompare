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
#include "trace.h"

/*****************************************************************************!
 * Function : FileTreeFile
 *****************************************************************************/
FileTreeFile::FileTreeFile
(QString InAbsoluteFileName1, QString InAbsoluteFileName2,
 CodeTrack* InTrack1, CodeTrack* InTrack2) : FileTreeElement(InAbsoluteFileName1,
                                                             InAbsoluteFileName2,
                                                             InTrack1,
                                                             InTrack2)
{
  Initialize();
}

/*****************************************************************************!
 * Function : ~FileTreeFile
 *****************************************************************************/
FileTreeFile::~FileTreeFile
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
FileTreeFile::Initialize
()
{
  IsDirectory = false;
  FilesHaveBeenRead = false;
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
  int                                   n;
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
  for ( int i = 0; i < InFileLines.count() ; i++ ) {
    QString                             st;
    st = InFileLines[i];
    n = st.length();
    if ( n == 0 ) {
      continue;
    }
    n--;
    if ( st[n] != '\r' ) {
      continue;
    }
    st = st.sliced(0, n);
    InFileLines[i] = st;
  }
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
    Diffs.ParseLines(stdOutput);
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

/*****************************************************************************!
 * Function : GetFileCount
 *****************************************************************************/
int
FileTreeFile::GetFileCount
()
{
  return 1;
}

/*****************************************************************************!
 * Function GetFileLines1Section
 *****************************************************************************/
QStringList
FileTreeFile::GetFileLines1Section
(int InStartLine, int InEndLine)
{
  return GetFileLinesSection(FileLines1, InStartLine, InEndLine);
}

/*****************************************************************************!
 * Function : GetFileLines2Section
 *****************************************************************************/
QStringList
FileTreeFile::GetFileLines2Section
(int InStartLine, int InEndLine)
{
  return GetFileLinesSection(FileLines2, InStartLine, InEndLine);
}

/*****************************************************************************!
 * Function : GetFileLinesSection
 *****************************************************************************/
QStringList
FileTreeFile::GetFileLinesSection
(QStringList InLines, int InStartLine, int InEndLine)
{
  int                                   n;
  QStringList                           lines;
  if ( InEndLine >= InLines.count() ) {
    return lines;
  }
  if ( InStartLine > InEndLine ) {
    return lines;
  }

  n = InEndLine - InStartLine + 1;
  lines = InLines.sliced(InStartLine, n);
  return lines;
}

/*****************************************************************************!
 * Function : GetChangeLinesCount
 *****************************************************************************/
QList<int>
FileTreeFile::GetChangeLinesCount
()
{
  return Diffs.GetCounts();
}

