/*****************************************************************************
 * FILE NAME    : CodeCompareToolBarButton.h
 * DATE         : May 02 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codecomparetoolbarbutton_h_
#define _codecomparetoolbarbutton_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CODE_COMPARE_TOOL_BAR_BUTTON_X  200
#define CODE_COMPARE_TOOL_BAR_BUTTON_Y  200
#define CODE_COMPARE_TOOL_BAR_BUTTON_WIDTH 200
#define CODE_COMPARE_TOOL_BAR_BUTTON_HEIGHT 200

/*****************************************************************************!
 * Exported Class : CodeCompareToolBarButton
 *****************************************************************************/
class CodeCompareToolBarButton : public QPushButton
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeCompareToolBarButton      (QWidget* InParent, int InX, QIcon InIcon);

 //! Destructor
 public :
  ~CodeCompareToolBarButton     ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :
  virtual void                  enterEvent              (QEnterEvent* InEvent);
  virtual void                  leaveEvent              (QEvent* InEvent);
  virtual void                  paintEvent              (QPaintEvent *event);
  virtual void                  mouseMoveEvent          (QMouseEvent *event);
  virtual void                  resizeEvent             (QResizeEvent* InEvent);
  
 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();

 //! Private Data
 private :
  bool                          mouseIn;
  QIcon                         buttonIcon;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codecomparetoolbarbutton_h_*/
