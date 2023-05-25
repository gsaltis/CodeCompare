/*****************************************************************************
 * FILE NAME    : BuildARLine.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildarline_h_
#define _buildarline_h_

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
 * Exported Class : BuildARLine
 *****************************************************************************/
class BuildARLine : public BuildLine
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildARLine                     ();

 //! Destructor
 public :
  ~BuildARLine                    ();

 //! Public Methods
 public :
  void                          ParseLine               (QString InBuildLine);
  QString                       GetTarget               (void);
  QString                       GetAction               (void);
  QStringList                   GetSources              (void);
  QString                       GetFlags                (void);
  
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
  QString                               action;
  QString                               target;
  QStringList                           sources;
  QString                               flags;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildarline_h_*/
