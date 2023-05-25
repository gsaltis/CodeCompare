/*****************************************************************************
 * FILE NAME    : BuildTreeItemComponent.h
 * DATE         : May 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreeitemcomponent_h_
#define _buildtreeitemcomponent_h_

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
#define BUILD_TREE_ITEM_COMPONENT_X     200
#define BUILD_TREE_ITEM_COMPONENT_Y     200
#define BUILD_TREE_ITEM_COMPONENT_WIDTH 200
#define BUILD_TREE_ITEM_COMPONENT_HEIGHT 200

/*****************************************************************************!
 * Exported Class : BuildTreeItemComponent
 *****************************************************************************/
class BuildTreeItemComponent : public BuildTreeItem
{
 //! Constructors
 public :
  BuildTreeItemComponent        ();

 //! Destructor
 public :
  ~BuildTreeItemComponent       ();

 //! Public Methods
 public :

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

#endif /* _buildtreeitemcomponent_h_*/
