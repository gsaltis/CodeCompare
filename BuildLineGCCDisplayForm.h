/*****************************************************************************
 * FILE NAME    : BuildLineGCCDisplayForm.h
 * DATE         : April 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildlinegccdisplayform_h_
#define _buildlinegccdisplayform_h_

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
 * Exported Class : BuildLineGCCDisplayForm
 *****************************************************************************/
class BuildLineGCCDisplayForm : public BuildLineBaseDisplayForm
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLineGCCDisplayForm          ();

 //! Destructor
 public :
  ~BuildLineGCCDisplayForm         ();

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
  QLabel*                       sourcesNameLabel;
  QLabel*                       libsNameLabel;
  QLabel*                       includePathsNameLabel;
  QLabel*                       libPathsNameLabel;
  QLabel*                       flagsNameLabel;

  QLabel*                       actionLabel;
  QLabel*                       targetLabel;
  QFrame*                       sourcesNames;
  QFrame*                       libsNames;
  QFrame*                       includesPaths;
  QFrame*                       libsPaths;
  QFrame*                       flags;
  QScrollArea*                  sourcesNamesScrollArea;
  QScrollArea*                  libsNamesScrollArea;
  QScrollArea*                  includesPathsScrollArea;
  QScrollArea*                  libsPathsScrollArea;
  QScrollArea*                  flagsScrollArea;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildlinegccdisplayform_h_*/
