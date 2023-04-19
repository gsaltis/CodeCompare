/*****************************************************************************
 * FILE NAME    : BuildTreeHierarchyContainer.h
 * DATE         : April 14 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreehierarchycontainer_h_
#define _buildtreehierarchycontainer_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTreeHierarchyTable.h"
#include "BuildLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_TREE_HIERARCHY_CONTAINER_X 200
#define BUILD_TREE_HIERARCHY_CONTAINER_Y 200
#define BUILD_TREE_HIERARCHY_CONTAINER_WIDTH 200
#define BUILD_TREE_HIERARCHY_CONTAINER_HEIGHT 200

/*****************************************************************************!
 * Exported Class : BuildTreeHierarchyContainer
 *****************************************************************************/
class BuildTreeHierarchyContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTreeHierarchyContainer   ();

 //! Destructor
 public :
  ~BuildTreeHierarchyContainer  ();

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
  void                          CreateConnections       (void);

 //! Private Data
 private :
  BuildTreeHierarchyTable*      buildTreeHierarchyTableWindow;

 //! Public Slots
 public slots :
  void                          SlotTreeItemSelected    (BuildLine* InBuildLine, QString InFilename);

 //! Public Signals
 signals :
  void                          SignalTreeItemSelected  (BuildLine* InBuildLine, QString InFilename);
  
 //! Public Actions
 public :

};

#endif /* _buildtreehierarchycontainer_h_*/
