/*****************************************************************************
 * FILE NAME    : DirTreeContainer.h
 * DATE         : May 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _dirtreecontainer_h_
#define _dirtreecontainer_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QAction>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirTree.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define DIR_TREE_CONTAINER_X            0
#define DIR_TREE_CONTAINER_Y            0
#define DIR_TREE_CONTAINER_WIDTH        200
#define DIR_TREE_CONTAINER_HEIGHT       200

/*****************************************************************************!
 * Exported Class : DirTreeContainer
 *****************************************************************************/
class DirTreeContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  DirTreeContainer              (DirTree* InTree);

 //! Destructor
 public :
  ~DirTreeContainer             ();

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
  DirTree*                      dirTree;
  QFrame*                       toolBar;
  
  QPushButton*                  CollapseButton;

 //! Public Slots
 public slots :
  void                          SlotCollapseButtonPushed (void);

 //! Public Signals
 signals :
  void                          SignalCollapseTree      (void);

 //! Public Actions
 public :
  QAction*                      ActionCollapseButtonPushed;

};

#endif /* _dirtreecontainer_h_*/
