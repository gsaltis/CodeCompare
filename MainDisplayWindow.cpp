/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.cpp
 * DATE         : March 22 2023
 * PROJECT      : CodeCompare
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <QMessageBox>
#include <QHeaderView>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeCompareDir.h"
#include "FileTreeWidgetItem.h"
#include "MainDisplayWindow.h"
#include "gui.h"
#include "trace.h"
#include "main.h"
#include "BuildUnknownLine.h"
#include "BuildCompileLine.h"
#include "BuildARLine.h"
#include "BuildLNLine.h"
#include "BuildRanlibLine.h"
#include "BuildForLine.h"
#include "BuildEchoLine.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Function : MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::MainDisplayWindow
(QString InTrack1DirectoryName, QString InTrack2DirectoryName) : QWidget()
{
  Track1DirectoryName = InTrack1DirectoryName;
  Track2DirectoryName = InTrack2DirectoryName;
  buildLines = new BuildLineSet();
  buildSystem = new BuildSystem();
  displayDiffsAtStart = false;
  SetBackgroundColor();  
  Initialize();
}

/*****************************************************************************!
 * Function : SetBackgroundColor
 *****************************************************************************/
void
MainDisplayWindow::SetBackgroundColor
()
{
  QPalette                              pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(160, 160, 160)));
  setPalette(pal);
  setAutoFillBackground(true);
}

/*****************************************************************************!
 * Function : ~MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::~MainDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
MainDisplayWindow::Initialize()
{
  codeTrack1 = new CodeTrack(Track1DirectoryName, 1);
  codeTrack2 = new CodeTrack(Track2DirectoryName, 2);
  
  CreateActions();
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
MainDisplayWindow::InitializeSubWindows()
{
  codeWindow1 = NULL;
  codeWindow2 = NULL;
  sourceFileCompareTree = NULL;
  dependencyTreeWindow = NULL;
}

/*****************************************************************************!
 * Function : CreateActions
 *****************************************************************************/
