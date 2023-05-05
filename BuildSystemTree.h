/*****************************************************************************
 * FILE NAME    : BuildSystemTree.h
 * DATE         : May 04 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildsystemtree_h_
#define _buildsystemtree_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QTreeWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildSystem.h"
#include "BuildLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_SYSTEM_TREE_X             200
#define BUILD_SYSTEM_TREE_Y             200
#define BUILD_SYSTEM_TREE_WIDTH         200
#define BUILD_SYSTEM_TREE_HEIGHT        200

/*****************************************************************************!
 * Exported Class : BuildSystemTree
 *****************************************************************************/
class BuildSystemTree : public QTreeWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildSystemTree               ();

 //! Destructor
 public :
  ~BuildSystemTree              ();

 //! Public Methods
 public :
  void                          SetBuildSystem          (BuildSystem* InBuildSystem);

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
  void                          Populate                ();
  
 //! Private Data
 private :
  BuildSystem*                  buildSystem;
  
 //! Public Slots
 public slots :
  void                          SlotTreeWidgetItemSelected      (QTreeWidgetItem*, int);
  
 //! Public Signals
 signals :
  void                          SignalBuildTreeItemSelected     (BuildLine* InBuildLine, QString InFileName);

 //! Public Actions
 public :

};

#endif /* _buildsystemtree_h_*/
