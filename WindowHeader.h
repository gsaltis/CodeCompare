/*****************************************************************************
 * FILE NAME    : WindowHeader.h
 * DATE         : March 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _windowheader_h_
#define _windowheader_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define WINDOW_HEADER_X                 0
#define WINDOW_HEADER_Y                 0
#define WINDOW_HEADER_WIDTH             200
#define WINDOW_HEADER_HEIGHT            15

/*****************************************************************************!
 * Exported Class : WindowHeader
 *****************************************************************************/
class WindowHeader : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  WindowHeader                  ();

 //! Destructor
 public :
  ~WindowHeader                 ();

 //! Public Methods
 public :
  void                          SetText                 (QString InText);

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
  QLabel*                       headerText;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _windowheader_h_*/
