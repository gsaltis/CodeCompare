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
#include "gui.h"

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
  CreateGroupSection(includePathsNameLabel, "Header Paths", QStringList(),
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
  int                                   width, height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  PerformResize(width, height);
}

/*****************************************************************************!
 * Function : PerformResize
 *****************************************************************************/
void
BuildLineGCCDisplayForm::PerformResize
(int InWidth, int InHeight)
{
  (void)InHeight;
  int                                   elementX, elementY, elementW, elementH;
  int                                   y;
  
  //! Sources Area
  elementX = sourcesNamesScrollArea->pos().x();
  elementH = sourcesNamesScrollArea->size().height();
  elementY = sourcesNamesScrollArea->pos().y();
  elementW = InWidth - (elementX + 10);
  sourcesNamesScrollArea->resize(elementW, elementH);
  y = elementY + elementH + GUI_Y_SMALL_GAP;

  //! Libraries Area
  elementH = libsNamesScrollArea->size().height();
  libsNamesScrollArea->resize(elementW, elementH);
  libsNamesScrollArea->move(libsNamesScrollArea->pos().x(), y);
  elementH = libsNames->size().height();
  libsNames->resize(elementW-3, elementH);
  libsNameLabel->move(libsNameLabel->pos().x(), y);
  y +=elementH + GUI_Y_SMALL_GAP;

  //! Include Area
  elementH = includesPathsScrollArea->size().height();  
  includesPathsScrollArea->resize(elementW, elementH);
  elementH = includesPaths->size().height();
  includesPaths->resize(elementW-3, elementH);
  includesPathsScrollArea->move(includesPathsScrollArea->pos().x(), y);
  includePathsNameLabel->move(includePathsNameLabel->pos().x(), y);
  y +=elementH + GUI_Y_SMALL_GAP;

  //! Libraries Path Area
  elementH = libsPathsScrollArea->size().height();  
  libsPathsScrollArea->resize(elementW, elementH);
  elementH = libsPaths->size().height();
  libsPaths->resize(elementW-3, elementH);
  libsPathsScrollArea->move(libsPathsScrollArea->pos().x(), y);
  libPathsNameLabel->move(libPathsNameLabel->pos().x(), y);
  y +=elementH + GUI_Y_SMALL_GAP;
  
  //! Flags Area
  elementH = flagsScrollArea->size().height();
  flagsScrollArea->resize(elementW, elementH);
  elementH = flags->size().height();
  flagsScrollArea->move(flagsScrollArea->pos().x(), y);
  flagsNameLabel->move(flagsNameLabel->pos().x(), y);
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

  PopulateGroupSection(sourcesNames, sourcesNamesScrollArea, compileBuildLine->GetSources());
  PopulateGroupSection(libsNames, libsNamesScrollArea, compileBuildLine->GetLibraries());
  PopulateGroupSection(includesPaths, includesPathsScrollArea, compileBuildLine->GetIncludePaths());
  PopulateGroupSection(libsPaths, libsPathsScrollArea, compileBuildLine->GetLibraryPaths());
  PopulateGroupSection(flags, flagsScrollArea, compileBuildLine->GetFlags());
  PerformResize(size().width(), size().height());
}
