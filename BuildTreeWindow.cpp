/*****************************************************************************
 * FILE NAME    : BuildTreeWindow.cpp
 * DATE         : April 10 2023
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
#include "BuildTreeWindow.h"
#include "BuildTreeItem.h"
#include "gui.h"
#include "trace.h"
#include "BuildLine.h"
#include "BuildCompileLine.h"
#include "BuildARLine.h"
#include "BuildLNLine.h"

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
bool
CompareTopLevelNames
(QString InString1, QString InString2);

/*****************************************************************************!
 * Function : BuildTreeWindow
 *****************************************************************************/
BuildTreeWindow::BuildTreeWindow
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 0, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShadow(QFrame::Sunken);
  setFrameShape(QFrame::Box);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTreeWindow
 *****************************************************************************/
BuildTreeWindow::~BuildTreeWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeWindow::CreateSubWindows()
{
  //! Create the CloseButton button  
  CloseButton = new QPushButton();
  CloseButton->setParent(this);
  CloseButton->setText("Close");
  CloseButton->move(10, 10);
  CloseButton->resize(100,20);
  connect(CloseButton, SIGNAL(pressed()), this, SLOT(SlotCloseButtonPushed()));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTreeWindow::InitializeSubWindows()
{
  QTreeWidgetItem*                      treeHeader;
  treeWidget = new QTreeWidget(this);
  treeWidget->move(GUI_X_GAP, GUI_Y_GAP);

  treeHeader = new QTreeWidgetItem(QStringList(QString("Name")));
  treeWidget->setHeaderItem(treeHeader);

  connect(treeWidget,
          SIGNAL(itemClicked(QTreeWidgetItem*, int)),
          this,
          SLOT(SlotTreeWidgetItemSelected(QTreeWidgetItem*, int)));
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   width34;
  int                                   width14;
  int                                   height;
  QSize                                 size;  
  int                                   width;
  int                                   closeButtonX, closeButtonY;
  int                                   closeButtonW, closeButtonH;
  int                                   treeWidgetW, treeWidgetH;
  int                                   treeWidgetX, treeWidgetY;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();
  width34 = width * 3 / 4;
  width14 = width - width34;
  (void)width14;
  closeButtonW = 60;
  closeButtonH = 20;
  closeButtonX = width - (closeButtonW + GUI_X_GAP);
  closeButtonY = height- (closeButtonH + GUI_Y_GAP);

  treeWidgetX = GUI_X_GAP;
  treeWidgetY = GUI_Y_GAP;
  treeWidgetW = width34 - (GUI_X_GAP * 3);
  treeWidgetH = height - (GUI_Y_GAP * 2);

  treeWidget->move(treeWidgetX, treeWidgetY);
  treeWidget->resize(treeWidgetW, treeWidgetH);
  
  CloseButton->move(closeButtonX, closeButtonY);
  CloseButton->resize(closeButtonW, closeButtonH);
}

/*****************************************************************************!
 * Function : SlotCloseButtonPushed
 *****************************************************************************/
void
BuildTreeWindow::SlotCloseButtonPushed(void)
{
  emit SignalTreeWindowClosed();
}

/*****************************************************************************!
 * Function : SlotBuildSystemSelected
 *****************************************************************************/
void
BuildTreeWindow::SlotBuildSystemSelected
(BuildSystem* InSystem)
{
  BuildElement*                         element;
  BuildElementSet*                      elementSet;
  BuildLine*                            buildLine;
  BuildLine::Type                       buildLineType;
  QString                               st;
  QString                               targetName;
  QStringList                           returnNames;
  BuildTreeItem*                        binaryItem;
  BuildTreeItem*                        cgiItem;
  BuildTreeItem*                        item1;
  BuildTreeItem*                        item2;
  BuildTreeItem*                        item;
  BuildTreeItem*                        sharedObjectsItem;
  BuildTreeItem*                        staticLibItem;
  BuildTreeItem*                        unknownItem;
  int                                   i;
  int                                   j;
  int                                   k;
  int                                   n;

  buildSystem = InSystem;
  returnNames = InSystem->GetTopLevelNames();
  n = returnNames.count();

  std::sort(returnNames.begin(), returnNames.end(), CompareTopLevelNames);

  binaryItem = new BuildTreeItem(QStringList("Binaries"));
  treeWidget->addTopLevelItem(binaryItem);

  staticLibItem = new BuildTreeItem(QStringList("Static Libraries"));
  treeWidget->addTopLevelItem(staticLibItem);

  sharedObjectsItem = new BuildTreeItem(QStringList("Shared Objects"));
  treeWidget->addTopLevelItem(sharedObjectsItem);

  cgiItem = new BuildTreeItem(QStringList("CGI Binaries"));
  treeWidget->addTopLevelItem(cgiItem);

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
        treeWidget->addTopLevelItem(unknownItem);
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
      item1 = new BuildTreeItem(QStringList(element->GetName()));
      item->addChild(item1);
      buildLine = element->GetBuildLine();
      if ( NULL == buildLine ) {
        continue;
      }
      item1->SetBuildLine(buildLine);
      buildLineType = buildLine->GetType();
      if ( buildLineType == BuildLine::TypeCompile ) {
        BuildCompileLine*               compileLine;
        compileLine = (BuildCompileLine*)buildLine;
        targetName = compileLine->GetTarget();
        item2 = new BuildTreeItem(QStringList(targetName));
        item1->addChild(item2);
        continue;
      }
      if ( buildLineType == BuildLine::TypeAR ) {
        BuildARLine*                    ARLine;
        ARLine = (BuildARLine*)buildLine;
        targetName = ARLine->GetTarget();
        item2 = new BuildTreeItem(QStringList(targetName));
        item1->addChild(item2);
        continue;
      }
      if ( buildLineType == BuildLine::TypeLN ) {
        BuildLNLine*                    LNLine;
        LNLine = (BuildLNLine*)buildLine;
        targetName = LNLine->GetTarget();
        item2 = new BuildTreeItem(QStringList(targetName));
        item1->addChild(item2);
        continue;
      }
    }
  }
}

/*****************************************************************************!
 * Function : SlotTreeWidgetItemSelected
 *****************************************************************************/
void
BuildTreeWindow::SlotTreeWidgetItemSelected
(QTreeWidgetItem* InItem, int InColumn)
{
  BuildCompileLine*                     buildCompileLine;
  BuildLine*                            buildLine;
  BuildLine::Type                       type;
  BuildTreeItem*                        item;
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
    sources = buildCompileLine->GetSources();
    foreach (QString st, sources) {
      TRACE_FUNCTION_QSTRING(st);
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
