/*****************************************************************************
 * FILE NAME    : BuildLineForDisplayForm.cpp
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
#include "BuildLineForDisplayForm.h"
#include "BuildForLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildLineForDisplayForm
 *****************************************************************************/
BuildLineForDisplayForm::BuildLineForDisplayForm
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
 * Function : ~BuildLineForDisplayForm
 *****************************************************************************/
BuildLineForDisplayForm::~BuildLineForDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineForDisplayForm::initialize()
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
BuildLineForDisplayForm::CreateSubWindows()
{
  int                                   y;
  y = 30;

  //!
  CreateLabel(actionNameLabel, actionLabel, "Action", QString(), y);

  //!
  CreateGroupSection(targetsNameLabel, "Targets", QStringList(), targets, targetsScrollArea, y);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineForDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineForDisplayForm::resizeEvent
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
  
  elementH = targetsScrollArea->size().height();
  targetsScrollArea->resize(elementW, elementH);
  elementH = targets->size().height();
  targets->resize(elementW-3, elementH);
}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildLineForDisplayForm::SetBuildLine
(BuildLine* InBuildLine)
{
  BuildForLine*                         forBuildLine;
  
  if ( NULL == InBuildLine ) {
    return;
  }

  buildLine = InBuildLine;
  forBuildLine = (BuildForLine*)buildLine;
  actionLabel->setText(forBuildLine->GetAction());
}
