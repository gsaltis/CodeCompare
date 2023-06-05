/*****************************************************************************
 * FILE NAME    : DirBuildContainer.h
 * DATE         : May 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _dirbuildcontainer_h_
#define _dirbuildcontainer_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>
#include <QStackedWidget>
#include <QPushButton>
#include <QAction>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirTreeContainer.h"
#include "BuildTreeContainer.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define DIR_BUILD_CONTAINER_X           200
#define DIR_BUILD_CONTAINER_Y           200
#define DIR_BUILD_CONTAINER_WIDTH       200
#define DIR_BUILD_CONTAINER_HEIGHT      200

/*****************************************************************************!
 * Exported Class : DirBuildContainer
 *****************************************************************************/
class DirBuildContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  DirBuildContainer             (DirTreeContainer* InDirContainer,
                                 BuildTreeContainer* InBuildContainer);
 //! Destructor
 public :
  ~DirBuildContainer            ();

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
  void                          SetWindow               (int InWindowIndex);
  
 //! Private Data
 private :
  QFrame*                       toolBar;
  DirTreeContainer*             dirContainer;
  BuildTreeContainer*           buildContainer;
  QStackedWidget*               stacker;
  QPushButton*                  toggleViewButton;
  QStringList                   WindowNames;
  int                           WindowIndexBuild;
  int                           WindowIndexDir;
  
 //! Public Slots
 public slots :
  void                          SlotToggleViewButtonPushed      (void);
  void                          SlotSetBuildWindow              (void);
  void                          SlotSetDirWindow                (void);
  
 //! Public Signals
 signals :

 //! Public Actions
 public :
  QAction*                      ActionToggleViewButtonPushed;

};

#endif /* _dirbuildcontainer_h_*/
