/*****************************************************************************
 * FILE NAME    : BuildLineForDisplayForm.h
 * DATE         : April 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildlinefordisplayform_h_
#define _buildlinefordisplayform_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include <QFrame>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildLine.h"
#include "BuildLineBaseDisplayForm.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_LINE_GCC_DISPLAY_FORM_X       200
#define BUILD_LINE_GCC_DISPLAY_FORM_Y       200
#define BUILD_LINE_GCC_DISPLAY_FORM_WIDTH   200
#define BUILD_LINE_GCC_DISPLAY_FORM_HEIGHT  200

/*****************************************************************************!
 * Exported Class : BuildLineForDisplayForm
 *****************************************************************************/
class BuildLineForDisplayForm : public BuildLineBaseDisplayForm
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLineForDisplayForm        ();

 //! Destructor
 public :
  ~BuildLineForDisplayForm       ();

 //! Public Methods
 public :
  void                          SetBuildLine            (BuildLine* InBuildLine);

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
  BuildLine*                    buildLine;
  QLabel*                       actionNameLabel;
  QLabel*                       targetsNameLabel;

  QLabel*                       actionLabel;
  QFrame*                       targets;
  QScrollArea*                  targetsScrollArea;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildlinefordisplayform_h_*/
