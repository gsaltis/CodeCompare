/*****************************************************************************
 * FILE NAME    : FileTreeDirectory.cpp
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
#include "FileTreeDirectory.h"
#include "trace.h"

/*****************************************************************************!
 * Function : FileTreeDirectory
 *****************************************************************************/
FileTreeDirectory::FileTreeDirectory
(QString InAbsoluteFileName1, QString InAbsoluteFileName2,
 CodeTrack* InTrack1, CodeTrack* InTrack2) : FileTreeElement(InAbsoluteFileName1,
                                                             InAbsoluteFileName2,
                                                             InTrack1,
                                                             InTrack2)
{
  FilesHaveBeenRead = false;
  IsDirectory = true;
}

/*****************************************************************************!
 * Function : ~FileTreeDirectory
 *****************************************************************************/
FileTreeDirectory::~FileTreeDirectory
()
{
}

/*****************************************************************************!
 * Function : Read
 *****************************************************************************/
void
FileTreeDirectory::Read
()
{


}

/*****************************************************************************!
 * Function : GetFileCount
 *****************************************************************************/
int
FileTreeDirectory::GetFileCount
()
{
  int                                   m, n, i;

  n = count();
  m = 0;
  for (i = 0; i < n; i++) {
    auto f = at(i);
    m += f.GetFileCount();
  }
  return m;
}

/*****************************************************************************!
 * Function : GetChangeLinesCount
 *****************************************************************************/
QList<int>
FileTreeDirectory::GetChangeLinesCount
()
{
  QList<int>                            n;

  n << 0 << 0  << 0;
  return n;
}

