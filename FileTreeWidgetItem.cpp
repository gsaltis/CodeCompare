/*****************************************************************************
 * FILE NAME    : FileTreeWidgetItem.cpp
 * DATE         : April 20 2023
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
#include "FileTreeWidgetItem.h"
#include "trace.h"

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName, int InColumn) : QTreeWidgetItem()
{
  initialize();
  if ( InColumn == 0 ) {
    SetAbsoluteFileName1(InAbsoluteFileName);
    return;
  }
  SetAbsoluteFileName2(InAbsoluteFileName);
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName, QTreeWidget* InTree) : QTreeWidgetItem()
{
  initialize();
  SetAbsoluteFileName1(InAbsoluteFileName);
  this->isDirectory = true;
  InTree->addTopLevelItem(this);
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName, QTreeWidgetItem* InParent, int InColumn) : QTreeWidgetItem()
{
  initialize();
  if ( InColumn == 0 ) {
    SetAbsoluteFileName1(InAbsoluteFileName);
    InParent->addChild(this);
    return;
  }
  SetAbsoluteFileName2(InAbsoluteFileName);
  InParent->addChild(this);
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName1, QString InAbsoluteFileName2) : QTreeWidgetItem()
{
  initialize();
  SetAbsoluteFileNames(InAbsoluteFileName1, InAbsoluteFileName2);
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName1, QString InAbsoluteFileName2, QTreeWidgetItem* InParent) : QTreeWidgetItem()
{
  initialize();
  SetAbsoluteFileNames(InAbsoluteFileName1, InAbsoluteFileName2);
  InParent->addChild(this);
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
FileTreeWidgetItem::initialize
()
{
  isDirectory = false;
  FilesDiffer = false;
}

/*****************************************************************************!
 * Function : ~FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::~FileTreeWidgetItem
()
{
}

/*****************************************************************************!
 * Function : GetAbsoluteFileName1
 *****************************************************************************/
QString
FileTreeWidgetItem::GetAbsoluteFileName1(void)
{
  return absoluteFileName1;  
}

/*****************************************************************************!
 * Function : SetAbsoluteFileName1
 *****************************************************************************/
void
FileTreeWidgetItem::SetAbsoluteFileName1
(QString InAbsoluteFileName1)
{
  absoluteFileName2 = InAbsoluteFileName1;

  setText(0, QString(""));
  QFileInfo                             fileInfo1(absoluteFileName1);
  setText(1, fileInfo1.fileName());
  absoluteFileName1 = InAbsoluteFileName1;
}

/*****************************************************************************!
 * Function : GetAbsoluteFileName2
 *****************************************************************************/
QString
FileTreeWidgetItem::GetAbsoluteFileName2(void)
{
  return absoluteFileName2;  
}

/*****************************************************************************!
 * Function : SetAbsoluteFileName2
 *****************************************************************************/
void
FileTreeWidgetItem::SetAbsoluteFileName2
(QString InAbsoluteFileName2)
{
  absoluteFileName2 = InAbsoluteFileName2;

  QFileInfo                             fileInfo2(absoluteFileName2);
  setText(0, fileInfo2.fileName());
}

/*****************************************************************************!
 * Function : SetAbsoluteFileNames
 *****************************************************************************/
void
FileTreeWidgetItem::SetAbsoluteFileNames
(QString InAbsoluteFileName1, QString InAbsoluteFileName2)
{
  absoluteFileName1 = InAbsoluteFileName1;
  absoluteFileName2 = InAbsoluteFileName2;

  QFileInfo                             fileInfo1(absoluteFileName1);
  setText(0, fileInfo1.fileName());

  QFileInfo                             fileInfo2(absoluteFileName2);
  setText(1, fileInfo2.fileName());
}

/*****************************************************************************!
 * Function : ParseDiffLines
 *****************************************************************************/
void
FileTreeWidgetItem::ParseDiffLines
(QString InDiffLines)
{
  diffs.ParseLines(InDiffLines);
}

/*****************************************************************************!
 * Function : GetFilesDiffer
 *****************************************************************************/
bool
FileTreeWidgetItem::GetFilesDiffer(void)
{
  return FilesDiffer;  
}

/*****************************************************************************!
 * Function : SetFilesDiffer
 *****************************************************************************/
void
FileTreeWidgetItem::SetFilesDiffer
(bool InFilesDiffer)
{
  FilesDiffer = InFilesDiffer;
}

/*****************************************************************************!
 * Function : GetIsDirectory
 *****************************************************************************/
bool
FileTreeWidgetItem::GetIsDirectory(void)
{
  return isDirectory;  
}

/*****************************************************************************!
 * Function : SetIsDirectory
 *****************************************************************************/
void
FileTreeWidgetItem::SetIsDirectory
(bool InIsDirectory)
{
  isDirectory = InIsDirectory;  
}

/*****************************************************************************!
 * Function : GetFileName1
 *****************************************************************************/
QString
FileTreeWidgetItem::GetFileName1
()
{
  return absoluteFileName1;
}

/*****************************************************************************!
 * Function : GetFileName2
 *****************************************************************************/
QString
FileTreeWidgetItem::GetFileName2
()
{
  return absoluteFileName2;
}

/*****************************************************************************!
 * Function : IsSourceFile
 *****************************************************************************/
bool
FileTreeWidgetItem::IsSourceFile(void)
{
  QString                               suffix;
  QFileInfo                             fileInfo;

  if ( ! absoluteFileName1.isEmpty() ) {
    fileInfo.setFile(absoluteFileName1);
  } else {
    fileInfo.setFile(absoluteFileName2);
  }
  suffix = fileInfo.suffix();

  return suffix == "h" ||
    suffix == "c" ||
    suffix == ".cpp";
}

/*****************************************************************************!
 * Function : GetChangeLinesCount
 *****************************************************************************/
QList<int>
FileTreeWidgetItem::GetChangeLinesCount
()
{
  if ( ! FilesDiffer ) {
    QList<int>                  n;
    n << 0 << 0 << 0;
    return n;
  }
  return diffs.GetCounts();
}