void
MainDisplayWindow::CreateActions()
{
  ActionOnlyDifferences = new QAction(QIcon(QPixmap(":/images/NotEqual.png")), "Only Show Differences", this);
  connect(ActionOnlyDifferences, SIGNAL(triggered()), this, SLOT(SlotOnlyDifferences()));

  ActionCollapseSourceCompareTree = new QAction(QIcon(QPixmap(":/images/Collapse.png")),
                                                "Collapse Source Compare Tree", this);
  connect(ActionCollapseSourceCompareTree, SIGNAL(triggered()), this, SLOT(SlotCollapseSourceCompareTree()));

  //!
  ActionFilesDifferInformation = new QAction(QIcon(QPixmap(":/images/Info.png")),
                                                "Files Differences Information", this);
  connect(ActionFilesDifferInformation, SIGNAL(triggered()), this, SLOT(SlotFileDifferInformation()));
  ActionFilesDifferInformation->setCheckable(true);
  
  //!
  ActionAnalyzeDifferences = new QAction(QIcon(QPixmap(":/images/Pinion.png")),
                                         "Analyze Differences", this);
  connect(ActionAnalyzeDifferences, SIGNAL(triggered()), this, SLOT(SlotAnalyzeDifferences()));

  //!
  ActionSaveSummaryFile = new QAction(QIcon(QPixmap(":/images/Pencil.png")),
                                      "Save Summary File", this);
  connect(ActionSaveSummaryFile, SIGNAL(triggered()), this, SLOT(SlotSaveSummaryFile()));
  ActionSaveSummaryFile->setEnabled(false);

}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
MainDisplayWindow::CreateSubWindows()
{
  QPalette                              pal;
  QHeaderView*                          headerView;
  QTreeWidgetItem*                      headerItem;
  int                                   windowW;
  int                                   windowH;
  QSize                                 windowSize;
  
  windowSize = mainSystemConfig->GetMainWindowSize();
  windowW = windowSize.width();
  windowH = windowSize.height();

  stack1 = new QStackedWidget();
  stack2 = new QStackedWidget();
  stack3 = new QStackedWidget();
  stack4 = new QStackedWidget();

  codeWindow1 = new CodeEditor();
  codeWindow2 = new CodeEditor();

  buildSystemTree = new BuildSystemTree();
  
  jsonCode1 = new BuildTreeJSONCodeContainer(codeTrack1);
  connect(jsonCode1,
          SIGNAL(SignalBuildTreeJSONErrorOutput(QString)),
          this,
          SLOT(SlotDisplayJSONErrorOutput(QString)));
  connect(jsonCode1,
          SIGNAL(SignalBuildLineProcessed(BuildLine*, QString)),
          this,
          SLOT(SlotBuildLineProcessed(BuildLine*, QString)));
  connect(jsonCode1,
          SIGNAL(SignalSendDisplayMessage(QString)),
          this,
          SLOT(SlotSendDisplayMessage(QString)));
  jsonCode2 = new BuildTreeJSONCodeContainer(codeTrack2);
  sourceFileCompareTree = new QTreeWidget(this);

  connect(buildSystemTree,
          SIGNAL(SignalBuildTreeItemSelected(BuildLine*, QString)),
          jsonCode1,
          SLOT(SlotTreeItemSelected(BuildLine*, QString)));
  connect(jsonCode2,
          SIGNAL(SignalSendDisplayMessage(QString)),
          this,
          SLOT(SlotSendDisplayMessage(QString)));
  
  clangErrorWindow = new QTextEdit();
  pal = clangErrorWindow->palette();
  pal.setBrush(QPalette::Base, QBrush(QColor(0, 0, 200)));
  clangErrorWindow->setPalette(pal);
  clangErrorWindow->setTextBackgroundColor(QColor(0, 0, 200));
  clangErrorWindow->setTextColor(QColor(244, 244, 244));
  clangErrorWindow->setAutoFillBackground(true);
  
  sourceDiffWindow = new SourceDifferencesWindow();
  stack3->resize(300, 277);
  sourceFilesCompareViewToolBar = new SourceCodeComparisonToolBar();
  sourceFilesCompareViewToolBar->setParent(this);

  sourceFileCompareToolBar = new QToolBar();

  codeWindowContainer1 = new TitledWindow(stack1, QString("Track 2"));
  codeWindowContainer2 = new TitledWindow(stack2, QString("Track 3"));

  sourceFileCompareContainer = new TitledWindow(stack4,
                                                sourceFileCompareToolBar,
                                                QString("File Comparison"));
  compareContainer = new SourceFileCompareTreeContainer(sourceFileCompareContainer, sourceFileCompareTree);
  connect(compareContainer,
          SIGNAL(SignalCurrentAnalysisFileNameChanged(QString)),
          this,
          SLOT(SlotCurrentAnalysisFileNameChanged(QString)));
  
  connect(this,
          SIGNAL(SignalAnalysisDone()),
          compareContainer,
          SLOT(SlotAnalysisDone()));

  splitter = new QSplitter(this);
  splitter->show();
  sourceFilesSplitter = new QSplitter();
  sourceFilesSplitter->resize(windowW - 300, windowH);
  
  sourceFilesChangesSplitter = new QSplitter();
  sourceFilesChangesSplitter->resize(windowW - 300, windowH - 300);
  
  dependencyTreeWindow = new DependencyTreeWindow(codeTrack1);
  dependencyTreeWindow->setParent(this);
  dependencyTreeWindow->hide();

  buildTreeWindow = new BuildTreeWindow(codeTrack1, codeTrack2);
  buildTreeWindow->setParent(this);
  buildTreeWindow->hide();

  //!
  stack1->addWidget(codeWindow1);
  stack1->addWidget(jsonCode1);
  
  stack2->addWidget(codeWindow2);
  stack2->addWidget(jsonCode2);

  stack3->addWidget(sourceDiffWindow);
  stack3->addWidget(clangErrorWindow);

  stack4->addWidget(sourceFileCompareTree);
  stack4->addWidget(buildSystemTree);
  
  codeWindowContainer1->resize(QSize(600, 200));
  codeWindowContainer2->resize(QSize(600, 200));
                                
  sourceFilesChangesSplitter->setOrientation(Qt::Vertical);

  sourceFilesSplitter->addWidget(codeWindowContainer1);
  sourceFilesSplitter->addWidget(codeWindowContainer2);

  sourceFilesChangesSplitter->addWidget(sourceFilesSplitter);
  sourceFilesChangesSplitter->addWidget(stack3);
  
  splitter->addWidget(compareContainer);
  splitter->addWidget(sourceFilesChangesSplitter);

  
  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Track 1");
  headerItem->setText(1, "Track 2");
  headerView = sourceFileCompareTree->header();
  pal = headerView->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(128, 128, 128)));
  headerView->setPalette(pal);
  headerView->setAutoFillBackground(true);
  
  headerView->resizeSection(0, 200);
  sourceFileCompareTree->resize(300, windowH);
  
  sourceFileCompareTree->setColumnCount(2);
  sourceFileCompareTree->setHeaderItem(headerItem);

  sourceFileCompareToolBar->resize(100, 32);
  sourceFileCompareToolBar->setIconSize(QSize(32, 32));
  sourceFileCompareToolBar->addAction(ActionCollapseSourceCompareTree);
  sourceFileCompareToolBar->addAction(ActionOnlyDifferences);
  sourceFileCompareToolBar->addAction(ActionFilesDifferInformation);
  sourceFileCompareToolBar->addAction(ActionAnalyzeDifferences);
  sourceFileCompareToolBar->addAction(ActionSaveSummaryFile);


  stack1->setCurrentIndex(0);
  stack2->setCurrentIndex(0);
  stack3->setCurrentIndex(0);
  DisplayTracks();
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
MainDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   dependencyTreeWindowH;
  int                                   dependencyTreeWindowW;
  int                                   dependencyTreeWindowX;
  int                                   dependencyTreeWindowY;
  int                                   buildTreeWindowH;
  int                                   buildTreeWindowW;
  int                                   buildTreeWindowX;
  int                                   buildTreeWindowY;
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   splitterX, splitterY, splitterW, splitterH;
  int                                   toolbarX, toolbarY, toolbarW, toolbarH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  //!
  splitterX = (GUI_X_GAP);
  splitterY = GUI_Y_GAP * 2 + SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT;
  splitterW = width - (GUI_X_GAP * 2);
  splitterH = height - (GUI_Y_GAP * 3 + SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT);
  
  toolbarX = (GUI_X_GAP);
  toolbarY = GUI_Y_GAP;
  toolbarW = width - (GUI_X_GAP * 2);
  toolbarH = SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT;
  
  //!
  dependencyTreeWindowX = (GUI_X_GAP);
  dependencyTreeWindowY = GUI_Y_GAP + SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT;
  dependencyTreeWindowW = width - (GUI_X_GAP * 2);
  dependencyTreeWindowH = height - (GUI_Y_GAP * 3 + SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT);

  //!
  buildTreeWindowX = (GUI_X_GAP);
  buildTreeWindowY = GUI_Y_GAP + SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT;
  buildTreeWindowW = width - (GUI_X_GAP * 2);
  buildTreeWindowH = height - (GUI_Y_GAP * 3 + SOURCE_CODE_COMPARISON_TOOL_BAR_HEIGHT);

  //!
  if ( dependencyTreeWindow ) {
    dependencyTreeWindow->move(dependencyTreeWindowX, dependencyTreeWindowY);
    dependencyTreeWindow->resize(dependencyTreeWindowW, dependencyTreeWindowH);
  }

  //!
  if ( splitter ) {
    splitter->move(splitterX, splitterY);
    splitter->resize(splitterW, splitterH);
  }

  //!
  if ( sourceFilesCompareViewToolBar ) {
    sourceFilesCompareViewToolBar->move(toolbarX, toolbarY);
    sourceFilesCompareViewToolBar->resize(toolbarW, toolbarH);
  }
  
  //!
  if ( buildTreeWindow ) {
    buildTreeWindow->move(buildTreeWindowX, buildTreeWindowY);
    buildTreeWindow->resize(buildTreeWindowW, buildTreeWindowH);
  }    
}

