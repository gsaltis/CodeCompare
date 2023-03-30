/*****************************************************************************
 * FILE NAME    : CodeNameWindow.h
 * DATE         : March 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codenamewindow_h_
#define _codenamewindow_h_

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

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CODE_NAME_WINDOW_X              200
#define CODE_NAME_WINDOW_Y              200
#define CODE_NAME_WINDOW_WIDTH          200
#define CODE_NAME_WINDOW_HEIGHT         200

/*****************************************************************************!
 * Exported Class : CodeNameWindow
 *****************************************************************************/
class CodeNameWindow : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeNameWindow                ();

 //! Destructor
 public :
  ~CodeNameWindow               ();

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

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codenamewindow_h_*/
