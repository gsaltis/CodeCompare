/*****************************************************************************
 * FILE NAME    : BuildForLine.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildforline_h_
#define _buildforline_h_

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
 * Exported Class : BuildForLine
 *****************************************************************************/
class BuildForLine : public BuildLine
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildForLine                     ();

 //! Destructor
 public :
  ~BuildForLine                    ();

 //! Public Methods
 public :
  void                          ParseLine               (QString InBuildLine);
  QStringList                   GetTargets              (void);
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
  QStringList                           targets;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildforline_h_*/
