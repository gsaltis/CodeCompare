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
() : QTreeWidget()
{
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

}
/*****************************************************************************!
 * Function : SlotTreeItemSelected
 *****************************************************************************/
void
BuildTreeHierarchyTable::SlotTreeItemSelected
(BuildLine* InBuildLine, QString InFilename)
{
  QTreeWidgetItem*                      treeItem;
  int                                   depth;
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
  QString                               outputString;
  QProcess                              process;
  QString                               sourcePath = getenv("ACU_SOURCE_DIR");
  int                                   sourcePathLen = sourcePath.length();
  QString                               st2;
  QString                               st;
  QList<QTreeWidgetItem*>               headerItems;

  (void)InBuildLine;
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

  clear();
  foreach (headerLine, errorOutputLines) {
    
    found = false;
    foreach ( excludeLine, excludeLines) {
      if ( headerLine.contains(excludeLine) ) {
        found = true;
        continue;
      }
    }
    if ( found ) {
      continue;
    }
    if ( headerLine.isEmpty() ) {
      continue;
    }
    if (headerLine[0] != QChar('.') ) {
      continue;
    }

    //!
    depth = headerLine.indexOf(' ') - 1;
    st = headerLine.remove(QRegularExpression("^[.]+ "));
    st = QDir::toNativeSeparators(st);
    st2 = st.sliced(0, sourcePathLen);
    if ( st2.compare(sourcePath, Qt::CaseInsensitive) == 0 ) {
      st = st.sliced(sourcePathLen);
    }
    st = QString("${ACU_SOURCE_DIR}") + st;

    treeItem = new QTreeWidgetItem();
    treeItem->setText(0, st);
    
    if ( depth == 0 ) {
      addTopLevelItem(treeItem);
      headerItems.clear();
      headerItems << treeItem;
      continue;
    }
    if ( depth + 1 == headerItems.size() ) {
      headerItems[depth-1]->addChild(treeItem);
      continue;
    }
    headerItems[depth-1]->addChild(treeItem);
    headerItems << treeItem;
  }
}
