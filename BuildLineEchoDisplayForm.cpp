/*****************************************************************************
 * FILE NAME    : BuildLineEchoDisplayForm.cpp
 * DATE         : April 05 2023
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
#include "BuildLineEchoDisplayForm.h"
#include "BuildEchoLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildLineEchoDisplayForm
 *****************************************************************************/
BuildLineEchoDisplayForm::BuildLineEchoDisplayForm
() : BuildLineBaseDisplayForm()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShadow(QFrame::Sunken);
  setFrameShape(QFrame::Box);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildLineEchoDisplayForm
 *****************************************************************************/
BuildLineEchoDisplayForm::~BuildLineEchoDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineEchoDisplayForm::initialize()
{
  BuildLineBaseDisplayForm::initialize();
  buildLine = NULL;
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildLineEchoDisplayForm::CreateSubWindows()
{
  int                                   y;
  y = 30;

  //!
  CreateLabel(actionNameLabel, actionLabel, "Action", QString(), y);

  //!
  CreateLabel(echoLineNameLabel, echoLineLabel, "Echo Line", QString(), y);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineEchoDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineEchoDisplayForm::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   elementW, elementH;
  int                                   width;
  
  size = InEvent->size();
  width = size.width();
  elementW = width - (elementX + 10);
  
  elementH = actionLabel->size().height();
  actionLabel->resize(elementW, elementH);
  
  elementH = echoLineLabel->size().height();
  echoLineLabel->resize(elementW, elementH);
}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildLineEchoDisplayForm::SetBuildLine
(BuildLine* InBuildLine)
{
  BuildEchoLine*                        lnBuildLine;
  
  if ( NULL == InBuildLine ) {
    return;
  }

  buildLine = InBuildLine;
  lnBuildLine = (BuildEchoLine*)buildLine;
  actionLabel->setText(lnBuildLine->GetAction());
  echoLineLabel->setText(lnBuildLine->GetEchoLine());
}
