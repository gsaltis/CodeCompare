/*****************************************************************************
 * FILE NAME    : BuildTreeHierarchyTableItem.h
 * DATE         : April 15 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreehierarchytableitem_h_
#define _buildtreehierarchytableitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QFrame>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
nn *****************************************************************************/
#define BUILD_TREE_HIERARCHY_TABLE_ITEM_X 5
#define BUILD_TREE_HIERARCHY_TABLE_ITEM_Y 200
#define BUILD_TREE_HIERARCHY_TABLE_ITEM_WIDTH 200
#define BUILD_TREE_HIERARCHY_TABLE_ITEM_HEIGHT 17

/*****************************************************************************!
 * Exported Class : BuildTreeHierarchyTableItem
 *****************************************************************************/
class BuildTreeHierarchyTableItem : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTreeHierarchyTableItem   (QString InName, QWidget* InParent);

 //! Destructor
 public :
  ~BuildTreeHierarchyTableItem  ();

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
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QLabel*                       nameLabel;
  QString                       name;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildtreehierarchytableitem_h_*/
