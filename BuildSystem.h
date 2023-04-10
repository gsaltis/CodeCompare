/*****************************************************************************
 * FILE NAME    : BuildSystem.h
 * DATE         : April 10 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildsystem_h_
#define _buildsystem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildElementSet.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : BuildSystem
 *****************************************************************************/
class BuildSystem : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildSystem                   ();

 //! Destructor
 public :
  ~BuildSystem                  ();

 //! Public Methods
 public :
  void
  BuildElementSetAdd
  (BuildElementSet* InSet);

  void
  Dump
  ();
  void                          GetTopLevelElements     (void);
  bool                          IsSourceElement         (QString InName);
  
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
  QList<BuildElementSet*>       targets;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildsystem_h_*/

