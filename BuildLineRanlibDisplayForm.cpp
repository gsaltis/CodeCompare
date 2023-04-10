/*****************************************************************************
 * FILE NAME    : BuildLineRanlibDisplayForm.cpp
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
#include "BuildLineRanlibDisplayForm.h"
#include "BuildARLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildLineRanlibDisplayForm
 *****************************************************************************/
BuildLineRanlibDisplayForm::BuildLineRanlibDisplayForm
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
 * Function : ~BuildLineRanlibDisplayForm
 *****************************************************************************/
BuildLineRanlibDisplayForm::~BuildLineRanlibDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineRanlibDisplayForm::initialize()
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
BuildLineRanlibDisplayForm::CreateSubWindows()
{
  int                                   y;
  y = 30;

  //!
  CreateLabel(actionNameLabel, actionLabel, "Action", QString(), y);

  //!
  CreateLabel(targetNameLabel, targetLabel, "Target", QString(), y);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineRanlibDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineRanlibDisplayForm::resizeEvent
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
  
  elementH = targetLabel->size().height();
  targetLabel->resize(elementW, elementH);
}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildLineRanlibDisplayForm::SetBuildLine
(BuildLine* InBuildLine)
{
  BuildARLine*                          arBuildLine;
  
  if ( NULL == InBuildLine ) {
    return;
  }

  buildLine = InBuildLine;
  arBuildLine = (BuildARLine*)buildLine;
  actionLabel->setText(arBuildLine->GetAction());
  targetLabel->setText(arBuildLine->GetTarget());
}
