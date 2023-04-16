/*****************************************************************************
 * FILE NAME    : BuildTreeHierarchyTable.cpp
 * DATE         : April 14 2023
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
#include "BuildTreeHierarchyTable.h"
#include "trace.h"
#include "main.h"

/*****************************************************************************!
 * Function : BuildTreeHierarchyTable
 *****************************************************************************/
BuildTreeHierarchyTable::BuildTreeHierarchyTable
() : QScrollArea()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTreeHierarchyTable
 *****************************************************************************/
BuildTreeHierarchyTable::~BuildTreeHierarchyTable
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeHierarchyTable::initialize()
{
  CreateSubWindows();
  InitializeSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeHierarchyTable::CreateSubWindows()
{
  container = new QWidget();
  setWidget(container);
  container->move(0, 0);
  container->resize(size());
  QPalette pal = container->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(128, 128, 0)));
  container->setPalette(pal);
  container->setAutoFillBackground(true);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTreeHierarchyTable::InitializeSubWindows()
{
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeHierarchyTable::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   containerH;
  QSize                                 size;  
  int                                   width;

  size = InEvent->size();
  width = size.width();
  containerH = container->size().height();
  container->resize(width, containerH);
  foreach (auto b, elements) {
    b->resize(width, BUILD_TREE_HIERARCHY_TABLE_ITEM_HEIGHT);
  }
}

/*****************************************************************************!
 * Function : SlotTreeItemSelected
 *****************************************************************************/
void
BuildTreeHierarchyTable::SlotTreeItemSelected
(QString InFilename)
{
  QString                               allLines;
  QStringList                           args;
  QString                               clangExe;
  QStringList                           clangHeaderOptions;
  QStringList                           clangIncludePaths;
  QStringList                           clangOptions;
  QStringList                           errorOutputLines;
  QString                               errorOutputString;
  QString                               excludeLine;
  QStringList                           excludeLines;
  bool                                  found;
  QString                               headerLine;
  QStringList                           headerLines;
  BuildTreeHierarchyTableItem*          item;
  QString                               outputString;
  QProcess                              process;
  QString                               sourcePath = getenv("ACU_SOURCE_DIR");
  int                                   sourcePathLen = sourcePath.length();
  QString                               st2;
  QString                               st;
  int                                   y;

  sourcePath = QDir::toNativeSeparators(sourcePath);
  clangExe = mainSystemConfig->GetClangExecutable();
  clangOptions = mainSystemConfig->GetClangOptions();
  clangIncludePaths = mainSystemConfig->GetClangIncludePaths();
  clangHeaderOptions = mainSystemConfig->GetClangHeaderOptions();
  excludeLines = mainSystemConfig->GetClangHeaderExcludePaths();
  
  (void)clangExe;
  (void)process;
  args << clangOptions;
  args << clangIncludePaths;
  args << clangHeaderOptions;
  args << InFilename;
  
  process.start(clangExe, args);
  process.waitForFinished();
  
  outputString = QString(process.readAllStandardOutput());
  errorOutputString = QString(process.readAllStandardError());

  errorOutputLines = errorOutputString.split("\r\n");
  foreach (headerLine, errorOutputLines) {
    found = false;
    foreach ( excludeLine, excludeLines) {
      if ( headerLine.contains(excludeLine) ) {
        found = true;
        continue;
      }
    }
    if ( !found ) {
      if ( headerLine.isEmpty() ) {
        continue;
      }
      if (headerLine[0] != QChar('.') ) {
        continue;
      }
      st = headerLine.remove(QRegularExpression("^[.]+ "));
      st = QDir::toNativeSeparators(st);
      st2 = st.sliced(0, sourcePathLen);
      if ( st2.compare(sourcePath, Qt::CaseInsensitive) == 0 ) {
        st = st.sliced(sourcePathLen);
      }
      st = QString("$ACU_SOURCE_DIR") + st;
      headerLines << st;
    }
  }

  y = 0;

  container->resize(size().width(), headerLines.count() * BUILD_TREE_HIERARCHY_TABLE_ITEM_HEIGHT);
  headerLines.sort();
  foreach (headerLine, headerLines) {
    item = new BuildTreeHierarchyTableItem(headerLine, container);
    item->show();
    item->move(0, y);
    y += BUILD_TREE_HIERARCHY_TABLE_ITEM_HEIGHT;
    elements << item;
  }
}
