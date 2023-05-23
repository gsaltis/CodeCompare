/*****************************************************************************
 * FILE NAME    : DirBuildContainer.cpp
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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirBuildContainer.h"

/*****************************************************************************!
 * Local Macros 
 *****************************************************************************/

/*****************************************************************************!
 * Function : DirBuildContainer
 *****************************************************************************/
DirBuildContainer::DirBuildContainer
(DirTreeContainer* InDirContainer, BuildTreeContainer* InBuildContainer) : QWidget()
{
  dirContainer = InDirContainer;
  buildContainer = InBuildContainer;
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~DirBuildContainer
 *****************************************************************************/
DirBuildContainer::~DirBuildContainer
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
DirBuildContainer::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  ActionToggleViewButtonPushed = new QAction("ToggleViewButtonPushed", this);
  connect(ActionToggleViewButtonPushed, SIGNAL(triggered()), this, SLOT(SlotToggleViewButtonPushed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
DirBuildContainer::CreateSubWindows()
{
  toolBar = new QFrame(this);
  toolBar->setFrameShadow(QFrame::Sunken);
  toolBar->setFrameStyle(QFrame::Panel);
  toolBar->setStyleSheet("QFrame { border : 1px solid #CCC}");
  
  //! Create the toggleViewButton button  
  toggleViewButton = new QPushButton();
  toggleViewButton->setParent(this);
  toggleViewButton->setText("SC");
  toggleViewButton->move(1, 1);
  toggleViewButton->resize(30,30);
  connect(toggleViewButton, SIGNAL(pressed()), this, SLOT(SlotToggleViewButtonPushed()));

  stacker = new QStackedWidget(this);
  stacker->addWidget(dirContainer);
  stacker->addWidget(buildContainer);
  stacker->setCurrentIndex(0);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
DirBuildContainer::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
DirBuildContainer::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   toolBarX, toolBarY;
  int                                   toolBarW, toolBarH;
  int                                   stackerX, stackerY;
  int                                   stackerW, stackerH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  toolBarX = 0;
  toolBarY = 0;
  toolBarW = width;
  toolBarH = 32;

  stackerX = 0;
  stackerY = 32;
  stackerW = width;
  stackerH = height - 32;

  toolBar->move(toolBarX, toolBarY);
  toolBar->resize(toolBarW, toolBarH);
  
  stacker->move(stackerX, stackerY);
  stacker->resize(stackerW, stackerH);
}

/*****************************************************************************!
 * Function : SlotToggleViewButtonPushed
 *****************************************************************************/
void
DirBuildContainer::SlotToggleViewButtonPushed(void)
{
  int                                   windowIndex;
  QString                               names[] = { "SC", "BT" };
  windowIndex = stacker->currentIndex();
  windowIndex++;
  windowIndex = windowIndex % stacker->count();
  stacker->setCurrentIndex(windowIndex);
  toggleViewButton->setText(names[windowIndex]);
}
