/*****************************************************************************
 * FILE NAME    : CodeCompareDir.cpp
 * DATE         : April 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <dirent.h>
#include <sys/stat.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeCompareDir.h"
#include "trace.h"

/*****************************************************************************!
 * Function : CodeCompareDir
 *****************************************************************************/
CodeCompareDir::CodeCompareDir
(QString InDirectoryName) 
{
  directoryName = QString(InDirectoryName);
}

/*****************************************************************************!
 * Function : ~CodeCompareDir
 *****************************************************************************/
CodeCompareDir::~CodeCompareDir
()
{
}

/*****************************************************************************!
 * Function : ReadDirectories
 *****************************************************************************/
QStringList
CodeCompareDir::ReadDirectories
()
{
  DIR*                                  dir;
  QString                               dirName;
  struct dirent*                        entry;
  QString                               entryName;
  QString                               fullFilename;
  QStringList                           returnNames = QStringList();
  QString                               sepString;
  struct stat                           statbuf;

  sepString = QString("%1").arg(QDir::separator());
  dirName = QDir::toNativeSeparators(directoryName);
  if ( ! dirName.endsWith(sepString) ) {
    dirName += sepString;
  }
  dir = opendir(directoryName.toStdString().c_str());
  for ( entry = readdir(dir) ; entry ; entry = readdir(dir) ) {
    entryName = QString(entry->d_name);
    if ( entryName == "." || entryName == ".." ) {
      continue;
    }
    fullFilename = directoryName + QString("\\") + entryName;
    stat(fullFilename.toStdString().c_str(), &statbuf);
    if ( (statbuf.st_mode & S_IFMT) == S_IFDIR ) {
      returnNames << fullFilename;
    }
  }
  closedir(dir);
  returnNames.sort();
  return returnNames;
}

/*****************************************************************************!
 * Function : ReadFiles
 *****************************************************************************/
QStringList
CodeCompareDir::ReadFiles
()
{
  DIR*                                  dir;
  QString                               dirName;
  struct dirent*                        entry;
  QString                               entryName;
  QString                               fullFilename;
  QStringList                           returnNames = QStringList();
  QString                               sepString;
  struct stat                           statbuf;

  sepString = QString("%1").arg(QDir::separator());
  dirName = QDir::toNativeSeparators(directoryName);
  if ( ! dirName.endsWith(sepString) ) {
    dirName += sepString;
  }
  dir = opendir(directoryName.toStdString().c_str());
  for ( entry = readdir(dir) ; entry ; entry = readdir(dir) ) {
    entryName = QString(entry->d_name);
    if ( entryName == "." || entryName == ".." ) {
      continue;
    }
    fullFilename = directoryName + QString("\\") + entryName;
    stat(fullFilename.toStdString().c_str(), &statbuf);
    if ( (statbuf.st_mode & S_IFMT) != S_IFDIR ) {
      returnNames << fullFilename;
    }
  }
  closedir(dir);
  returnNames.sort();
  return returnNames;
}

