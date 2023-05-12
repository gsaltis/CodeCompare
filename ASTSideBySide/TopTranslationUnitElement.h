/*****************************************************************************
 * FILE NAME    : TopTranslationUnitElement.h
 * DATE         : May 11 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _toptranslationunitelement_h_
#define _toptranslationunitelement_h_

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
 * Exported Class : TopTranslationUnitElement
 *****************************************************************************/
class TopTranslationUnitElement : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TopTranslationUnitElement     (QString InKind, QString InName,
                                 QJsonValue InContent);

 //! Destructor
 public :
  ~TopTranslationUnitElement    ();

 //! Public Methods
 public :

 //! Public Data
 public :
  QString                       kind;
  QString                       name;
  QJsonValue                    content;

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
#endif /* _toptranslationunitelement_h_*/
