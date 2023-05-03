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
#include <SourceCodeComparisonToolBar.h>
#include <QStackedWidget>
#include <QTextEdit>

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
#include "SourceDifferencesWindow.h"
#include "CodeTrack.h"
#include "BuildTreeJSONCodeContainer.h"
#include "BuildLineSet.h"
#include "BuildLine.h"

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
  MainDisplayWindow             (QString InTrack1DirectoryName, QString InTrack2DirectoryName);

 //! Destructor
 public :
  ~MainDisplayWindow            ();

 //! Public Methods
 public :
  void                          SetCodeBaseDirectoryName        (QString InCodeBaseDirectoryName);
  void                          DisplayTracks                   ();
  
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
  void                          PopulateCodeDisplay             (FileTreeWidgetItem* InItem, CodeEditor* InCodeWindow1, CodeEditor* InCodeWindow2);
  void                          DiffFiles                       (FileTreeWidgetItem* InItem, QString InFilename1, QString InFilename2);
  void                          AnalyzeDifferences              (FileTreeWidgetItem* InItem);
  bool                          CreateComparisonSummary         (void);
  void                          CreateComparisonSummaryItems    (QFile* InFile, FileTreeWidgetItem* InItem);
  void                          SetBackgroundColor              ();
  void                          PerformMake                     ();
  void                          ParseMakefileOutput             (QString InMakeOutput, QString InFullPath);
  BuildLine*                    ParseMakefileOutputLine         (QString InOutputLine);
  
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
  QSplitter*                    sourceFilesSplitter;
  QSplitter*                    sourceFilesChangesSplitter;
  SourceDifferencesWindow*      sourceDiffWindow;
  CodeTrack*                    codeTrack1;
  CodeTrack*                    codeTrack2;
  SourceCodeComparisonToolBar*  sourceFilesCompareViewToolBar;
  BuildTreeJSONCodeContainer*   jsonCode1;
  BuildTreeJSONCodeContainer*   jsonCode2;
  QStackedWidget*               stack1;
  QStackedWidget*               stack2;
  QStackedWidget*               stack3;
  QTextEdit*                    clangErrorWindow;
  BuildLineSet*                 buildLines;
  BuildSystem*                  buildSystem;
  
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
  void                          SlotTrack1CodeLineChanged (int InStartLine);
  void                          SlotTrack2CodeLineChanged (int InStartLine);
  void                          SlotCodeViewSelected    (void);
  void                          SlotFunctionViewSelected (void);

 //! Public Signals
 signals :
  void                          SignalDependencyWindowClose     (void);
  void                          SignalBuildSystemSelected       (BuildSystem* InSystem);
  void                          SignalSendDisplayMessage        (QString InMessage);
  void                          SignalTreeItemSelected          (FileTreeWidgetItem* InItem);
  void                          SignalFileItemSelected          (FileTreeFile* InFileItem);
  void                          SignalAnalysisDone              (void);
  
 //! Public Actions
 public :
  QAction*                      ActionOnlyDifferences;
  QAction*                      ActionCollapseSourceCompareTree;
  QAction*                      ActionFilesDifferInformation;
  QAction*                      ActionAnalyzeDifferences;
  QAction*                      ActionSaveSummaryFile;

};

#endif /* _maindisplaywindow_h_*/
