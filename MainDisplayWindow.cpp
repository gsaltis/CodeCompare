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
  codeTrack1 = new CodeTrack(Track1DirectoryName);
  codeTrack2 = new CodeTrack(Track2DirectoryName);
  
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
  codeWindow1 = new CodeEditor();
  codeWindow2 = new CodeEditor();
  jsonCode1 = new BuildTreeJSONCodeContainer(codeTrack1);
  jsonCode2 = new BuildTreeJSONCodeContainer(codeTrack2);
  stack1->addWidget(codeWindow1);
  stack1->addWidget(jsonCode1);
  stack2->addWidget(codeWindow2);
  stack2->addWidget(jsonCode2);

  sourceFileCompareTree = new QTreeWidget(this);
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
  
  sourceDiffWindow = new SourceDifferencesWindow();
  sourceFilesCompareViewToolBar = new SourceCodeComparisonToolBar();

  sourceFileCompareTree->setColumnCount(2);
  sourceFileCompareTree->setHeaderItem(headerItem);
  sourceFileCompareToolBar = new QToolBar();
  sourceFileCompareToolBar->resize(100, 32);
  sourceFileCompareToolBar->setIconSize(QSize(32, 32));
  sourceFileCompareToolBar->addAction(ActionCollapseSourceCompareTree);
  sourceFileCompareToolBar->addAction(ActionOnlyDifferences);
  sourceFileCompareToolBar->addAction(ActionFilesDifferInformation);
  sourceFileCompareToolBar->addAction(ActionAnalyzeDifferences);
  sourceFileCompareToolBar->addAction(ActionSaveSummaryFile);


  codeWindowContainer1 = new TitledWindow(stack1, QString("Track 2"));
  codeWindowContainer2 = new TitledWindow(stack2, QString("Track 3"));
  stack1->setCurrentIndex(0);
  stack2->setCurrentIndex(0);
  
  codeWindowContainer1->resize(QSize(600, 200));
  codeWindowContainer2->resize(QSize(600, 200));
                                
  sourceFileCompareContainer = new TitledWindow(sourceFileCompareTree,
                                                sourceFileCompareToolBar,
                                                QString("File Comparison"));
  compareContainer = new SourceFileCompareTreeContainer(sourceFileCompareContainer, sourceFileCompareTree);
  connect(this,
          SIGNAL(SignalAnalysisDone()),
          compareContainer,
          SLOT(SlotAnalysisDone()));

  splitter = new QSplitter(this);
  sourceFilesSplitter = new QSplitter();
  sourceFilesSplitter->resize(windowW - 300, windowH);
  
  sourceFilesChangesSplitter = new QSplitter();
  sourceFilesChangesSplitter->resize(windowW - 300, windowH - 300);
  
  sourceFilesChangesSplitter->setOrientation(Qt::Vertical);

  sourceFilesSplitter->addWidget(codeWindowContainer1);
  sourceFilesSplitter->addWidget(codeWindowContainer2);

  sourceFilesChangesSplitter->addWidget(sourceFilesCompareViewToolBar);
  sourceFilesChangesSplitter->addWidget(sourceFilesSplitter);
  sourceFilesChangesSplitter->addWidget(sourceDiffWindow);
  
  splitter->addWidget(compareContainer);
  splitter->addWidget(sourceFilesChangesSplitter);

  dependencyTreeWindow = new DependencyTreeWindow(codeTrack1);
  dependencyTreeWindow->setParent(this);
  dependencyTreeWindow->hide();

  buildTreeWindow = new BuildTreeWindow(codeTrack1, codeTrack2);
  buildTreeWindow->setParent(this);
  buildTreeWindow->hide();

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
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  //!
  splitterX = (GUI_X_GAP);
  splitterY = GUI_Y_GAP;
  splitterW = width - (GUI_X_GAP * 2);
  splitterH = height - (GUI_Y_GAP * 2);
  
  //!
  dependencyTreeWindowX = (GUI_X_GAP);
  dependencyTreeWindowY = GUI_Y_GAP;
  dependencyTreeWindowW = width - (GUI_X_GAP * 2);
  dependencyTreeWindowH = height - (GUI_Y_GAP * 2);

  //!
  buildTreeWindowX = (GUI_X_GAP);
  buildTreeWindowY = GUI_Y_GAP;
  buildTreeWindowW = width - (GUI_X_GAP * 2);
  buildTreeWindowH = height - ((GUI_Y_GAP * 2) + 0);

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

  if ( fileInfo1.size() != fileInfo2.size() ) {
    return true;
  }
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
}

/*****************************************************************************!
 * Function : SlotFunctionViewSelected
 *****************************************************************************/
void
MainDisplayWindow::SlotFunctionViewSelected(void)
{
  stack1->setCurrentIndex(1);
  stack2->setCurrentIndex(1);
}
