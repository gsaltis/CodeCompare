/*****************************************************************************
 * FILE NAME    : BuildTreeJSONCodeContainer.h
 * DATE         : April 14 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreejsoncodecontainer_h_
#define _buildtreejsoncodecontainer_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_TREE_JSONCODE_CONTAINER_X 200
#define BUILD_TREE_JSONCODE_CONTAINER_Y 200
#define BUILD_TREE_JSONCODE_CONTAINER_WIDTH 200
#define BUILD_TREE_JSONCODE_CONTAINER_HEIGHT 200

/*****************************************************************************!
 * Exported Class : BuildTreeJSONCodeContainer
 *****************************************************************************/
class BuildTreeJSONCodeContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTreeJSONCodeContainer    ();

 //! Destructor
 public :
  ~BuildTreeJSONCodeContainer   ();

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

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildtreejsoncodecontainer_h_*/
