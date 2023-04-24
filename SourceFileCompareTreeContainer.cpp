/*****************************************************************************
 * FILE NAME    : SourceFileCompareTreeContainer.cpp
 * DATE         : April 24 2023
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
#include "SourceFileCompareTreeContainer.h"
#include "FileTreeWidgetItem.h"
#include "trace.h"

/*****************************************************************************!
 * Function : SourceFileCompareTreeContainer
 *****************************************************************************/
SourceFileCompareTreeContainer::SourceFileCompareTreeContainer
(TitledWindow* InSourceTreeWindow, QTreeWidget* InSourceTree) : QWidget()
{
  sourceFileCompareTree = InSourceTreeWindow;
  sourceTree = InSourceTree;
  sourceFileCompareTree->setParent(this);
  displayStatsWindow = false;
  displayAnalyzeStatsWindow = false;
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~SourceFileCompareTreeContainer
 *****************************************************************************/
SourceFileCompareTreeContainer::~SourceFileCompareTreeContainer
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SourceFileCompareTreeContainer::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SourceFileCompareTreeContainer::CreateSubWindows()
{
  statsWindow = new SourceFileCompareStatsWindow();
  statsWindow->setParent(this);
  statsAnalyzeWindow = new SourceFileCompareAnalyzeStatsWindow();
  statsAnalyzeWindow->setParent(this);
  statsAnalyzeWindow->hide();
  if ( ! displayStatsWindow ) {
    statsWindow->hide();
  }
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SourceFileCompareTreeContainer::InitializeSubWindows()
{
  statsWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SourceFileCompareTreeContainer::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;
  size = InEvent->size();

  SetSize(size);
}

/*****************************************************************************!
 * Function : SetSize
 *****************************************************************************/
void
SourceFileCompareTreeContainer::SetSize
(QSize InSize)
{
  int                                   width;
  int                                   height;
  int                                   sourceFileCompareTreeX, sourceFileCompareTreeY;
  int                                   sourceFileCompareTreeW, sourceFileCompareTreeH;
  int                                   statsWindowX, statsWindowY;
  int                                   statsWindowW, statsWindowH;
  int                                   statsAnalyzeWindowX, statsAnalyzeWindowY;
  int                                   statsAnalyzeWindowW, statsAnalyzeWindowH;
  
  width = InSize.width();
  height = InSize.height();

  sourceFileCompareTreeH = height;
  statsWindowX = 0;
  statsWindowW = width;
  statsWindowH = 0;
  if ( displayStatsWindow ) {
    statsWindowH = SOURCE_FILE_COMPARE_STATS_WINDOW_HEIGHT;
    sourceFileCompareTreeH = height - statsWindowH;
  }
  statsWindowY = height - statsWindowH;

  statsAnalyzeWindowX = 0;
  statsAnalyzeWindowW = width;
  statsAnalyzeWindowH = 0;
  if ( displayAnalyzeStatsWindow ) {
    statsAnalyzeWindowH = SOURCE_FILE_COMPARE_STATS_WINDOW_HEIGHT;
    sourceFileCompareTreeH = height - statsAnalyzeWindowH;
  }
  statsAnalyzeWindowY = height - statsAnalyzeWindowH;
  
  sourceFileCompareTreeX = 0;
  sourceFileCompareTreeY = 0;
  sourceFileCompareTreeW = width;
  
  if ( sourceFileCompareTree ) {
    sourceFileCompareTree->move(sourceFileCompareTreeX, sourceFileCompareTreeY);
    sourceFileCompareTree->resize(sourceFileCompareTreeW, sourceFileCompareTreeH);
  }
  if ( displayStatsWindow ) {
    statsWindow->move(statsWindowX, statsWindowY);
    statsWindow->resize(statsWindowW, statsWindowH);
  } else if ( displayAnalyzeStatsWindow ) {
    statsAnalyzeWindow->move(statsAnalyzeWindowX, statsAnalyzeWindowY);
    statsAnalyzeWindow->resize(statsAnalyzeWindowW, statsAnalyzeWindowH);
  }
}

/*****************************************************************************!
 * Function : GetDisplayStatsWindow
 *****************************************************************************/
bool
SourceFileCompareTreeContainer::GetDisplayStatsWindow(void)
{
  return displayStatsWindow;
}

/*****************************************************************************!
 * Function : GetDisplayAnalyzeStatsWindow
 *****************************************************************************/
bool
SourceFileCompareTreeContainer::GetDisplayAnalyzeStatsWindow(void)
{
  TRACE_FUNCTION_START();
  TRACE_FUNCTION_BOOL(displayAnalyzeStatsWindow);
  TRACE_FUNCTION_END();
  return displayAnalyzeStatsWindow;
}

/*****************************************************************************!
 * Function : SetDisplayStatsWindow
 *****************************************************************************/
void
SourceFileCompareTreeContainer::SetDisplayStatsWindow
(bool InDisplayStatsWindow)
{
  displayStatsWindow = InDisplayStatsWindow;
  displayAnalyzeStatsWindow = false;
  statsAnalyzeWindow->hide();
  if ( displayStatsWindow ) {
    statsWindow->show();
    statsWindow->SetFileCount(GetFileCount());
    statsWindow->SetFileDifferCount(GetFileDifferCount());
    statsWindow->SetFileSourceCount(GetSourceFileCount());
    } else {
    statsWindow->hide();
  }
  SetSize(size());
}

/*****************************************************************************!
 * Function : SetDisplayAnalyzeStatsWindow
 *****************************************************************************/
void
SourceFileCompareTreeContainer::SetDisplayAnalyzeStatsWindow
(bool InDisplayAnalyzeStatsWindow)
{
  TRACE_FUNCTION_START();
  TRACE_FUNCTION_BOOL(InDisplayAnalyzeStatsWindow);
  displayAnalyzeStatsWindow = InDisplayAnalyzeStatsWindow;
  displayStatsWindow = false;
  statsWindow->hide();
  statsAnalyzeWindow->show();
  if ( displayAnalyzeStatsWindow ) {
    TRACE_FUNCTION_LOCATION();
    statsAnalyzeWindow->show();
    statsAnalyzeWindow->SetFileCount(GetFileCount());
    statsAnalyzeWindow->SetFileDifferCount(GetFileDifferCount());
    statsAnalyzeWindow->SetFileSourceCount(GetSourceFileCount());
    } else {
    statsAnalyzeWindow->hide();
  }
  SetSize(size());
  TRACE_FUNCTION_END();
}

/*****************************************************************************!
 * Function : GetFileCount
 *****************************************************************************/
int
SourceFileCompareTreeContainer::GetFileCount(void)
{
  FileTreeWidgetItem*                   item;
  int                                   count;
  
  item = (FileTreeWidgetItem*)sourceTree->topLevelItem(0);
  count = 0;

  GetItemFileCount(item, count);
  return count;
}

/*****************************************************************************!
 * Function : GetItemFileCount
 *****************************************************************************/
void
SourceFileCompareTreeContainer::GetItemFileCount // 
(FileTreeWidgetItem* InItem, int &InCount)
{
  int                                   i;
  int                                   n;
  QFileInfo                             fileInfo;
  
  if ( !InItem->GetIsDirectory() ) {
    TRACE_FUNCTION_LOCATION();
    InCount++;
    return;
  }

  n = InItem->childCount();
  for ( i = 0 ; i < n ; i++ ) {
    FileTreeWidgetItem*                 item;

    item = (FileTreeWidgetItem*)InItem->child(i);
    if ( item->GetIsDirectory() ) {
      GetItemFileCount(item, InCount);
      continue;
    }
    QFileInfo fileInfo;
    fileInfo.setFile(item->GetFileName1());
    InCount++;
  }
}

/*****************************************************************************!
 * Function : GetFileDifferCount
 *****************************************************************************/
int
SourceFileCompareTreeContainer::GetFileDifferCount(void)
{
  FileTreeWidgetItem*                   item;
  int                                   count;

  item = (FileTreeWidgetItem*)sourceTree->topLevelItem(0);
  count = 0;

  GetItemFileDifferCount(item, count);
  return count;
}

/*****************************************************************************!
 * Function : GetItemFileDifferCount
 *****************************************************************************/
void
SourceFileCompareTreeContainer::GetItemFileDifferCount
(FileTreeWidgetItem* InItem, int &InCount)
{
  int                                   i;
  int                                   n;

  if ( !InItem->GetIsDirectory() ) {
    if ( InItem->GetFilesDiffer() ) {
      InCount++;
    }
    return;
  }
  
  n = InItem->childCount();
  for ( i = 0 ; i < n ; i++ ) {
    FileTreeWidgetItem*                 item;

    item = (FileTreeWidgetItem*)InItem->child(i);
    if ( item->GetIsDirectory() ) {
      GetItemFileDifferCount(item, InCount);
      continue;
    }
    if ( item->GetFilesDiffer() ) {
      InCount++;
    }
  }
}

/*****************************************************************************!
 * Function : SetFileTreeItem
 *****************************************************************************/
void
SourceFileCompareTreeContainer::SetFileTreeItem
(FileTreeWidgetItem* InItem)
{
  statsWindow->SetFileItem(InItem);
  statsAnalyzeWindow->SetFileItem(InItem);
}

/*****************************************************************************!
 * Function : GetSourceFileCount
 *****************************************************************************/
int
SourceFileCompareTreeContainer::GetSourceFileCount(void)
{
  FileTreeWidgetItem*                   item;
  int                                   count;
  
  item = (FileTreeWidgetItem*)sourceTree->topLevelItem(0);
  count = 0;

  GetItemSourceFileCount(item, count);
  return count;
}

/*****************************************************************************!
 * Function : GetItemSourceFileCount
 *****************************************************************************/
void
SourceFileCompareTreeContainer::GetItemSourceFileCount // 
(FileTreeWidgetItem* InItem, int &InCount)
{
  int                                   i;
  int                                   n;
  QFileInfo                             fileInfo;
  QString                               suffix;
  
  n = InItem->childCount();
  for ( i = 0 ; i < n ; i++ ) {
    FileTreeWidgetItem*                 item;

    item = (FileTreeWidgetItem*)InItem->child(i);
    if ( item->GetIsDirectory() ) {
      GetItemSourceFileCount(item, InCount);
      continue;
    }
    QFileInfo fileInfo;
    fileInfo.setFile(item->GetFileName1());
    suffix = fileInfo.suffix();
    if ( suffix == "h" || suffix == "c" ) {
      InCount++;
    }
  }
}

