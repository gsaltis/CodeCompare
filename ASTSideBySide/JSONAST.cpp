/*****************************************************************************
 * FILE NAME    : JSONAST.cpp
 * DATE         : May 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "JSONAST.h"
#include "trace.h"

/*****************************************************************************!
 * Function : JSONAST
 *****************************************************************************/
JSONAST::JSONAST
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~JSONAST
 *****************************************************************************/
JSONAST::~JSONAST
()
{
}

/*****************************************************************************!
 * Function : FindCallExprName
 *****************************************************************************/
QString
JSONAST::FindCallExprName
(QJsonObject InCallExprObject)
{
  QJsonValue                            val;
  QJsonObject                           refDecl;
  QJsonObject                           declRefExpr;
  QJsonArray                            inner2;
  QJsonObject                           castExpr;
  QJsonArray                            inner1;

  val = InCallExprObject["inner"];
  if ( ! val.isArray() ) {
    return QString();
  }
  inner1 = val.toArray();

  for ( int i = 0 ; i < inner1.count() ; i++ ) {
    val = inner1[i];
    if ( ! val.isObject() ) {
      continue;
    }
    
    castExpr = val.toObject();
    
    val = castExpr["inner"];
    if ( ! val.isArray() ) {
      continue;
    }
    inner2 = val.toArray();
    
    val = inner2[0];
    if ( ! val.isObject() ) {
      continue;
    }
    
    declRefExpr = val.toObject();
    val = declRefExpr["referencedDecl"];
    if ( ! val.isObject() ) {
      continue;
    }
    refDecl = val.toObject();
    
    val = refDecl["name"];
    if ( ! val.isString() ) {
      continue;
    }
    return val.toString();
  }
  return QString();
}

/*****************************************************************************!
 * Function : FindDeclStmtName
 *****************************************************************************/
QString
JSONAST::FindDeclStmtName
(QJsonObject InDeclStmtObject)
{
  
  QJsonValue                            val;
  QJsonArray                            inner;
  QJsonObject                           obj;
  QJsonValue                            name;

  val = InDeclStmtObject["inner"];
  if ( ! val.isArray() ) {
    return QString();
  }
  inner = val.toArray();

  for ( int i = 0 ; i < inner.count() ; i++ ) {
    val = inner[i];
    if ( ! val.isObject() ) {
      continue;
    }
    
    obj = val.toObject();
    name = obj["name"];
    if ( ! name.isString() ) {
      continue;
    }
    return name.toString();
  }
  return QString();
}

/*****************************************************************************!
 * Function : GetTopLevelLinesNumbers
 *****************************************************************************/
void
JSONAST::GetTopLevelLinesNumbers
(QJsonObject InTUObject, int &InStartLine, int &InEndLine, QString &InFilename)
{
  QJsonObject                           endObject;
  QJsonValue                            fileValue;
  QJsonObject                           locObject;
  QJsonObject                           rangeObject;
  QJsonValue                            val;

  InStartLine = 0;
  InEndLine = 0;
  
  val = InTUObject["loc"];
  if ( ! val.isObject() ) {
    return;
  }

  locObject = val.toObject();
  fileValue = locObject["file"];
  if ( fileValue.isString() ) {
    InFilename = fileValue.toString();
  }
  val = locObject["line"];
  if ( ! val.isDouble() ) {
    return;
  }
  InStartLine = val.toInt();
  InEndLine = InStartLine;

  val = InTUObject["range"];
  if ( ! val.isObject() ) {
    return;
  }
  rangeObject = val.toObject();

  val = rangeObject["end"];
  if ( ! val.isObject() ) {
    return;
  }
  endObject = val.toObject();
  val = endObject["line"];
  if ( ! val.isDouble() ) {
    return;
  }
  InEndLine = val.toInt();
}

/*****************************************************************************!
 * Function : DisplayValue
 *****************************************************************************/
