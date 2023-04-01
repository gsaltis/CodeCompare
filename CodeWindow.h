/*****************************************************************************
 * FILE NAME    : CodeWindow.h
 * DATE         : March 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codewindow_h_
#define _codewindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QFrame>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "WindowHeader.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CODE_WINDOW_X                   200
#define CODE_WINDOW_Y                   200
#define CODE_WINDOW_WIDTH               200
#define CODE_WINDOW_HEIGHT              200

/*****************************************************************************!
 * Exported Class : CodeWindow
 *****************************************************************************/
class CodeWindow : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeWindow                    ();

 //! Destructor
 public :
  ~CodeWindow                   ();

 //! Public Methods
 public :
  void                          SetTitle                (QString InTitle);
  void                          AddDirectory            (QString InDirectoryName);

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
  WindowHeader*                 header;
  QString                       directoryName;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codewindow_h_*/
