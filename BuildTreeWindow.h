/*****************************************************************************
 * FILE NAME    : BuildTreeWindow.h
 * DATE         : April 10 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreewindow_h_
#define _buildtreewindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QTreeWidget>
#include <QTextEdit>
#include <QSplitter>
#include <QTabWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildSystem.h"
#include "BuildTreeJSONCodeContainer.h"
#include "BuildTreeHierarchyContainer.h"
#include "TitledWindow.h"
#include "CodeHighlighter.h"
#include "BuildLine.h"
#include "BuildCompileLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_TREE_WINDOW_X             200
#define BUILD_TREE_WINDOW_Y             200
#define BUILD_TREE_WINDOW_WIDTH         200
#define BUILD_TREE_WINDOW_HEIGHT        200

/*****************************************************************************!
 * Exported Class : BuildTreeWindow
 *****************************************************************************/
class BuildTreeWindow : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTreeWindow               ();

 //! Destructor
 public :
  ~BuildTreeWindow              ();

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
  void                          DisplayFileText         (QString InFilename);
  void                          CreateConnections       ();
  void                          SetFileDisplayTabWidth  (int InTabWidth);
  void                          PopulateCompileOptions  (BuildCompileLine* InCompileLine);
  
 //! Private Data
 private :
  QPushButton*                  CloseButton;
  QTreeWidget*                  treeWidget;
  BuildSystem*                  buildSystem;
  QTextEdit*                    fileDisplay;
  QSplitter*                    splitter;
  QTabWidget*                   fileTabPane;
  BuildTreeJSONCodeContainer*   jsonDisplay;
  BuildTreeHierarchyContainer*  hierarchyDisplay;
  TitledWindow*                 fileTabContainer;
  int                           fileDisplayTabWidth;
  CodeHighlighter*              codeHighlighter;
  QTreeWidget*                  compilerOptionsTree;
  TitledWindow*                 compilerOptionsWindow;
  
 //! Public Slots
 public slots :
  void                          SlotCloseButtonPushed           (void);
  void                          SlotBuildSystemSelected         (BuildSystem* InSystem);
  void                          SlotTreeWidgetItemSelected      (QTreeWidgetItem* InItem, int InColumn);

 //! Public Signals
 signals :
  void                          SignalTreeWindowClosed          (void);
  void                          SignalTreeItemSelected          (BuildLine* InLine, QString InFilename);

 //! Public Actions
 public :

};

#endif /* _buildtreewindow_h_*/
