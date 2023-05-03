/*****************************************************************************
 * FILE NAME    : SourceCodeComparisonToolBar.cpp
 * DATE         : May 02 2023
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
#include "SourceCodeComparisonToolBar.h"
#include "main.h"
#include "CodeCompareToolBarButton.h"

/*****************************************************************************!
 * Function : SourceCodeComparisonToolBar
 *****************************************************************************/
SourceCodeComparisonToolBar::SourceCodeComparisonToolBar
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(MainToolBarBackgroundColor));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShadow(QFrame::Raised);
  setFrameShape(QFrame::Box);
  setMinimumHeight(SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT);
  setMaximumHeight(SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT);
  initialize();
}

/*****************************************************************************!
 * Function : ~SourceCodeComparisonToolBar
 *****************************************************************************/
SourceCodeComparisonToolBar::~SourceCodeComparisonToolBar
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SourceCodeComparisonToolBar::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  ActionCodeViewButtonPushed = new QAction("CodeViewButtonPushed", this);
  connect(ActionCodeViewButtonPushed, SIGNAL(triggered()), this, SLOT(SlotCodeViewButtonPushed()));
  ActionFunctionViewButtonPushed = new QAction("FunctionViewButtonPushed", this);
  connect(ActionFunctionViewButtonPushed, SIGNAL(triggered()), this, SLOT(SlotFunctionViewButtonPushed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SourceCodeComparisonToolBar::CreateSubWindows()
{
  //! Create the CodeViewButton button
  CodeViewButton = new CodeCompareToolBarButton(this, 0, QIcon(QPixmap(":/images/CodeView.png")));
  connect(CodeViewButton, SIGNAL(pressed()), this, SLOT(SlotCodeViewButtonPushed()));

  //! Create the FunctionViewButton button
  FunctionViewButton = new CodeCompareToolBarButton(this, 37, QIcon(QPixmap(":/images/FunctionView.png")));
  connect(FunctionViewButton, SIGNAL(pressed()), this, SLOT(SlotFunctionViewButtonPushed()));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SourceCodeComparisonToolBar::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SourceCodeComparisonToolBar::resizeEvent
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
 * Function : SlotCodeViewButtonPushed
 *****************************************************************************/
void
SourceCodeComparisonToolBar::SlotCodeViewButtonPushed(void)
{
  emit SignalCodeViewSelected();
}

/*****************************************************************************!
 * Function : SlotFunctionViewButtonPushed
 *****************************************************************************/
void
SourceCodeComparisonToolBar::SlotFunctionViewButtonPushed(void)
{
  emit SignalFunctionViewSelected();  
}
