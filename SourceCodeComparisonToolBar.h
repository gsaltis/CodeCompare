/*****************************************************************************
 * FILE NAME    : SourceCodeComparisonToolBar.h
 * DATE         : May 02 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sourcecodecomparisontoolbar_h_
#define _sourcecodecomparisontoolbar_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QAction>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SOURCE_CODE_COMPARISON_TOOL_BAR_X 200
#define SOURCE_CODE_COMPARISON_TOOL_BAR_Y 200
#define SOURCE_CODE_COMPARISON_TOOL_BAR_WIDTH 200
#define SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT 32

/*****************************************************************************!
 * Exported Class : SourceCodeComparisonToolBar
 *****************************************************************************/
class SourceCodeComparisonToolBar : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  SourceCodeComparisonToolBar   ();

 //! Destructor
 public :
  ~SourceCodeComparisonToolBar  ();

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
  QPushButton*                  CodeViewButton;
  QPushButton*                  FunctionViewButton;

 //! Public Slots
 public slots :
  void                          SlotCodeViewButtonPushed (void);
  void                          SlotFunctionViewButtonPushed (void);

 //! Public Signals
 signals :
  void                          SignalCodeViewSelected          (void);
  void                          SignalFunctionViewSelected      (void);

 //! Public Actions
 public :
  QAction*                      ActionCodeViewButtonPushed;
  QAction*                      ActionFunctionViewButtonPushed;

};

#endif /* _sourcecodecomparisontoolbar_h_*/
