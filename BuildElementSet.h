/*****************************************************************************
 * FILE NAME    : BuildElementSet.h
 * DATE         : April 10 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildelementset_h_
#define _buildelementset_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildElement.h"
#include "BuildLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : BuildElementSet
 *****************************************************************************/
class BuildElementSet : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildElementSet
  (QString InElementName);

 //! Destructor
 public :
  ~BuildElementSet              ();

 //! Public Methods
 public :
  void
  AddElement
  (BuildElement* InElement);

  QString
  GetTarget
  (void);

  void
  SetTarget
  (QString InTarget);
  void

  Dump
  (int InIndent);
  bool                          IsSourceElement         (QString InName);

  void
  SetBuildLine
  (BuildLine* InBuildLine);

  int
  GetElementCount
  (void);

  BuildElement*
  GetElementByIndex
  (int InIndex);
  void                          Dump                    (void);
  
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
  QList<BuildElement*>          elements;
  QString                       target;
  BuildLine*                    buildLine;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildelementset_h_*/
