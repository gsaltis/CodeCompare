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
#include "main.h"
#include "BuildLine.h"
#include "BuildLineSet.h"
#include "BuildCompileLine.h"
#include "BuildForLine.h"
#include "BuildARLine.h"
#include "BuildTreeItem.h"
#include "BuildTreeItemTop.h"
#include "BuildTreeItemComponent.h"
#include "BuildTreeItemSubSection.h"

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
  QString                                       jsonFilename1;
  QString                                       jsonFilename2;

  splitter = new QSplitter(this);

  //!
  jsonTree1 = new TUTree(filename1);
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

  dirTree = new DirTree(mainSystemConfig->GetSourceASTTrack1Path(),
                        mainSystemConfig->GetSourceASTTrack2Path());
  dirTreeContainer = new DirTreeContainer(dirTree);
  
  dirTreeContainer->resize(400, 0);
  connect(dirTree, DirTree::SignalFileSelected, this, MainDisplayWindow::SlotDirFileSelected);

  buildTree = new BuildTree(mainSystemConfig->GetSourceASTTrack1Path(),
                            mainSystemConfig->GetSourceASTTrack2Path());
  buildTreeContainer = new BuildTreeContainer(buildTree);
  buildTreeBinary = new BuildTreeItemSection("Binary");
  buildTreeCGI = new BuildTreeItemSection("CGI");
  buildTreeSharedObject = new BuildTreeItemSection("Shared Object");
  buildTreeOther = new BuildTreeItemSection("Other");
  buildTree->addTopLevelItem(buildTreeBinary);
  buildTree->addTopLevelItem(buildTreeSharedObject);
  buildTree->addTopLevelItem(buildTreeCGI);
  buildTree->addTopLevelItem(buildTreeOther);
  
                             dirBuildContainer = new DirBuildContainer(dirTreeContainer, buildTreeContainer);;
  dirBuildContainer->resize(400, 0);
  
  //!
  jsonTree2 = new TUTree(filename2);
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
  
  jsonTreeContainer1 = new TUTreeContainer(jsonTree1, filename1 + QString(".errors"));
  jsonTreeContainer2 = new TUTreeContainer(jsonTree2, filename2 + QString(".errors"));
  connect(jsonTreeContainer1, TUTreeContainer::SignalSplitterMoved, this, MainDisplayWindow::SlotSetErrorWindowHeight2);

  jsonFilename1 = filename1 + QString(".json");
  jsonFilename2 = filename2 + QString(".json");
  fileWindow1 = new TitledWindow(jsonTreeContainer1, filename1);
  fileWindow2 = new TitledWindow(jsonTreeContainer2, filename2);

  splitter->addWidget(dirBuildContainer);
  splitter->addWidget(fileWindow1);
  splitter->addWidget(fileWindow2);
  PopulateASTTree(jsonTree1, jsonFilename1);
  PopulateASTTree(jsonTree2, jsonFilename2);
  FlagTranslationUnitDifferences();
  CreateBuildTree();
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
  QString                               declName;
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

        item = new TUTreeElement(TUTreeElement::Element, QStringList(key), obj[key]);
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
          } else if ( st == "DeclStmt" ) {
            declName = JSONAST::FindDeclStmtName(obj2);
            names << declName;
          } else if ( st == "ParmVarDecl" ) {
            names << obj2["name"].toString();
          }
        }
        item = new TUTreeElement(TUTreeElement::Element, names, val);
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
  TUTree*                               tuTree;
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

  item = new TUTreeElement(TUTreeElement::TopLevel, "Source", "", QJsonValue());
  tuTree = (TUTree*)InTree;
  tuTree->clear();
  tuTree->AddElement(item);
  tuTree->expandItem(item);
  
  filename = fileinfo.completeBaseName();
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
    item2 = new TUTreeElement(TUTreeElement::TranslationUnitElement, QStringList(key), value);
    tuTree->AddElementToElements(item2);
    item->addChild(item2);
    ProcessValue(item2, value);
  }
  ProcessTranslationUnitInner(tuTree, item, innerValue.toArray(), filename);
  // InTree->sortItems(0, Qt::AscendingOrder);
}

