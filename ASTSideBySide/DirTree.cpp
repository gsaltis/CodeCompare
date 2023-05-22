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
(QString InFilePath1, QString InFilePath2) : QTreeWidget()
{
  expanded = false;
  QTreeWidgetItem*                      headerItem;
  QDir                                  d;
  QHeaderView*                          headerView;
  QString                               commonPrefix;
  int                                   n, m, len1, len2;
  QString                               namePath1, namePath2;
  
  expanded = false;
  headerView = header();

  connect(this, QTreeWidget::itemClicked, this, DirTree::SlotFileSelected);
  
  filePath1 = d.toNativeSeparators(InFilePath1);
  filePath2 = d.toNativeSeparators(InFilePath2);

  commonPrefix = GetCommonPrefix(filePath1, filePath2);
  if ( ! commonPrefix.isEmpty() ) {
    n = commonPrefix.length();
    len1 = filePath1.length();
    len2 = filePath2.length();
    m = len1 - n;
    namePath1 = filePath1.sliced(n, m);

    m  = len2 - n;
    namePath2 = filePath2.sliced(n, m);
  }
  setColumnCount(2);

  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, namePath1);
  headerItem->setText(1, namePath2);
  headerView->resizeSection(0, 200);
  setHeaderItem(headerItem);

  PopulateTree();
  PopulateTree2();
  initialize();
}

/*****************************************************************************!
 * Function : ~DirTree
 *****************************************************************************/
DirTree::~DirTree
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
DirTree::initialize()
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
 * Function : GetCommonPrefix
 *****************************************************************************/
QString
DirTree::GetCommonPrefix
(QString InFilename1, QString InFilename2)
{
  int                                   i;
  int                                   len1;
  int                                   len2;
  int                                   len;
  int                                   lastDirSep;
  
  if ( InFilename1.isEmpty() || InFilename2.isEmpty() ) {
    return QString();
  }

  len1 = InFilename1.length();
  len2 = InFilename2.length();

  len = len1 < len2 ?  len1 : len2;

  lastDirSep = 0;
  for (i = 0; i < len; i++) {
    if ( InFilename1[i] == InFilename2[i] ) {
      if ( InFilename1[i] == '/' || InFilename1[i] == '\\' ) {
        lastDirSep = i;
      }
      continue;
    }
    break;
  }
  if ( len == 0 && len == i ) {
    return QString();
  }

  if ( lastDirSep > 0 ) {
    lastDirSep++;
  }
  if ( lastDirSep == len ) {
    return QString();
  }
  return InFilename1.sliced(0, lastDirSep);
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
