/*****************************************************************************
 * FILE NAME    : BuildTreeJSONCodeContainer.cpp
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
#include <QJsonDocument>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTreeJSONCodeContainer.h"
#include "main.h"
#include "SystemConfig.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildTreeJSONCodeContainer
 *****************************************************************************/
BuildTreeJSONCodeContainer::BuildTreeJSONCodeContainer
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
 * Function : ~BuildTreeJSONCodeContainer
 *****************************************************************************/
BuildTreeJSONCodeContainer::~BuildTreeJSONCodeContainer
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::initialize()
{
  CreateSubWindows();
  InitializeSubWindows();  
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::CreateSubWindows()
{
  jsonFileDisplay = new QTreeWidget(this);
  jsonFileDisplay->move(0, 0);
  jsonFileDisplay->setColumnCount(2);
  // jsonFileDisplay->setHeaderItem(new QTreeWidgetItem(QStringList("", "")));
  
  errorWindow = new QTextEdit(this);
  errorWindowHeight = 200;
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::InitializeSubWindows()
{
  QPalette                              pal;
  QColor                                background = QColor(0, 0, 200);
  
  errorWindow->setTextBackgroundColor(background);
  errorWindow->setTextColor(QColor(240, 240, 0));
  pal = errorWindow->palette();
  pal.setBrush(QPalette::Base, QBrush(background));
  errorWindow->setPalette(pal);
  errorWindow->setAutoFillBackground(true);
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   errorWindowY;
  int                                   fileDisplayH;
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  fileDisplayH = height  - errorWindowHeight;

  errorWindowY = fileDisplayH;
  jsonFileDisplay->resize(width, fileDisplayH);
  errorWindow->move(0, errorWindowY);
  errorWindow->resize(width, errorWindowHeight);
}

/*****************************************************************************!
 * Function : SlotTreeItemSelected
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::SlotTreeItemSelected
(QString InFilename)
{
  QStringList                           topKeys;
  QJsonObject                           topObject;
  QString                               allLines;
  QStringList                           args;
  QString                               clangExe;
  QStringList                           clangHeaderOptions;
  QStringList                           clangOptions;
  QStringList                           clangCodeGatherOptions;
  QStringList                           clangIncludePaths;
  QStringList                           errorOutputLines;
  QString                               errorOutputString;
  QString                               excludeLine;
  QStringList                           excludeLines;
  QString                               headerLine;
  QStringList                           headerLines;
  QString                               outputString;
  QProcess                              process;
  QString                               st2;
  QString                               st;
  QJsonDocument                         jsonCodeDoc;
  
  clangExe = mainSystemConfig->GetClangExecutable();
  clangOptions = mainSystemConfig->GetClangOptions();
  clangIncludePaths = mainSystemConfig->GetClangIncludePaths();
  clangCodeGatherOptions = mainSystemConfig->GetClangCodeGatherOptions();
  excludeLines = mainSystemConfig->GetClangHeaderExcludePaths();
  
  args << clangOptions;
  args << clangIncludePaths;
  args << clangHeaderOptions;
  args << clangCodeGatherOptions;
  args << InFilename;

  st = args.join(" ");
  process.start(clangExe, args);
  process.waitForFinished();
  
  outputString = QString(process.readAllStandardOutput());
  errorOutputString = QString(process.readAllStandardError());
  errorWindow->setText(errorOutputString);
  jsonCodeDoc = QJsonDocument::fromJson(outputString.toLatin1());
  topObject = jsonCodeDoc.object();
  topKeys = topObject.keys();

  foreach (st, topKeys) {
    QJsonValue                          value = topObject[st];
    if ( value.isObject() ) {
      QStringList                       keys;
      QJsonObject                       obj;

      obj = value.toObject();
      keys = obj.keys();
      continue;
    }
    if ( st == "inner" ) {
      if ( value.isArray() ) {
        QJsonArray array = value.toArray();
        ProcessInnerTranslationUnitArray(array, InFilename);
      }
      continue;
    }
  }
  
#if 0
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
#endif
}

/*****************************************************************************!
 * Function : ProcessInnerTranslationUnitArray
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessInnerTranslationUnitArray
(QJsonArray InTUArray, QString InFilename)
{
  QString                               fileName;
  bool                                  inTargetFile;
  QStringList                           keys;
  QString                               kind;
  QJsonObject                           locObj;
  QString                               name;
  QJsonObject                           obj;
  QTreeWidgetItem*                      treeItem1;
  QTreeWidgetItem*                      treeItem2;

  jsonFileDisplay->clear();
  inTargetFile = false;
  for ( int i = 0 ; i < InTUArray.size() ; i++ ) {
    obj = InTUArray[i].toObject();
    kind = obj["kind"].toString();
    locObj = obj["loc"].toObject();
    if ( locObj.isEmpty() ) {
      continue;
    }
    fileName = locObj["file"].toString();
    if ( fileName == InFilename ) {
      inTargetFile = true;
    }
    if ( ! inTargetFile ) {
      continue;
    }
    name = obj["name"].toString();
    treeItem1 = new QTreeWidgetItem(QStringList(name));
    jsonFileDisplay->addTopLevelItem(treeItem1);
    keys = obj.keys();
    foreach ( auto key, keys) {
      treeItem2 = new QTreeWidgetItem(QStringList(key));
      treeItem1->addChild(treeItem2);
      FontifyTreeItem(treeItem1, kind);
      if ( key == "kind" ) {
        treeItem2->setText(1, kind);
        continue;
      }
      if ( key == "isUsed" ) {
        bool b = obj[key].toBool();
        treeItem2->setText(1, b ? "True" : "False");
        continue;
      }
      if ( key == "inner" ) {
        ProcessInnerObject(treeItem2, obj[key].toArray());
        continue;
      }
    }
  }
}

/*****************************************************************************!
 * Function : FontifyTreeItem
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::FontifyTreeItem
(QTreeWidgetItem* InTreeItem, QString InKind)
{
  QFont                                 font = QFont("", 9, QFont::Bold);
  if ( InKind == "VarDecl" ) {
    InTreeItem->setForeground(0, QBrush(QColor(0, 0, 128)));
    InTreeItem->setFont(0, font);
    return;
  }
  if ( InKind == "FunctionDecl" ) {
    InTreeItem->setForeground(0, QBrush(QColor(128, 0, 0)));
    InTreeItem->setFont(0, font);
    return;
  }
}

/*****************************************************************************!
 * Function : ProcessInnerObject
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessInnerObject
(QTreeWidgetItem* InTreeItem, QJsonArray InArray)
{
  int                                   i;
  QString                               kind;
  QString                               name;
  QJsonObject                           obj;
  QTreeWidgetItem*                      treeItem1;

  for (i = 0; i < InArray.size(); i++) {
    obj = InArray[i].toObject();
    kind = obj["kind"].toString();
    name = obj["name"].toString();
    treeItem1 = new QTreeWidgetItem();
    InTreeItem->addChild(treeItem1);
    treeItem1->setText(0, kind);
    treeItem1->setText(1, name);
  }
}
