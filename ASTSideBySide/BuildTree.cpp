/*****************************************************************************
 * FILE NAME    : BuildTree.cpp
 * DATE         : May 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTree.h"
#include "trace.h"
#include "BuildLine.h"
#include "BuildCompileLine.h"
#include "BuildARLine.h"
#include "BuildTreeItem.h"
#include "BuildTreeItemSection.h"
#include "BuildTreeItemSubSection.h"
#include "BuildTreeItemTop.h"
#include "BuildTreeItemComponent.h"

/*****************************************************************************!
 * Function : BuildTree
 *****************************************************************************/
BuildTree::BuildTree
(QString InFilePath1, QString InFilePath2) : CommonFileTree(InFilePath1, InFilePath2)
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setColumnCount(2);
  totalFiles = 0;
  changedFiles = 0;
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTree
 *****************************************************************************/
BuildTree::~BuildTree
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTree::initialize()
{
  processLibsLines = false;
  displayIntermediateFiles = false;
  expanded = false;
  displayAllItems = true;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTree::CreateSubWindows()
{
  buildTreeBinary = new BuildTreeItemSection("Binary");
  buildTreeCGI = new BuildTreeItemSection("CGI");
  buildTreeSharedObject = new BuildTreeItemSection("Shared Object");
  buildTreeOther = new BuildTreeItemSection("Other");
  addTopLevelItem(buildTreeBinary);
  addTopLevelItem(buildTreeSharedObject);
  addTopLevelItem(buildTreeCGI);
  addTopLevelItem(buildTreeOther);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTree::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTree::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : SlotToggleTreeView
 *****************************************************************************/
void
BuildTree::SlotToggleTreeView(void)
{
  int                                   i;
  int                                   n;

  n = topLevelItemCount();
  if ( expanded ) {
    expanded = false;
    for (i = 0; i < n; i++) {
      BuildTreeItem*                    item;
      item = (BuildTreeItem*)topLevelItem(i);
      item->CollapseChildren();
    }
    return;
  }
  for (i = 0; i < n; i++) {
    BuildTreeItem*                    item;
    item = (BuildTreeItem*)topLevelItem(i);
    item->ExpandChildren();
  }
  expanded = true;
}

/*****************************************************************************!
 * Function : SlotToggleChangedItems
 *****************************************************************************/
void
BuildTree::SlotToggleChangedItems
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
 * Function : ProcessBuildLines
 *****************************************************************************/
void
BuildTree::ProcessBuildLines
(QString , BuildLineSet* InBuildLines)
{
  QList<CompileSourceLine*>             sources;
  QStringList                           libs;
  BuildCompileLine*                     compileLine;
  BuildARLine*                          arLine;
  QString                               target;
  int                                   i, n;
  BuildTreeItemTop*                     topItem;
  BuildTreeItem*                        mainItem;
  QString                               fullFileName;

  n = InBuildLines->GetLineCount();

  for (i = 0; i < n; i++) {
    BuildLine*                          line;

    line = InBuildLines->GetLineByIndex(i);
    switch ( line->GetType() ) {
      case BuildLine::TypeCompile : {
        compileLine = (BuildCompileLine*)line;
        sources = compileLine->GetSources();
        target = compileLine->GetTarget();
        if ( compileLine->GetIsTargetObject() ) {
          break;
        }
        fullFileName = compileLine->GetFullFileName();
        do {
          QFileInfo                       info(target);
          QString                         suffix;
          
          suffix = info.suffix();
          if ( true ) {
            topItem = new BuildTreeItemTop();
            topItem->setText(0, target);
            if ( suffix == "so" ) {
              if ( !buildTreeSharedObject->ElementExists(target) ) {
                buildTreeSharedObject->addChild(topItem);
              }
              buildTreeSharedObject->addChild(topItem);
            } else if ( suffix == "cgi" ) {
              if ( !buildTreeCGI->ElementExists(target) ) {
                buildTreeCGI->addChild(topItem);
              }
            } else if ( suffix == "" ) {
              if ( !buildTreeBinary->ElementExists(target) ) {
                buildTreeBinary->addChild(topItem);
              }
            } else {
              addTopLevelItem(topItem);
            }
            ProcessBuildLineSources(fullFileName, topItem, sources, InBuildLines);
            mainItem = (BuildTreeItem*)topItem;
            break;
          }
          if ( suffix == "so" ) {
            ProcessBuildLineSources(fullFileName, buildTreeSharedObject, sources, InBuildLines);
            mainItem = (BuildTreeItem*)buildTreeSharedObject;
            break;
          }
          if ( suffix == "cgi" ) {
            ProcessBuildLineSources(fullFileName, buildTreeCGI, sources, InBuildLines);
            mainItem = (BuildTreeItem*)buildTreeCGI;
            break;
          }
          if ( suffix == "" ) {
            ProcessBuildLineSources(fullFileName, buildTreeBinary, sources, InBuildLines);
            mainItem = (BuildTreeItem*)buildTreeBinary;
            break;
          }
          ProcessBuildLineSources(fullFileName, buildTreeOther, sources, InBuildLines);
          mainItem = (BuildTreeItem*)buildTreeOther;
          break;
        } while(false);
          
        if ( processLibsLines ) {
          libs = compileLine->GetLibraries();
          ProcessBuildLineLibs(fullFileName,mainItem, libs);
        }
        break;
      }
      case BuildLine::TypeAR : {
        arLine = (BuildARLine*)line;
        target = arLine->GetTarget();
        sources = arLine->GetSources();
        topItem = new BuildTreeItemTop();
        topItem->setText(0, target);
        buildTreeOther->addChild(topItem);
        ProcessBuildLineSources(fullFileName, topItem, sources, InBuildLines);
        break;
      }
      default :
        break;
    }
  }
  buildTreeBinary->sortChildren(0, Qt::AscendingOrder);
  buildTreeCGI->sortChildren(0, Qt::AscendingOrder);
  buildTreeSharedObject->sortChildren(0, Qt::AscendingOrder);
  emit SignalFileCountsChanged(totalFiles, changedFiles);
}

/*****************************************************************************!
 * Function : ProcessBuildLineSources
 *****************************************************************************/
void
BuildTree::ProcessBuildLineSources
(QString InFullFileName, BuildTreeItem* InItem, QList<CompileSourceLine*> InSources, BuildLineSet* InLineSet)
{
  QString                               st;
  QList<CompileSourceLine*>             sources;
  BuildLine*                            buildLine;
  BuildTreeItemComponent*               sourceItem;
  BuildTreeItem*                        mainItem;
#if 0
  BuildTreeItemSubSection*              subSection;
#endif

  if ( InSources.size() == 0 ) {
    return;
  }
#if 0
  subSection = new BuildTreeItemSubSection("Sources");
  InItem->addChild(subSection);
#endif  
  foreach ( auto s, InSources ) {
    mainItem = InItem;
    if ( displayIntermediateFiles ) {
      st = s->GetFullSourceFileName();
      sourceItem = new BuildTreeItemComponent(st);
      totalFiles++;
      changedFiles += sourceItem->GetChanged() ? 1 : 0;
      
      sourceItem->setText(0, s->GetSourceFileName());
      mainItem = (BuildTreeItem*)sourceItem;
      InItem->addChild(sourceItem);
    }
    buildLine = InLineSet->GetLineByTargetName(s->GetSourceFileName());
    if ( buildLine == NULL ) {
      continue;
    }
    if ( buildLine->GetType() == BuildLine::TypeCompile ) {
      BuildCompileLine*                 compileLine;
      compileLine = (BuildCompileLine*)buildLine;
      sources = compileLine->GetSources();
      ProcessBuildLineSecondarySources(InFullFileName, mainItem, sources);
    }
  }
}

/*****************************************************************************!
 * Function : ProcessBuildLineSecondarySources
 *****************************************************************************/
void
BuildTree::ProcessBuildLineSecondarySources
(QString, BuildTreeItem* InItem, QList<CompileSourceLine*> InSources)
{
  BuildTreeItemComponent*               sourceItem;

  if ( InSources.size() == 0 ) {
    return;
  }
  foreach ( auto s, InSources ) {
    sourceItem = new BuildTreeItemComponent(s->GetFullSourceFileName());
    totalFiles++;
    changedFiles += sourceItem->GetChanged() ? 1 : 0;
    sourceItem->setText(0, s->GetSourceFileName());
    InItem->addChild(sourceItem);
  }
}

/*****************************************************************************!
 * Function : ProcessBuildLineLibs
 *****************************************************************************/
void
BuildTree::ProcessBuildLineLibs
(QString, BuildTreeItem* InItem, QStringList InLibs)
{
  BuildTreeItemComponent*               sourceItem;
  BuildTreeItemSubSection*              subSection;
  
  if ( InLibs.size() == 0 ) {
    return;
  }

  subSection = new BuildTreeItemSubSection("Libs");
  InItem->addChild(subSection);
  
  foreach ( auto s, InLibs ) {
    sourceItem = new BuildTreeItemComponent(s);
    totalFiles++;
    changedFiles += sourceItem->GetChanged() ? 1 : 0;

    if ( InItem->Contains(s) ) {
      continue;
    }
    sourceItem->setText(0, s);
    subSection->addChild(sourceItem);
  }
  subSection->sortChildren(0, Qt::AscendingOrder);
}
  
/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BuildTree::CreateConnections
()
{
  connect(this, QTreeWidget::itemClicked, this, BuildTree::SlotFileSelected);
}

/*****************************************************************************!
 * Function : SlotFileSelected
 *****************************************************************************/
void
BuildTree::SlotFileSelected
(QTreeWidgetItem* InItem, int )
{
  BuildTreeItem*                        item;
  QString                               fullFileName;
  BuildTreeItemComponent*               component;
  QString                               st;
  
  item = (BuildTreeItem*)InItem;

  if ( item->GetType() != BuildTreeItem::Type::Component ) {
    return;
  }
  component = (BuildTreeItemComponent*)item;
  fullFileName = component->GetFullFileName();

  st = track1.RemoveLeadingBasePath(fullFileName);
  
  emit SignalFileSelected(st);
}

/*****************************************************************************!
 * Function : ShowChangedItems
 *****************************************************************************/
void
BuildTree::ShowChangedItems(void)
{
  int                                   i, n;
  BuildTreeItemTop*                     dirItem;
  QTreeWidgetItem*                      item;
  
  n = topLevelItemCount();

  for (i = 0; i < n; i++) {
    item = topLevelItem(i);
    dirItem = (BuildTreeItemTop*)item;

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
BuildTree::DirChanged
(BuildTreeItem* InBuildItem)
{
  int                                   i, n;
  bool                                  c;
  bool                                  rvalue;

  rvalue = false;
  n = InBuildItem->childCount();
  
  for ( i = 0 ; i < n ; i++ ) {
    BuildTreeItem*                      item;
    item = (BuildTreeItem*)InBuildItem->child(i);
    BuildTreeItem::Type                 t = item->GetType();
    if ( t == BuildTreeItem::Type::Top || t == BuildTreeItem::Type::Section ) {
      c = DirChanged(item);
      if ( c ) {
        rvalue = true;
      }
      item->setHidden(!c);
      continue;
    }
    if ( item->GetType() == BuildTreeItem::Type::Component ) {
      BuildTreeItemComponent*           componentItem;
      componentItem = (BuildTreeItemComponent*)item;
      c = componentItem->GetChanged();
      if ( c ) {
        rvalue = true;
      }
      componentItem->setHidden(!c);
    }
  }
  return rvalue;
}

/*****************************************************************************!
 * Function : ShowAllItems
 *****************************************************************************/
void
BuildTree::ShowAllItems
()
{
  QTreeWidgetItem*                      item;
  int                                   i, n;
  BuildTreeItem*                        buildItem;
  
  n = topLevelItemCount();

  for (i = 0; i < n; i++) {
    item = topLevelItem(i);
    buildItem = (BuildTreeItem*)item;
    ShowAllDirItems(buildItem);
  }
}

/*****************************************************************************!
 * Function : ShowAllDirItems
 *****************************************************************************/
void
BuildTree::ShowAllDirItems
(BuildTreeItem* InItem)
{
  int                                   i, n;
  QTreeWidgetItem*                      item;
  BuildTreeItem*                        buildItem;
  BuildTreeItem::Type                   t;

  n = InItem->childCount();

  for (i = 0; i < n; i++) {
    item = InItem->child(i);
    buildItem = (BuildTreeItem*)item;
    t = buildItem->GetType();
    if ( t == BuildTreeItem::Type::Top || t == BuildTreeItem::Type::Section ) {
      ShowAllDirItems(buildItem);
    }
    item->setHidden(false);
  }
}

/*****************************************************************************!
 * Function : RemoveLeadingBasePath1
 *****************************************************************************/
QString
BuildTree::RemoveLeadingBasePath1
(QString InFullFileName)
{
  return track1.RemoveLeadingBasePath(InFullFileName);
}

