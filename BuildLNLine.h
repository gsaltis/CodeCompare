/*****************************************************************************
 * FILE NAME    : BuildLNLine.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildlnline_h_
#define _buildlnline_h_

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
 * Exported Class : BuildLNLine
 *****************************************************************************/
class BuildLNLine : public BuildLine
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLNLine                     ();

 //! Destructor
 public :
  ~BuildLNLine                    ();

 //! Public Methods
 public :
  void                          ParseLine               (QString InBuildLine);
  QString                       GetTarget               (void);
  QString                       GetAction               (void);
  QString                       GetLinkName             (void);
  QStringList                   GetFlags                (void);
  
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
  QString                               linkName;
  QStringList                           flags;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildlnline_h_*/
