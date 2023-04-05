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

/*****************************************************************************!
 * Function : BuildLineDisplayForm
 *****************************************************************************/
BuildLineDisplayForm::BuildLineDisplayForm
(BuildLine* InBuildLine) : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 0)));
  setPalette(pal);
  setAutoFillBackground(true);
  buildLine = InBuildLine;
  y = 0;
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
  QStringList                           sl;
  int                                   n, h;

  TRACE_FUNCTION_START();
  actionLabel = new QLabel();
  actionLabel->setText(buildLine->GetAction());
  actionLabel->resize(100, 20);

  AddRow("Action", actionLabel);

  targetLabel = new QLabel();
  targetLabel->setText(buildLine->GetTarget());
  targetLabel->resize(100, 20);
  AddRow("Target", targetLabel);

  //!
  sourcesTable = new QListWidget();
  sl = buildLine->GetSources();
  n = sl.count();
  h = n * 20;
  if ( h > 120 ) {
    h = 120;
  }
  sourcesTable->addItems(sl);
  sourcesTable->setMaximumHeight(h);
  AddRow("Sources", sourcesTable);

  //!
  libsTable = new QListWidget();
  sl = buildLine->GetLibraries();
  n = sl.count();
  h = n * 20;
  if ( h > 120 ) {
    h = 120;
  }
  libsTable->addItems(sl);
  libsTable->setMaximumHeight(h);
  AddRow("Libraries", libsTable);

  //!
  sl = buildLine->GetIncludePaths();
  n = sl.count();
  h = 20;
  if ( n > 0 ) {
    h = n * 20;
    if ( n == 1 ) {
      h = 40;
    }
  }
  if ( h > 120 ) {
    h = 120;
  }
  includePathsTable = NULL;
  TRACE_FUNCTION_INT(n);
  TRACE_FUNCTION_INT(h);
  if ( n > 0 ) {
    TRACE_FUNCTION_LOCATION();
    includePathsTable = new QListWidget();
    includePathsTable->addItems(sl);
    includePathsTable->resize(130, h);
  }
  AddRow("Include Paths", includePathsTable);

  //
  libPathsTable = new QListWidget();
  sl = buildLine->GetLibraryPaths();
  n = sl.count();
  h = n > 0 ? n : 1 * 20;
  
  if ( h > 120 ) {
    h = 120;
  }
  libPathsTable->addItems(sl);
  libPathsTable->setMaximumHeight(h);
  AddRow("Library Paths", libPathsTable);

  flagsTable = new QListWidget();
  flagsTable->addItems(buildLine->GetFlags());
  AddRow("Flags", flagsTable);
  TRACE_FUNCTION_END();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineDisplayForm::InitializeSubWindows()
{
  
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
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : CreateLabel
 *****************************************************************************/
QLabel*
BuildLineDisplayForm::CreateLabel
(QString InText)
{
  QLabel*                               label;  
  label = new QLabel(InText + QString(" : "));
  label->resize(120, 20);
  label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  return label;
}

/*****************************************************************************!
 * Function : AddRow
 *****************************************************************************/
void
BuildLineDisplayForm::AddRow
(QString InLabelText, QWidget* InWidget)
{
  QLabel*                               label;
  int                                   h, h2;

  TRACE_FUNCTION_START();
  label = CreateLabel(InLabelText);

  label->move(10, y);
  label->setParent(this);

  InWidget->move(140, y);
  InWidget->setParent(this);

  h = label->size().height();
  if ( NULL == InWidget ) {
    TRACE_FUNCTION_LOCATION();
  }
  if ( InWidget ) {
    h2 = InWidget->size().height();
    if ( h2 > h ) {
      h = h2;
    }
  }
  y += (h + 5);
  TRACE_FUNCTION_END();
}

/*****************************************************************************!
 * Function : InsertRow
 *****************************************************************************/
void
BuildLineDisplayForm::InsertRow
(QString InLabelText, QWidget* InWidget)
{
  (void)InLabelText;
  (void)InWidget;
}

/*****************************************************************************!
 * Function : RemoveRow
 *****************************************************************************/
void
BuildLineDisplayForm::RemoveRow
()
{
}
