/*****************************************************************************
 * FILE NAME    : BuildLineDisplayForm.cpp
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
#include "BuildLineDisplayForm.h"
#include "trace.h"
#include "BuildCompileLine.h"
#include "BuildLNLine.h"
#include "BuildLine.h"

/*****************************************************************************!
 * Function : BuildLineDisplayForm
 *****************************************************************************/
BuildLineDisplayForm::BuildLineDisplayForm
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildLineDisplayForm
 *****************************************************************************/
BuildLineDisplayForm::~BuildLineDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineDisplayForm::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildLineDisplayForm::CreateSubWindows()
{
  gccForm = new BuildLineGCCDisplayForm();  
  gccForm->setParent(this);
  gccForm->hide();
  
  lnForm = new BuildLineLNDisplayForm();  
  lnForm->setParent(this);
  lnForm->hide();
  
  unknownBuildTypeForm = new BuildLineUnknownDisplayForm();
  unknownBuildTypeForm->setParent(this);
  unknownBuildTypeForm->hide();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineDisplayForm::InitializeSubWindows()
{
  gccForm = NULL;
  lnForm = NULL;
  unknownBuildTypeForm = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineDisplayForm::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  if ( gccForm ) {
    gccForm->resize(width, height);
  }
  if ( lnForm ) {
    lnForm->resize(width, height);
  }
  if ( unknownBuildTypeForm ) {
    unknownBuildTypeForm->resize(width, height);
  }
}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildLineDisplayForm::SetBuildLine
(BuildLine* InBuildLine)
{
  QString                               action;
  BuildLine::Type                       lineType;
  
  buildLine = InBuildLine;
  gccForm->hide();
  lnForm->hide();
  unknownBuildTypeForm->hide();

  lineType = buildLine->GetType();
  if ( buildLine == NULL ) {
    return;
  }
  if ( lineType == BuildLine::TypeCompile ) {
    BuildCompileLine*                   compileLine;

    compileLine = (BuildCompileLine*)buildLine;
    gccForm->show();
    gccForm->SetBuildLine(compileLine);
    return;
  }
  if ( lineType == BuildLine::TypeLN ) {
    BuildLNLine*                        lnLine;
    lnLine = (BuildLNLine*)buildLine;
    lnForm->show();
    lnForm->SetBuildLine(lnLine);
    return;
  }
  unknownBuildTypeForm->show();
  unknownBuildTypeForm->SetBuildLine(buildLine);
}