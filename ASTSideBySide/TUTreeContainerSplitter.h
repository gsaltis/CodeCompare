/*****************************************************************************
 * FILE NAME    : TUTreeContainerSplitter.h
 * DATE         : May 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _tutreecontainersplitter_h_
#define _tutreecontainersplitter_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QSplitter>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TUTREE_CONTAINER_SPLITTER_X     200
#define TUTREE_CONTAINER_SPLITTER_Y     200
#define TUTREE_CONTAINER_SPLITTER_WIDTH 200
#define TUTREE_CONTAINER_SPLITTER_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TUTreeContainerSplitter
 *****************************************************************************/
class TUTreeContainerSplitter : public QSplitter
{
  Q_OBJECT;

 //! Constructors
 public :
  TUTreeContainerSplitter       ();

 //! Destructor
 public :
  ~TUTreeContainerSplitter      ();

 //! Public Methods
 public :
  void                          ResizeErrorWindow       (int InHeight);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _tutreecontainersplitter_h_*/
