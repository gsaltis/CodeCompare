/*****************************************************************************
 * FILE NAME    : BuildTreeHierarchyTable.h
 * DATE         : April 14 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreehierarchytable_h_
#define _buildtreehierarchytable_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QScrollArea>
#include <QWidget>
#include <QTreeWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTreeHierarchyTableItem.h"
#include "BuildLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_TREE_HIERARCHY_TABLE_X    200
#define BUILD_TREE_HIERARCHY_TABLE_Y    200
#define BUILD_TREE_HIERARCHY_TABLE_WIDTH 200
#define BUILD_TREE_HIERARCHY_TABLE_HEIGHT 200

/*****************************************************************************!
 * Exported Class : BuildTreeHierarchyTable
 *****************************************************************************/
class BuildTreeHierarchyTable : public QTreeWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTreeHierarchyTable       ();

 //! Destructor
 public :
  ~BuildTreeHierarchyTable      ();

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
  void                          SlotTreeItemSelected    (BuildLine* InBuildLine, QString InFilename);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildtreehierarchytable_h_*/
