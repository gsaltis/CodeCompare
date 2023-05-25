/*****************************************************************************
 * FILE NAME    : BuildTreeItem.h
 * DATE         : May 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreeitem_h_
#define _buildtreeitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_TREE_ITEM_X               200
#define BUILD_TREE_ITEM_Y               200
#define BUILD_TREE_ITEM_WIDTH           200
#define BUILD_TREE_ITEM_HEIGHT          200

/*****************************************************************************!
 * Exported Class : BuildTreeItem
 *****************************************************************************/
class BuildTreeItem : public QTreeWidgetItem
{
 //! Constructors
 public :
  BuildTreeItem                 ();

 //! Enumerated Types
 public :
  enum Type
  {
    None,
    Top,
    Component,
    Section
  };
  
 //! Destructor
 public :
  ~BuildTreeItem                ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :
  Type                          type;
  
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

#endif /* _buildtreeitem_h_*/
