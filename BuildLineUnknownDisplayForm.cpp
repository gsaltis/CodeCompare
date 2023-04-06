/*****************************************************************************
 * FILE NAME    : BuildLineUnknownDisplayForm.cpp
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
#include "BuildLineUnknownDisplayForm.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildLineUnknownDisplayForm
 *****************************************************************************/
BuildLineUnknownDisplayForm::BuildLineUnknownDisplayForm
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
 * Function : ~BuildLineUnknownDisplayForm
 *****************************************************************************/
BuildLineUnknownDisplayForm::~BuildLineUnknownDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineUnknownDisplayForm::initialize()
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
BuildLineUnknownDisplayForm::CreateSubWindows()
{
  int                                   y;
  y = 30;

  CreateEditSection(unknownTextLabel, QString("Unknown"),
                    QString(""),
                    unknownTextEdit,
                    y);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineUnknownDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineUnknownDisplayForm::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width, height;
  int                                   elementX, elementW, elementH, elementY;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();
  
  elementX = unknownTextEdit->pos().x();
  elementY = unknownTextEdit->pos().y();
  elementH = height;
  elementH -= elementY;
  elementH -= 10;
  elementW = width - (elementX + 10);
  unknownTextEdit->resize(elementW, elementH);
}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildLineUnknownDisplayForm::SetBuildLine
(BuildLine* InBuildLine)
{
  if ( NULL == InBuildLine ) {
    return;
  }

  buildLine = InBuildLine;
  unknownTextEdit->setText(buildLine->GetText());
}
