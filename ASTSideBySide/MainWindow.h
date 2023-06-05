/*****************************************************************************
 * FILE NAME    : MainWindow.h
 * DATE         : May 10 2023
 * PROJECT      : ASTSByS
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
#include <QApplication>

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
  MainWindow                    (QString InFilename1, QString InFilename2, QApplication* InApplication);
  MainWindow                    (QWidget* InParent, QString InFilename1, QString InFilename2, QApplication* InApplication);

 //! Destructor
 public :
  ~MainWindow                   ();

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
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateActions           ();
  void                          CreateMenus             ();

 //! Private Data
 private :
  MainDisplayWindow*            displayWindow;
  QMenuBar*                     menubar;
  QMenu*                        fileMenu;
  QStatusBar*                   statusbar;
  QString                       filename1;
  QString                       filename2;
  QApplication*                 application;
  
 //! Public Slots
 public slots :
  void                          SlotExit                (void);
  void                          SlotSetBuildWindow      (void);
  
 //! Public Signals
 signals :

 //! Public Actions
 public :
  QAction*                      ActionExit;

};

#endif /* _mainwindow_h_*/
