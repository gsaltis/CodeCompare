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
    displayAllItems = false;
    return;
  }

  displayAllItems = true;
}

/*****************************************************************************!
 * Function : ProcessBuildLines
 *****************************************************************************/
void
BuildTree::ProcessBuildLines
(QString InTrackName, BuildLineSet* InBuildLines)
{
  QStringList                           sources;
  QStringList                           libs;
  BuildCompileLine*                     compileLine;
  BuildARLine*                          arLine;
  QString                               target;
  int                                   i, n;
  BuildTreeItemTop*                     topItem;
  BuildTreeItem*                        mainItem;

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
            ProcessBuildLineSources(InTrackName, topItem, sources, InBuildLines);
            mainItem = (BuildTreeItem*)topItem;
            break;
          }
          if ( suffix == "so" ) {
            ProcessBuildLineSources(InTrackName, buildTreeSharedObject, sources, InBuildLines);
            mainItem = (BuildTreeItem*)buildTreeSharedObject;
            break;
          }
          if ( suffix == "cgi" ) {
            ProcessBuildLineSources(InTrackName, buildTreeCGI, sources, InBuildLines);
            mainItem = (BuildTreeItem*)buildTreeCGI;
            break;
          }
          if ( suffix == "" ) {
            ProcessBuildLineSources(InTrackName, buildTreeBinary, sources, InBuildLines);
            mainItem = (BuildTreeItem*)buildTreeBinary;
            break;
          }
          ProcessBuildLineSources(InTrackName, buildTreeOther, sources, InBuildLines);
          mainItem = (BuildTreeItem*)buildTreeOther;
          break;
        } while(false);
          
        if ( processLibsLines ) {
          libs = compileLine->GetLibraries();
          ProcessBuildLineLibs(InTrackName,mainItem, libs);
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
        ProcessBuildLineSources(InTrackName, topItem, sources, InBuildLines);
        break;
      }
      default :
        break;
    }
  }
  buildTreeBinary->sortChildren(0, Qt::AscendingOrder);
  buildTreeCGI->sortChildren(0, Qt::AscendingOrder);
  buildTreeSharedObject->sortChildren(0, Qt::AscendingOrder);
}

/*****************************************************************************!
 * Function : ProcessBuildLineSources
 *****************************************************************************/
void
BuildTree::ProcessBuildLineSources
(QString InTrackName, BuildTreeItem* InItem, QStringList InSources, BuildLineSet* InLineSet)
{
  QStringList                           sources;
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
      sourceItem = new BuildTreeItemComponent(InTrackName);
      sourceItem->setText(0, s);
      mainItem = (BuildTreeItem*)sourceItem;
      InItem->addChild(sourceItem);
    }
    buildLine = InLineSet->GetLineByTargetName(s);
    if ( buildLine == NULL ) {
      continue;
    }
    if ( buildLine->GetType() == BuildLine::TypeCompile ) {
      BuildCompileLine*                 compileLine;
      compileLine = (BuildCompileLine*)buildLine;
      sources = compileLine->GetSources();
      ProcessBuildLineSecondarySources(InTrackName, mainItem, sources);
    }
  }
}

/*****************************************************************************!
 * Function : ProcessBuildLineSecondarySources
 *****************************************************************************/
void
BuildTree::ProcessBuildLineSecondarySources
(QString InTrackName, BuildTreeItem* InItem, QStringList InSources)
{
  BuildTreeItemComponent*               sourceItem;
  
  if ( InSources.size() == 0 ) {
    return;
  }
  foreach ( auto s, InSources ) {
    sourceItem = new BuildTreeItemComponent(InTrackName);
    
    sourceItem->setText(0, s);
    InItem->addChild(sourceItem);
  }
}

/*****************************************************************************!
 * Function : ProcessBuildLineLibs
 *****************************************************************************/
void
BuildTree::ProcessBuildLineLibs
(QString InTrackName, BuildTreeItem* InItem, QStringList InLibs)
{
  BuildTreeItemComponent*               sourceItem;
  BuildTreeItemSubSection*              subSection;
  
  if ( InLibs.size() == 0 ) {
    return;
  }

  subSection = new BuildTreeItemSubSection("Libs");
  InItem->addChild(subSection);
  
  foreach ( auto s, InLibs ) {
    sourceItem = new BuildTreeItemComponent(InTrackName);

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
  QString                               trackName;
  BuildTreeItemComponent*               component;
  item = (BuildTreeItem*)InItem;

  if ( item->GetType() != BuildTreeItem::Type::Component ) {
    return;
  }
  component = (BuildTreeItemComponent*)item;
  trackName = component->GetTrackName();
}


  
