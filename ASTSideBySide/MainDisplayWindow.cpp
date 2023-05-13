/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.cpp
 * DATE         : May 10 2023
 * PROJECT      : ASTSByS
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHeaderView>

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainDisplayWindow.h"
#include "TitledWindow.h"
#include "JSONAST.h"
#include "trace.h"
#include "TUTreeElement.h"
#include "TopTranslationUnitElement.h"

/*****************************************************************************!
 * 
 *****************************************************************************/
#if 0
struct {
  bool operator()(TopTranslationUnitElement* In1, TopTranslationUnitElement* In2) {
    if ( In1->kind < In2->kind ) {
      return true;
    }
    if ( In1->kind > In2->kind ) {
      return false;
    }

    if ( In1->name < In2->name ) {
      return true;
    }

    return false;
  }
} TUElementCompare;
#endif
/*****************************************************************************!
 * Function : MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::MainDisplayWindow
(QString InFilename1, QString InFilename2, QApplication* InApplication) : QWidget()
{
  QPalette                              pal;

  application = InApplication;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(160, 160, 160)));
  setPalette(pal);
  setAutoFillBackground(true);
  filename1 = InFilename1;
  filename2 = InFilename2;
  Initialize();
}

/*****************************************************************************!
 * Function : ~MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::~MainDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
MainDisplayWindow::Initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
MainDisplayWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
MainDisplayWindow::CreateSubWindows()
{
  TUTreeElement*                                item;
  QTreeWidgetItem*                              headerItem;
  QHeaderView*                                  headerView;
  QString                                       jsonFilename1;
  QString                                       jsonFilename2;
  
  splitter = new QSplitter(this);

  //!
  jsonTree1 = new TUTree();
  connect(jsonTree1,
          SIGNAL(itemClicked(QTreeWidgetItem*, int)),
          this,
          SLOT(SlotJSON1TreeClicked(QTreeWidgetItem*, int)));
  connect(jsonTree1,
          SIGNAL(itemExpanded(QTreeWidgetItem*)),
          this,
          SLOT(SlotJSON1TreeExpanded(QTreeWidgetItem*)));
  connect(jsonTree1,
          SIGNAL(itemCollapsed(QTreeWidgetItem*)),
          this,
          SLOT(SlotJSON1TreeCollapsed(QTreeWidgetItem*)));

  dirTree = new DirTree("../BuildDir/Track2", "../BuildDir/Track3");
  
  jsonTree1->setColumnCount(2);
  item = new TUTreeElement(TUTreeElement::TopLevel, "Source", "");
  headerView = jsonTree1->header();
  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Name");
  headerItem->setText(1, "Value");
  headerView->resizeSection(0, 300);
  jsonTree1->addTopLevelItem(item);
  jsonTree1->expandItem(item);
  jsonTree1->setHeaderItem(headerItem);

  //!
  jsonTree2 = new TUTree();
  connect(jsonTree2,
          SIGNAL(itemClicked(QTreeWidgetItem*, int)),
          this,
          SLOT(SlotJSON2TreeClicked(QTreeWidgetItem*, int)));
  connect(jsonTree2,
          SIGNAL(itemExpanded(QTreeWidgetItem*)),
          this,
          SLOT(SlotJSON2TreeExpanded(QTreeWidgetItem*)));
  connect(jsonTree2,
          SIGNAL(itemCollapsed(QTreeWidgetItem*)),
          this,
          SLOT(SlotJSON2TreeCollapsed(QTreeWidgetItem*)));
  
  jsonTree2->setColumnCount(2);
  headerView = jsonTree2->header();
  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Name");
  headerItem->setText(1, "Value");
  headerView->resizeSection(0, 300);
  item = new TUTreeElement(TUTreeElement::TopLevel, "Source", "");
  jsonTree2->addTopLevelItem(item);
  jsonTree2->expandItem(item);
  jsonTree2->setHeaderItem(headerItem);

  jsonTreeContainer1 = new TUTreeContainer(jsonTree1, filename1 + QString(".errors"));
  jsonTreeContainer2 = new TUTreeContainer(jsonTree2, filename2 + QString(".errors"));
  connect(jsonTreeContainer1, TUTreeContainer::SignalSplitterMoved, this, MainDisplayWindow::SlotSetErrorWindowHeight2);
  // connect(jsonTreeContainer2, TUTreeContainer::SignalSplitterMoved, jsonTreeContainer1, TUTreeContainer::SlotSetErrorWindowHeight);

  jsonFilename1 = filename1 + QString(".json");
  jsonFilename2 = filename2 + QString(".json");
  fileWindow1 = new TitledWindow(jsonTreeContainer1, filename1);
  fileWindow2 = new TitledWindow(jsonTreeContainer2, filename2);
  splitter->addWidget(dirTree);
  splitter->addWidget(fileWindow1);
  splitter->addWidget(fileWindow2);
  PopulateASTTree(jsonTree1, jsonFilename1);
  PopulateASTTree(jsonTree2, jsonFilename2);
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
MainDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  splitter->resize(width, height);
}

/*****************************************************************************!
 * Function : ProcessValue
 *****************************************************************************/
