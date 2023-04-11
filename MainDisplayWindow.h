/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.h
 * DATE         : March 22 2023
 * PROJECT      : CodeCompare
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _maindisplaywindow_h_
#define _maindisplaywindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeWindow.h"
#include "CodeNameWindow.h"
#include "DependencyTreeWindow.h"
#include "BuildTreeWindow.h"
#include "BuildSystem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : MainDisplayWindow
 *****************************************************************************/
class MainDisplayWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  MainDisplayWindow             ();

 //! Destructor
 public :
  ~MainDisplayWindow            ();

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
  void                          Initialize              ();
  void                          InitializeSubWindows    ();
  void                          CreateSubWindows        ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateConnections       (void);

 //! Private Data
 private :
  CodeWindow*                   codeWindowTrack1;
  CodeWindow*                   codeWindowTrack2;
  CodeNameWindow*               codeNameWindow;
  CodeWindow*                   codeWindowMerge;
  DependencyTreeWindow*         dependencyTreeWindow;
  BuildTreeWindow*              buildTreeWindow;
  
 //! Public Slots
 public slots :
  void                          SlotCreateDependencyTree (void);
  void                          SlotDependencyWindowClose (void);
  void                          SlotBuildTreeWindowOpen (void);
  void                          SlotBuildTreeWindowClosed (void);
  void                          SlotBuildSystemSelected (BuildSystem* InSystem);

 //! Public Signals
 signals :
  void                          SignalDependencyWindowClose     (void);
  void                          SignalBuildSystemSelected (BuildSystem* InSystem);

 //! Public Actions
 public :

};

#endif /* _maindisplaywindow_h_*/
