/*****************************************************************************
 * FILE NAME    : BuildTreeItemTop.h
 * DATE         : May 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreeitemtop_h_
#define _buildtreeitemtop_h_

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
#define BUILD_TREE_ITEM_TOP_X           200
#define BUILD_TREE_ITEM_TOP_Y           200
#define BUILD_TREE_ITEM_TOP_WIDTH       200
#define BUILD_TREE_ITEM_TOP_HEIGHT      200

/*****************************************************************************!
 * Exported Class : BuildTreeItemTop
 *****************************************************************************/
class BuildTreeItemTop : public BuildTreeItem
{
 //! Constructors
 public :
  BuildTreeItemTop              ();

 //! Destructor
 public :
  ~BuildTreeItemTop             ();

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

#endif /* _buildtreeitemtop_h_*/