void
MainDisplayWindow::ProcessValue
(TUTreeElement* InItem, QJsonValue InValue)
{
  QStringList                           names;
  QString                               callName;
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
        TUTreeElement*                          item;

        item = new TUTreeElement(TUTreeElement::Element, QStringList(key));
        InItem->addChild(item);
        ProcessValue(item, obj[key]);
      }
      return;
    }
    case QJsonValue::Array : {
      QString                                   name = InItem->text(0);
      name += QString("[]");
      InItem->setText(0, name);
      
      QJsonArray                                obj = InValue.toArray();
      int                                       n = obj.count();
      for ( auto i = 0 ; i < n; i++ ) {
        TUTreeElement*                          item;
        QJsonValue                              val = obj[i];
        QString                                 st;

        names = QStringList();
        st = QString("%1").arg(i);
        if ( val.isObject() ) {
          QJsonObject                           obj2 = val.toObject();
          QJsonValue                            val2 = obj2["kind"];
          if ( val2.isString() ) {
            st = val2.toString();
          }
          names << st;
          if ( st == "CallExpr" ) {
            callName = JSONAST::FindCallExprName(obj2);
            names << callName;
          }
        }
        item = new TUTreeElement(TUTreeElement::Element, names);
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

/*****************************************************************************!
 * Function : PopulateASTTree
 * Purpose  : QTreeWidget*
 *****************************************************************************/
void
MainDisplayWindow::PopulateASTTree
(QTreeWidget* InTree, QString InFilename)
{
  QJsonValue                            innerValue;
  QString                               objectFilename;
  QJsonValue                            value;
  TUTreeElement*                        item2;
  QFile                                 file(InFilename);
  QString                               contents;
  QJsonDocument                         doc;
  QJsonObject                           obj;
  TUTreeElement*                        item;
  QStringList                           keys;
  QString                               filename;
  QFileInfo                             fileinfo(InFilename);

  
  filename = fileinfo.completeBaseName();
  item = (TUTreeElement*)InTree->topLevelItem(0);
  file.open(QIODeviceBase::ReadOnly);
  doc = QJsonDocument::fromJson(file.readAll());
  file.close();
  obj = doc.object();
  keys = obj.keys();
  foreach (auto key, keys) {
    value = obj[key];
    if ( key == "inner" ) {
      innerValue = value;
      continue;
    }
    item2 = new TUTreeElement(TUTreeElement::TranslationUnitElement, QStringList(key));
    item->addChild(item2);
    ProcessValue(item2, value);
  }
  ProcessTranslationUnitInner(item, innerValue.toArray(), filename);
  InTree->sortItems(0, Qt::AscendingOrder);
}

/*****************************************************************************!
 * Function : ProcessTranslationUnitInner
 *****************************************************************************/
void
MainDisplayWindow::ProcessTranslationUnitInner
(TUTreeElement* InItem, QJsonArray InArray, QString InFilename)
{
  QString                               name;
  QString                               kind;
  QJsonValue                            value;
  int                                   i;
  QJsonObject                           obj;
  bool                                  inTargetFile;
  QString                               objectFilename;
  int                                   endLine;
  int                                   startLine;
  QList<TopTranslationUnitElement*>      tuElements;

  inTargetFile = false;

  for ( i = 0 ; i < InArray.count(); i++ ) {
    value = InArray[i];
    obj = value.toObject();
    kind = obj["kind"].toString();
    name = obj["name"].toString();
    application->processEvents();
    JSONAST::GetTopLevelLinesNumbers(obj, startLine, endLine, objectFilename);
    QFileInfo                           fileInfo2(objectFilename);
    objectFilename = fileInfo2.fileName();
    if ( objectFilename == InFilename ) {
      inTargetFile = true;
    }
    if ( ! inTargetFile ) {
      continue;
    }
#if 1
    printf("%5d of %lld : %30s : %-60s\r", i + 1, InArray.count(),
           kind.toStdString().c_str(),
           name.toStdString().c_str());
#endif    
    TopTranslationUnitElement* t = new TopTranslationUnitElement(kind, name, value);
#if 0
    tuElements << t;
#endif    
    TUTreeElement* item = CreateTreeItem(InItem, t);
    InItem->addChild(item);
  }
#if 1
  printf("\n");
#endif
#if 0
  std::sort(tuElements.begin(), tuElements.end(), TUElementCompare);
  for ( int i = 0 ; i <  tuElements.count(); i++  ) {
           
    TopTranslationUnitElement* t = tuElements[i];
    printf("%4d of %lld : %s %s\n", i + 1, tuElements.count(),
           t->kind.toStdString().c_str(),
           t->name.toStdString().c_str());
  }
  printf("\n");
#endif  
}

/*****************************************************************************!
 * Function : CreateTreeItem
 *****************************************************************************/
TUTreeElement*
MainDisplayWindow::CreateTreeItem
(TUTreeElement* InItem, TopTranslationUnitElement* InTUElement)
{
  TUTreeElement*                      item;
  item = new TUTreeElement(TUTreeElement::TranslationUnitElement, InTUElement->kind, InTUElement->name);
  InItem->addChild(item);
  FontifyTreeItem(item, InTUElement->content.toObject(), InTUElement->kind);
  ProcessValue(item, InTUElement->content);
  return item;
}

/*****************************************************************************!
 * Function : FontifyTreeItem
 *****************************************************************************/
void
MainDisplayWindow::FontifyTreeItem
(TUTreeElement* InTreeItem, QJsonObject InObject, QString InKind)
{
  QFont                                 font = InTreeItem->font(0);

  font.setBold(true);
  if ( InKind == "EnumDecl" ) {
    InTreeItem->setForeground(0, QBrush(QColor(128, 64, 32)));
    InTreeItem->SetTUType(TUTreeElement::EnumDecl);
    InTreeItem->setFont(0, font);
    return;
  }
  if ( InKind == "VarDecl" ) {
    InTreeItem->setForeground(0, QBrush(QColor(0, 0, 128)));
    InTreeItem->setFont(0, font);
    InTreeItem->SetTUType(TUTreeElement::VarDecl);
    return;
  }
  if ( InKind == "RecordDecl" ) {
    InTreeItem->setForeground(0, QBrush(QColor(128, 0, 128)));
    InTreeItem->setFont(0, font);
    InTreeItem->SetTUType(TUTreeElement::RecordDecl);
    return;
  }
  if ( InKind == "TypedefDecl" ) {
    InTreeItem->setForeground(0, QBrush(QColor(0, 128, 128)));
    InTreeItem->setFont(0, font);
    InTreeItem->SetTUType(TUTreeElement::TypedefDecl);
    return;
  }
  if ( InKind == "FunctionDecl" ) {
    QJsonArray                          innerObject = InObject["inner"].toArray();
    QJsonObject                         compoundStatement = FindElementInInnerObject(innerObject, "CompoundStmt");
    if ( compoundStatement.isEmpty() ) {
      InTreeItem->setForeground(0, QBrush(QColor(128, 128, 0)));
      InTreeItem->SetTUType(TUTreeElement::FunctionDecl);
    } else {
      InTreeItem->setForeground(0, QBrush(QColor(128, 0, 0)));
      InTreeItem->SetTUType(TUTreeElement::FunctionDef);
    }
    InTreeItem->setFont(0, font);
    return;
  }
}

/*****************************************************************************!
 * Function FindElementInInnerObject
 *****************************************************************************/
QJsonObject
MainDisplayWindow::FindElementInInnerObject
(QJsonArray InInnerObject, QString InName)
{
  QJsonObject                           obj;
  QString                               kindString;
  int                                           i;
  int                                           n = InInnerObject.count();

  for (i = 0; i < n; i++) {
    QJsonValue                                  value = InInnerObject[i];
    if ( ! value.isObject() ) {
      continue;
    }
    obj = value.toObject();
    kindString = obj["kind"].toString();
    if ( kindString == InName ) {
      return obj;
    }
  }
  return QJsonObject();
}

/*****************************************************************************!
 * Function : SlotJSON1TreeClicked
 *****************************************************************************/
void
MainDisplayWindow::SlotJSON1TreeClicked
(QTreeWidgetItem*, int)
{
}

/*****************************************************************************!
 * Function : SlotJSON1TreeExpanded
 *****************************************************************************/
void
MainDisplayWindow::SlotJSON1TreeExpanded
(QTreeWidgetItem* InItem)
{
  TUTreeElement*                        te;
  TUTreeElement*                        element;
  TUTreeElement::Type                   type;
  
  element = (TUTreeElement*)InItem;
  type = element->GetType();
  if ( type != TUTreeElement::TranslationUnitElement ) {
    return;
  }
  QString                               name = element->text(1);
  TUTreeElement::TranslationUnitType    tuType = element->GetTUType();
  
  te = jsonTree2->FindElementByNameType(name, tuType);
  if ( NULL == te ) {
    return;
  }
  
  jsonTree2->expandItem(te);
  if ( tuType == TUTreeElement::FunctionDef ) {
    ExpandFunction(jsonTree2, te);
    ExpandFunction(jsonTree1, element);
  }
}

/*****************************************************************************!
 * Function : ExpandFunction
 *****************************************************************************/
void
MainDisplayWindow::ExpandFunction
(TUTree* InTree, TUTreeElement* InElement)
{
  TUTreeElement*                        teinner2;
  TUTreeElement*                        tecs;
  TUTreeElement*                        teinner;

  teinner = InElement->FindChildByName("inner[]");
  if ( NULL == teinner ) {
    return;
  }
  tecs = teinner->FindChildByName("CompoundStmt");
  if ( tecs == NULL ) {
    return;
  }
  teinner2 = tecs->FindChildByName("inner[]");
  if ( NULL == teinner2 ) {
    return;
  }
  InTree->expandItem(teinner);
  InTree->expandItem(tecs);
  InTree->expandItem(teinner2);
}

/*****************************************************************************!
 * Function : SlotJSON1TreeCollapsed
 *****************************************************************************/
void
MainDisplayWindow::SlotJSON1TreeCollapsed
(QTreeWidgetItem* InItem)
{
  TUTreeElement*                        element;
  TUTreeElement*                        te;

  element = (TUTreeElement*)InItem;
  QString                               name = element->text(1);
  
  te = jsonTree2->FindElementByNameType(name, element->GetTUType());
  if ( NULL == te ) {
    return;
  }
  jsonTree2->collapseItem(te);
}

/*****************************************************************************!
 * Function : SlotJSON2TreeClicked
 *****************************************************************************/
void
MainDisplayWindow::SlotJSON2TreeClicked
(QTreeWidgetItem*, int)
{
}

/*****************************************************************************!
 * Function : SlotJSON2TreeExpanded
 *****************************************************************************/
void
MainDisplayWindow::SlotJSON2TreeExpanded
(QTreeWidgetItem* )
{
}

/*****************************************************************************!
 * Function : SlotJSON2TreeCollapsed
 *****************************************************************************/
void
MainDisplayWindow::SlotJSON2TreeCollapsed
(QTreeWidgetItem* )
{
}

/*****************************************************************************!
 * Function : SlotSetErrorWindowHeight2
 *****************************************************************************/
void
MainDisplayWindow::SlotSetErrorWindowHeight2
(int InPosition )
{
  jsonTreeContainer2->SlotSetErrorWindowHeight(InPosition);
}
