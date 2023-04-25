/*****************************************************************************
 * FILE NAME    : TitledWindow.h
 * DATE         : April 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _titledwindow_h_
#define _titledwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QToolBar>
#include <QFrame>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "WindowHeader.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TITLED_WINDOW_X                 200
#define TITLED_WINDOW_Y                 200
#define TITLED_WINDOW_WIDTH             200
#define TITLED_WINDOW_HEIGHT            200

/*****************************************************************************!
 * Exported Class : TitledWindow
 *****************************************************************************/
class TitledWindow : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  TitledWindow                  (QWidget* InWidget, QString InText);
  TitledWindow                  (QWidget* InWidget, QToolBar* InToolbar, QString InText);

 //! Destructor
 public :
  ~TitledWindow                 ();

 //! Public Methods
 public :
  void                          SetHeaderText           (QString InText);
  void                          SetHeaderBackground     (QBrush InBackground);
  void                          SetHeaderFont           (QFont InHeaderFont);
  void                          SetHeaderAlignment      (Qt::AlignmentFlag InHeaderAlignment);
  void                          SetHeaderHeight         (int InHeaderHeight);
  QColor                        GetHeaderForeground     (void);
  void                          SetHeaderForeground     (QColor InHeaderForeground);
  void                          SetContainer            (QWidget* InContainer);

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
  void                          SetSize                 (QSize InSize);

 //! Private Data
 private :
  QWidget*                      container;
  QWidget*                      header;
  Qt::AlignmentFlag             headerAlignment;
  QBrush                        headerBackground;
  QFont                         headerFont;
  QColor                        headerForeground;
  int                           headerHeight;
  QLabel*                       headerLabel;
  QString                       headerText;
  QToolBar*                     toolbar;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _titledwindow_h_*/
