/*****************************************************************************
 * FILE NAME    : BuildTreeItemSubSection.h
 * DATE         : May 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreeitemsubsection_h_
#define _buildtreeitemsubsection_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTreeItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : BuildTreeItemSubSection
 *****************************************************************************/
class BuildTreeItemSubSection : public BuildTreeItem
{
 //! Constructors
 public :
  BuildTreeItemSubSection       (QString InName);

 //! Destructor
 public :
  ~BuildTreeItemSubSection      ();

 //! Public Methods
 public :
  bool                          ElementExists           (QString InName);
  
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

#endif /* _buildtreeitemsubsection_h_*/
