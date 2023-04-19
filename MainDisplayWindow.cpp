/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.cpp
 * DATE         : March 22 2023
 * PROJECT      : CodeCompare
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
#include "MainDisplayWindow.h"
#include "trace.h"
#include "gui.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Function : MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::MainDisplayWindow
() : QWidget()
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(160, 160, 160)));
  setPalette(pal);
  setAutoFillBackground(true);

  Initialize();
}

/*****************************************************************************!
 * Function : ~MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::~MainDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
MainDisplayWindow::Initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
MainDisplayWindow::InitializeSubWindows()
{
  codeWindow1 = NULL;
  codeWindow2 = NULL;
  sourceFileCompareTree = NULL;
  dependencyTreeWindow = NULL;
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
MainDisplayWindow::CreateSubWindows()
{
  QTreeWidgetItem*                      headerItem;

  splitter = new QSplitter(this);

  codeWindow1 = new QTextEdit(this);
  codeWindow2 = new QTextEdit(this);
  sourceFileCompareTree = new QTreeWidget(this);
  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Track 1");
  headerItem->setText(1, "Track 2");
  sourceFileCompareTree->setColumnCount(2);
  sourceFileCompareTree->setHeaderItem(headerItem);
  
  codeWindowContainer1 = new TitledWindow(codeWindow1, QString("Track 2"));
  codeWindowContainer2 = new TitledWindow(codeWindow2, QString("Track 3"));
  sourceFileCompareContainer = new TitledWindow(sourceFileCompareTree, QString("File Comparison"));
  sourceFileCompareTree->resize(300, 100);
  
  splitter->addWidget(sourceFileCompareContainer);
  splitter->addWidget(codeWindowContainer1);
  splitter->addWidget(codeWindowContainer2);

  dependencyTreeWindow = new DependencyTreeWindow();
  dependencyTreeWindow->setParent(this);
  dependencyTreeWindow->hide();

  buildTreeWindow = new BuildTreeWindow();
  buildTreeWindow->setParent(this);
  buildTreeWindow->hide();
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
MainDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   dependencyTreeWindowH;
  int                                   dependencyTreeWindowW;
  int                                   dependencyTreeWindowX;
  int                                   dependencyTreeWindowY;
  int                                   buildTreeWindowH;
  int                                   buildTreeWindowW;
  int                                   buildTreeWindowX;
  int                                   buildTreeWindowY;
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   splitterX, splitterY, splitterW, splitterH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  //!
  splitterX = (GUI_X_GAP);
  splitterY = GUI_Y_GAP;
  splitterW = width - (GUI_X_GAP * 2);
  splitterH = height - (GUI_Y_GAP * 2);
  
  //!
  dependencyTreeWindowX = (GUI_X_GAP);
  dependencyTreeWindowY = GUI_Y_GAP;
  dependencyTreeWindowW = width - (GUI_X_GAP * 2);
  dependencyTreeWindowH = height - (GUI_Y_GAP * 2);

  //!
  buildTreeWindowX = (GUI_X_GAP);
  buildTreeWindowY = GUI_Y_GAP;
  buildTreeWindowW = width - (GUI_X_GAP * 2);
  buildTreeWindowH = height - ((GUI_Y_GAP * 2) + 0);

  //!
  if ( dependencyTreeWindow ) {
    dependencyTreeWindow->move(dependencyTreeWindowX, dependencyTreeWindowY);
    dependencyTreeWindow->resize(dependencyTreeWindowW, dependencyTreeWindowH);
  }

  //!
  if ( splitter ) {
    splitter->move(splitterX, splitterY);
    splitter->resize(splitterW, splitterH);
  }

  //!
  if ( buildTreeWindow ) {
    buildTreeWindow->move(buildTreeWindowX, buildTreeWindowY);
    buildTreeWindow->resize(buildTreeWindowW, buildTreeWindowH);
  }    
}

/*****************************************************************************!
 * Function : SlotCreateDependencyTree
 *****************************************************************************/
void
MainDisplayWindow::SlotCreateDependencyTree(void)
{
  splitter->hide();
  dependencyTreeWindow->show();
}

/*****************************************************************************!
 * Function : SlotDependencyWindowClose
 *****************************************************************************/
void
MainDisplayWindow::SlotDependencyWindowClose(void)
{
  emit SignalDependencyWindowClose();
  splitter->show();
  dependencyTreeWindow->hide();
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
MainDisplayWindow::CreateConnections(void)
{
  connect(dependencyTreeWindow,
          SIGNAL(SignalWindowClose()),
          this,
          SLOT(SlotDependencyWindowClose()));

  connect(dependencyTreeWindow,
          SIGNAL(SignalTreeWindowOpen()),
          this,
          SLOT(SlotBuildTreeWindowOpen()));

  connect(buildTreeWindow,
          SIGNAL(SignalTreeWindowClosed()),
          this,
          SLOT(SlotBuildTreeWindowClosed()));

  connect(dependencyTreeWindow,
          SIGNAL(SignalBuildSystemSelected(BuildSystem*)),
          this,
          SLOT(SlotBuildSystemSelected(BuildSystem*)));

  connect(this,
          SIGNAL(SignalBuildSystemSelected(BuildSystem*)),
          buildTreeWindow,
          SLOT(SlotBuildSystemSelected(BuildSystem*)));
}

/*****************************************************************************!
 * Function : SlotBuildTreeWindowOpen
 *****************************************************************************/
void
MainDisplayWindow::SlotBuildTreeWindowOpen(void)
{
  dependencyTreeWindow->hide();
  buildTreeWindow->show();
}

/*****************************************************************************!
 * Function : SlotBuildTreeWindowClosed
 *****************************************************************************/
void
MainDisplayWindow::SlotBuildTreeWindowClosed(void)
{
  dependencyTreeWindow->show();
  buildTreeWindow->hide();
}

/*****************************************************************************!
 * Function : SlotBuildSystemSelected
 *****************************************************************************/
void
MainDisplayWindow::SlotBuildSystemSelected
(BuildSystem* InSystem)
{
  emit SignalBuildSystemSelected(InSystem);
}

/*****************************************************************************!
 * Function : SetCodeBaseDirectory
 *****************************************************************************/
void
MainDisplayWindow::SetCodeBaseDirectoryName
(QString InCodeBaseDirectoryName)
{
  SlotBuildTreeWindowOpen();
  dependencyTreeWindow->SetCodeBaseDirectoryName(InCodeBaseDirectoryName);
}

/*****************************************************************************!
 * Function : SetTracksDirectoryNames
 *****************************************************************************/
void
MainDisplayWindow::SetTracksDirectoryNames
(QString InTrack1DirectoryName, QString InTrack2DirectoryName)
{
  Track1DirectoryName = InTrack1DirectoryName;
  Track2DirectoryName = InTrack2DirectoryName;

  if ( codeWindowContainer1 ) {
    codeWindowContainer1->SetHeaderText(Track1DirectoryName);
  }
  if ( codeWindowContainer2 ) {
    codeWindowContainer2->SetHeaderText(Track2DirectoryName);
  }
}