/*****************************************************************************!
 * Function : SlotCreateDependencyTree
 *****************************************************************************/
void
MainDisplayWindow::SlotCreateDependencyTree(void)
{
  splitter->hide();
  dependencyTreeWindow->show();
}

/*****************************************************************************!
 * Function : SlotDependencyWindowClose
 *****************************************************************************/
void
MainDisplayWindow::SlotDependencyWindowClose(void)
{
  emit SignalDependencyWindowClose();
  splitter->show();
  dependencyTreeWindow->hide();
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
MainDisplayWindow::CreateConnections(void)
{
  connect(dependencyTreeWindow,
          SIGNAL(SignalWindowClose()),
          this,
          SLOT(SlotDependencyWindowClose()));

  connect(dependencyTreeWindow,
          SIGNAL(SignalTreeWindowOpen()),
          this,
          SLOT(SlotBuildTreeWindowOpen()));

  connect(buildTreeWindow,
          SIGNAL(SignalTreeWindowClosed()),
          this,
          SLOT(SlotBuildTreeWindowClosed()));

  connect(dependencyTreeWindow,
          SIGNAL(SignalBuildSystemSelected(BuildSystem*)),
          this,
          SLOT(SlotBuildSystemSelected(BuildSystem*)));

  connect(this,
          SIGNAL(SignalBuildSystemSelected(BuildSystem*)),
          buildTreeWindow,
          SLOT(SlotBuildSystemSelected(BuildSystem*)));

  connect(sourceFileCompareTree,
          SIGNAL(itemClicked(QTreeWidgetItem*, int)),
          this,
          SLOT(SlotTreeWidgetItemSelected(QTreeWidgetItem*, int)));
  connect(this,
          SIGNAL(SignalFileItemSelected(FileTreeFile*)),
          sourceDiffWindow,
          SLOT(SlotSetFileItem(FileTreeFile*)));

  connect(sourceDiffWindow,
          SIGNAL(SignalTrack1CodeLineChanged(int)),
          this,
          SLOT(SlotTrack1CodeLineChanged(int)));
  connect(sourceDiffWindow,
          SIGNAL(SignalTrack2CodeLineChanged(int)),
          this,
          SLOT(SlotTrack2CodeLineChanged(int)));
  connect(sourceFilesCompareViewToolBar,
          SIGNAL(SignalCodeViewSelected()),
          this,
          SLOT(SlotCodeViewSelected()));
  connect(sourceFilesCompareViewToolBar,
          SIGNAL(SignalFunctionViewSelected()),
          this,
          SLOT(SlotFunctionViewSelected()));
}

/*****************************************************************************!
 * Function : SlotBuildTreeWindowOpen
 *****************************************************************************/
void
MainDisplayWindow::SlotBuildTreeWindowOpen(void)
{
  dependencyTreeWindow->hide();
  buildTreeWindow->show();
}

/*****************************************************************************!
 * Function : SlotBuildTreeWindowClosed
 *****************************************************************************/
void
MainDisplayWindow::SlotBuildTreeWindowClosed(void)
{
  dependencyTreeWindow->show();
  buildTreeWindow->hide();
}

/*****************************************************************************!
 * Function : SlotBuildSystemSelected
 *****************************************************************************/
void
MainDisplayWindow::SlotBuildSystemSelected
(BuildSystem* InSystem)
{
  emit SignalBuildSystemSelected(InSystem);
}

/*****************************************************************************!
 * Function : SetCodeBaseDirectory
 *****************************************************************************/
void
MainDisplayWindow::SetCodeBaseDirectoryName
(QString InCodeBaseDirectoryName)
{
  SlotBuildTreeWindowOpen();
  dependencyTreeWindow->SetCodeBaseDirectoryName(InCodeBaseDirectoryName);
}

/*****************************************************************************!
 * Function : DisplayTracks
 *****************************************************************************/
void
MainDisplayWindow::DisplayTracks
()
{
  FileTreeWidgetItem*                   sourceItems;
  if ( codeWindowContainer1 ) {
    codeWindowContainer1->SetHeaderText(Track1DirectoryName);
  }
  if ( codeWindowContainer2 ) {
    codeWindowContainer2->SetHeaderText(Track2DirectoryName);
  }

  sourceItems = new FileTreeWidgetItem("", sourceFileCompareTree, true, codeTrack1, codeTrack2);
  sourceItems->setText(0, "Source");
  
  PopulateDirectoriesAndFiles(sourceItems, Track1DirectoryName, Track2DirectoryName);
  sourceFileCompareTree->expandItem(sourceItems);
}

/*****************************************************************************!
 * Function : PopulateDirectoriesAndFiles
 *****************************************************************************/
void
MainDisplayWindow::PopulateDirectoriesAndFiles
(FileTreeWidgetItem* InHead, QString InTrack1DirectoryName, QString InTrack2DirectoryName)
{
  QStringList                           entryFileList1;
  QStringList                           entryFileList2;
  CodeCompareDir*                       dir1;
  CodeCompareDir*                       dir2;
  bool                                  dirsDiff;
  
  //! Get the directories
  if ( ! InTrack2DirectoryName.isEmpty() ) {
    dir1 = new CodeCompareDir(InTrack1DirectoryName);
    entryFileList1 = dir1->ReadDirectories();
    delete dir1;
  }

  if ( ! InTrack2DirectoryName.isEmpty() ) {
    dir2 = new CodeCompareDir(InTrack2DirectoryName);
    entryFileList2 = dir2->ReadDirectories();
    delete dir2;
  }
  if ( entryFileList1.size() > 0 && entryFileList2.size() > 0 ) {
    PopulateTreeDirectory(entryFileList1, entryFileList2, InHead);
  }

  //! Get the file names
  if ( ! InTrack2DirectoryName.isEmpty() ) {
    dir1 = new CodeCompareDir(InTrack1DirectoryName);
    entryFileList1 = dir1->ReadFiles();
    delete dir1;
  }
  if ( ! InTrack2DirectoryName.isEmpty() ) {
    dir2 = new CodeCompareDir(InTrack2DirectoryName);
    entryFileList2 = dir2->ReadFiles();
    delete dir2;
  }
  if ( entryFileList1.size() > 0 && entryFileList2.size() > 0 ) {
    dirsDiff = PopulateTreeFiles(entryFileList1, entryFileList2, InHead);
    QString                           pixmapName = ":/images/Folder.png";

    if ( displayDiffsAtStart ) { 
      if ( dirsDiff ) {
        pixmapName = ":/images/FolderDifferent.png";
        dirsDiff = true;
      } else {
        pixmapName = ":/images/FolderSame.png";
      }
    }
    QPixmap                   pixmap(pixmapName);
    InHead->setIcon(0, pixmap);
  }
}

/*****************************************************************************!
 * Function : PopulateTreeDirectory
 *****************************************************************************/
void
MainDisplayWindow::PopulateTreeDirectory
(QStringList InEntryList1, QStringList InEntryList2, FileTreeWidgetItem* InHead)
{

  QFileInfo                             entryFile1, entryFile2;
  QString                               fileName1, fileName2, st;
  QString                               filePath1, filePath2;
  int                                   i1, i2, n1, n2;
  FileTreeWidgetItem*                   treeItem;

  //! Walk the directories
  InEntryList1.sort();
  InEntryList2.sort();
  n1 = InEntryList1.size();
  n2 = InEntryList2.size();

  if ( n1 == 0 && n2 == 0 ) {
    return;
  }
  i1 = 0;
  i2 = 0;
  do {

    fileName1 = fileName2 = filePath1 = filePath2 = QString();
    if ( i1 < n1 ) {
      entryFile1 = QFileInfo(InEntryList1[i1]);
      fileName1 = entryFile1.fileName();
      filePath1 = entryFile1.absoluteFilePath();
    }
    if ( i2 < n2 ) {
      entryFile2 = QFileInfo(InEntryList2[i2]);
      fileName2 = entryFile2.fileName();
      filePath2 = entryFile2.absoluteFilePath();
    }
    st = QString("%1 ").arg(i1, 2) + fileName1 + QString(" ") + filePath1;
    st = QString("%1 ").arg(i2, 2) + fileName2 + QString(" ") + filePath2;
    
    //! Directory name are equal
    if ( fileName1 == fileName2 ) {
      treeItem = new FileTreeWidgetItem(filePath1, filePath2, InHead, true, codeTrack1, codeTrack2);
      treeItem->SetFilesDiffer(false);
      QPixmap                   pixmap(":/images/Folder.png");
      treeItem->setIcon(0, QIcon(pixmap));
      PopulateDirectoriesAndFiles(treeItem, filePath1, filePath2);
      i1++;
      i2++;
    }
    //! Extra filename in track 1
    else if ( fileName1 < fileName2 || i2 == n2 ) {
      treeItem = new FileTreeWidgetItem(entryFile1.absoluteFilePath(), QString(""), InHead, true, codeTrack1, codeTrack2);
      treeItem->SetFilesDiffer(false);
      QPixmap                   pixmap(":/images/Folder.png");
      treeItem->setIcon(0, QIcon(pixmap));
      i1++;
    }

    //! Extra filename in track 2
    else {
      treeItem = new FileTreeWidgetItem(QString(""), entryFile2.absoluteFilePath(), InHead, true, codeTrack1, codeTrack2);
      treeItem->SetFilesDiffer(false);
      QPixmap                   pixmap(":/images/Folder.png");
      treeItem->setIcon(0, QIcon(pixmap));
      i2++;
    }
    treeItem->setForeground(0, QBrush(QColor(192, 0, 0)));
    treeItem->setForeground(1, QBrush(QColor(192, 0, 0)));
  } while (i1 != n1 && i2 != n2 );
}

/*****************************************************************************!
 * Function : PopulateTreeFiles
 *****************************************************************************/
bool
MainDisplayWindow::PopulateTreeFiles
(QStringList InEntryList1, QStringList InEntryList2, FileTreeWidgetItem* InHead)
{

  QFileInfo                             entryFile1, entryFile2;
  QString                               fileName1, fileName2, st;
  QString                               filePath1, filePath2;
  int                                   i1, i2, n1, n2;
  FileTreeWidgetItem*                   treeItem;
  bool                                  dirsDiff;
  
  //! Walk the file List
  InEntryList1.sort();
  InEntryList2.sort();
  n1 = InEntryList1.size();
  n2 = InEntryList2.size();

  if ( n1 == 0 && n2 == 0 ) {
    return true;
  }
  i1 = 0;
  i2 = 0;
  do {

    fileName1 = fileName2 = filePath1 = filePath2 = QString();
    if ( i1 < n1 ) {
      entryFile1 = QFileInfo(InEntryList1[i1]);
      fileName1 = entryFile1.fileName();
      filePath1 = entryFile1.absoluteFilePath();
    }
    if ( i2 < n2 ) {
      entryFile2 = QFileInfo(InEntryList2[i2]);
      fileName2 = entryFile2.fileName();
      filePath2 = entryFile2.absoluteFilePath();
    }
    st = QString("%1 ").arg(i1, 2) + fileName1 + QString(" ") + filePath1;
    st = QString("%1 ").arg(i2, 2) + fileName2 + QString(" ") + filePath2;
    
    //! Directory name are equal
    if ( fileName1 == fileName2 ) {
      QString                           pixmapName = ":/images/File.png";
      treeItem = new FileTreeWidgetItem(filePath1, filePath2, InHead, false, codeTrack1, codeTrack2);
      if ( displayDiffsAtStart ) {
        if ( FilesAreDifferent(filePath1, filePath2) ) {
          pixmapName = ":/images/FileDifferent.png";
          dirsDiff = true;
          treeItem->SetFilesDiffer(true);
        } else {
          pixmapName = ":/images/FileSame.png";
          treeItem->SetFilesDiffer(false);
        }
      }

      QPixmap                   pixmap(pixmapName);
      treeItem->setIcon(0, QIcon(pixmap));
      i1++;
      i2++;
    }
    //! Extra filename in track 1
    else if ( fileName1 < fileName2 || i2 == n2 ) {
      dirsDiff = true;
      treeItem = new FileTreeWidgetItem(entryFile1.absoluteFilePath(), QString(""), InHead, false, codeTrack1, codeTrack2);
      if ( mainSystemConfig->GetDiffMissingIsDiff() ) {
        QPixmap                   pixmap(":/images/FileMissing.png");
        treeItem->SetFilesDiffer(true);
        treeItem->setIcon(0, QIcon(pixmap));
      } else {
        QPixmap                   pixmap(":/images/File.png");
        treeItem->setIcon(0, QIcon(pixmap));
      }
      i1++;
    }

    //! Extra filename in track 2
    else {
      dirsDiff = true;
      treeItem = new FileTreeWidgetItem(QString(""), entryFile2.absoluteFilePath(), InHead, false, codeTrack1, codeTrack2);
      if ( mainSystemConfig->GetDiffMissingIsDiff() ) {
        QPixmap                   pixmap(":/images/FileMissing.png");
        treeItem->SetFilesDiffer(true);
        treeItem->setIcon(0, QIcon(pixmap));
      } else {
        QPixmap                   pixmap(":/images/File.png");
        treeItem->setIcon(0, QIcon(pixmap));
      }
      i2++;
    }
    treeItem->setForeground(0, QBrush(QColor(0, 0, 192)));
    treeItem->setForeground(1, QBrush(QColor(0, 0, 192)));
  } while (i1 != n1 && i2 != n2 );
  return dirsDiff;
}

/*****************************************************************************!
 * Function : FilesAreDifferent
 *****************************************************************************/
bool
MainDisplayWindow::FilesAreDifferent
(QString InFileName1, QString InFileName2)
{
  QFileInfo                             fileInfo1(InFileName1);
  QFileInfo                             fileInfo2(InFileName2);
  QProcess                              diffProcess;
  QString                               stdOutput;
  QString                               errorOutput;
  QStringList                           args;
  QString                               program = mainSystemConfig->GetDiff();
  QString                               fname, ffname;

  fname = codeTrack1->RemoveLeadingBasePath(InFileName1);
  ffname = mainSystemConfig->GetBuildDirectoryName() + QString("\\") + fname;
  args << "-q" << InFileName1 << InFileName2;
  diffProcess.start(program, args);
  diffProcess.waitForFinished();
  stdOutput = QString(diffProcess.readAllStandardOutput().trimmed());
  errorOutput = QString(diffProcess.readAllStandardError().trimmed());
  
  if ( ! stdOutput.isEmpty() ) {
    return true;
  }
  return false;
}

/*****************************************************************************!
 * Function : SlotOnlyDifferences
 *****************************************************************************/
void
MainDisplayWindow::SlotOnlyDifferences(void)
{
  
}

/*****************************************************************************!
 * Function : SlotCollapseSourceCompareTree
 *****************************************************************************/
void
MainDisplayWindow::SlotCollapseSourceCompareTree(void)
{
  QTreeWidgetItem*                      treeItem;

  treeItem = sourceFileCompareTree->topLevelItem(0);
  SourceTreeCollapseItem(treeItem);
  sourceFileCompareTree->expandItem(treeItem);
}

/*****************************************************************************!
 * Function : SourceTreeCollapseItem
 *****************************************************************************/
void
MainDisplayWindow::SourceTreeCollapseItem
(QTreeWidgetItem* InItem)
{
  int                                   i, n;
  n = InItem->childCount();
  for (i = 0; i < n; i++) {
    sourceFileCompareTree->collapseItem(InItem->child(i));
    SourceTreeCollapseItem(InItem->child(i));
  }
}

/*****************************************************************************!
 * Function : SlotTreeWidgetItemSelected
 *****************************************************************************/
void
MainDisplayWindow::SlotTreeWidgetItemSelected
(QTreeWidgetItem* InItem, int)
{
  FileTreeFile*                         fileItem;
  FileTreeElement*                      fileTreeElement;
  QString                               fileName1;
  QString                               fileName2;
  FileTreeWidgetItem*                   item;
  QList<int>                            changeLinesCount;
  
  codeWindow1->setPlainText("");
  codeWindow2->setPlainText("");
  item = (FileTreeWidgetItem*)InItem;
  fileName1 = item->GetAbsoluteFileName1();
  fileName2 = item->GetAbsoluteFileName2();
  codeWindowContainer1->SetHeaderText(fileName1);
  codeWindowContainer2->SetHeaderText(fileName2);
  item->ReadFiles();
  PopulateCodeDisplay(item, codeWindow1, codeWindow2);

  fileTreeElement = item->GetTreeElement();
  changeLinesCount = fileTreeElement->GetChangeLinesCount();
  SlotFileDifferInformation();
  compareContainer->SetFileTreeItem(fileTreeElement);
  emit SignalTreeItemSelected(item);
  if ( !fileTreeElement->GetIsDirectory() ) {
    fileItem = (FileTreeFile*)fileTreeElement;
    emit SignalFileItemSelected(fileItem);
  }
}

/*****************************************************************************!
 * Function : PopulateCodeDisplay
 *****************************************************************************/
void
MainDisplayWindow::PopulateCodeDisplay
(FileTreeWidgetItem* InItem,
 CodeEditor* InCodeWindow1,
 CodeEditor* InCodeWindow2)
{
  InCodeWindow1->setPlainText(InItem->GetFile1Lines().join("\n"));
  InCodeWindow2->setPlainText(InItem->GetFile2Lines().join("\n"));
}

/*****************************************************************************!
 * Function : SlotFileDifferInformation
 *****************************************************************************/
void
MainDisplayWindow::SlotFileDifferInformation(void)
{
  compareContainer->SetDisplayStatsWindow(true);
}

/*****************************************************************************!
 * Function : SlotAnalyzeDifferences
 *****************************************************************************/
void
MainDisplayWindow::SlotAnalyzeDifferences(void)
{
  FileTreeWidgetItem*                   treeItem;

  filesDifferCount = 0;
  currentSourceFileCount = 0;
  compareContainer->SetDisplayAnalyzeStatsWindow(!compareContainer->GetDisplayAnalyzeStatsWindow());
  
  treeItem = (FileTreeWidgetItem*)sourceFileCompareTree->topLevelItem(0);

  AnalyzeDifferences(treeItem);
  compareContainer->SetFileTreeItem(NULL);
  ActionSaveSummaryFile->setEnabled(true);
  buildSystemTree->SetBuildSystem(buildSystem);

  buildLines->BuildAST(codeTrack1);
  emit SignalAnalysisDone();
}

/*****************************************************************************!
 * Function : AnalyzeDifferences
 *****************************************************************************/
void
MainDisplayWindow::AnalyzeDifferences
(FileTreeWidgetItem* InItem)
{
  int                                   i, n;
  int                                   linesDiffer = 0;
  
  n = InItem->childCount();
  for ( i = 0 ; i < n ; i++ ) {
    FileTreeWidgetItem*                 item;

    item = (FileTreeWidgetItem*)InItem->child(i);
    if ( item->GetIsDirectory() ) {
      auto st = item->GetAbsoluteFileName1() + "/Makefile";
      QFileInfo f(st);
      if ( f.exists() ) {
        PerformMake(item->GetTreeElement());
      }
      AnalyzeDifferences(item);
    } else if ( item->IsSourceFile() ) {
      item->DiffFiles(linesDiffer);
      currentSourceFileCount++;
      compareContainer->SetFileCurrentSourceCount(currentSourceFileCount);
    }
    
    compareContainer->SetFileTreeItem(item->GetTreeElement());
    application->processEvents();
  }
}

/*****************************************************************************!
 * Function : PerformMake
 *****************************************************************************/
void
MainDisplayWindow::PerformMake
(FileTreeElement* InTreeElement)
{
  QString                               errorString;
  QString                               text;
  QString                               fullPath;
  QProcess                              makeProcess;
  QProcessEnvironment                   processEnvironment;                              
  QStringList                           args;
  QString                               program;
  QString                               outputString;
  QString                               libdlPath;
  QFileInfo                             libdlFileInfo;
  bool                                  alreadyHasLIBDL = false;
  QFile                                 file;
  
  fullPath = InTreeElement->GetAbsoluteFileName1();

  if ( mainSystemConfig->GetMakeNeedLIBDLTarget() ) {
    // Create libdl.a since some of the targets rely on -ldl
    libdlPath = fullPath + QString("/libdl.a");
    libdlFileInfo.setFile(libdlPath);
    alreadyHasLIBDL = libdlFileInfo.exists();
    file.setFileName(libdlPath);
    if ( ! alreadyHasLIBDL ) {
      file.open(QIODeviceBase::ReadWrite);
    }
  }
  
  makeProcess.setWorkingDirectory(fullPath);
  program = mainSystemConfig->GetMakeExeName();
  args = mainSystemConfig->GetMakeArgs();
  args << mainSystemConfig->GetMakeTarget();
  QString s = getenv("ACU_SOURCE_DIR");

  // processEnvironment.insert("ACE_SOURCE_DIR", s);
  // makeProcess.setProcessEnvironment(processEnvironment);
  makeProcess.start(program, args);
  makeProcess.waitForFinished();
  outputString = QString(makeProcess.readAllStandardOutput());
  errorString = QString(makeProcess.readAllStandardError());
  
  ParseMakefileOutput(InTreeElement, outputString, fullPath);
  if ( mainSystemConfig->GetMakeNeedLIBDLTarget() ) {
    if ( ! alreadyHasLIBDL ) {
      file.remove(); 
      file.close();
    }
  }
}

/*****************************************************************************!
 * Function : ParseMakefileOutput
 *****************************************************************************/
void
MainDisplayWindow::ParseMakefileOutput
(FileTreeElement* InTreeElement, QString InMakeOutput, QString InFullPath)
{
  QStringList                           lines;
  int                                   linesCount;
  BuildLine*                            line;

  (void)InTreeElement;
  lines = InMakeOutput.split("\n", Qt::SkipEmptyParts);
  linesCount = lines.count();

  for ( int i = 0 ; i < linesCount ; i++ ) {
    line = ParseMakefileOutputLine(lines[i]);
    if ( NULL == line ) {
      continue;
    }
    line->SetFilePath(InFullPath);
    if ( line->GetType() == BuildLine::TypeCompile ) {
      QString t = ((BuildCompileLine*)line)->GetTarget();
    }
    buildLines->AppendLine(line);
  }
}

/*****************************************************************************!
 * Function : ParseMakefileOutputLine
 *****************************************************************************/
BuildLine*
MainDisplayWindow::ParseMakefileOutputLine
(QString InOutputLine)
{
  QStringList                           elements;
  BuildLine*                            outputLine;
  QStringList                           sources;
  BuildElementSet*                      buildSet;
  BuildElement*                         buildElement;
  QString                               targetString;
  BuildUnknownLine*                     unknownBuildLine;
  
  outputLine = NULL;

  if ( InOutputLine.startsWith("#") ) {
    return NULL;
  }
  elements = BuildLine::GetLineElements(InOutputLine);

  
  if ( 0 == elements.count() ) {
    return outputLine;
  }

  //!
  if ( elements[0] == "gcc" ) {
    BuildCompileLine*                   compileBuildLine;
    
    compileBuildLine = new BuildCompileLine();
    compileBuildLine->ParseLine(InOutputLine);
    outputLine = compileBuildLine;
    targetString = compileBuildLine->GetTarget();
    sources = compileBuildLine->GetSources();
    buildSet = new BuildElementSet(targetString);
    buildSet->SetBuildLine(compileBuildLine);
    buildSystem->BuildElementSetAdd(buildSet);

    for ( int i = 0 ;  i < sources.count(); i++ ) {
      QString                           source;
      buildElement = new BuildElement(sources[i]);
      buildSet->AddElement(buildElement);
      buildElement->SetBuildLine(compileBuildLine);
    }
    return outputLine;
  }

  //!
  if ( elements[0] == "ln" ) {
    BuildLNLine*                        line;
    line = new BuildLNLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }

  //!
  if ( elements[0] == "ranlib" ) {
    BuildRanlibLine*                    line;
    line = new BuildRanlibLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }

  //!
  if ( elements[0] == "ar" ) {
    BuildARLine*                        line;
    line = new BuildARLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    targetString = line->GetTarget();
    sources = line->GetSources();
    buildSet = new BuildElementSet(targetString);
    buildSystem->BuildElementSetAdd(buildSet);
    for ( int i = 0 ;  i < sources.count(); i++ ) {
      QString                           source;
      buildElement = new BuildElement(sources[i]);
      buildSet->AddElement(buildElement);
      buildSet->SetBuildLine(line);
    }
    return outputLine;
  }

  //!
  if ( elements[0] == "for" ) {
    BuildForLine*                       line;
    line = new BuildForLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }

  //!
  if ( elements[0] == "echo" ) {
    BuildEchoLine*                      line;
    line = new BuildEchoLine();
    line->ParseLine(InOutputLine);
    outputLine = line;
    return outputLine;
  }
  
  unknownBuildLine = new BuildUnknownLine();
  unknownBuildLine->ParseLine(InOutputLine);
  outputLine = unknownBuildLine;
  return outputLine;
}


/*****************************************************************************!
 * Function : CreateComparisonSummary
 *****************************************************************************/
bool
MainDisplayWindow::CreateComparisonSummary(void)
{
  FileTreeWidgetItem*                   treeItem;
  QFile                                 file;
  QString                               filename = "CodeComparison.csv";
  
  file.setFileName(filename);
  if ( !file.open(QIODeviceBase::ReadWrite | QIODeviceBase::Truncate) ) {
    QString message = QString("Could not open ") + filename;
    QMessageBox::critical(this, filename, message);
    return false;
  }

  treeItem = (FileTreeWidgetItem*)sourceFileCompareTree->topLevelItem(0);
  CreateComparisonSummaryItems(&file, treeItem);
  file.close();
  return true;
}

/*****************************************************************************!
 * Function : CreateComparisonSummaryItems
 *****************************************************************************/
void
MainDisplayWindow::CreateComparisonSummaryItems
(QFile* InFile, FileTreeWidgetItem* InItem)
{
  FileTreeWidgetItem*                   item;
  int                                   i, n;

  n = InItem->childCount();

  for (i = 0; i < n; i++) {
    item = (FileTreeWidgetItem*)InItem->child(i);
    if ( item->GetIsDirectory() ) {
      CreateComparisonSummaryItems(InFile, item);
      continue;
    }
    if ( item->GetFilesDiffer() ) {
      QString                           outputLine;
      QList<int>                        diffCounts;

      diffCounts = item->GetTreeElement()->GetChangeLinesCount();
      outputLine = QString("%1,%2,%3,%4,%5\n").
        arg(item->GetAbsoluteFileName1()).
        arg(item->GetAbsoluteFileName2()).
        arg(diffCounts[0]).
        arg(diffCounts[1]).
        arg(diffCounts[2]);
      InFile->write(outputLine.toLatin1());
    }            
  }
}

/*****************************************************************************!
 * Function : SlotSaveSummaryFile
 *****************************************************************************/
void
MainDisplayWindow::SlotSaveSummaryFile(void)
{
  if ( CreateComparisonSummary() ) {
    emit SignalSendDisplayMessage(QString("Comparison Summary Created"));
  }
}

/*****************************************************************************!
 * Function : SlotTrack1CodeLineChanged
 *****************************************************************************/
void
MainDisplayWindow::SlotTrack1CodeLineChanged
(int InStartLine)
{
  codeWindow1->SlotSetCurrentLine(InStartLine);
}

/*****************************************************************************!
 * Function : SlotTrack2CodeLineChanged
 *****************************************************************************/
void
MainDisplayWindow::SlotTrack2CodeLineChanged
(int InStartLine)
{
  codeWindow2->SlotSetCurrentLine(InStartLine);
}

/*****************************************************************************!
 * Function : SlotCodeViewSelected
 *****************************************************************************/
void
MainDisplayWindow::SlotCodeViewSelected(void)
{
  stack1->setCurrentIndex(0);
  stack2->setCurrentIndex(0);
  stack3->setCurrentIndex(0);
  stack4->setCurrentIndex(0);
}

/*****************************************************************************!
 * Function : SlotFunctionViewSelected
 *****************************************************************************/
void
MainDisplayWindow::SlotFunctionViewSelected(void)
{
  stack1->setCurrentIndex(1);
  stack2->setCurrentIndex(1);
  stack3->setCurrentIndex(1);
  stack4->setCurrentIndex(1);
}

/*****************************************************************************!
 * Function : SlotDisplayJSONErrorOutput
 *****************************************************************************/
void
MainDisplayWindow::SlotDisplayJSONErrorOutput
(QString InErrorOutput)
{
  clangErrorWindow->setText(InErrorOutput);
}

/*****************************************************************************!
 * Function : SlotCurrentAnalysisFileNameChanged
 *****************************************************************************/
void
MainDisplayWindow::SlotCurrentAnalysisFileNameChanged
(QString InFilename)
{
  if ( splashScreen ) {
    splashScreen->showMessage(InFilename, Qt::AlignVCenter);
  }
}

/*****************************************************************************!
 * Function : SlotBuildLineProcessed
 *****************************************************************************/
void
MainDisplayWindow::SlotBuildLineProcessed
(BuildLine* InBuildLine, QString InFilename)
{
  QTreeWidgetItem*                      p;
  FileTreeWidgetItem*                   tw;
  FileTreeElement*                      t;
  FileTreeWidgetItem*                   treeItem;
  FileTreeDirectory*                    treeElement;
  TranslationUnit                       tuType;
  int                                   n;
  FileContentsDiff                      diffs;
  QString                               filename;
  QFileInfo                             f(InFilename);
  filename = f.canonicalFilePath();
  
  treeItem = (FileTreeWidgetItem*)sourceFileCompareTree->topLevelItem(0);
  treeElement = (FileTreeDirectory*)treeItem->GetTreeElement();
  t = treeElement->FindTreeElementByName(InFilename);
  tw = treeItem->FindChildByFileName(filename);
  sourceFileCompareTree->expandItem(tw);
  p = tw->parent();
  do {
    sourceFileCompareTree->expandItem(p);
    p = p->parent();
  } while (p);
  tuType = InBuildLine->GetTranslationUnit();
  n = tuType.count();
  diffs = tw->GetDifferences();
  for ( int i = 0 ; i < n; i++ ) {
    TranslationUnitType* tue = tuType[i];
    QString name = tue->GetName();
    if ( tue->HasTargetChangeLines(&diffs) ) {
      tw->addChild(new QTreeWidgetItem(QStringList(name)));
    }
  }
  
  if ( NULL == t ) {
    return;
  }
  if ( t->GetIsDirectory() ) {
    return;
  }
  FileTreeFile*                         fileElement;

  fileElement = (FileTreeFile*)t;
  fileElement->SetBuildLine(InBuildLine);
  
  InBuildLine->SetFileTreeElement(fileElement);
}

/*****************************************************************************!
 * Function : SlotSendDisplayMessage
 *****************************************************************************/
void
MainDisplayWindow::SlotSendDisplayMessage
(QString InMessage)
{
  emit SignalSendDisplayMessage(InMessage);
}
