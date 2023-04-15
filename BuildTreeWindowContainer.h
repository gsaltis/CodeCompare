/*****************************************************************************
 * FILE NAME    : BuildTreeWindowContainer.h
 * DATE         : April 14 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreewindowcontainer_h_
#define _buildtreewindowcontainer_h_

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
#define BUILD_TREE_WINDOW_CONTAINER_X   200
#define BUILD_TREE_WINDOW_CONTAINER_Y   200
#define BUILD_TREE_WINDOW_CONTAINER_WIDTH 200
#define BUILD_TREE_WINDOW_CONTAINER_HEIGHT 200

/*****************************************************************************!
 * Exported Class : BuildTreeWindowContainer
 *****************************************************************************/
class BuildTreeWindowContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTreeWindowContainer      ();

 //! Destructor
 public :
  ~BuildTreeWindowContainer     ();

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

#endif /* _buildtreewindowcontainer_h_*/