void
JSONAST::DisplayValue
(QJsonValue InValue, int InDepth)
{
  QString                       fill;

  fill.fill(QChar(' '), InDepth);

  //!
  switch (InValue.type() ) {
    case QJsonValue::Null : {
      printf("Null\n");
      return ;
    }

    //!
    case QJsonValue::Bool : {
      printf("%s\n", InValue.toBool() ? "true" : "false");
      return ;
    }
      
    //!
    case QJsonValue::Double : {
      char                              s[32];
      
      sprintf(s, "%f", InValue.toDouble());
      QString                           st = QString(s);
      QStringList                       s2 = st.split(".");
      if ( s2[1] == "000000") {
        printf("%s\n", s2[0].toStdString().c_str());
        return;
      }
      printf("%s\n", s);
      return ;
    }

    //!
    case QJsonValue::String : {
      printf("%s\n", InValue.toString().toStdString().c_str());
      return ;
    }
      
    //!
    case QJsonValue::Array : {
      QJsonArray                        array;
      QString                           fill2;

      fill2.fill(QChar(' '), InDepth + 2);
      printf("[\n");
      array = InValue.toArray();
      for ( int i = 0 ; i < array.count(); i++ ) {
        QJsonValue                      val = array[i];
        printf("%s", fill2.toStdString().c_str());
        DisplayValue(val, InDepth + 2);
      }
      printf("%s]\n", fill.toStdString().c_str());
      return ;
    }
      
    //!
    case QJsonValue::Object : {
      QStringList                       keys;
      QJsonObject                       object;
      QString                           fill2;
      QJsonValue                        val2;
      
      fill2.fill(QChar(' '), InDepth + 2);
      object = InValue.toObject();
      keys = object.keys();
      printf("{\n");
      foreach ( auto key, keys) {
        val2 = object[key];
        printf("%s%s : ", fill2.toStdString().c_str(), key.toStdString().c_str());
        DisplayValue(val2, InDepth + 2);
      }
      printf("%s}\n", fill.toStdString().c_str());
      return ;
    }
      
    case QJsonValue::Undefined : {
      return ;
    }
  }
}

/*****************************************************************************!
 * Function : CompareVarDecl
 *****************************************************************************/
bool
JSONAST::CompareVarDecl
(QJsonValue InDecl1, QJsonValue InDecl2)
{
  QString                               key2;
  QString                               key1;
  int                                   i;
  int                                   count1;
  int                                   count2;
  QJsonObject                           obj1;
  QJsonObject                           obj2;
  QStringList                           keys1;
  QStringList                           keys2;
  
  if ( ! (InDecl1.isObject() && InDecl2.isObject() )  ) {
    return false;
  }

  obj1 = InDecl1.toObject();
  obj2 = InDecl2.toObject();

  keys1 = obj1.keys();
  keys2 = obj2.keys();

  count1 = keys1.count();
  count2 = keys2.count();
  if ( count1 != count2 ) {
    return false;
  }

  for ( i = 0 ; i < count1; i++ ) {
    key1 = keys1[i];
    key2 = keys2[i];

    if ( key1 != key2 ) {
      return false;
    }
    if ( key1 == "id" || key1 == "loc" || key1 == "previousDecl" || key1 == "range" ) {
      continue;
    }
    if ( key1 == "type" ) {
      if ( !CompareVarDeclType(obj1[key1], obj2[key2]) ) {
        return false;
      }
      continue;
    }
    if( ! CompareValues(obj1[key1], obj2[key2]) ) {
      return false;
    }
  }
  return true;
}

/*****************************************************************************!
 * Function : CompareVarDeclType
 *****************************************************************************/
bool
JSONAST::CompareVarDeclType
(QJsonValue InValue1, QJsonValue InValue2)
{
  QJsonObject                       obj1;
  QJsonObject                       obj2;
  QStringList                       keys1;
  QStringList                       keys2;
  QString                           key1;
  QString                           key2;
  int                               i;
  int                               count;
  QJsonValue                        val1;
  QJsonValue                        val2;
  
  obj1 = InValue1.toObject();
  obj2 = InValue2.toObject();
  
  keys1 = obj1.keys();
  keys2 = obj2.keys();
  
  count = keys1.count();
  if ( count != keys2.count() ) {
    return false;
  }
  
  for ( i = 0 ; i < count; i++ ) {
    key1 = keys1[i];
    key2 = keys2[i];
    if ( key1 != key2 ) {
      return false;
    }

    if ( key1 == "typeAliasDeclId" ) {
      continue;
    }
    val1 = obj1[key1];
    val2 = obj2[key2];
    if ( ! CompareValues(val1, val2) ) {
      return false;
    }
  }
  return true;
}      

/*****************************************************************************!
 * Function : CompareValues
 *****************************************************************************/
