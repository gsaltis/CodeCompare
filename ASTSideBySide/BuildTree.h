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
#include "BuildTreeItemSection.h"
#include "BuildTreeItem.h"
#include "BuildLineSet.h"

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
  void                          ProcessBuildLines                       (QString InTrackName , BuildLineSet* InBuildLines);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize                              ();
  void                          CreateSubWindows                        ();
  void                          InitializeSubWindows                    ();
  void                          resizeEvent                             (QResizeEvent* InEvent);
  void                          ProcessBuildLineLibs                    (QString InTrackName, BuildTreeItem* InItem, QStringList InLibs);
  void                          ProcessBuildLineSources                 (QString InTrackName, BuildTreeItem* InItem, QStringList InSources, BuildLineSet* InLineSet);
  void                          ProcessBuildLineSecondarySources        (QString InTrackName, BuildTreeItem* InItem, QStringList InSources);
  void                          CreateConnections                       ();
  
 //! Private Data
 private :
  BuildTreeItemSection*         buildTreeBinary;
  BuildTreeItemSection*         buildTreeCGI;
  BuildTreeItemSection*         buildTreeSharedObject;
  BuildTreeItemSection*         buildTreeOther;
  bool                          processLibsLines;
  bool                          displayIntermediateFiles;
  
 //! Public Slots
 public slots :
  void                          SlotToggleTreeView                      (void);
  void                          SlotToggleChangedItems                  (void);
  void                          SlotFileSelected                        (QTreeWidgetItem* InItem, int InIndex);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildtree_h_*/
