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
() : QTableWidget()
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
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeHierarchyTable::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTreeHierarchyTable::InitializeSubWindows()
{
  setColumnCount(1);
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeHierarchyTable::resizeEvent
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
 * Function : SlotTreeItemSelected
 *****************************************************************************/
void
BuildTreeHierarchyTable::SlotTreeItemSelected
(QString InFilename)
{
  int                                   i;
  QString                               st2;
  bool                                  found;
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
  QString                               headerLine;
  QStringList                           headerLines;
  QString                               outputString;
  QProcess                              process;
  QString                               st;
  QString                               sourcePath = getenv("ACU_SOURCE_DIR");
  int                                   sourcePathLen = sourcePath.length();

  sourcePath = QDir::toNativeSeparators(sourcePath);
  TRACE_FUNCTION_QSTRING(sourcePath);
  clangExe = mainSystemConfig->GetClangExecutable();
  clangOptions = mainSystemConfig->GetClangOptions();
  clangIncludePaths = mainSystemConfig->GetClangIncludePaths();
  clangHeaderOptions = mainSystemConfig->GetClangHeaderOptions();
  excludeLines = mainSystemConfig->GetClangHeaderExcludePaths();
  TRACE_FUNCTION_INT(excludeLines.count());
  
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
      TRACE_FUNCTION_QSTRING(st);
      headerLines << st;
    }
  }
  i = 0;
  setRowCount(headerLines.count());
  foreach (headerLine, headerLines) {
    setItem(i, 0, new QTableWidgetItem(headerLine));
    i++;
  }
}