bool
JSONAST::CompareValues
(QJsonValue InValue1, QJsonValue InValue2)
{
  if ( InValue1.type() != InValue2.type() ) {
    return false;
  }

  //!
  switch (InValue1.type() ) {
    case QJsonValue::Null : {
      return true;
    }

    //!
    case QJsonValue::Bool : {
      return InValue1.toBool() == InValue2.toBool();
    }
      
    //!
    case QJsonValue::Double : {
      return InValue1.toDouble() == InValue2.toDouble();
    }

    //!
    case QJsonValue::String : {
      return InValue1.toString() == InValue2.toString();
    }
      
    //!
    case QJsonValue::Array : {
      QJsonArray                        array1;
      QJsonArray                        array2;
      int                               count;
      QJsonValue                        val1;
      QJsonValue                        val2;
      int                               i;
      
      array1 = InValue1.toArray();
      array2 = InValue2.toArray();

      count = array1.count();

      if ( count != array2.count() ) {
        return false;
      }

      for ( i = 0 ; i < count; i++ ) {
        val1 = array1[i];
        val2 = array2[i];
        if ( ! CompareValues(val1, val2) ) {
          return false;
        }
      }
      
      return true;
    }
      
    //!
    case QJsonValue::Object : {
      QJsonObject                       obj1;
      QJsonObject                       obj2;
      QStringList                       keys1;
      QStringList                       keys2;
      QString                           key1;
      QString                           key2;
      int                               i;
      int                               count;
      QJsonValue                        val1;
      QJsonValue                        val2;

      obj1 = InValue1.toObject();
      obj2 = InValue2.toObject();

      keys1 = obj1.keys();
      keys2 = obj2.keys();

      count = keys1.count();
      if ( count != keys2.count() ) {
        return false;
      }

      for ( i = 0 ; i < count; i++ ) {
        key1 = keys1[i];
        key2 = keys2[i];
        if ( key1 != key2 ) {
          return false;
        }

        val1 = obj1[key1];
        val2 = obj2[key2];
        if ( ! CompareValues(val1, val2) ) {
          return false;
        }
      }
      return true;
        
    }
      
    case QJsonValue::Undefined : {
      return true;
    }
  }
  return false;
}

/*****************************************************************************!
 * Function : GetTopLevelRangeInfo
 *****************************************************************************/
void
JSONAST::GetTopLevelRangeInfo
(QJsonValue InValue, int& InLineNumber, int& InBegin, int& InEnd)
{
  QJsonObject                           expansionLocObj;
  QJsonValue                            rangeVal;
  QJsonValue                            expansionLocVal;
  QJsonObject                           obj;
  QJsonObject                           rangeObj;
  QJsonObject                           beginObj;
  QJsonObject                           endObj;
  QJsonValue                            offsetVal;
  QJsonValue                            tokenLengthVal;
  QJsonValue                            offsetVal2;
  QJsonValue                            tokenLengthVal2;
  int                                   offset;
  int                                   tokenLength;
  QJsonValue                            locVal;
  QJsonValue                            lineVal;
  QJsonObject                           locObject;
  
  InBegin = -1;
  InEnd = -1;

  obj = InValue.toObject();
  if ( obj.empty() ) {
    return;
  }

  locVal = obj["loc"];
  if ( ! locVal.isObject() ) {
    return;
  }

  locObject = locVal.toObject();
  lineVal = locObject["line"];
  if ( ! lineVal.isDouble() ) {
    return;
  }
  InLineNumber = lineVal.toInt();
  
  rangeVal = obj["range"];
  
  rangeObj = rangeVal.toObject();
  if ( rangeObj.empty() ) {
    return;
  }

  //!

  beginObj = rangeObj["begin"].toObject();
  if ( beginObj.empty() ) {
    return;
  }
  if ( ! JSONAST::GetTopLevelBeginInfo(beginObj, InBegin) ) {
    return;
  }
  
  //
  endObj = rangeObj["end"].toObject();
  if ( endObj.empty() ) {
    InBegin = -1;
    return;
  }

  offsetVal = endObj["offset"];
  tokenLengthVal = endObj["tokLen"];

  if ( offsetVal.isDouble() && tokenLengthVal.isDouble() ) {
    offset = offsetVal.toInteger();
    tokenLength = tokenLengthVal.toInteger();
    InEnd = offset + tokenLength;
    return;
  }

  expansionLocVal = endObj["expansionLoc"].toObject();
  if ( expansionLocVal.isObject() ) {
    expansionLocObj = expansionLocVal.toObject();
    offsetVal2 = expansionLocObj["offset"];
    tokenLengthVal2 = expansionLocObj["tokLen"];
    
    if ( offsetVal2.isDouble() && tokenLengthVal2.isDouble() ) {
      offset = offsetVal2.toInteger();
      tokenLength = tokenLengthVal2.toInteger();
      InEnd = offset + tokenLength;
    }
  }
}

/*****************************************************************************!
 * Function : GetTopLevelBeginInfo
 *****************************************************************************/
bool
JSONAST::GetTopLevelBeginInfo
(QJsonObject InBeginObject, int& InBegin)
{
  QJsonObject                           expansionLocObj;
  QJsonValue                            expansionLocVal;
  QJsonValue                            offsetVal;
  QJsonValue                            offsetVal2;

  offsetVal = InBeginObject["offset"];
  if ( offsetVal.isDouble() ) {
    InBegin = offsetVal.toInteger();
    return true;
  }
  expansionLocVal = InBeginObject["expansionLoc"].toObject();
  if ( expansionLocVal.isObject() ) {
    expansionLocObj = expansionLocVal.toObject();
    offsetVal2 = expansionLocObj["offset"];
    if ( offsetVal2.isDouble() ) {
      InBegin = offsetVal2.toInteger();
      return true;
    }
  }
  return false;
}
  