/*****************************************************************************!
 * Function : ProcessTranslationUnitInner
 *****************************************************************************/
void
MainDisplayWindow::ProcessTranslationUnitInner
(TUTree* InTree, TUTreeElement* InItem, QJsonArray InArray, QString InFilename)
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
#if 0
    printf("%5d of %lld : %30s : %-60s\r", i + 1, InArray.count(),
           kind.toStdString().c_str(),
           name.toStdString().c_str());
#endif    
    TopTranslationUnitElement* t = new TopTranslationUnitElement(kind, name, value);
    TUTreeElement* item = CreateTreeItem(InItem, t);
    InItem->addChild(item);
    InTree->AddElementToElements(item);
  }
#if 0  
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
  item = new TUTreeElement(TUTreeElement::TranslationUnitElement, InTUElement->kind, InTUElement->name, InTUElement->content);
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
(QTreeWidgetItem* InItem, int)
{
  QString                               section;
  QString                               section2;
  int                                   end;
  int                                   begin;
  int                                   lineNumber;
  TUTreeElement*                        element;
  TUTreeElement*                        element2;
  QJsonValue                            value;
  QJsonValue                            value2;

  //!
  element = (TUTreeElement*)InItem;
  if ( element->GetType() != TUTreeElement::TranslationUnitElement ) {
    return;
  }
  jsonTreeContainer1->ClearTextWindow();
  value = element->GetJSONValue();
  JSONAST::GetTopLevelRangeInfo(value, lineNumber, begin, end);
  section = jsonTree1->GetFileSection(begin, end);
  jsonTreeContainer1->SetTextSection(section, lineNumber);
  jsonTreeContainer1->DisplayTextWindow();

  //!
  jsonTreeContainer2->DisplayTextWindow();
  jsonTreeContainer2->ClearTextWindow();

  //!
  element2 = jsonTree2->FindElementByNameType(element->text(1), element->GetTUType());
  if ( NULL == element2 ) {
    return;
  }
  value2 = element2->GetJSONValue();
  JSONAST::GetTopLevelRangeInfo(value2, lineNumber, begin, end);
  section2 = jsonTree2->GetFileSection(begin, end);
  jsonTreeContainer2->SetTextSection(section2, lineNumber);
} 

/*****************************************************************************!
 * Function : CheckForVarDeclDifference
 *****************************************************************************/
void
MainDisplayWindow::CheckForVarDeclDifference
(TUTreeElement*                         InElement)
{
  QJsonValue                            content1;
  QJsonValue                            content2;
  QString                               section1;
  QString                               section2;
  int                                   begin1;
  int                                   end1;
  int                                   begin2;
  int                                   end2;
  int                                   lineNumber;
  TUTreeElement*                        element2;
  bool                                  b;

  element2 = jsonTree2->FindElementByNameType(InElement->text(1), TUTreeElement::VarDecl);
  if ( NULL == element2 ) {
    return;
  }
  content1 = InElement->GetJSONValue();
  content2 = element2->GetJSONValue();
  JSONAST::GetTopLevelRangeInfo(content1, lineNumber, begin1, end1);
  JSONAST::GetTopLevelRangeInfo(content2, lineNumber, begin2, end2);
  section1 = jsonTree1->GetFileSection(begin1, end1);
  section2 = jsonTree2->GetFileSection(begin2, end2);
  
  b = section1 == section2;
  if ( b ) {
    InElement->setText(2, "TRUE");
  } else {
    InElement->setText(2, "FALSE");
    InElement->setForeground(2, QBrush(QColor(192, 0, 0)));
    for ( int i = 0; i < 3 ; i++ ) {
      InElement->setBackground(i, QBrush(QColor(240, 240, 240)));
    }
    QFont f = InElement->font(2);
    f.setBold(true);
    InElement->setFont(2, f);
  }
}

