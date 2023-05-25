/*****************************************************************************
 * FILE NAME    : BuildTreeItemSection.h
 * DATE         : May 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreeitemsection_h_
#define _buildtreeitemsection_h_

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
#define BUILD_TREE_ITEM_SECTION_X       200
#define BUILD_TREE_ITEM_SECTION_Y       200
#define BUILD_TREE_ITEM_SECTION_WIDTH   200
#define BUILD_TREE_ITEM_SECTION_HEIGHT  200

/*****************************************************************************!
 * Exported Class : BuildTreeItemSection
 *****************************************************************************/
class BuildTreeItemSection : public BuildTreeItem
{
 //! Constructors
 public :
  BuildTreeItemSection          (QString InName);

 //! Destructor
 public :
  ~BuildTreeItemSection         ();

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

#endif /* _buildtreeitemsection_h_*/
