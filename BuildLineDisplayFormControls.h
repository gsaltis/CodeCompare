/*****************************************************************************
 * FILE NAME    : BuildLineDisplayFormControls.h
 * DATE         : April 07 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildlinedisplayformcontrols_h_
#define _buildlinedisplayformcontrols_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildLineSet.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_LINE_DISPLAY_FORM_CONTROLS_X 200
#define BUILD_LINE_DISPLAY_FORM_CONTROLS_Y 200
#define BUILD_LINE_DISPLAY_FORM_CONTROLS_WIDTH 200
#define BUILD_LINE_DISPLAY_FORM_CONTROLS_HEIGHT 200

/*****************************************************************************!
 * Exported Class : BuildLineDisplayFormControls
 *****************************************************************************/
class BuildLineDisplayFormControls : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLineDisplayFormControls  ();

 //! Destructor
 public :
  ~BuildLineDisplayFormControls ();

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
  void                          CreateConnections       (void);

 //! Private Data
 private :
  QPushButton*                  previousButton;
  QPushButton*                  nextButton;
  BuildLineSet*                 buildLines;
  QLabel*                       currentLineLabel;
  QLabel*                       lineCountLabel;
  int                           currentLine;
  
 //! Public Slots
 public slots :
  void                          SlotNextButtonPushed    (void);
  void                          SlotPreviousButtonPushed(void);
  void                          SlotBuildLinesSet       (BuildLineSet* InLineSet);
  
 //! Public Signals
 signals :
  void                          SignalBuildLineSelected (BuildLine* InBuildLine);

 //! Public Actions
 public :

};

#endif /* _buildlinedisplayformcontrols_h_*/
