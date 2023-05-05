/*****************************************************************************
 * FILE NAME    : BuildSystemTree.cpp
 * DATE         : May 04 2023
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
#include "BuildSystemTree.h"
#include "BuildTreeItem.h"
#include "BuildElement.h"
#include "BuildElementSet.h"
#include "BuildCompileLine.h"

/*****************************************************************************!
 * 
 *****************************************************************************/
static bool
CompareTopLevelNames
(QString InString1, QString InString2);

/*****************************************************************************!
 * Function : BuildSystemTree
 *****************************************************************************/
BuildSystemTree::BuildSystemTree
() : QTreeWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildSystemTree
 *****************************************************************************/
BuildSystemTree::~BuildSystemTree
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildSystemTree::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildSystemTree::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildSystemTree::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildSystemTree::resizeEvent
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
 * Function : SetBuildSystem
 *****************************************************************************/
void
BuildSystemTree::SetBuildSystem
(BuildSystem* InBuildSystem)
{
  buildSystem = InBuildSystem;
  Populate();
  connect(this,
          SIGNAL(itemClicked(QTreeWidgetItem*, int)),
          this,
          SLOT(SlotTreeWidgetItemSelected(QTreeWidgetItem*, int)));
}

/*****************************************************************************!
 * Function : Populate
 *****************************************************************************/
void
BuildSystemTree::Populate
()
{
  BuildElement*                         element;
  BuildElementSet*                      childSet;
  BuildElementSet*                      elementSet;
  BuildLine*                            buildLine;
  BuildTreeItem*                        binaryItem;
  BuildTreeItem*                        cgiItem;
  BuildTreeItem*                        item1;
  BuildTreeItem*                        item2;
  BuildTreeItem*                        item;
  BuildTreeItem*                        sharedObjectsItem;
  BuildTreeItem*                        staticLibItem;
  BuildTreeItem*                        unknownItem;
  QString                               st2;
  QString                               st;
  QString                               targetName;
  QStringList                           returnNames;
  int                                   i;
  int                                   j;
  int                                   k;
  int                                   n;

  returnNames = buildSystem->GetTopLevelNames();
  n = returnNames.count();

  std::sort(returnNames.begin(), returnNames.end(), CompareTopLevelNames);

  binaryItem = new BuildTreeItem(QStringList("Binaries"));
  addTopLevelItem(binaryItem);

  staticLibItem = new BuildTreeItem(QStringList("Static Libraries"));
  addTopLevelItem(staticLibItem);

  sharedObjectsItem = new BuildTreeItem(QStringList("Shared Objects"));
  addTopLevelItem(sharedObjectsItem);

  cgiItem = new BuildTreeItem(QStringList("CGI Binaries"));
  addTopLevelItem(cgiItem);

  unknownItem = NULL;

  for ( i = 0; i < n ; i++ ) {
    st = returnNames[i];
    item = new BuildTreeItem(QStringList(st));
    elementSet = buildSystem->GetBuildElementByName(st);

    QFileInfo fileInfo(st);
    QString suffix = fileInfo.suffix();
    if ( suffix == QString("so") ) {
      sharedObjectsItem->addChild(item);
    } else if ( suffix == QString("a") ) {
      staticLibItem->addChild(item);
    } else if ( suffix == QString("cgi") ) {
      cgiItem->addChild(item);
    } else if ( suffix == QString("") ) {
      binaryItem->addChild(item);
    } else {
      if ( unknownItem == NULL ) {
        unknownItem = new BuildTreeItem(QStringList("Unknown"));
        addTopLevelItem(unknownItem);
      }   
      unknownItem->addChild(item);
    }
    if ( NULL == elementSet ) {
      continue;
    }
    j = elementSet->GetElementCount();
    
    //!
    for ( k = 0 ; k < j ; k++ ) {
      element = elementSet->GetElementByIndex(k);
      if ( NULL == element ) {
        continue;
      }
      st2 = element->GetName();
      item1 = new BuildTreeItem(QStringList(st2));
      item->addChild(item1);
      childSet = buildSystem->GetBuildElementByName(st2);
      if ( NULL == childSet ) {
        printf("Missing %s\n", st.toStdString().c_str());
        continue;
      }

      // Create the actual source files elements
      for ( int i2 = 0 ; i2 < childSet->GetElementCount(); i2++ ) {
        BuildElement* element = childSet->GetElementByIndex(i2);
        QString elementName = element->GetName();
        item2 = new BuildTreeItem(QStringList(elementName));
        item1->addChild(item2);
        buildLine = element->GetBuildLine();
        if ( NULL == buildLine ) {
          continue;
        }
        item2->SetBuildLine(buildLine);
      }
    }
  }
}

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
bool
CompareTopLevelNames
(QString InString1, QString InString2)
{
  QString                               base1;
  QString                               base2;
  QString                               suffix1;
  QString                               suffix2;
  QFileInfo                             info1;
  QFileInfo                             info2;
  bool                                  b;
    
  info1.setFile(InString1);
  info2.setFile(InString2);

  base1 = info1.completeBaseName();
  suffix1 = info1.suffix();

  base2 = info2.completeBaseName();
  suffix2 = info2.suffix();

  do {
    
    if ( suffix1.isEmpty() && suffix2.isEmpty() ) {
      b = base1 < base2;
      break;
    }
    if ( suffix1.isEmpty() ) {
      b = true;
      break;
    }
    if ( suffix2.isEmpty() ) {
      b = false;
      break;
    }

    if ( suffix1 == suffix2 ) {
      b = base1 < base2;
      break;
    }
    b = suffix1 < suffix2;
  } while (false);
  return b;
}

/*****************************************************************************!
 * Function : SlotTreeItemSelected
 *****************************************************************************/
void
BuildSystemTree::SlotTreeWidgetItemSelected
(QTreeWidgetItem* InItem, int InColumn)
{
  BuildCompileLine*                     buildCompileLine;
  BuildLine*                            buildLine;
  BuildLine::Type                       type;
  BuildTreeItem*                        item;
  QString                               fileName;
  QString                               filePath;
  QStringList                           sources;

  (void)InColumn;

  item = (BuildTreeItem*)InItem;
  buildLine = item->GetBuildLine();
  if ( NULL == buildLine ) {
    return;
  }
  type = buildLine->GetType();
  if ( type == BuildLine::TypeCompile ) {
    buildCompileLine = (BuildCompileLine*)buildLine;
    filePath = buildCompileLine->GetFilePath();
    sources = buildCompileLine->GetSources();
    foreach (QString st, sources) {
      fileName = filePath + QString("/") + st;
      emit SignalBuildTreeItemSelected(buildLine, fileName);
    }
  }
}
