/*****************************************************************************
 * FILE NAME    : BuildLineLNDisplayForm.cpp
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
#include "BuildLineLNDisplayForm.h"
#include "BuildLNLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildLineLNDisplayForm
 *****************************************************************************/
BuildLineLNDisplayForm::BuildLineLNDisplayForm
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
 * Function : ~BuildLineLNDisplayForm
 *****************************************************************************/
BuildLineLNDisplayForm::~BuildLineLNDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineLNDisplayForm::initialize()
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
BuildLineLNDisplayForm::CreateSubWindows()
{
  int                                   y;
  y = 30;

  //!
  CreateLabel(actionNameLabel, actionLabel, "Action", QString(), y);

  //!
  CreateLabel(targetNameLabel, targetLabel, "Target", QString(), y);
  
  //!
  CreateLabel(linkNameLabel, linkLabel, "Line", QString(), y);
  
  //!
  CreateGroupSection(flagsNameLabel, "Flags", QStringList(),
                     flags, flagsScrollArea, y);  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineLNDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineLNDisplayForm::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   elementW, elementH;
  int                                   width;
  
  size = InEvent->size();
  width = size.width();
  elementW = width - (elementX + 10);
  
  elementH = flagsScrollArea->size().height();
  flagsScrollArea->resize(elementW, elementH);
  elementH = flags->size().height();
  flags->resize(elementW-3, elementH);

  elementH = actionLabel->size().height();
  actionLabel->resize(elementW, elementH);
  
  elementH = targetLabel->size().height();
  targetLabel->resize(elementW, elementH);

  elementH = linkLabel->size().height();
  linkLabel->resize(elementW, elementH);
}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildLineLNDisplayForm::SetBuildLine
(BuildLine* InBuildLine)
{
  BuildLNLine*                          lnBuildLine;
  
  if ( NULL == InBuildLine ) {
    return;
  }

  buildLine = InBuildLine;
  lnBuildLine = (BuildLNLine*)buildLine;
  actionLabel->setText(lnBuildLine->GetAction());
  linkLabel->setText(lnBuildLine->GetLinkName());
  targetLabel->setText(lnBuildLine->GetTarget());
}
