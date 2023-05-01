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
(QString InAbsoluteFilename1, QString InAbsoluteFilename2) : FileTreeElement(InAbsoluteFilename1,
                                                                             InAbsoluteFilename2)
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

