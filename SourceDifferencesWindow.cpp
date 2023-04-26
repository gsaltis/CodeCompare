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
 * Function : SlotSetTreeItem
 *****************************************************************************/
void
SourceDifferencesWindow::SlotSetTreeItem
(FileTreeWidgetItem* InTreeItem)
{
  treeItem = InTreeItem;
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
  int                                   height;
  int                                   width;
  FileContentsDiff                      diffs;
  QSize                                 s = size();
  int                                   i, n, y;

  width = s.width();
  diffs = treeItem->GetDifferences();
  n = diffs.count();
  y = 0;
  height = n * SOURCE_DIFFERENCES_ITEM_HEIGHT;
  container->resize(width, height);
  for (i = 0; i < n; i++) {
    differenceItems << new SourceDifferencesItem(container, y, width, &diffs[i]);
    y += SOURCE_DIFFERENCES_ITEM_HEIGHT;
  }
}
