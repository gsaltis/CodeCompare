/*****************************************************************************
 * FILE NAME    : BuildLineUnknownDisplayForm.h
 * DATE         : April 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildlineunknowndisplayform_h_
#define _buildlineunknowndisplayform_h_

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
#define BUILD_LINE_Unknown_DISPLAY_FORM_X       200
#define BUILD_LINE_Unknown_DISPLAY_FORM_Y       200
#define BUILD_LINE_Unknown_DISPLAY_FORM_WIDTH   200
#define BUILD_LINE_Unknown_DISPLAY_FORM_HEIGHT  200

/*****************************************************************************!
 * Exported Class : BuildLineUnknownDisplayForm
 *****************************************************************************/
class BuildLineUnknownDisplayForm : public BuildLineBaseDisplayForm
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLineUnknownDisplayForm          ();

 //! Destructor
 public :
  ~BuildLineUnknownDisplayForm         ();

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
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          initialize              ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  
 //! Private Data
 private :
  BuildLine*                    buildLine;
  QLabel*                       unknownTextLabel;
  QTextEdit*                    unknownTextEdit;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildlineunknowndisplayform_h_*/
