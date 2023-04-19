/*****************************************************************************
 * FILE NAME    : MainWindow.h
 * DATE         : March 22 2023
 * PROJECT      : CodeCompare
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _mainwindow_h_
#define _mainwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QAction>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainDisplayWindow.h"
#include "SystemConfig.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define MAIN_WINDOW_WIDTH                       640
#define MAIN_WINDOW_HEIGHT                      480
#define MAIN_WINDOW_Y                           100
#define MAIN_WINDOW_X                           100

/*****************************************************************************!
 * Exported Class : MainWindow
 *****************************************************************************/
class MainWindow : public QMainWindow
{
  Q_OBJECT;

 //! Constructors
 public :
  MainWindow                    ();
  MainWindow                    (QWidget* );

 //! Destructor
 public :
  ~MainWindow                   ();

 //! Public Methods
 public :
  void                          SetCodeBaseDirectoryName(QString InCodeBaseDirectoryName);
  void                          SetTracksDirectoryNames         (QString InTrack1DirectoryName, QString InTrack2DirectoryName);

 //! Public Data
 public :

 //! Protected Methods
 protected :
  
 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateActions           ();
  void                          CreateMenus             ();
  void                          CreateConnections       (void);

 //! Private Data
 private :
  MainDisplayWindow*            displayWindow;
  QMenuBar*                     menubar;
  QMenu*                        fileMenu;
  QStatusBar*                   statusbar;
  QMenu*                        actionMenu;

 //! Public Slots
 public slots :
  void                          SlotExit                (void);
  void                          SlotOpen                (void);
  void                          SlotCreateDependencyTree (void);
  void                          SlotDependencyTreeWindowClose (void);
  
 //! Public Signals
 signals :
  void                          SignalCreateDependencyTree (void);

 //! Public Actions
 public :
  QAction*                      ActionExit;
  QAction*                      ActionOpen;
  QAction*                      ActionCreateDependencyTree;

};

#endif /* _mainwindow_h_*/
