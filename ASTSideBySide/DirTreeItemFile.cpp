/*****************************************************************************
 * FILE NAME    : DirTreeItemFile.cpp
 * DATE         : May 12 2023
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
#include "DirTreeItemFile.h"

/*****************************************************************************!
 * Function : DirTreeItem
 *****************************************************************************/
DirTreeItemFile::DirTreeItemFile
(QString InLabel, QString InFilename) : DirTreeItem()
{
  changed = false;
  type = File;
  setText(0, InLabel);
  filename = InFilename;
  initialize();
}

/*****************************************************************************!
 * Function : ~DirTreeItemFile
 *****************************************************************************/
DirTreeItemFile::~DirTreeItemFile
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
DirTreeItemFile::initialize()
{
  QFont                                 f = font(0);
  f.setBold(true);
  setFont(0, f);
  setFont(1, f);
  setForeground(0, QBrush(QColor(87, 114, 174)));
}

/*****************************************************************************!
 * Function : GetFilename
 *****************************************************************************/
QString
DirTreeItemFile::GetFilename
()
{
  return filename;
}

/*****************************************************************************!
 * Function : GetChanged
 *****************************************************************************/
bool
DirTreeItemFile::GetChanged(void)
{
  return changed;
}

/*****************************************************************************!
 * Function : SetChanged
 *****************************************************************************/
void
DirTreeItemFile::SetChanged
(bool InChanged)
{
  changed = InChanged;
}

/*****************************************************************************!
 * Function : operater<<
 *****************************************************************************/
void
DirTreeItemFile::operator<<
(bool InChanged)
{
  changed = InChanged;
}
