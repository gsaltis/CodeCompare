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
#include <QFormLayout>
#include <QLabel>
#include <QListWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildLine.h"

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
  BuildLineDisplayForm          (BuildLine* InLine);

 //! Destructor
 public :
  ~BuildLineDisplayForm         ();

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
  QLabel*                       CreateLabel             (QString InText);
  void                          AddRow                  (QString InLabelText, QWidget* InWidget);
  void                          InsertRow               (QString InLabelText, QWidget* InWidget);
  void                          RemoveRow               ();

 //! Private Data
 private :
  BuildLine*                    buildLine;
  QFormLayout*                  formLayout;
  QLabel*                       actionLabel;
  QLabel*                       targetLabel;
  QListWidget*                  sourcesTable;
  QListWidget*                  libsTable;
  QListWidget*                  libPathsTable;
  QListWidget*                  includePathsTable;
  QListWidget*                  flagsTable;
  int                           y;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildlinedisplayform_h_*/
