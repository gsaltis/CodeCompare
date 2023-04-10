/*****************************************************************************
 * FILE NAME    : BuildLineARDisplayForm.cpp
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
#include "BuildLineARDisplayForm.h"
#include "BuildARLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildLineARDisplayForm
 *****************************************************************************/
BuildLineARDisplayForm::BuildLineARDisplayForm
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
 * Function : ~BuildLineARDisplayForm
 *****************************************************************************/
BuildLineARDisplayForm::~BuildLineARDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineARDisplayForm::initialize()
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
BuildLineARDisplayForm::CreateSubWindows()
{
  int                                   y;
  y = 30;

  //!
  CreateLabel(actionNameLabel, actionLabel, "Action", QString(), y);

  //!
  CreateLabel(targetNameLabel, targetLabel, "Target", QString(), y);
  
  //!
  CreateGroupSection(sourcesLabel, "Sources", QStringList(), sources, sourcesScrollArea, y);
  
  //!
  CreateLabel(flagsNameLabel, flagsLabel, "Flags", QString(), y);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineARDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineARDisplayForm::resizeEvent
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

  elementH = sourcesScrollArea->size().height();
  sourcesScrollArea->resize(elementW, elementH);
  
  elementH = flagsLabel->size().height();
  flagsLabel->resize(elementW-3, elementH);

}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildLineARDisplayForm::SetBuildLine
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
  flagsLabel->setText(arBuildLine->GetFlags());
}
