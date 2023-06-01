/*****************************************************************************
 * FILE NAME    : CommonFileTree.cpp
 * DATE         : May 23 2023
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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CommonFileTree.h"

/*****************************************************************************!
 * Function : CommonFileTree
 *****************************************************************************/
CommonFileTree::CommonFileTree
(QString InFilePath1, QString InFilePath2) : QTreeWidget()
{
  QDir                                  d;

  filePath1 = d.toNativeSeparators(InFilePath1);
  filePath2 = d.toNativeSeparators(InFilePath2);
  track1.SetBasePath(filePath1);
  track2.SetBasePath(filePath2);

  initialize();
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
CommonFileTree::initialize
()
{
  QTreeWidgetItem*                      headerItem;
  QHeaderView*                          headerView;
  QString                               commonPrefix;
  int                                   n, m, len1, len2;
  
  headerView = header();
  commonPrefix = GetCommonPrefix(filePath1, filePath2);
  if ( ! commonPrefix.isEmpty() ) {
    n = commonPrefix.length();
    len1 = filePath1.length();
    len2 = filePath2.length();
    m = len1 - n;
    headerName1 = filePath1.sliced(n, m);

    m  = len2 - n;
    headerName2 = filePath2.sliced(n, m);
  }
  setColumnCount(2);
  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, headerName1);
  headerItem->setText(1, headerName2);
  headerView->resizeSection(0, 200);
}

/*****************************************************************************!
 * Function : ~CommonFileTree
 *****************************************************************************/
CommonFileTree::~CommonFileTree
()
{
}

/*****************************************************************************!
 * Function : GetCommonPrefix
 *****************************************************************************/
QString
CommonFileTree::GetCommonPrefix
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
 * Function : GetExpanded
 *****************************************************************************/
bool
CommonFileTree::GetExpanded(void)
{
  return expanded;
}

/*****************************************************************************!
 * Function : GetDisplayAllItems
 *****************************************************************************/
bool
CommonFileTree::GetDisplayAllItems(void)
{  
  return displayAllItems;
}

/*****************************************************************************!
 * Function : InitializeHeaders
 *****************************************************************************/
void
CommonFileTree::InitializeHeaders(void)
{
  QFileInfo                             fileInfo1(filePath1);
  QFileInfo                             fileInfo2(filePath2);
  QString                               fname1 = fileInfo1.fileName();
  QString                               fname2 = fileInfo2.fileName();
  QTreeWidgetItem*                      headerItem;

  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, fname1);
  headerItem->setText(1, fname2);
  setHeaderItem(headerItem);  
}
