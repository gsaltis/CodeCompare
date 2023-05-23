/*****************************************************************************
 * FILE NAME    : BuildTreeContainer.h
 * DATE         : May 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreecontainer_h_
#define _buildtreecontainer_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTree.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_TREE_CONTAINER_X          200
#define BUILD_TREE_CONTAINER_Y          200
#define BUILD_TREE_CONTAINER_WIDTH      200
#define BUILD_TREE_CONTAINER_HEIGHT     200

/*****************************************************************************!
 * Exported Class : BuildTreeContainer
 *****************************************************************************/
class BuildTreeContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTreeContainer            (BuildTree* InBuildTree);

 //! Destructor
 public :
  ~BuildTreeContainer           ();

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
  BuildTree*                    buildTree;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildtreecontainer_h_*/