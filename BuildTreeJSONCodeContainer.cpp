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
#include <QTreeWidgetItem>
#include <QHeaderView>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTreeJSONCodeContainer.h"
#include "main.h"
#include "SystemConfig.h"
#include "trace.h"
#include "BuildCompileLine.h"

/*****************************************************************************!
 * Function : BuildTreeJSONCodeContainer
 *****************************************************************************/
BuildTreeJSONCodeContainer::BuildTreeJSONCodeContainer
(CodeTrack* InCodeTrack) : QWidget()
{
  QPalette pal;
  codeTrack = InCodeTrack;
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
  QTreeWidgetItem*                              headerItem;
  QHeaderView*                                  headerView;
  
  jsonFileDisplay = new QTreeWidget(this);
  jsonFileDisplay->move(0, 0);
  jsonFileDisplay->setColumnCount(2);
  headerView = jsonFileDisplay->header();
  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Name");
  headerItem->setText(1, "Value");
  headerView->resizeSection(0, 200);
  jsonFileDisplay->setHeaderItem(headerItem);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::InitializeSubWindows()
{
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  jsonFileDisplay->resize(width, height);
}

/*****************************************************************************!
 * Function : SlotTreeItemSelected
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::SlotTreeItemSelected
(BuildLine* InBuildLine, QString InFilename)
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
  QStringList                           lineArgs;
  
  clangExe = mainSystemConfig->GetClangExecutable();
  clangOptions = mainSystemConfig->GetClangOptions();
  clangIncludePaths = mainSystemConfig->GetClangIncludePaths();
  clangCodeGatherOptions = mainSystemConfig->GetClangCodeGatherOptions();
  excludeLines = mainSystemConfig->GetClangHeaderExcludePaths();

  lineArgs = ((BuildCompileLine*)InBuildLine)->GetFlags();
  args << clangOptions;
  args << clangIncludePaths;
  args << clangHeaderOptions;
  args << clangCodeGatherOptions;
  args << lineArgs;
  args << InFilename;

  st = args.join(" ");
  process.start(clangExe, args);
  process.waitForFinished();
  
  outputString = QString(process.readAllStandardOutput());
  errorOutputString = QString(process.readAllStandardError());
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
}

/*****************************************************************************!
 * Function : ProcessInnerTranslationUnitArray
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessInnerTranslationUnitArray
(QJsonArray InTUArray, QString InFilename)
{
  QSize                                 size2;
  QFont                                 font;
  QString                               fileName;
  bool                                  inTargetFile;
  QStringList                           keys;
  QString                               kind;
  QJsonObject                           locObj;
  QString                               name;
  QJsonObject                           obj;
  QTreeWidgetItem*                      treeItem1;
  QTreeWidgetItem*                      treeItem2;
  QSize                                 size;
  QTreeWidgetItem*                      headerItem;
  
  jsonFileDisplay->clear();
  headerItem = new QTreeWidgetItem();
  size = headerItem->sizeHint(0);
  size.setWidth(400);
  size.setHeight(30);
  
  headerItem->setSizeHint(0, size);

  size2 = headerItem->sizeHint(0);
  
  headerItem->setTextAlignment(0, Qt::AlignCenter | Qt::AlignVCenter);
  headerItem->setTextAlignment(1, Qt::AlignLeft | Qt::AlignVCenter);
  font = headerItem->font(0);
  // font.setBold(true);
  headerItem->setFont(0, font);
  headerItem->setText(0, QString("Name"));
  headerItem->setBackground(0, QBrush(QColor(255, 192, 192)));
  headerItem->setText(1, QString("Value"));
  
  jsonFileDisplay->setHeaderItem(headerItem);

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
    ProcessValue(treeItem1, InTUArray[i]);
    continue;
    keys = obj.keys();

    //!
    foreach ( auto key, keys) {
      treeItem2 = new QTreeWidgetItem(QStringList(key));
      treeItem1->addChild(treeItem2);
      FontifyTreeItem(treeItem1, kind);

      //!
      if ( key == "kind" ) {
        treeItem2->setText(1, kind);
        continue;
      }

      //!
      if ( key == "isUsed" ) {
        bool b = obj[key].toBool();
        treeItem2->setText(1, b ? "True" : "False");
        continue;
      }

      //!
      if ( key == "inner" ) {
        ProcessTopLevelInnerObject(treeItem2, obj[key].toArray());
        continue;
      }

      if ( key == "range" ) {
        ProcessRangeObject(treeItem2, obj[key]);
        continue;
      }
      //!
      if ( key == "type" ) {
        QJsonObject                     obj2 = obj["type"].toObject();
        QString                         qualType = obj2["qualType"].toString();
        int                             n = qualType.indexOf(" ");
        QString                         st = qualType.sliced(0, n);
        treeItem2->setText(1, st);
      }

      //!
      if ( key == "storageClass" ) {
        QString                         storageClass = obj["storageClass"].toString();
        treeItem2->setText(1, storageClass);
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
  QFont                                 font = InTreeItem->font(0);

  font.setBold(true);
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
 * Function : ProcessTopLevelInnerObject
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessTopLevelInnerObject
(QTreeWidgetItem* InTreeItem, QJsonArray InArray)
{
  for (int i = 0; i < InArray.size(); i++) {
    ProcessValue(InTreeItem, InArray[i]);
  }
}
#if 0
  int                                   i;
  QString                               kind;
  QString                               name;
  QJsonObject                           obj;
  QTreeWidgetItem*                      treeItem1;
  QJsonArray                            innerArray;
  
    obj = InArray[i].toObject();
    kind = obj["kind"].toString();
    name = obj["name"].toString();
    treeItem1 = new QTreeWidgetItem();
    InTreeItem->addChild(treeItem1);
    treeItem1->setText(0, kind);
    treeItem1->setText(1, name);
    if ( kind == "ParmVarDecl" ) {
      ProcessValue(treeItem1,  InArray[i]);
    }
    if ( kind == "loc" ) {
      ProcessValue(treeItem1, InArray[i]);
    }
    innerArray = obj["inner"].toArray();
    if ( kind == "CompoundStmt" ) {
      ProcessCompoundStatement(treeItem1, innerArray);
    }
  }
}
#endif
/*****************************************************************************!
 * Function : ProcessCompoundStatement
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessCompoundStatement
(QTreeWidgetItem* InTreeItem, QJsonArray InArray)
{
  for ( int i = 0 ; i < InArray.size(); i++ ) {
    QJsonObject                         obj = InArray[i].toObject();
    QString                             kind = obj["kind"].toString();
    QTreeWidgetItem*                    treeItem1;

    treeItem1 = new QTreeWidgetItem();
    treeItem1->setText(0, kind);
    InTreeItem->addChild(treeItem1);
    if ( kind == "CallExpr" ) {
      ProcessCallExpr(treeItem1, obj);
    }
    if ( kind == "DeclStmt" ) {
      ProcessDeclStmt(treeItem1, obj);
    }
    if ( kind == "loc" ) {
      ProcessDeclStmt(treeItem1, obj);
    }
  }
}

/*****************************************************************************!
 * Function : ProcessCallExpr
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessCallExpr
(QTreeWidgetItem* InTreeItem, QJsonObject InObject)
{
  QString                               name;
  QTreeWidgetItem*                      item;
  QTreeWidgetItem*                      item2;
  QStringList                           keys, keys2;
  QJsonObject                           obj2;
  QJsonArray                            array1;
  QJsonValue                            value;
  
  keys = InObject.keys();
  foreach ( auto key, keys ) {
    item = new QTreeWidgetItem();
    item->setText(0, key);
    value = InObject[key];

    if ( !value.isObject() && !value.isArray() ) {
      ProcessSingleItem(value, item);
      continue;
    }
    InTreeItem->addChild(item);
    if ( key == "inner" ) {
      array1 = value.toArray();
      for ( int i1 = 0 ; i1 < array1.size(); i1++ ) {
        obj2 = array1[i1].toObject();
        keys2 = obj2.keys();
        foreach ( auto key2, keys2) {
          item2 = new QTreeWidgetItem();
          item2->setText(0, key2);
          item->addChild(item2);
          if ( key2 == "name" ) {
            name = obj2[key2].toString();
            InTreeItem->setText(1, name);
          }
        }
      }
    }
  }
}

/*****************************************************************************!
 * Function : ProcessDeclStmt
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessDeclStmt
(QTreeWidgetItem* InTreeItem, QJsonObject InObject)
{
  QStringList                           keys;
  QTreeWidgetItem*                      item;
  
  keys = InObject.keys();
  foreach ( auto key, keys ) {
    item = new QTreeWidgetItem();
    item->setText(0, key);
    InTreeItem->addChild(item);
    ProcessValue(item, InObject[key]);
  }
}

/*****************************************************************************!
 * Function : ProcessSingleItem
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessSingleItem
(QJsonValue InValue, QTreeWidgetItem* InItem)
{
  if ( InValue.isString() ) {
    InItem->setText(1, InValue.toString());
    return;
  }
  if ( InValue.isBool() ) {
    InItem->setText(1, InValue.toBool() ? "true" : "false");
    return;
  }
}  

/*****************************************************************************!
 * Function : ProcessRangeObject
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessRangeObject
(QTreeWidgetItem* InItem, QJsonValue InRangeObject)
{
  ProcessValue(InItem, InRangeObject);
}

/*****************************************************************************!
 * Function : ProcessValue
 *****************************************************************************/
void
BuildTreeJSONCodeContainer::ProcessValue
(QTreeWidgetItem* InItem, QJsonValue InValue)
{
  QJsonValue::Type                      type;

  type = InValue.type();

  switch (type) {
    case QJsonValue::Null : {
      InItem->setText(1, QString("Null"));
      return;
    }
    case QJsonValue::Bool : {
      InItem->setText(1, InValue.toBool() ? "True" : "False");
      return;
    }
    case QJsonValue::String : {
      InItem->setText(1, InValue.toString());
      return;
    }
    case QJsonValue::Double : {
      if ( InValue.isDouble() ) {
        InItem->setText(1, QString("%1").arg(InValue.toDouble()));
        return;
      }
      InItem->setText(1, QString("%1").arg(InValue.toInt()));
      return;
    }
    case QJsonValue::Object : {
      QJsonObject                               obj = InValue.toObject();
      QStringList                               keys = obj.keys();

      foreach ( auto key, keys ) {
        QTreeWidgetItem*                        item;

        item = new QTreeWidgetItem(QStringList(key));
        InItem->addChild(item);
        ProcessValue(item, obj[key]);
      }
      return;
    }
    case QJsonValue::Array : {
      QJsonArray                                obj = InValue.toArray();
      int                                       n = obj.count();
      for ( auto i = 0 ; i < n; i++ ) {
        QTreeWidgetItem*                        item;
        QJsonValue                              val = obj[i];
        QString                                 st;

        st = QString("%1").arg(i);
        if ( val.isObject() ) {
          QJsonObject                           obj2 = val.toObject();
          QJsonValue                            val2 = obj2["kind"];
          if ( val2.isString() ) {
            st = val2.toString();
          }
        }
        item = new QTreeWidgetItem(QStringList(st));
        InItem->addChild(item);
        ProcessValue(item, obj[i]);
      }
      return;
    }
    case QJsonValue::Undefined : {
      break;
    }
  }
}
