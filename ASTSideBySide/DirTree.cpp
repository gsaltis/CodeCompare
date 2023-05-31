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
  displayAllItems = true;
  connect(this, QTreeWidget::itemClicked, this, DirTree::SlotFileSelected);
  PopulateTree();
  PopulateTree2();
  InitializeHeaders();
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
    dirItems << dirItem;
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
  bool                                  anyChanged;
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  dir.setSorting(QDir::Name);

  filePathLen = InFilePath.length();
  QFileInfoList                         list = dir.entryInfoList();

  for (auto i = list.begin() ; i != list.end(); i++ ) {
    QFileInfo                           info = *i;
    QString                             filename = info.fileName();
    DirTreeItemDir*                     dirItem;

    dirItem = new DirTreeItemDir();
    dirItems << dirItem;
    dirItem->setText(0, filename);
    InItem->addChild(dirItem);
    PopulateTreeDir(dirItem, InFilePath, info);
  }

  dir.setFilter(QDir::Files);
  list = dir.entryInfoList();
  anyChanged = false;
  for (auto i = list.begin() ; i != list.end(); i++ ) {
    QFileInfo                           info = *i;
    QString                             filename = info.completeBaseName();
    QString                             cfilename = dir.toNativeSeparators(info.canonicalFilePath());
    int                                 n2 = cfilename.length() ;
    int                                 n = n2 - filePathLen;
    QString                             filename1 = cfilename.sliced(filePathLen + 1, n-1);
    DirTreeItemFile*                    fileItem;
    QString                             st;
    bool                                b;
    
    if ( info.suffix() != "json" ) {
      continue;
    }

    QFileInfo                           info2(filename1);
    QString                             fp = info2.path();
    QString                             bn = info2.completeBaseName();
    QString                             fn = fp + QString("/") + bn;

    fn = dir.toNativeSeparators(fn);
    st = info.path() + QString("/") + info.completeBaseName() + QString(".diff");
    st = dir.toNativeSeparators(st);
    b = dir.exists(st);
    if ( b ) {
      anyChanged = true;
    }
    fileItem = new DirTreeItemFile(filename, fn);
    fileItem->SetChanged(b);
    
    fileItems << fileItem;
    InItem->addChild(fileItem);
  }
  InItem->SetChanged(anyChanged);
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
      PopulateTreeDir2(item, info.canonicalFilePath());
    }
  }
}

/*****************************************************************************!
 * Function: PopulateTreeDir2
 *****************************************************************************/
