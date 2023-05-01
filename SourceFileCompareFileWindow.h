/*****************************************************************************
 * FILE NAME    : SourceFileCompareFileWindow.h
 * DATE         : April 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sourcefilecomparefilewindow_h_
#define _sourcefilecomparefilewindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SourceFileCompareStatsWindow.h"
#include "FileTreeElement.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SOURCE_FILE_COMPARE_FILE_WINDOW_X 200
#define SOURCE_FILE_COMPARE_FILE_WINDOW_Y 200
#define SOURCE_FILE_COMPARE_FILE_WINDOW_WIDTH 200
#define SOURCE_FILE_COMPARE_FILE_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : SourceFileCompareFileWindow
 *****************************************************************************/
class SourceFileCompareFileWindow : public SourceFileCompareStatsWindow
{
  Q_OBJECT;

 //! Constructors
 public :
  SourceFileCompareFileWindow   ();

 //! Destructor
 public :
  ~SourceFileCompareFileWindow  ();

 //! Public Methods
 public :
  void                          SetFileTreeItemNames    (FileTreeElement* InItem);
  void                          SetCounts               (QList<int> InValues);

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
  QLabel*                       fileLabel1;
  QLabel*                       fileLabel2;
  QLabel*                       addCountLabel;
  QLabel*                       changeCountLabel;
  QLabel*                       deleteCountLabel;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _sourcefilecomparefilewindow_h_*/
