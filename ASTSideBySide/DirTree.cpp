/*****************************************************************************
 * FILE NAME    : DirTree.cpp
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
#include <QHeaderView>

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirTree.h"
#include "DirTreeItemDir.h"
#include "DirTreeItemFile.h"
#include "trace.h"

/*****************************************************************************!
 * Function : DirTree
 *****************************************************************************/
DirTree::DirTree
(QString InFilePath1, QString InFilePath2)
  : CommonFileTree(InFilePath1, InFilePath2)
{
  expanded = false;

  connect(this, QTreeWidget::itemClicked, this, DirTree::SlotFileSelected);
  PopulateTree();
  PopulateTree2();
}

/*****************************************************************************!
 * Function : ~DirTree
 *****************************************************************************/
DirTree::~DirTree
()
{
}

/*****************************************************************************!
 * Function : PopulateTree
 *****************************************************************************/
void
DirTree::PopulateTree(void)
{
  QDir                                  dir(filePath1);
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  dir.setSorting(QDir::Name);

  QFileInfoList                         list = dir.entryInfoList();

  for (auto i = list.begin() ; i != list.end(); i++ ) {
    QFileInfo                           info = *i;
    QString                             filename = info.fileName();
    DirTreeItemDir*                     dirItem;

    dirItem = new DirTreeItemDir();
    dirItem->setText(0, filename);
    addTopLevelItem(dirItem);
    PopulateTreeDir(dirItem, filePath1, info);
  }
}

/*****************************************************************************!
 * Function : PopulateTree2
 *****************************************************************************/
void
DirTree::PopulateTree2(void)
{
  QDir                                  dir(filePath2);
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  dir.setSorting(QDir::Name);

  QFileInfoList                         list = dir.entryInfoList();

  for (auto i = list.begin() ; i != list.end(); i++ ) {
    QFileInfo                           info = *i;
    QString                             dirname = info.fileName();
    DirTreeItemDir*                     item = FindDirItem(dirname);
    if ( item ) {
      item->setText(1, dirname);
    }
  }
}

/*****************************************************************************!
 * Function : PopulateTreeDir
 *****************************************************************************/
void
DirTree::PopulateTreeDir
(DirTreeItemDir* InItem, QString InFilePath, QFileInfo InFileInfo)
{
  QDir                                  dir(InFileInfo.absoluteFilePath());
  int                                   filePathLen;
  
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  dir.setSorting(QDir::Name);

  filePathLen = InFilePath.length();
  QFileInfoList                         list = dir.entryInfoList();

  for (auto i = list.begin() ; i != list.end(); i++ ) {
    QFileInfo                           info = *i;
    QString                             filename = info.fileName();
    DirTreeItemDir*                     dirItem;

    dirItem = new DirTreeItemDir();
    dirItem->setText(0, filename);
    InItem->addChild(dirItem);
    PopulateTreeDir(dirItem, InFilePath, info);
  }

  dir.setFilter(QDir::Files);
  list = dir.entryInfoList();
  for (auto i = list.begin() ; i != list.end(); i++ ) {
    QFileInfo                           info = *i;
    QString                             filename = info.completeBaseName();
    QString                             cfilename = dir.toNativeSeparators(info.canonicalFilePath());
    int                                 n2 = cfilename.length() ;
    int                                 n = n2 - filePathLen;
    QString                             filename1 = cfilename.sliced(filePathLen + 1, n-1);
    DirTreeItemFile*                    fileItem;

    if ( info.suffix() != "json" ) {
      continue;
    }

    QFileInfo                           info2(filename1);
    QString                             fp = info2.path();
    QString                             bn = info2.completeBaseName();
    QString                             fn = fp + QString("/") + bn;

    fn = dir.toNativeSeparators(fn);
    fileItem = new DirTreeItemFile(filename, fn);
    InItem->addChild(fileItem);
  }
}

/*****************************************************************************!
 * Function : SlotFileSelected
 *****************************************************************************/
void
DirTree::SlotFileSelected
(QTreeWidgetItem* InItem, int)
{
  QString                               filename;
  DirTreeItem*                          d;
  DirTreeItemFile*                      f;

  d = (DirTreeItem*)InItem;

  if ( d->GetType() != DirTreeItem::File ) {
    return;
  }

  f = (DirTreeItemFile*)d;
  filename = f->GetFilename();
  emit SignalFileSelected(filename);
}

/*****************************************************************************!
  * Function : FindDirItem
 *****************************************************************************/
DirTreeItemDir*
DirTree::FindDirItem
(QString InDirName)
{
  DirTreeItemDir*                       dirItem;
  int                                   i, n;

  n = topLevelItemCount();

  for (i = 0; i < n; i++) {
    dirItem = (DirTreeItemDir*)topLevelItem(i);
    if ( dirItem->text(0) == InDirName ) {
      return dirItem;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : SlotToggleTreeView
 *****************************************************************************/
void
DirTree::SlotToggleTreeView(void)
{
  int                                   n = topLevelItemCount();

  if ( expanded ) {
    for (int i = 0; i < n; i++) {
      DirTreeItemDir* dirItem = (DirTreeItemDir*)topLevelItem(i);
      dirItem->CollapseChildren();
    }
    expanded = false;
    return;
  }
  for (int i = 0; i < n; i++) {
    DirTreeItemDir* dirItem = (DirTreeItemDir*)topLevelItem(i);
    dirItem->ExpandChildren();
  }
  expanded = true;
}

/*****************************************************************************!
 * Function : GetExpanded
 *****************************************************************************/
bool
DirTree::GetExpanded(void)
{
  return expanded;
}
