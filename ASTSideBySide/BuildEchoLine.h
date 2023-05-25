/*****************************************************************************
 * FILE NAME    : BuildEchoLine.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildecholine_h_
#define _buildecholine_h_

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
 * Exported Class : BuildEchoLine
 *****************************************************************************/
class BuildEchoLine : public BuildLine
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildEchoLine                 ();

 //! Destructor
 public :
  ~BuildEchoLine                ();

 //! Public Methods
 public :
  void                          ParseLine               (QString InBuildLine);
  QString                       GetEchoLine             (void);
  QString                       GetAction               (void);
  
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
  QString                               echoLine;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildecholine_h_*/
