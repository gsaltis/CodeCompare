/*****************************************************************************
 * FILE NAME    : TUTree.h
 * DATE         : May 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _tutree_h_
#define _tutree_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTreeWidget>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TUTreeElement.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TUTREE_X                        200
#define TUTREE_Y                        200
#define TUTREE_WIDTH                    200
#define TUTREE_HEIGHT                   200

/*****************************************************************************!
 * Exported Class : TUTree
 *****************************************************************************/
class TUTree : public QTreeWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TUTree                        (QString InFilename);

 //! Destructor
 public :
  ~TUTree                       ();

 //! Public Methods
 public :
  TUTreeElement*                FindElementByNameType   (QString InName, TUTreeElement::TranslationUnitType InType);
  QString                       GetFilename             (void);
  void                          SetFilename             (QString InFilename);
  QString                       GetFileSection          (int InBegin, int InEnd);

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
  QString                       filename;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _tutree_h_*/
