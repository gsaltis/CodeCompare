/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.h
 * DATE         : March 22 2023
 * PROJECT      : CodeCompare
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _maindisplaywindow_h_
#define _maindisplaywindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QToolBar>
#include <QAction>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeWindow.h"
#include "CodeNameWindow.h"
#include "DependencyTreeWindow.h"
#include "BuildTreeWindow.h"
#include "BuildTreeWindowContainer.h"
#include "BuildSystem.h"
#include "TitledWindow.h"
#include "FileTreeWidgetItem.h"
#include "CodeEditor.h"
#include "SourceFileCompareTreeContainer.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : MainDisplayWindow
 *****************************************************************************/
class MainDisplayWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  MainDisplayWindow             ();

 //! Destructor
 public :
  ~MainDisplayWindow            ();

 //! Public Methods
 public :
  void                          SetCodeBaseDirectoryName        (QString InCodeBaseDirectoryName);
  void                          SetTracksDirectoryNames         (QString InTrack1DirectoryName, QString InTrack2DirectoryName);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              ();
  void                          InitializeSubWindows    ();
  void                          CreateSubWindows        ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateConnections       (void);
  void                          SetTrackSubDirSingle    (QFileInfo InFileInfo, QTreeWidgetItem* InItem, int InColumn);
  void                          SetTracksDirectoryNamesPair (QTreeWidgetItem* InItem, QString  InDirName1, QString InDirName2);
  void                          PopulateTreeDirectory           (QStringList InEntryList1, QStringList InEntryList2, FileTreeWidgetItem* InHead);
  bool                          PopulateTreeFiles               (QStringList InEntryList1, QStringList InEntryList2, FileTreeWidgetItem* InHead);
  void                          PopulateDirectoriesAndFiles     (FileTreeWidgetItem* InHead, QString InTrack1DirectoryName, QString InTrack2DirectoryName);
  bool                          FilesAreDifferent               (QString InFilename1, QString InFilename2);
  void                          CreateActions                   ();
  void                          SourceTreeCollapseItem          (QTreeWidgetItem* InItem);
  void                          PopulateCodeDisplay             (QString InFilename, CodeEditor* InCodeWindow);
  void                          DiffFiles                       (FileTreeWidgetItem* InItem, QString InFilename1, QString InFilename2);
  void                          AnalyzeDifferences              (FileTreeWidgetItem* InItem);
  bool                          CreateComparisonSummary         (void);
  void                          CreateComparisonSummaryItems    (QFile* InFile, FileTreeWidgetItem* InItem);

 //! Private Data
 private :
  QString                       Track1DirectoryName;
  QString                       Track2DirectoryName;
  QSplitter*                    splitter;
  TitledWindow*                 codeWindowContainer1;
  TitledWindow*                 codeWindowContainer2;
  TitledWindow*                 sourceFileCompareContainer;
  CodeEditor*                   codeWindow1;
  CodeEditor*                   codeWindow2;
  QTreeWidget*                  sourceFileCompareTree;
  QToolBar*                     sourceFileCompareToolBar;
  DependencyTreeWindow*         dependencyTreeWindow;
  BuildTreeWindow*              buildTreeWindow;
  BuildTreeWindowContainer*     buildTreeContainer;
  bool                          displayDiffsAtStart;
  SourceFileCompareTreeContainer* compareContainer;
  int                           filesDifferCount;
  int                           currentSourceFileCount;
  
 //! Public Slots
 public slots :
  void                          SlotCreateDependencyTree (void);
  void                          SlotDependencyWindowClose (void);
  void                          SlotBuildTreeWindowOpen (void);
  void                          SlotBuildTreeWindowClosed (void);
  void                          SlotBuildSystemSelected (BuildSystem* InSystem);
  void                          SlotOnlyDifferences     (void);
  void                          SlotCollapseSourceCompareTree (void);
  void                          SlotTreeWidgetItemSelected (QTreeWidgetItem* InItem, int InIndex);
  void                          SlotFileDifferInformation (void);
  void                          SlotAnalyzeDifferences  (void);
  void                          SlotSaveSummaryFile     (void);

 //! Public Signals
 signals :
  void                          SignalDependencyWindowClose     (void);
  void                          SignalBuildSystemSelected (BuildSystem* InSystem);
  void                          SignalSendDisplayMessage (QString InMessage);

 //! Public Actions
 public :
  QAction*                      ActionOnlyDifferences;
  QAction*                      ActionCollapseSourceCompareTree;
  QAction*                      ActionFilesDifferInformation;
  QAction*                      ActionAnalyzeDifferences;
  QAction*                      ActionSaveSummaryFile;

};

#endif /* _maindisplaywindow_h_*/
