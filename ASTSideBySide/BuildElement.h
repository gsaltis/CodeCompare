/*****************************************************************************
 * FILE NAME    : BuildElement.h
 * DATE         : April 10 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildelement_h_
#define _buildelement_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : BuildElement
 *****************************************************************************/
class BuildElement : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildElement                  (QString InName);

 //! Destructor
 public :
  ~BuildElement                 ();

 //! Public Methods
 public :
  void                          Dump                    (int InIndex);
  QString                       GetName                 ();
  BuildLine*                    GetBuildLine            (void);
  void                          SetBuildLine            (BuildLine* InBuildLine);
  
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
  class BuildElementSet*        elements;
  QString                       name;
  BuildLine*                    buildLine;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildelement_h_*/