void
DirTree::PopulateTreeDir2
(DirTreeItemDir* InItem, QString InFilePath)
{
  QString                               fullPath;
  DirTreeItemDir*                       dirItem;
  DirTreeItem*                          item;
  QString                               filename;
  QFileInfo                             fileInfo(InFilePath);
  QDir                                  dir(InFilePath);
  QString                               suffix;
  
  filename = fileInfo.fileName();
  
  dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
  dir.setSorting(QDir::Name);

  QFileInfoList                         list = dir.entryInfoList();

  for (auto i = list.begin() ; i != list.end(); i++ ) {
    QFileInfo                           info = *i;
    QString                             name = info.fileName();
    item = InItem->FindItem(name);
    fullPath = info.canonicalFilePath();

    suffix = info.suffix();
    if ( item ) {
      if ( item->GetType() == DirTreeItem::Dir ) {
        item->setText(1, name);
        dirItem = (DirTreeItemDir*)item;
        PopulateTreeDir2(dirItem, fullPath);
        continue;
      }
      if ( info.suffix() != "c" ) {
        continue;
      }
      item->setText(1, name);
      continue;
    }
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
 * Function : SlotToggleChangedItems
 *****************************************************************************/
void
DirTree::SlotToggleChangedItems
()
{
  if ( displayAllItems ) {
    ShowChangedItems();
    displayAllItems = false;
    return;
  }

  ShowAllItems();
  displayAllItems = true;
}

/*****************************************************************************!
 * Function : GetAllFileNames
 *****************************************************************************/
void
DirTree::GetAllFileNames
(QString InBaseFilePath, QString InFilePath, QStringList& InFilenames)
{
  QString                               fullFilePath;
  QDir                                  dir;
  QFileInfoList                         fileInfoList;
  int                                   basePathLen;
  int                                   fileLength;
  int                                   len;
  
  basePathLen = InBaseFilePath.length() + 1;
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  dir.setSorting(QDir::Name);
  dir.setPath(InFilePath);
  fileInfoList = dir.entryInfoList();
  for (auto i = fileInfoList.begin() ; i != fileInfoList.end(); i++ ) {
    QFileInfo                           info = *i;
    fullFilePath = info.canonicalFilePath();
    fullFilePath = dir.toNativeSeparators(fullFilePath);
    GetAllFileNames(InBaseFilePath, fullFilePath, InFilenames);
  }

  dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
  dir.setSorting(QDir::Name);
  fileInfoList = dir.entryInfoList();
  for (auto i = fileInfoList.begin() ; i != fileInfoList.end(); i++ ) {
    QFileInfo                           info = *i;
    QString s = info.canonicalFilePath();
    s = dir.toNativeSeparators(s);
    if ( info.suffix() != "c" ) {
      continue;
    }
    fileLength = s.length();
    len = fileLength - basePathLen;
    s = s.sliced(basePathLen, len);
    if ( !InFilenames.contains(s) ) {
      InFilenames << s;
    }
  }
}

/*****************************************************************************!
 * Function : GetAllDifferingFilenames
 *****************************************************************************/
void
DirTree::GetAllDifferingFilenames
(QString InFilePath1, QString InFilePath2, QStringList InFilenames, QStringList& InDifferingNames)
{
  QString                       fullFilename1;
  QString                       fullFilename2;
  QFileInfo                     fileInfo1;
  QFileInfo                     fileInfo2;
  QDir                          dir;

  foreach ( auto filename, InFilenames ) {
    fullFilename1 = InFilePath1 + "/" + filename;
    fullFilename1 = dir.toNativeSeparators(fullFilename1);
    fileInfo1.setFile(fullFilename1);
    
    fullFilename2 = InFilePath2 + "/" + filename;
    fullFilename2 = dir.toNativeSeparators(fullFilename2);
    fileInfo2.setFile(fullFilename2);

    if ( !fileInfo1.exists() || !fileInfo2.exists() ) {
      InDifferingNames << filename;
      continue;
    }
    if ( fileInfo1.size() != fileInfo2.size() ) {
      InDifferingNames << filename;
      continue;
    }

    if ( !FilesAreSame(fullFilename1, fullFilename2) ) {
      InDifferingNames << filename;
      continue;
    }
  } 
}

/*****************************************************************************!
 * Function : FilesAreSame
 *****************************************************************************/
bool
DirTree::FilesAreSame
(QString InFilename1, QString InFilename2)
{
  QString                               diffFilename1;
  QString                               diffFilename2;
  QDir                                  dir;
  
  diffFilename1 = InFilename1 + ".diff";
  diffFilename2 = InFilename2 + ".diff";

  if ( dir.exists(diffFilename2) || dir.exists(diffFilename1) ) {
    return false;
  }

  return true;
}

/*****************************************************************************!
 * Function : LineIsCopyrightLine
 *****************************************************************************/
bool
DirTree::LineIsCopyrightLine
(QString InLine)
{
  int                                   n = InLine.length();
  int                                   state = 0;
  int                                   i;
  QString                               s;
  QChar                                 ch;

  for ( i = 0 ; i < n ; i++ ) {
    ch = InLine[i];
    if ( state == 0 ) {
      if ( ch == ' ' ) {
        continue;
      }
      if ( ch == '*' ) {
        state = 1;
        continue;
      }
      return false;
    }
    if ( state == 1 ) {
      if ( ch == ' ' || ch == '\t' ) {
        continue;
      }
      break;
    }
  }
  if ( i == n ) {
    return false;
  }
  s = InLine.sliced(i, 9);
  if ( s == "Copyright" ) {
    return true;
  }
  return false;
}

/*****************************************************************************!
 * Function : ShowAllItems
 *****************************************************************************/
void
DirTree::ShowAllItems(void)
{
  int                                   i, n;

  n = fileItems.size();
  for (i = 0; i < n; i++) {
    fileItems[i]->setHidden(false);
  }

  n = dirItems.size();
  for (i = 0; i < n; i++) {
    dirItems[i]->setHidden(false);
  }
}

/*****************************************************************************!
 * Function : ShowChangedItems
 *****************************************************************************/
void
DirTree::ShowChangedItems(void)
{
  int                                   i, n;
  DirTreeItemDir*                       dirItem;
  QTreeWidgetItem*                      item;
  
  n = topLevelItemCount();

  for (i = 0; i < n; i++) {
    item = topLevelItem(i);
    dirItem = (DirTreeItemDir*)item;

    if ( DirChanged(dirItem) ) {
      dirItem->setHidden(false);
    } else {
      dirItem->setHidden(true);
    }
  }
}

/*****************************************************************************!
 * Function: DirChanged
 *****************************************************************************/
bool
DirTree::DirChanged
(DirTreeItemDir* InDirItem)
{
  int                                   i, n;
  bool                                  c;
  bool                                  rvalue;

  rvalue = false;
  n = InDirItem->childCount();
  
  for ( i = 0 ; i < n ; i++ ) {
    DirTreeItem*                        item;
    item = (DirTreeItem*)InDirItem->child(i);
    if ( item->GetType() == DirTreeItem::Type::Dir ) {
      DirTreeItemDir*                   dirItem;
      dirItem = (DirTreeItemDir*)item;
      c = DirChanged(dirItem);
      if ( c ) {
        rvalue = true;
      }
      dirItem->setHidden(!c);
      continue;
    }
    if ( item->GetType() == DirTreeItem::Type::File ) {
      DirTreeItemFile*                  fileItem;
      fileItem = (DirTreeItemFile*)item;
      c = fileItem->GetChanged();
      if ( c ) {
        rvalue = true;
      }
      fileItem->setHidden(!c);
    }
  }
  return rvalue;
}
  
