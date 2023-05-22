/*****************************************************************************
 * FILE NAME    : TUTreeElement.cpp
 * DATE         : May 11 2023
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
#include "TUTreeElement.h"

/*****************************************************************************!
 * Function : TUTreeElement
 *****************************************************************************/
TUTreeElement::TUTreeElement
(Type InType, QString InText1, QString InText2, QJsonValue InValue) : QTreeWidgetItem()
{
  jsonValue = InValue;
  type = InType;
  tuType = None;
  setText(0, InText1);
  setText(1, InText2);
}

/*****************************************************************************!
 * Function : TUTreeElement
 *****************************************************************************/
TUTreeElement::TUTreeElement
(Type InType, QStringList InNames, QJsonValue InValue)
{
  jsonValue = InValue;
  tuType = None;
  type = InType;
  for (int i = 0 ; i < InNames.count(); i++ ) {
    setText(i, InNames[i]);
  }
}

/*****************************************************************************!
 * Function : ~TUTreeElement
 *****************************************************************************/
TUTreeElement::~TUTreeElement
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TUTreeElement::initialize()
{
}

/*****************************************************************************!
 * Function : operator<
 *****************************************************************************/
bool
TUTreeElement::operator<
(const QTreeWidgetItem &other) const
{
  int                                   sortC;

  sortC = treeWidget()->sortColumn();
  return text(sortC) < other.text(sortC);
}

/*****************************************************************************!
 * Function : GetType
 *****************************************************************************/
TUTreeElement::Type
TUTreeElement::GetType
()
{
  return type;
}

/*****************************************************************************!
 * Function : GetTUType
 *****************************************************************************/
TUTreeElement::TranslationUnitType
TUTreeElement::GetTUType
()
{
  return tuType;
}

/*****************************************************************************!
 * Function : SetTUType
 *****************************************************************************/
void
TUTreeElement::SetTUType
(TranslationUnitType InType)
{
  tuType = InType;
}

/*****************************************************************************!
 * Function : FindChildByName
 *****************************************************************************/
TUTreeElement*
TUTreeElement::FindChildByName
(QString InChildName)
{
  TUTreeElement*                        te;
  int                                   i, n;

  n = childCount();

  for (i = 0; i < n; i++) {
    te = (TUTreeElement*)child(i);
    if ( te->text(0) == InChildName ) {
      return te;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : GetJSONValue
 *****************************************************************************/
QJsonValue
TUTreeElement::GetJSONValue
()
{
  return jsonValue;
}

/*****************************************************************************!
 * Function : TranslationUnitTypeToString
 *****************************************************************************/
QString
TUTreeElement::TranslationUnitTypeToString
(TUTreeElement::TranslationUnitType InType)
{
  switch(InType) {
    case None : {
      return QString("None");
    }
      
    case RecordDecl : {
      return QString("RecordDecl");
    }
      
    case TypedefDecl : {
      return QString("TypedefDecl");
    }
      
    case EnumDecl : {
      return QString("EnumDecl");
    }
      
    case VarDecl : {
      return QString("VarDecl");
    }
      
    case FunctionDecl : {
      return QString("FunctionDecl");
    }
      
    case FunctionDef : {
      return QString("FunctionDef");
    }
      
    case Other : {
      break;
    }
  }
  return QString("Other");
}
