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
#include "CodeHighlighter.h"

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
  setWindowTitle("BuildTreeWindow");
  pal.setBrush(QPalette::Window, QBrush(QColor(224, 224, 224)));
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
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeWindow::CreateSubWindows()
{
  QPalette                              pal;
  QTreeWidgetItem*                      treeHeader;
  QFont                                 font;
  QColor                                fileDisplayBackground = QColor(224, 224, 224);
  
  //! Create the CloseButton button  
  CloseButton = new QPushButton();
  CloseButton->setParent(this);
  CloseButton->setText("Close");
  CloseButton->move(10, 10);
  CloseButton->resize(100,20);
  connect(CloseButton, SIGNAL(pressed()), this, SLOT(SlotCloseButtonPushed()));

  splitter = new QSplitter(this);
  treeWidget = new QTreeWidget(this);

  treeHeader = new QTreeWidgetItem(QStringList(QString("Name")));
  treeWidget->setHeaderItem(treeHeader);

  fileTabPane = new QTabWidget();
  fileTabContainer = new TitledWindow(fileTabPane, QString(""));
  fileTabContainer->setParent(this);

  font = QFont();
  font.setBold(true);
  fileTabContainer->SetHeaderFont(font);
  
  fileDisplay = new QTextEdit(this);
  fileDisplay->setFont(QFont("Courier", 9));
  SetFileDisplayTabWidth(4);
  codeHighlighter = new CodeHighlighter(fileDisplay->document());

  pal = fileDisplay->palette();
  pal.setBrush(QPalette::Base, QBrush(fileDisplayBackground));
  fileDisplay->setPalette(pal);
  fileDisplay->setAutoFillBackground(true);
  
  jsonDisplay = new BuildTreeJSONCodeContainer();
  hierarchyDisplay = new BuildTreeHierarchyContainer();
  
  fileTabPane->addTab(fileDisplay, QString("Code Text"));
  fileTabPane->addTab(jsonDisplay, QString("JSON"));
  fileTabPane->addTab(hierarchyDisplay, QString("Hierarchy"));

  compilerOptionsTree = new QTreeWidget();
  compilerOptionsWindow = new TitledWindow(compilerOptionsTree, QString("Compiler Options"));
  
  splitter->addWidget(treeWidget);
  splitter->addWidget(fileTabContainer);
  splitter->addWidget(compilerOptionsWindow);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTreeWindow::InitializeSubWindows()
{

}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BuildTreeWindow::CreateConnections()
{
  connect(treeWidget,
          SIGNAL(itemClicked(QTreeWidgetItem*, int)),
          this,
          SLOT(SlotTreeWidgetItemSelected(QTreeWidgetItem*, int)));

  connect(this,
          SIGNAL(SignalTreeItemSelected(BuildLine*, QString)),
          hierarchyDisplay,
          SLOT(SlotTreeItemSelected(BuildLine*, QString)));

  connect(this,
          SIGNAL(SignalTreeItemSelected(BuildLine*, QString)),
          jsonDisplay,
          SLOT(SlotTreeItemSelected(BuildLine*, QString)));
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   height;
  QSize                                 size;  
  int                                   width;
  int                                   closeButtonX, closeButtonY;
  int                                   closeButtonW, closeButtonH;
  int                                   splitterX, splitterY, splitterW, splitterH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  closeButtonW = 60;
  closeButtonH = 20;
  closeButtonX = width - (closeButtonW + GUI_X_GAP);
  closeButtonY = height- (closeButtonH + GUI_Y_GAP);

  splitterX = GUI_X_GAP;
  splitterY = GUI_Y_GAP;
  splitterW = width - (GUI_X_GAP * 2);
  splitterH = height - (GUI_Y_GAP + 50);

  splitter->move(splitterX, splitterY);
  splitter->resize(splitterW, splitterH);
  
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
      DisplayFileText(fileName);
      fileTabContainer->SetHeaderText(fileName);
      emit SignalTreeItemSelected(buildLine, fileName);
      PopulateCompileOptions(buildCompileLine);
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
 * Function : DisplayFileText
 *****************************************************************************/
void
BuildTreeWindow::DisplayFileText
(QString InFilename)
{
  QString                               st;
  QByteArray                            ba;
  QFile                                         file(InFilename);

  fileDisplay->setText(QString(""));

  if ( ! file.exists() ) {
    return;
  }

  file.open(QIODeviceBase::ReadOnly);
  ba = file.readAll();
  st = QString(ba);
  fileDisplay->setText(st);
  file.close();
}

/*****************************************************************************!
 * Function : SetFileDisplayTabWidth
 *****************************************************************************/
void
BuildTreeWindow::SetFileDisplayTabWidth
(int InTabWidth)
{
  QFont                                 font;
  font = fileDisplay->font();
  QFontMetrics                          fm(font);
  int width = fm.averageCharWidth();
  fileDisplay->setTabStopDistance(InTabWidth * width);
  fileDisplayTabWidth = InTabWidth;
}

/*****************************************************************************!
 * Function : PopulateCompileOptions
 *****************************************************************************/
void
BuildTreeWindow::PopulateCompileOptions
(BuildCompileLine* InCompileLine)
{
  QTreeWidgetItem*                      treeItem;
  QStringList                           flags;
  
  compilerOptionsTree->clear();

  flags = InCompileLine->GetFlags();
  foreach (auto flag, flags) {
    treeItem = new QTreeWidgetItem();
    treeItem->setText(0, flag);
    compilerOptionsTree->addTopLevelItem(treeItem);
  }
}
