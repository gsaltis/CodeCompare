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

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TranslationUnitType
 *****************************************************************************/
class TranslationUnitType : public QWidget
{

 //! Constructors
 public :
  TranslationUnitType           (QString InName, int InLineStart, int InLineEnd);

 //! Destructor
 public :
  ~TranslationUnitType          ();

 //! Public Types
  enum Type {
    None,
    Function,
    Variable
  };
  
 //! Public Methods
 public :

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

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _translationunittype_h_*/