/*****************************************************************************!
 * Function : CheckForFunctionDefDifference
 *****************************************************************************/
void
MainDisplayWindow::CheckForFunctionDefDifference
(TUTreeElement*                         InElement)
{
  QJsonValue                            content1;
  QJsonValue                            content2;
  QString                               section1;
  QString                               section2;
  int                                   begin1;
  int                                   end1;
  int                                   lineNumber;
  int                                   begin2;
  int                                   end2;
  TUTreeElement*                        element2;
  bool                                  b;

  element2 = jsonTree2->FindElementByNameType(InElement->text(1), TUTreeElement::FunctionDef);
  if ( NULL == element2 ) {
    return;
  }
  content1 = InElement->GetJSONValue();
  content2 = element2->GetJSONValue();
  JSONAST::GetTopLevelRangeInfo(content1, lineNumber, begin1, end1);
  JSONAST::GetTopLevelRangeInfo(content2, lineNumber, begin2, end2);
  section1 = jsonTree1->GetFileSection(begin1, end1);
  section2 = jsonTree2->GetFileSection(begin2, end2);
  b = CompareCodeSections(section1, section2);
  if ( InElement->text(1) == "WatchDog_Feed" ) {
  }
  if ( b ) {
    InElement->setText(2, "TRUE");
  } else {
    InElement->setText(2, "FALSE");
    InElement->setForeground(2, QBrush(QColor(192, 0, 0)));
    for ( int i = 0; i < 3 ; i++ ) {
      InElement->setBackground(i, QBrush(QColor(240, 240, 240)));
    }
    QFont f = InElement->font(2);
    f.setBold(true);
    InElement->setFont(2, f);
  }
}

/*****************************************************************************!
 * Function : CheckForFunctionDeclDifference
 *****************************************************************************/
