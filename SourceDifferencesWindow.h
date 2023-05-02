/*****************************************************************************
 * FILE NAME    : SourceDifferencesWindow.h
 * DATE         : April 25 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sourcedifferenceswindow_h_
#define _sourcedifferenceswindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QScrollArea>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "FileTreeFile.h"
#include "SourceDifferencesItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SOURCE_DIFFERENCES_WINDOW_X     200
#define SOURCE_DIFFERENCES_WINDOW_Y     200
#define SOURCE_DIFFERENCES_WINDOW_WIDTH 200
#define SOURCE_DIFFERENCES_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : SourceDifferencesWindow
 *****************************************************************************/
class SourceDifferencesWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SourceDifferencesWindow       ();

 //! Destructor
 public :
  ~SourceDifferencesWindow      ();

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
  void                          ClearDisplay            (void);
  void                          DisplayChanges          (void);

 //! Private Data
 private :
  FileTreeFile*                 fileItem;
  QList<SourceDifferencesItem*> diffItems;
  QWidget*                      container;
  QScrollArea*                  scrollArea;
  QList<SourceDifferencesItem*> differenceItems;
  
 //! Public Slots
 public slots :
  void                          SlotSetFileItem         (FileTreeFile* InFileItem);
  void                          SlotDifferenceSelected  (FileSectionDiff* InItem);
  
 //! Public Signals
 signals :
  void                          SignalTrack1CodeLineChanged (int InStartLine);
  void                          SignalTrack2CodeLineChanged (int InStartLine);

 //! Public Actions
 public :

};

#endif /* _sourcedifferenceswindow_h_*/
