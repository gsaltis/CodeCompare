/*****************************************************************************
 * FILE NAME    : TUTreeElement.h
 * DATE         : May 11 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _tutreeelement_h_
#define _tutreeelement_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QJsonValue>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TUTREE_ELEMENT_X                200
#define TUTREE_ELEMENT_Y                200
#define TUTREE_ELEMENT_WIDTH            200
#define TUTREE_ELEMENT_HEIGHT           200

/*****************************************************************************!
 * Exported Class : TUTreeElement
 *****************************************************************************/
class TUTreeElement : public QTreeWidgetItem
{
  //! Types
 public :
  enum Type
  {
    TopLevel,
    Element,
    TranslationUnitElement
  };

  enum TranslationUnitType
  {
    None,
    RecordDecl,
    TypedefDecl,
    EnumDecl,
    VarDecl,
    FunctionDecl,
    FunctionDef,
    Other,
  };
  
 //! Constructors
 public :
  TUTreeElement                 (Type InType, QString InText1, QString InText2, QJsonValue InValue);
  TUTreeElement                 (Type InType, QStringList InNames, QJsonValue InValue);
  
 //! Destructor
 public :
  ~TUTreeElement                ();

 //! Public Methods
 public :
  bool                          operator<               (const QTreeWidgetItem &other) const;
  Type                          GetType                 ();
  TranslationUnitType           GetTUType               ();
  void                          SetTUType               (TranslationUnitType InType);
  TUTreeElement*                FindChildByName         (QString InChildName);
  QJsonValue                    GetJSONValue            ();
  static QString                TranslationUnitTypeToString     (TranslationUnitType InType);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
private :
  Type                          type;
  TranslationUnitType           tuType;
  QJsonValue                    jsonValue;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _tutreeelement_h_*/