void
MainDisplayWindow::CheckForFunctionDeclDifference
(TUTreeElement*                         InElement)
{
  QJsonValue                            content1;
  QJsonValue                            content2;
  QString                               section1;
  QString                               section2;
  int                                   begin1;
  int                                   end1;
  int                                   begin2;
  int                                   lineNumber;
  int                                   end2;
  TUTreeElement*                        element2;
  bool                                  b;

  element2 = jsonTree2->FindElementByNameType(InElement->text(1), InElement->GetTUType());
  if ( NULL == element2 ) {
    return;
  }
  content1 = InElement->GetJSONValue();
  content2 = element2->GetJSONValue();
  JSONAST::GetTopLevelRangeInfo(content1, lineNumber, begin1, end1);
  JSONAST::GetTopLevelRangeInfo(content2, lineNumber, begin2, end2);
  section1 = jsonTree1->GetFileSection(begin1, end1);
  section2 = jsonTree2->GetFileSection(begin2, end2);

  b = CompareCodeSections(section1, section2);
  if ( b ) {
    InElement->setText(2, "TRUE");
  } else {
    InElement->setText(2, "FALSE");
    InElement->setForeground(2, QBrush(QColor(192, 0, 0)));
    for ( int i = 0; i < 3 ; i++ ) {
      InElement->setBackground(i, QBrush(QColor(240, 240, 240)));
    }
    QFont f = InElement->font(2);
    f.setBold(true);
    InElement->setFont(2, f);
  }
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
(QTreeWidgetItem* , int)
{
  //  TUTreeElement*                                element = (TUTreeElement*)InItem;
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

/*****************************************************************************!
 * Function : SlotDirFileSelected
 *****************************************************************************/
void
MainDisplayWindow::SlotDirFileSelected
(QString InFilename)
{
  QString                               basename1;
  QString                               basename2;
  QDir                                  d;
  QString                               jsonFilename1;
  QString                               jsonFilename2;
  QString                               errorFilename1;
  QString                               errorFilename2;

  basename1 = mainSystemConfig->GetSourceASTTrack1Path() + QString("/") + InFilename;
  basename1 = d.toNativeSeparators(basename1);
  
  basename2 = mainSystemConfig->GetSourceASTTrack2Path() + QString("/") + InFilename;
  basename2 = d.toNativeSeparators(basename2);

  filename1 = basename1;
  filename2 = basename2;

  jsonFilename1 = filename1 + ".json";
  jsonFilename2 = filename2 + ".json";
  errorFilename1 = filename1 + ".errors";
  errorFilename2 = filename2 + ".errors";
  
  PopulateASTTree(jsonTree1, jsonFilename1);
  PopulateASTTree(jsonTree2, jsonFilename2);
  jsonTree1->SetFilename(filename1);
  jsonTree2->SetFilename(filename2);
  jsonTreeContainer1->SetErrorFilename(errorFilename1);
  jsonTreeContainer2->SetErrorFilename(errorFilename2);  
  FlagTranslationUnitDifferences();
}

/*****************************************************************************!
 * Function : FlagTranslationUnitDifferences
 *****************************************************************************/
void
MainDisplayWindow::FlagTranslationUnitDifferences(void)
{
  FlagTranslationUnitDifferences(jsonTree1, jsonTree2);
  FlagTranslationUnitDifferences(jsonTree2, jsonTree1);
}

/*****************************************************************************!
 * Function : FlagTranslationUnitDifferences
 *****************************************************************************/
void
MainDisplayWindow::FlagTranslationUnitDifferences
(TUTree* InTree1, TUTree* InTree2)
{
  QFont                                 font;
  int                                   n;
  int                                   i;
  TUTreeElement*                        top;
  TUTreeElement*                        item2;

  top = (TUTreeElement*)InTree1->topLevelItem(0);
  n = top->childCount();
  for (i = 0; i < n; i++) {
    TUTreeElement*                      item = (TUTreeElement*)top->child(i);
    QString                             s2 = item->text(1);
    TUTreeElement::TranslationUnitType  tutype;

    tutype = item->GetTUType();
    item2 = InTree2->FindElementByNameType(s2, tutype);
    if ( NULL == item2 ) {
      item->setForeground(1, QBrush(QColor(128, 0, 0)));
      continue;
    }

    font = item2->font(1);
    font.setBold(true);
    item2->setFont(1, font);
    item->setFont(1, font);

    item->setForeground(1, QBrush(QColor(0, 128, 0)));
    item2->setForeground(1, QBrush(QColor(0, 128, 0)));
    if ( item->GetTUType() == TUTreeElement::VarDecl ) {
      CheckForVarDeclDifference(item);
      continue;
    }
    if ( item->GetTUType() == TUTreeElement::FunctionDef ) {
      CheckForFunctionDefDifference(item);
    }
    if ( item->GetTUType() == TUTreeElement::FunctionDecl ) {
      CheckForFunctionDeclDifference(item);
    }
  }
}

/*****************************************************************************!
 * Function : CompareCodeSections
 *****************************************************************************/
bool
MainDisplayWindow::CompareCodeSections
(QString InSection1, QString InSection2)
{
  QStringList                           lines1;
  QStringList                           lines2;
  QString                               line1;
  QString                               line2;
  int                                   count1;
  int                                   count2;
  int                                   i;
  int                                   len1;
  int                                   len2;

  lines1 = InSection1.split("\n");
  lines2 = InSection2.split("\n");
  count1 = lines1.count();
  count2 = lines2.count();
  if ( count1 != count2 ) {
    return false;
  }

  for ( i = 0 ; i < count1; i++ ) {
    line1 = lines1[i];
    line2 = lines2[i];
    len1 = line1.length();
    len2 = line2.length();

    if ( line1[len1-1] == QChar('\r') ) {
      len1--;
      line1 = line1.sliced(0, len1);
    }
    if ( line2[len2-1] == QChar('\r') ) {
      len2--;
      line2 = line2.sliced(0, len2);
    }
    
    if ( line1 != line2 ) {
      return false;
    }
  }
  return true;
}

/*****************************************************************************!
 * Function : CreateBuildTree
 *****************************************************************************/
void
MainDisplayWindow::CreateBuildTree(void)
{
  QString                               track1Name;
  BuildLineSet*                         buildLines;
  
  track1Name = mainSystemConfig->GetSourceASTTrack1Path();
  buildLines = new BuildLineSet();
  CreateBuildTreeDir(track1Name, buildLines);
  ProcessBuildLines(track1Name, buildLines);
  buildTreeBinary->sortChildren(0, Qt::AscendingOrder);
  buildTreeCGI->sortChildren(0, Qt::AscendingOrder);
  buildTreeSharedObject->sortChildren(0, Qt::AscendingOrder);
}

/*****************************************************************************!
 * Function : CreateBuildTreeDir
 *****************************************************************************/
void
MainDisplayWindow::CreateBuildTreeDir
(QString InDirName, BuildLineSet* InBuildLineSet)
{
  QString                               dirName;
  QString                               fullFilePath;
  QDir                                  dir;
  QFileInfoList                         fileInfoList;
  int                                   i, n;
  QFileInfo                             info;
  QString                               buildFilename;
  
  dir.setPath(InDirName);

  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  dir.setSorting(QDir::Name);
  fileInfoList = dir.entryInfoList();
  n = fileInfoList.size();
  for (i = 0; i < n; i++) {
    info = fileInfoList.at(i);
    fullFilePath = info.canonicalFilePath();
    buildFilename = fullFilePath + "/build.txt";
    buildFilename = QDir::toNativeSeparators(buildFilename);
    dirName = info.fileName();
    if ( dir.exists(buildFilename) ) {
    }
    GetBuildLines(buildFilename, InBuildLineSet);
    CreateBuildTreeDir(fullFilePath, InBuildLineSet);
  }
}

/*****************************************************************************!
 * Function : GetBuildLines
 *****************************************************************************/
void
MainDisplayWindow::GetBuildLines
(QString InFilePath, BuildLineSet* InBuildLines)
{
  QString                               command;
  QStringList                           lineParts;
  QString                               line;
  QStringList                           lines;
  QString                               content;
  QFile                                 file(InFilePath);

  if ( ! file.open(QIODeviceBase::ReadOnly) ) {
    return;
  }
  content = QString(file.readAll());
  lines = content.split("\n", Qt::SkipEmptyParts);
  for ( int i = 0; i < lines.size(); i++ ) {
    line = lines[i];
    lineParts = BuildLine::GetLineElements(line);
    command = lineParts[0];
    if ( command[0] == QChar('#') ) {
      continue;
    }
    if ( command == "gcc" ) {
      BuildCompileLine*                 compileLine = new BuildCompileLine();
      compileLine->ParseLine(line);      
      InBuildLines->AppendLine(compileLine);
      continue;
    }

    if ( command == "ln" ) {
      // Nothing to be done for ln command
      continue;
    }

    if ( command == "echo" ) {
      // Nothing to be done for echo command
      continue;
    }

    if ( command == "ranlib" ) {
      // Nothing to be done for ranlib command
      continue;
    }

    if ( command == "ar" ) {
      BuildARLine*                      arLine = new BuildARLine();
      arLine->ParseLine(line);
      InBuildLines->AppendLine(arLine);
      continue;
    }
    
    if ( command.sliced(0, 4) == "make" ) {
      // Nothing to be done for make command
      continue;
    }
    if ( command == "for" ) {
      BuildForLine*                     forLine = new BuildForLine();
      forLine->ParseLine(line);
      InBuildLines->AppendLine(forLine);
      continue;
    }
    TRACE_FUNCTION_QSTRING(lineParts[0]);

  }
  file.close();
}

/*****************************************************************************!
 * Function : ProcessBuildLines
 *****************************************************************************/
void
MainDisplayWindow::ProcessBuildLines
(QString , BuildLineSet* InBuildLines)
{
  QStringList                           sources;
  QStringList                           libs;
  BuildCompileLine*                     compileLine;
  BuildARLine*                          arLine;
  QString                               target;
  int                                   i, n;
  BuildTreeItemTop*                     topItem;
  
  n = InBuildLines->GetLineCount();

  for (i = 0; i < n; i++) {
    BuildLine*                          line;

    line = InBuildLines->GetLineByIndex(i);
    switch ( line->GetType() ) {
      case BuildLine::TypeCompile : {
        compileLine = (BuildCompileLine*)line;
        target = compileLine->GetTarget();
        if ( compileLine->GetIsTargetObject() ) {
          break;
        }
        
        topItem = new BuildTreeItemTop();
        topItem->setText(0, target);
        QFileInfo                       info(target);
        QString                         suffix;

        suffix = info.suffix();
        if ( suffix == "so" ) {
          if ( !buildTreeSharedObject->ElementExists(target) ) {
            buildTreeSharedObject->addChild(topItem);
          }
          buildTreeSharedObject->addChild(topItem);
        } else if ( suffix == "cgi" ) {
          if ( !buildTreeCGI->ElementExists(target) ) {
            buildTreeCGI->addChild(topItem);
          }
        } else if ( suffix == "" ) {
          if ( !buildTreeBinary->ElementExists(target) ) {
            buildTreeBinary->addChild(topItem);
          }
        } else {
          buildTree->addTopLevelItem(topItem);
        }
        sources = compileLine->GetSources();
        libs = compileLine->GetLibraries();
        ProcessBuildLineSources(topItem, sources, InBuildLines);
        ProcessBuildLineLibs(topItem, libs);
        break;
      }
      case BuildLine::TypeAR : {
        arLine = (BuildARLine*)line;
        target = arLine->GetTarget();
        sources = arLine->GetSources();
        topItem = new BuildTreeItemTop();
        topItem->setText(0, target);
        buildTreeOther->addChild(topItem);
        ProcessBuildLineSources(topItem, sources, InBuildLines);
        break;
      }
      default :
        break;
    }
  }
}

/*****************************************************************************!
 * Function : ProcessBuildLineSources
 *****************************************************************************/
void
MainDisplayWindow::ProcessBuildLineSources
(BuildTreeItem* InItem, QStringList InSources, BuildLineSet* InLineSet)
{
  QStringList                           sources;
  BuildLine*                            buildLine;
  BuildTreeItemComponent*               sourceItem;
  BuildTreeItemSubSection*              subSection;

  
  if ( InSources.size() == 0 ) {
    return;
  }

  subSection = new BuildTreeItemSubSection("Sources");
  InItem->addChild(subSection);
  
  foreach ( auto s, InSources ) {
    sourceItem = new BuildTreeItemComponent();
    sourceItem->setText(0, s);
    subSection->addChild(sourceItem);
    buildLine = InLineSet->GetLineByTargetName(s);
    if ( buildLine == NULL ) {
      continue;
    }
    if ( buildLine->GetType() == BuildLine::TypeCompile ) {
      BuildCompileLine*                 compileLine;
      compileLine = (BuildCompileLine*)buildLine;
      sources = compileLine->GetSources();
      ProcessBuildLineSources(sourceItem, sources, InLineSet);
    }
  }
}
  
/*****************************************************************************!
 * Function : ProcessBuildLineLibs
 *****************************************************************************/
void
MainDisplayWindow::ProcessBuildLineLibs
(BuildTreeItem* InItem, QStringList InLibs)
{
  BuildTreeItemComponent*               sourceItem;
  BuildTreeItemSubSection*              subSection;
  
  if ( InLibs.size() == 0 ) {
    return;
  }

  subSection = new BuildTreeItemSubSection("Libs");
  InItem->addChild(subSection);
  
  foreach ( auto s, InLibs ) {
    sourceItem = new BuildTreeItemComponent();

    if ( InItem->Contains(s) ) {
      continue;
    }
    sourceItem->setText(0, s);
    subSection->addChild(sourceItem);
  }
  subSection->sortChildren(0, Qt::AscendingOrder);
}
  
