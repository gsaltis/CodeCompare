/*****************************************************************************
 * FILE NAME    : BuildLineGCCDisplayForm.cpp
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
#include "BuildLineGCCDisplayForm.h"
#include "BuildCompileLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildLineGCCDisplayForm
 *****************************************************************************/
BuildLineGCCDisplayForm::BuildLineGCCDisplayForm
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
 * Function : ~BuildLineGCCDisplayForm
 *****************************************************************************/
BuildLineGCCDisplayForm::~BuildLineGCCDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineGCCDisplayForm::initialize()
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
BuildLineGCCDisplayForm::CreateSubWindows()
{
  int                                   y;
  y = 30;

  //!
  CreateLabel(actionNameLabel, actionLabel, "Action", QString(), y);

  //!
  CreateLabel(targetNameLabel, targetLabel, "Target", QString(), y);
  
  //!
  CreateGroupSection(sourcesNameLabel, "Sources", QStringList(),
                     sourcesNames, sourcesNamesScrollArea, y);
  
  //!
  CreateGroupSection(libsNameLabel, "Libraries", QStringList(),
                     libsNames, libsNamesScrollArea, y);

  //!
  CreateGroupSection(libPathsNameLabel, "Include Header Paths", QStringList(),
                     includesPaths, includesPathsScrollArea, y);

  //!
  CreateGroupSection(libPathsNameLabel, "Library Paths", QStringList(),
                     libsPaths, libsPathsScrollArea, y);

  //!
  CreateGroupSection(flagsNameLabel, "Flags", QStringList(),
                     flags, flagsScrollArea, y);  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineGCCDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineGCCDisplayForm::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   elementX, elementW, elementH;
  
  size = InEvent->size();
  width = size.width();

  
  elementX = sourcesNamesScrollArea->pos().x();
  elementH = sourcesNamesScrollArea->size().height();
  elementW = width - (elementX + 10);
  sourcesNamesScrollArea->resize(elementW, elementH);
  elementH = sourcesNames->size().height();
  sourcesNames->resize(elementW-3, elementH);
  
  elementH = libsNamesScrollArea->size().height();
  libsNamesScrollArea->resize(elementW, elementH);
  elementH = libsNames->size().height();
  libsNames->resize(elementW-3, elementH);

  elementH = includesPathsScrollArea->size().height();  
  includesPathsScrollArea->resize(elementW, elementH);
  elementH = includesPaths->size().height();
  includesPaths->resize(elementW-3, elementH);

  elementH = libsPathsScrollArea->size().height();  
  libsPathsScrollArea->resize(elementW, elementH);
  elementH = libsPaths->size().height();
  libsPaths->resize(elementW-3, elementH);
  
  elementH = flagsScrollArea->size().height();
  flagsScrollArea->resize(elementW, elementH);
  elementH = flags->size().height();
  flags->resize(elementW-3, elementH);

  elementH = actionLabel->size().height();
  actionLabel->resize(elementW, elementH);
  
  elementH = targetLabel->size().height();
  targetLabel->resize(elementW, elementH);
}

/*****************************************************************************!
 * Function : SetBuildLine
 *****************************************************************************/
void
BuildLineGCCDisplayForm::SetBuildLine
(BuildLine* InBuildLine)
{
  BuildCompileLine*                     compileBuildLine;
  
  if ( NULL == InBuildLine ) {
    return;
  }

  buildLine = InBuildLine;
  compileBuildLine = (BuildCompileLine*)buildLine;
  actionLabel->setText(compileBuildLine->GetAction());
  targetLabel->setText(compileBuildLine->GetTarget());
}
