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
