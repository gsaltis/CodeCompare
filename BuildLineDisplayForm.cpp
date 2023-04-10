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
#include "BuildARLine.h"
#include "BuildRanlibLine.h"
#include "BuildForLine.h"
#include "BuildEchoLine.h"
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
  
  arForm = new BuildLineARDisplayForm();  
  arForm->setParent(this);
  arForm->hide();
  
  ranlibForm = new BuildLineRanlibDisplayForm();  
  ranlibForm->setParent(this);
  ranlibForm->hide();
  
  forForm = new BuildLineForDisplayForm();  
  forForm->setParent(this);
  forForm->hide();
  
  echoForm = new BuildLineEchoDisplayForm();  
  echoForm->setParent(this);
  echoForm->hide();
  
  unknownBuildTypeForm = new BuildLineUnknownDisplayForm();
  unknownBuildTypeForm->setParent(this);
  unknownBuildTypeForm->hide();

  controlsForm = new BuildLineDisplayFormControls();
  controlsForm->setParent(this);
  connect(controlsForm,
          SIGNAL(SignalBuildLineSelected(BuildLine*)),
          this,
          SLOT(SlotBuildLineSelected(BuildLine*)));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineDisplayForm::InitializeSubWindows()
{
  gccForm               = NULL;
  lnForm                = NULL;
  forForm               = NULL;
  unknownBuildTypeForm  = NULL;
  controlsForm          = NULL;
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
  int                                   elementHeight;
  int                                   controlsFormX, controlsFormY;
  int                                   controlsFormW, controlsFormH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();
  elementHeight = height - 35;

  controlsFormX = 0;
  controlsFormY = height - 30;
  controlsFormH = 30;
  controlsFormW = width;
  
  if ( gccForm ) {
    gccForm->resize(width, elementHeight);
  }
  if ( lnForm ) {
    lnForm->resize(width, elementHeight);
  }
  if ( unknownBuildTypeForm ) {
    unknownBuildTypeForm->resize(width, elementHeight);
  }
  if ( forForm ) {
    forForm->resize(width, elementHeight);
  }
  if ( ranlibForm ) {
    ranlibForm->resize(width, elementHeight);
  }
  if ( arForm ) {
    arForm->resize(width, elementHeight);
  }
  if ( echoForm ) {
    echoForm->resize(width, elementHeight);
  }
  if ( controlsForm ) {
    controlsForm->resize(controlsFormW, controlsFormH);
    controlsForm->move(controlsFormX, controlsFormY);
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
  forForm->hide();
  echoForm->hide();
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
  if ( lineType == BuildLine::TypeAR ) {
    BuildARLine*                        arLine;
    arLine = (BuildARLine*)buildLine;
    arForm->show();
    arForm->SetBuildLine(arLine);
    return;
  }
  if ( lineType == BuildLine::TypeRanlib ) {
    BuildRanlibLine*                    ranlibLine;
    ranlibLine = (BuildRanlibLine*)buildLine;
    ranlibForm->show();
    ranlibForm->SetBuildLine(ranlibLine);
    return;
  }
  if ( lineType == BuildLine::TypeLN ) {
    BuildLNLine*                        lnLine;
    lnLine = (BuildLNLine*)buildLine;
    lnForm->show();
    lnForm->SetBuildLine(lnLine);
    return;
  }
  if ( lineType == BuildLine::TypeFor ) {
    BuildForLine*                       forLine;
    forLine = (BuildForLine*)buildLine;
    forForm->show();
    forForm->SetBuildLine(forLine);
    return;
  }
  if ( lineType == BuildLine::TypeEcho ) {
    BuildEchoLine*                      echoLine;
    echoLine = (BuildEchoLine*)buildLine;
    echoForm->show();
    echoForm->SetBuildLine(echoLine);
    return;
  }
  unknownBuildTypeForm->show();
  unknownBuildTypeForm->SetBuildLine(buildLine);
}

/*****************************************************************************!
 * Function : SlotBuildLinesSelected
 *****************************************************************************/
void
BuildLineDisplayForm::SlotBuildLinesSelected
(BuildLineSet* InLineSet)
{
  buildLines = InLineSet;
  controlsForm->SlotBuildLinesSet(buildLines);
}

/*****************************************************************************!
 * Function : SlotBuildLineSelected
 *****************************************************************************/
void
BuildLineDisplayForm::SlotBuildLineSelected
(BuildLine* InBuildLine)
{
  SetBuildLine(InBuildLine);
}
