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
  QTreeWidgetItem*                      headerItem;
  QDir                                  d;
  QHeaderView*                                  headerView;

  headerView = header();

  connect(this, QTreeWidget::itemClicked, this, DirTree::SlotFileSelected);
  
  filePath1 = d.toNativeSeparators(InFilePath1);
  filePath2 = d.toNativeSeparators(InFilePath2);

  setColumnCount(2);

  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, filePath1);
  headerItem->setText(1, filePath2);
  headerView->resizeSection(0, 200);
  setHeaderItem(headerItem);

  setMaximumWidth(400);

  PopulateTree();
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
    QString                             filename1 = cfilename.sliced(filePathLen + 1, cfilename.length() - filePathLen);
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
