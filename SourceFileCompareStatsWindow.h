/*****************************************************************************
 * FILE NAME    : SourceFileCompareStatsWindow.h
 * DATE         : April 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sourcefilecomparestatswindow_h_
#define _sourcefilecomparestatswindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "FileTreeElement.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SOURCE_FILE_COMPARE_STATS_WINDOW_X 200
#define SOURCE_FILE_COMPARE_STATS_WINDOW_Y 200
#define SOURCE_FILE_COMPARE_STATS_WINDOW_WIDTH 200
#define SOURCE_FILE_COMPARE_STATS_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : SourceFileCompareStatsWindow
 *****************************************************************************/
class SourceFileCompareStatsWindow : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  SourceFileCompareStatsWindow  ();

 //! Destructor
 public :
  ~SourceFileCompareStatsWindow ();

 //! Public Methods
 public :
  FileTreeElement*              GetFileItem             (void);
  virtual void                  SetFileItem             (FileTreeElement* InFileItem);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :
  FileTreeElement*              fileItem;

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _sourcefilecomparestatswindow_h_*/
