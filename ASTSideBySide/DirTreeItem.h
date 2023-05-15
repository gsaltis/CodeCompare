/*****************************************************************************
 * FILE NAME    : DirTreeItem.h
 * DATE         : May 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _dirtreeitem_h_
#define _dirtreeitem_h_

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
#define DIR_TREE_ITEM_X                 200
#define DIR_TREE_ITEM_Y                 200
#define DIR_TREE_ITEM_WIDTH             200
#define DIR_TREE_ITEM_HEIGHT            200

/*****************************************************************************!
 * Exported Class : DirTreeItem
 *****************************************************************************/
class DirTreeItem : public QTreeWidgetItem
{
 public:
  enum Type
  {
    File,
    Dir
  };
  
 //! Constructors
 public :
  DirTreeItem                   ();

 //! Destructor
 public :
  ~DirTreeItem                  ();

 //! Public Methods
 public :
  Type                          GetType                 ();
  
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

#endif /* _dirtreeitem_h_*/
