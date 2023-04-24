/*****************************************************************************
 * FILE NAME    : SourceFileCompareTreeContainer.h
 * DATE         : April 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sourcefilecomparetreecontainer_h_
#define _sourcefilecomparetreecontainer_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QTreeWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TitledWindow.h"
#include "SourceFileCompareStatsWindow.h"
#include "SourceFileCompareAnalyzeStatsWindow.h"
#include "FileTreeWidgetItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SOURCE_FILE_COMPARE_TREE_CONTAINER_X 200
#define SOURCE_FILE_COMPARE_TREE_CONTAINER_Y 200
#define SOURCE_FILE_COMPARE_TREE_CONTAINER_WIDTH 200
#define SOURCE_FILE_COMPARE_TREE_CONTAINER_HEIGHT 200

/*****************************************************************************!
 * Exported Class : SourceFileCompareTreeContainer
 *****************************************************************************/
class SourceFileCompareTreeContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SourceFileCompareTreeContainer (TitledWindow* InSourceTreeWindow,
                                  QTreeWidget* InSourceTree);

 //! Destructor
 public :
  ~SourceFileCompareTreeContainer ();

 //! Public Methods
 public :
  bool                          GetDisplayStatsWindow           (void);
  bool                          GetDisplayAnalyzeStatsWindow    (void);
  void                          SetDisplayStatsWindow           (bool InDisplayStatsWindow);
  void                          SetDisplayAnalyzeStatsWindow    (bool InDisplayAnalyzeStatsWindow);
  void                          SetFileTreeItem                 (FileTreeWidgetItem* InItem);
  void                          SetFilesDifferCount             (int InCount);
  
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
  void                          SetSize                 (QSize InSize);
  int                           GetFileCount            (void);
  void                          GetItemFileCount        (FileTreeWidgetItem* InItem, int &InCount);
  int                           GetSourceFileCount      (void);
  void                          GetItemSourceFileCount  (FileTreeWidgetItem* InItem, int &InCount);
  int                           GetFileDifferCount      (void);
  void                          GetItemFileDifferCount  (FileTreeWidgetItem* InItem, int &InCount);
  
 //! Private Data
 private :
  TitledWindow*                         sourceFileCompareTree;
  SourceFileCompareStatsWindow*         statsWindow;
  SourceFileCompareAnalyzeStatsWindow*  statsAnalyzeWindow;
  bool                                  displayStatsWindow;
  bool                                  displayAnalyzeStatsWindow;
  QTreeWidget*                          sourceTree;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _sourcefilecomparetreecontainer_h_*/
