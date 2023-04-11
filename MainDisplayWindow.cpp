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
  codeWindowTrack1 = NULL;
  codeWindowTrack2 = NULL;
  codeNameWindow = NULL;
  codeWindowMerge = NULL;
  dependencyTreeWindow = NULL;
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
MainDisplayWindow::CreateSubWindows()
{
  codeWindowTrack1 = new CodeWindow();
  codeWindowTrack1->setParent(this);
  codeWindowTrack1->AddDirectory("D:\\Source\\NCUCodeMerge\\Track2_NCU_CODE");
  codeWindowTrack2 = new CodeWindow();
  codeWindowTrack2->setParent(this);
  codeNameWindow = new CodeNameWindow();
  codeNameWindow->setParent(this);
  codeWindowMerge = new CodeWindow();
  codeWindowMerge->setParent(this);

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
  int                                   w;
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   track1X, track1Y, track1W, track1H;
  int                                   track2X, track2Y, track2W, track2H;
  int                                   mergeTrackX, mergeTrackY, mergeTrackW, mergeTrackH;
  int                                   codeNameWindowX, codeNameWindowY;
  int                                   codeNameWindowW, codeNameWindowH;
  int                                   codeWindowWidth;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  codeNameWindowX = GUI_X_GAP;
  codeNameWindowY = GUI_Y_GAP;
  codeNameWindowW = 250;
  codeNameWindowH = height - (GUI_Y_GAP * 2);

  w = width - (codeNameWindowW + (GUI_X_GAP * 5));
  codeWindowWidth = w / 3;

  
  track1X = (GUI_X_GAP * 2) + codeNameWindowW;
  track1Y = GUI_Y_GAP;
  track1W = codeWindowWidth;
  track1H = height - (GUI_Y_GAP * 2);

  mergeTrackX = (GUI_X_GAP * 3) + codeNameWindowW + track1W;
  mergeTrackY = GUI_Y_GAP;
  mergeTrackW = codeWindowWidth;
  mergeTrackH = height - (GUI_Y_GAP * 2);
  
  track2X = (GUI_X_GAP * 4) + codeNameWindowW + track1W + mergeTrackW;
  track2Y = GUI_Y_GAP;
  track2W = codeWindowWidth;
  track2H = height - (GUI_Y_GAP * 2);

  //!
  dependencyTreeWindowX = (GUI_X_GAP * 2) + codeNameWindowW;
  dependencyTreeWindowY = GUI_Y_GAP;
  dependencyTreeWindowW = width - (codeNameWindowW + GUI_X_GAP * 3);
  dependencyTreeWindowH = height - (GUI_Y_GAP * 2);

  //!
  buildTreeWindowX = (GUI_X_GAP * 2) + codeNameWindowW;
  buildTreeWindowY = GUI_Y_GAP;
  buildTreeWindowW = width - (codeNameWindowW + GUI_X_GAP * 3);
  buildTreeWindowH = height - ((GUI_Y_GAP * 2) + 0);

  //! 
  if ( codeWindowTrack1 ) {
    codeWindowTrack1->move(track1X, track1Y);
    codeWindowTrack1->resize(track1W, track1H);
  }
  if ( codeWindowTrack2 ) {
    codeWindowTrack2->move(track2X, track2Y);
    codeWindowTrack2->resize(track2W, track2H);
  }
  if ( codeNameWindow ) {
    codeNameWindow->move(codeNameWindowX, codeNameWindowY);
    codeNameWindow->resize(codeNameWindowW, codeNameWindowH);
  }
  if ( codeWindowMerge ) {
    codeWindowMerge->move(mergeTrackX, mergeTrackY);
    codeWindowMerge->resize(mergeTrackW, mergeTrackH);
  }

  //!
  if ( dependencyTreeWindow ) {
    dependencyTreeWindow->move(dependencyTreeWindowX, dependencyTreeWindowY);
    dependencyTreeWindow->resize(dependencyTreeWindowW, dependencyTreeWindowH);
  }
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
  codeWindowTrack1->hide();
  codeWindowTrack2->hide();
  codeWindowMerge->hide();
  dependencyTreeWindow->show();
}

/*****************************************************************************!
 * Function : SlotDependencyWindowClose
 *****************************************************************************/
void
MainDisplayWindow::SlotDependencyWindowClose(void)
{
  emit SignalDependencyWindowClose();
  codeWindowTrack1->show();
  codeWindowTrack2->show();
  codeWindowMerge->show();
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
