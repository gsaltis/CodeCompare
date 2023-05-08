/*****************************************************************************
 * FILE NAME    : TranslationUnitType.h
 * DATE         : May 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
 *****************************************************************************/
#ifndef _translationunittype_h_
#define _translationunittype_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "FileContentsDiff.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TranslationUnitType
 *****************************************************************************/
class TranslationUnitType : public QWidget
{
 public :
 //! Public Types
  enum Type {
    None,
    Function,
    Record,
    TypeDef,
    Variable
  };
  
 //! Constructors
 public :
  TranslationUnitType           (QString InName, int InLineStart, int InLineEnd);
  TranslationUnitType           (TranslationUnitType::Type InType, QString InName, int InLineStart, int InLineEnd);

 //! Destructor
 public :
  ~TranslationUnitType          ();

 //! Public Methods
 public :
  bool                          HasTargetChangeLines    (FileContentsDiff* InDiffs);
  QString                       GetName                 ();
  int                           GetLineStart            (void);
  int                           GetLineEnd              (void);
  void                          Write                   (QFile *InFile, bool InLastItem);
  bool                          GetHasChanged           (void);
  void                          SetHasChanged           (bool InHasChanged);
  static Type                   KindToTUType            (QString InKind);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :
  QString                               name;
  Type                                  type;
  int                                   lineStart;
  int                                   lineEnd;

 //! Private Methods
 private :

 //! Private Data
 private :
  bool                          hasChanged;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _translationunittype_h_*/
