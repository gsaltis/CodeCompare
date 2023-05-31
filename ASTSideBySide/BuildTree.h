/*****************************************************************************
 * FILE NAME    : BuildTree.h
 * DATE         : May 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtree_h_
#define _buildtree_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTreeWidget>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CommonFileTree.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_TREE_X                    200
#define BUILD_TREE_Y                    200
#define BUILD_TREE_WIDTH                200
#define BUILD_TREE_HEIGHT               200

/*****************************************************************************!
 * Exported Class : BuildTree
 *****************************************************************************/
class BuildTree : public CommonFileTree
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTree                     (QString InFilePath1, QString InFilePath2);

 //! Destructor
 public :
  ~BuildTree                    ();

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
  void                          SlotToggleTreeView      (void);
  void                          SlotToggleChangedItems  (void);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildtree_h_*/
