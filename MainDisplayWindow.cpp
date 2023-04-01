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

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/
#define X_GAP                           10
#define Y_GAP                           10

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

  codeNameWindowX = X_GAP;
  codeNameWindowY = Y_GAP;
  codeNameWindowW = 250;
  codeNameWindowH = height - (Y_GAP * 2);

  w = width - (codeNameWindowW + (X_GAP * 5));
  codeWindowWidth = w / 3;

  
  track1X = (X_GAP * 2) + codeNameWindowW;
  track1Y = Y_GAP;
  track1W = codeWindowWidth;
  track1H = height - (Y_GAP * 2);

  mergeTrackX = (X_GAP * 3) + codeNameWindowW + track1W;
  mergeTrackY = Y_GAP;
  mergeTrackW = codeWindowWidth;
  mergeTrackH = height - (Y_GAP * 2);
  
  track2X = (X_GAP * 4) + codeNameWindowW + track1W + mergeTrackW;
  track2Y = Y_GAP;
  track2W = codeWindowWidth;
  track2H = height - (Y_GAP * 2);

  dependencyTreeWindowX = (X_GAP * 2) + codeNameWindowW;
  dependencyTreeWindowY = Y_GAP;
  dependencyTreeWindowW = width - (codeNameWindowW + X_GAP * 2);
  dependencyTreeWindowH = height - (Y_GAP * 2);
  
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
  if ( dependencyTreeWindow ) {
    dependencyTreeWindow->move(dependencyTreeWindowX, dependencyTreeWindowY);
    dependencyTreeWindow->resize(dependencyTreeWindowW, dependencyTreeWindowH);
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
}
