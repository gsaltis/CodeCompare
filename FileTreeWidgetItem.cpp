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
#include "main.h"
#include "trace.h"

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName, QTreeWidget* InTree, bool InIsDirectory, CodeTrack* InTrack1, CodeTrack* InTrack2) : QTreeWidgetItem()
{
  initialize();
  if ( InIsDirectory ) {
    TreeElement = new FileTreeDirectory(InAbsoluteFileName, QString(""), InTrack1, InTrack2);
  } else {
    TreeElement = new FileTreeFile(InAbsoluteFileName, QString(""), InTrack1, InTrack2);
  } 
  SetAbsoluteFileName1();
  InTree->addTopLevelItem(this);
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName1, QString InAbsoluteFileName2, bool InIsDirectory, CodeTrack* InTrack1, CodeTrack* InTrack2) : QTreeWidgetItem()
{
  initialize();

  if ( InIsDirectory )  {
    TreeElement = new FileTreeDirectory(InAbsoluteFileName1, InAbsoluteFileName2, InTrack1, InTrack2);
  } else {
    TreeElement = new FileTreeFile(InAbsoluteFileName1, InAbsoluteFileName2, InTrack1, InTrack2);
  }  
  SetAbsoluteFileNames();
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName1, QString InAbsoluteFileName2, FileTreeWidgetItem* InParent, bool InIsDirectory, CodeTrack* InTrack1, CodeTrack* InTrack2) : QTreeWidgetItem()
{
  FileTreeDirectory*                    te;
  initialize();
  if ( InIsDirectory )  {
    TreeElement = new FileTreeDirectory(InAbsoluteFileName1, InAbsoluteFileName2, InTrack1, InTrack2);
  } else {
    TreeElement = new FileTreeFile(InAbsoluteFileName1, InAbsoluteFileName2, InTrack1, InTrack2);
  }  
  SetAbsoluteFileNames();
  InParent->addChild(this);
  te = (FileTreeDirectory*)InParent->GetTreeElement();
  te->append(TreeElement);
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
FileTreeWidgetItem::initialize
()
{
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
  return TreeElement->GetAbsoluteFileName1();
}

/*****************************************************************************!
 * Function : SetAbsoluteFileName1
 *****************************************************************************/
void
FileTreeWidgetItem::SetAbsoluteFileName1
()
{
  QString                               absoluteFileName;

  absoluteFileName = TreeElement->GetAbsoluteFileName1();

  setText(0, QString(""));
  QFileInfo                             fileInfo(absoluteFileName);
  setText(1, fileInfo.fileName());
}

/*****************************************************************************!
 * Function : GetAbsoluteFileName2
 *****************************************************************************/
QString
FileTreeWidgetItem::GetAbsoluteFileName2(void)
{
  return TreeElement->GetAbsoluteFileName2();;  
}

/*****************************************************************************!
 * Function : SetAbsoluteFileName2
 *****************************************************************************/
void
FileTreeWidgetItem::SetAbsoluteFileName2
()
{
  QString                               absoluteFileName;

  absoluteFileName = TreeElement->GetAbsoluteFileName1();

  QFileInfo                             fileInfo(absoluteFileName);
  setText(0, fileInfo.fileName());
}

/*****************************************************************************!
 * Function : SetAbsoluteFileNames
 *****************************************************************************/
void
FileTreeWidgetItem::SetAbsoluteFileNames
()
{
  QString                               absoluteFileName1 = TreeElement->GetAbsoluteFileName1();
  QString                               absoluteFileName2 = TreeElement->GetAbsoluteFileName2();

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
(QString )
{
  // TreeElement->ParseLines(InDiffLines);
}

/*****************************************************************************!
 * Function : GetFilesDiffer
 *****************************************************************************/
bool
FileTreeWidgetItem::GetFilesDiffer(void)
{
  FileTreeFile*                         e;

  e = (FileTreeFile*)TreeElement; 
  return e->GetFilesDiffer();  
}

/*****************************************************************************!
 * Function : GetIsDirectory
 *****************************************************************************/
bool
FileTreeWidgetItem::GetIsDirectory(void)
{
  return TreeElement->GetIsDirectory();
}

/*****************************************************************************!
 * Function : GetFileName1
 *****************************************************************************/
QString
FileTreeWidgetItem::GetFileName1
()
{
  return TreeElement->GetAbsoluteFileName1();
}

/*****************************************************************************!
 * Function : GetFileName2
 *****************************************************************************/
QString
FileTreeWidgetItem::GetFileName2
()
{
  return TreeElement->GetAbsoluteFileName2();
}

/*****************************************************************************!
 * Function : IsSourceFile
 *****************************************************************************/
bool
FileTreeWidgetItem::IsSourceFile(void)
{
  QString                               suffix;
  QFileInfo                             fileInfo;
  QString                               absoluteFileName1;
  QString                               absoluteFileName2;

  absoluteFileName1 = TreeElement->GetAbsoluteFileName1();
  absoluteFileName2 = TreeElement->GetAbsoluteFileName2();
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
 * Function : ReadFiles
 *****************************************************************************/
void
FileTreeWidgetItem::ReadFiles(void)
{
  TreeElement->Read();
}

/*****************************************************************************!
 * Function : GetFile1Lines
 *****************************************************************************/
QStringList
FileTreeWidgetItem::GetFile1Lines
()
{
  FileTreeFile*                         e;

  e = (FileTreeFile*)TreeElement;
  return e->GetFileLines1();
}

/*****************************************************************************!
 * Function : GetFile2Lines
 *****************************************************************************/
QStringList
FileTreeWidgetItem::GetFile2Lines
()
{
  FileTreeFile*                         e;

  e = (FileTreeFile*)TreeElement;
  return e->GetFileLines2();
}

/*****************************************************************************!
 * Function : GetFile1LinesSelection
 *****************************************************************************/
QStringList
FileTreeWidgetItem::GetFile1LinesSelection
(int InStartLine, int InEndLine)
{
  return GetFileLinesSelection(GetFile1Lines(), InStartLine, InEndLine);
}

/*****************************************************************************!
 * Function : GetFile2LinesSelection
 *****************************************************************************/
QStringList
FileTreeWidgetItem::GetFile2LinesSelection
(int InStartLine, int InEndLine)
{
  return GetFileLinesSelection(GetFile2Lines(), InStartLine, InEndLine);
}

/*****************************************************************************!
 * Function : GetFileLinesSelection
 *****************************************************************************/
QStringList
FileTreeWidgetItem::GetFileLinesSelection
(QStringList InFileLines, int InStartLine, int InEndLine)
{
  int                                   n;

  if ( InStartLine > InEndLine ) {
    return QStringList();
  }

  if ( InEndLine >= InFileLines.count() ) {
    return QStringList();
  }

  n = InEndLine - InStartLine + 1;
  return InFileLines.sliced(InStartLine, n);
}

/*****************************************************************************!
 * Function : GetTreeElement
 *****************************************************************************/
FileTreeElement*
FileTreeWidgetItem::GetTreeElement
()
{
  return TreeElement;
}

/*****************************************************************************!
 * Function : DiffFiles
 *****************************************************************************/
void
FileTreeWidgetItem::DiffFiles
(int& InFilesDifferCount)
{
  if ( NULL == TreeElement ) {
    return;
  }

  if ( TreeElement->GetIsDirectory() ) {
    return;
  }

  FileTreeFile*                         fileElement = (FileTreeFile*)TreeElement;
  fileElement->DiffFiles();
  if ( fileElement->GetFilesDiffer() ) {
    setIcon(0, QIcon(QPixmap(":/images/FileDifferent.png")));
    InFilesDifferCount++;
    return;
  }
  setIcon(0, QIcon(QPixmap(":/images/FileSame.png")));
}

/*****************************************************************************!
 * Function : SetFilesDiffer
 *****************************************************************************/
void
FileTreeWidgetItem::SetFilesDiffer
(bool InFilesDiffer)
{
  if ( NULL == TreeElement ) {
    return;
  }

  if ( TreeElement->GetIsDirectory() ) {
    return;
  }

  FileTreeFile*                                 fileElement = (FileTreeFile*)TreeElement;

  fileElement->SetFilesDiffer(InFilesDiffer);
}

/*****************************************************************************!
 * Function : GetDifferences
 *****************************************************************************/
FileContentsDiff
FileTreeWidgetItem::GetDifferences
()
{
  if ( NULL == TreeElement ) {
    return FileContentsDiff();
  }

  if ( TreeElement->GetIsDirectory() ) {
    return FileContentsDiff();
  }

  FileTreeFile*                                 fileElement = (FileTreeFile*)TreeElement;

  return fileElement->GetDiffs();
}

/*****************************************************************************!
 * Function : GetFileCount
 *****************************************************************************/
int
FileTreeWidgetItem::GetFileCount
()
{
  int                                   n;
  if ( TreeElement == NULL ) {
    return 0;
  }

  if ( TreeElement->GetIsDirectory() ) {
    n = TreeElement->GetFileCount();
    return n;
  }
  return 1;
}

/*****************************************************************************!
 * Function : FindChildByFileName
 *****************************************************************************/
FileTreeWidgetItem*
FileTreeWidgetItem::FindChildByFileName
(QString InFilename)
{
  FileTreeWidgetItem*                   t2;
  QString                               st;
  FileTreeWidgetItem*                   t;
  int                                   n, i;

  n = childCount();

  for (i = 0; i < n; i++) {
    t = (FileTreeWidgetItem*)child(i);
    if ( t->GetIsDirectory() ) {
      t2 = t->FindChildByFileName(InFilename);
      if ( t2 ) {
        return t2;
      }
    }
    st = t->GetAbsoluteFileName1();
    if ( st == InFilename ) {
      return t;
    }
    st = t->GetAbsoluteFileName2();
    if ( st == InFilename ) {
      return t;
    }
  }
  return NULL;
}
