/*****************************************************************************
 * FILE NAME    : JSONAST.h
 * DATE         : May 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _jsonast_h_
#define _jsonast_h_

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

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : JSONAST
 *****************************************************************************/
class JSONAST : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  JSONAST                       ();

 //! Destructor
 public :
  ~JSONAST                      ();

 //! Public Methods
 public :
  static QString                FindCallExprName        (QJsonObject InCallExprObject);
  static QString                FindDeclStmtName        (QJsonObject InDeclStmtObject);
  static void                   GetTopLevelLinesNumbers (QJsonObject InTUObject, int &InStartLine, int &InEndLine, QString &InFileName);
  static void                   DisplayValue            (QJsonValue InValue, int InDepth);
  static bool                   CompareVarDecl          (QJsonValue InDecl1, QJsonValue InDecl2);
  static bool                   CompareValues           (QJsonValue InValue1, QJsonValue InValue2);
  static bool                   CompareVarDeclType      (QJsonValue InValue1, QJsonValue InValue2);
  static void                   GetTopLevelRangeInfo    (QJsonValue InValue, int& InLineNumber, int& InBegin, int& InEnd);
  static bool                   GetTopLevelBeginInfo    (QJsonObject InBeginObject, int& InBegin);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _jsonast_h_*/
