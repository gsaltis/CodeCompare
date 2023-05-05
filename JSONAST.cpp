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
