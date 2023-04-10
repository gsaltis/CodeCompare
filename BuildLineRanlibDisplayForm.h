/*****************************************************************************
 * FILE NAME    : BuildLineRanlibDisplayForm.h
 * DATE         : April 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildlineranlibdisplayform_h_
#define _buildlineranlibdisplayform_h_

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
 * Exported Class : BuildLineRanlibDisplayForm
 *****************************************************************************/
class BuildLineRanlibDisplayForm : public BuildLineBaseDisplayForm
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLineRanlibDisplayForm        ();

 //! Destructor
 public :
  ~BuildLineRanlibDisplayForm       ();

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
  QLabel*                       targetNameLabel;
  QLabel*                       sourcesLabel;
  QLabel*                       flagsNameLabel;

  QLabel*                       actionLabel;
  QLabel*                       targetLabel;
  QLabel*                       flagsLabel;
  QFrame*                       sources;
  QScrollArea*                  sourcesScrollArea;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildlineranlibdisplayform_h_*/
