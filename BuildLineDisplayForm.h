/*****************************************************************************
 * FILE NAME    : BuildLineDisplayForm.h
 * DATE         : April 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildlinedisplayform_h_
#define _buildlinedisplayform_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildLineGCCDisplayForm.h"
#include "BuildLineLNDisplayForm.h"
#include "BuildLineARDisplayForm.h"
#include "BuildLineRanlibDisplayForm.h"
#include "BuildLineUnknownDisplayForm.h"
#include "BuildLineDisplayFormControls.h"
#include "BuildLineForDisplayForm.h"
#include "BuildLineEchoDisplayForm.h"
#include "BuildLine.h"
#include "BuildLineSet.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_LINE_DISPLAY_FORM_X       200
#define BUILD_LINE_DISPLAY_FORM_Y       200
#define BUILD_LINE_DISPLAY_FORM_WIDTH   200
#define BUILD_LINE_DISPLAY_FORM_HEIGHT  200

/*****************************************************************************!
 * Exported Class : BuildLineDisplayForm
 *****************************************************************************/
class BuildLineDisplayForm : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLineDisplayForm          ();

 //! Destructor
 public :
  ~BuildLineDisplayForm         ();

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
  BuildLineGCCDisplayForm*      gccForm;
  BuildLineUnknownDisplayForm*  unknownBuildTypeForm;
  BuildLineLNDisplayForm*       lnForm;
  BuildLineARDisplayForm*       arForm;
  BuildLineRanlibDisplayForm*   ranlibForm;
  BuildLineEchoDisplayForm*     echoForm;
  BuildLineForDisplayForm*      forForm;
  BuildLineDisplayFormControls* controlsForm;
  BuildLine*                    buildLine;
  BuildLineSet*                 buildLines;
  
 //! Public Slots
 public slots :
  void                          SlotBuildLinesSelected  (BuildLineSet* InLineSet);
  void                          SlotBuildLineSelected   (BuildLine* InBuildLine);
  
 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildlinedisplayform_h_*/
