/*****************************************************************************
 * FILE NAME    : BuildUnknownLine.h
 * DATE         : April 06 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildunknownline_h_
#define _buildunknownline_h_

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
 * Exported Class : BuildUnknownLine
 *****************************************************************************/
class BuildUnknownLine : public BuildLine
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildUnknownLine              ();

 //! Destructor
 public :
  ~BuildUnknownLine             ();

 //! Public Methods
 public :
  void
  ParseLine
  (QString InBuildLine);


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

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildunknownline_h_*/
