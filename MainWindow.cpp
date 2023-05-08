/*****************************************************************************
 * FILE NAME    : MainWindow.cpp
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
#include <QMenuBar>
#include <QStatusBar>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainWindow.h"
#include "CodeBaseOpenDialog.h"
#include "trace.h"

/*****************************************************************************!
 * Function : MainWindow
 *****************************************************************************/
MainWindow::MainWindow
(QString InTrack1DirectoryName, QString InTrack2DirectoryName, bool InStartAnalysis) 
{
  track1DirectoryName = InTrack1DirectoryName;
  track2DirectoryName = InTrack2DirectoryName;
  Initialize();
  CreateActions();
  CreateMenus();
  InitializeSubWindows();
  CreateSubWindows();
  CreateConnections();
  if ( InStartAnalysis ) {
    StartAnalysis();
  }
}

/*****************************************************************************!
 * Function : ~MainWindow
 *****************************************************************************/
MainWindow::~MainWindow
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
MainWindow::Initialize()
{
  setWindowTitle(SystemConfig::SystemName);  
}

/*****************************************************************************!
 * Function : CreateSubWindows
 * Purpose  : Create Sub Windows
 *****************************************************************************/
void
MainWindow::CreateSubWindows()
{
  displayWindow = new MainDisplayWindow(track1DirectoryName, track2DirectoryName);
  displayWindow->setParent(this);
  statusbar = statusBar();
  messageWindow = new QLabel(statusbar);
  messageWindow->setText("");
  messageWindow->move(5, 0);
  messageWindow->setFont(QFont("", 10, QFont::Bold));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 * Purpose  : Create Sub Windows
 *****************************************************************************/
void
MainWindow::InitializeSubWindows()
{
  displayWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 * Purpose  : Handle Resize Event
 *****************************************************************************/
void
MainWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   width;
  int                                   height;
  QSize                                 size;
  QSize                                 statusbar_size;
  QSize                                 menu_size;
  size = InEvent->size();  
  menu_size = menubar->size();
  statusbar_size = statusbar->size();
  width = size.width();
  height = size.height() - (menu_size.height() + statusbar_size.height());
  if ( displayWindow ) {
    displayWindow->move(0, menu_size.height());
    displayWindow->resize(width, height);
  }
  
  messageWindow->resize(statusbar_size.width() - 10, statusbar_size.height());
}

/*****************************************************************************!
 * Function : CreateActions
 * Purpose  : Create New Actions
 *****************************************************************************/
void
MainWindow::CreateActions()
{
  ActionExit = new QAction("E&xit", this);
  connect(ActionExit, SIGNAL(triggered()), this, SLOT(SlotExit()));
  ActionOpen = new QAction("Open", this);
  connect(ActionOpen, SIGNAL(triggered()), this, SLOT(SlotOpen()));
  ActionCreateDependencyTree = new QAction("Create Dependency Tree", this);
  connect(ActionCreateDependencyTree, SIGNAL(triggered()), this, SLOT(SlotCreateDependencyTree()));
}

/*****************************************************************************!
 * Function : CreateMenus
 * Purpose  : Create New Menus
 *****************************************************************************/
void
MainWindow::CreateMenus()
{
  menubar = menuBar();  
  fileMenu = menubar->addMenu("&File");
  fileMenu->addAction(ActionOpen);
  fileMenu->addAction(ActionExit);

  actionMenu = menubar->addMenu("&Action");
  actionMenu->addAction(ActionCreateDependencyTree);
}

/*****************************************************************************!
 * Function : SlotExit
 *****************************************************************************/
void
MainWindow::SlotExit(void)
{
  exit(EXIT_SUCCESS);  
}

/*****************************************************************************!
 * Function : SlotOpen
 *****************************************************************************/
void
MainWindow::SlotOpen(void)
{
  int                                   n;
  CodeBaseOpenDialog*                   dialog;

  dialog = new CodeBaseOpenDialog();
  n = dialog->exec();
  (void)n;
}

/*****************************************************************************!
 * Function : SlotCreateDependencyTree
 *****************************************************************************/
void
MainWindow::SlotCreateDependencyTree(void)
{
  ActionCreateDependencyTree->setEnabled(false);
  emit SignalCreateDependencyTree();
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
MainWindow::CreateConnections(void)
{
  connect(this,
          SIGNAL(SignalCreateDependencyTree()),
          displayWindow,
          SLOT(SlotCreateDependencyTree()));
  connect(displayWindow,
          SIGNAL(SignalDependencyWindowClose()),
          this,
          SLOT(SlotDependencyTreeWindowClose()));
  connect(displayWindow,
          SIGNAL(SignalSendDisplayMessage(QString)),
          this,
          SLOT(SlotSetMessage(QString)));
}

/*****************************************************************************!
 * Function : SlotDependencyTreeWindowClose
 *****************************************************************************/
void
MainWindow::SlotDependencyTreeWindowClose(void)
{
  ActionCreateDependencyTree->setEnabled(true);
}

/*****************************************************************************!
 * Function : SetCodeBaseDirectoryName
 *****************************************************************************/
void
MainWindow::SetCodeBaseDirectoryName
(QString InCodeBaseDirectoryName)
{
  displayWindow->SetCodeBaseDirectoryName(InCodeBaseDirectoryName);
}

/*****************************************************************************!
 * Function : SlotSetMessage
 *****************************************************************************/
void
MainWindow::SlotSetMessage
(QString InMessage)
{
  messageWindow->setText(InMessage);
}

/*****************************************************************************!
 * Function : StartAnalysis
 *****************************************************************************/
void
MainWindow::StartAnalysis
()
{
  displayWindow->SlotAnalyzeDifferences();
}
