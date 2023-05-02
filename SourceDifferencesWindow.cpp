/*****************************************************************************
 * FILE NAME    : SourceDifferencesWindow.cpp
 * DATE         : April 25 2023
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
#include "SourceDifferencesWindow.h"
#include "FileSectionDiff.h"
#include "trace.h"

/*****************************************************************************!
 * Function : SourceDifferencesWindow
 *****************************************************************************/
SourceDifferencesWindow::SourceDifferencesWindow
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(51, 102, 153)));
  pal.setBrush(QPalette::WindowText, QBrush(QColor(255, 255, 255)));
  
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~SourceDifferencesWindow
 *****************************************************************************/
SourceDifferencesWindow::~SourceDifferencesWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SourceDifferencesWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SourceDifferencesWindow::CreateSubWindows()
{
  container = new QWidget(this);
  QPalette pal = container->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(0, 0, 0, 0)));
  container->setPalette(pal);
  container->setAutoFillBackground(true);
  container->resize(100, 100);
  container->setObjectName("SourceDifferencesWindowContainer");
  scrollArea = new QScrollArea(this);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollArea->setWidget(container);
  scrollArea->move(0, 0);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SourceDifferencesWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SourceDifferencesWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   containerH;
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  scrollArea->resize(width, height);
  containerH = container->size().height();
  container->resize(width, containerH);

  foreach (auto i, differenceItems) {
    QSize s = i->size();
    i->resize(width, s.height());
  }
}

/*****************************************************************************!
 * Function : SlotSetFileItem
 *****************************************************************************/
void
SourceDifferencesWindow::SlotSetFileItem
(FileTreeFile* InFileItem)
{
  fileItem = InFileItem;
  ClearDisplay();
  DisplayChanges();
}

/*****************************************************************************!
 * Function : ClearDisplay
 *****************************************************************************/
void
SourceDifferencesWindow::ClearDisplay(void)
{
  foreach (auto i, differenceItems) {
    delete i;
  }
  differenceItems.clear();
}

/*****************************************************************************!
 * Function : DisplayChanges
 *****************************************************************************/
void
SourceDifferencesWindow::DisplayChanges(void)
{
  int                                   h;
  int                                   height;
  int                                   width;
  FileContentsDiff                      diffs;
  QSize                                 s = size();
  int                                   i, n, y;

  width = s.width();
  diffs = fileItem->GetDiffs();
  n = diffs.count();
  y = 0;
  height = 0;
  for (i = 0; i < n; i++) {
    auto s = new SourceDifferencesItem(fileItem, container, y, width, new FileSectionDiff(&diffs[i]));
    connect(s,
            SIGNAL(SignalDifferenceSelected(FileSectionDiff*)),
            this,
            SLOT(SlotDifferenceSelected(FileSectionDiff*)));
    differenceItems << s;
    h = s->size().height();
    y += h;
    height += h;
  }
  container->resize(width, height);
}

/*****************************************************************************!
 * Function : SlotDifferenceSelected
 *****************************************************************************/
void
SourceDifferencesWindow::SlotDifferenceSelected
(FileSectionDiff* InItem)
{
  int                                   targetStartLine;
  int                                   sourceStartLine;
  QString                               typeString;

  typeString = InItem->GetTypeString();
  targetStartLine = InItem->GetTargetStartLine();
  sourceStartLine = InItem->GetStartLine();
  emit SignalTrack1CodeLineChanged(sourceStartLine);
  emit SignalTrack2CodeLineChanged(targetStartLine);
}
