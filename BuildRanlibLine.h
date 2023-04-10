/*****************************************************************************
 * FILE NAME    : BuildRanlibLine.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildranlibline_h_
#define _buildranlibline_h_

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
 * Exported Class : BuildRanlibLine
 *****************************************************************************/
class BuildRanlibLine : public BuildLine
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildRanlibLine                     ();

 //! Destructor
 public :
  ~BuildRanlibLine                    ();

 //! Public Methods
 public :
  void                          ParseLine               (QString InBuildLine);
  QString                       GetTarget               (void);
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
  QString                               target;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildranlibline_h_*/
