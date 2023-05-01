/*****************************************************************************
 * FILE NAME    : SourceFileCompareAnalyzeStatsWindow.h
 * DATE         : April 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sourcefilecompareanalyzestatswindow_h_
#define _sourcefilecompareanalyzestatswindow_h_

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
#include "MonitoredLabel.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SOURCE_FILE_COMPARE_ANALYZE_STATS_WINDOW_X 200
#define SOURCE_FILE_COMPARE_ANALYZE_STATS_WINDOW_Y 200
#define SOURCE_FILE_COMPARE_ANALYZE_STATS_WINDOW_WIDTH 200
#define SOURCE_FILE_COMPARE_ANALYZE_STATS_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : SourceFileCompareAnalyzeStatsWindow
 *****************************************************************************/
class SourceFileCompareAnalyzeStatsWindow : public SourceFileCompareStatsWindow
{
  Q_OBJECT;

 //! Constructors
 public :
  SourceFileCompareAnalyzeStatsWindow ();

 //! Destructor
 public :
  ~SourceFileCompareAnalyzeStatsWindow ();

 //! Public Methods
 public :
  virtual void                  SetFileItem             (FileTreeWidgetItem* InFileItem);
  void                          SetFileCount            (int InFileCount);
  void                          SetFileDifferCount      (int InFileDifferCount);
  void                          SetFileSourceCount      (int InFileSourceCount);
  void                          SetFileCurrentSourceCount(int InCount);
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :
  QLabel*                       fileCountLabel;
  MonitoredLabel*               fileDifferCountLabel;
  QLabel*                       fileSourceCountLabel;
  QLabel*                       fileCurrentSourceCountLabel;
  int                           currentSourceCount;
  int                           differSourceCount;

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QLabel*                       LabelFileName1;

 //! Public Slots
 public slots :
  void                          SlotDifferLabelValueChanged (QString InString);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _sourcefilecompareanalyzestatswindow_h_*/
