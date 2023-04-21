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
() : QWidget()
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(160, 160, 160)));
  setPalette(pal);
  setAutoFillBackground(true);

  Initialize();
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
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
MainDisplayWindow::CreateSubWindows()
{
  QTreeWidgetItem*                      headerItem;

  splitter = new QSplitter(this);

  codeWindow1 = new CodeEditor();
  codeWindow1->show();
  codeWindow1->setText(QString("Hi Mom"));
  codeWindow2 = new CodeEditor();

  sourceFileCompareTree = new QTreeWidget(this);
  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Track 1");
  headerItem->setText(1, "Track 2");

  sourceFileCompareTree->setColumnCount(2);
  sourceFileCompareTree->setHeaderItem(headerItem);
  sourceFileCompareToolBar = new QToolBar();
  sourceFileCompareToolBar->resize(100, 32);
  sourceFileCompareToolBar->setIconSize(QSize(32, 32));
  sourceFileCompareToolBar->addAction(ActionCollapseSourceCompareTree);
  sourceFileCompareToolBar->addAction(ActionOnlyDifferences);
  
  codeWindowContainer1 = new TitledWindow(codeWindow1, QString("Track 2"));
  codeWindowContainer2 = new TitledWindow(codeWindow2, QString("Track 3"));
  sourceFileCompareContainer = new TitledWindow(sourceFileCompareTree,
                                                sourceFileCompareToolBar,
                                                QString("File Comparison"));
  sourceFileCompareTree->resize(300, 100);
  
  splitter->addWidget(sourceFileCompareContainer);
  splitter->addWidget(codeWindowContainer1);
  splitter->addWidget(codeWindowContainer2);

  dependencyTreeWindow = new DependencyTreeWindow();
  dependencyTreeWindow->setParent(this);
  dependencyTreeWindow->hide();

  buildTreeWindow = new BuildTreeWindow();
  buildTreeWindow->setParent(this);
  buildTreeWindow->hide();
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
 * Function : SetTracksDirectoryNames
 *****************************************************************************/
void
MainDisplayWindow::SetTracksDirectoryNames
(QString InTrack1DirectoryName, QString InTrack2DirectoryName)
{
  FileTreeWidgetItem*                   sourceItems;
  
  Track1DirectoryName = InTrack1DirectoryName;
  Track2DirectoryName = InTrack2DirectoryName;
  
  if ( codeWindowContainer1 ) {
    codeWindowContainer1->SetHeaderText(Track1DirectoryName);
  }
  if ( codeWindowContainer2 ) {
    codeWindowContainer2->SetHeaderText(Track2DirectoryName);
  }

  sourceItems = new FileTreeWidgetItem("", sourceFileCompareTree);
  sourceItems->setText(0, "Source");

  PopulateDirectoriesAndFiles(sourceItems, Track1DirectoryName, Track2DirectoryName);
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
    QString                           pixmapName;
    if ( dirsDiff ) {
      pixmapName = ":/images/FolderDifferent.png";
      dirsDiff = true;
    } else {
      pixmapName = ":/images/FolderSame.png";
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
      treeItem = new FileTreeWidgetItem(filePath1, filePath2, InHead);
      QPixmap                   pixmap(":/images/Folder.png");
      treeItem->setIcon(0, QIcon(pixmap));
      PopulateDirectoriesAndFiles(treeItem, filePath1, filePath2);
      i1++;
      i2++;
    }
    //! Extra filename in track 1
    else if ( fileName1 < fileName2 || i2 == n2 ) {
      treeItem = new FileTreeWidgetItem(entryFile1.absoluteFilePath(), QString(""), InHead);
      QPixmap                   pixmap(":/images/Folder.png");
      treeItem->setIcon(0, QIcon(pixmap));
      i1++;
    }

    //! Extra filename in track 2
    else {
      treeItem = new FileTreeWidgetItem(QString(""), entryFile2.absoluteFilePath(), InHead);
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
  
  //! Walk the directories
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
      QString                           pixmapName;
      if ( FilesAreDifferent(filePath1, filePath2) ) {
        pixmapName = ":/images/FileDifferent.png";
        dirsDiff = true;
      } else {
        pixmapName = ":/images/FileSame.png";
      }
      QPixmap                   pixmap(pixmapName);
      treeItem = new FileTreeWidgetItem(filePath1, filePath2, InHead);
      treeItem->setIcon(0, QIcon(pixmap));
      i1++;
      i2++;
    }
    //! Extra filename in track 1
    else if ( fileName1 < fileName2 || i2 == n2 ) {
      dirsDiff = true;
      treeItem = new FileTreeWidgetItem(entryFile1.absoluteFilePath(), QString(""), InHead);
      if ( mainSystemConfig->GetDiffMissingIsDiff() ) {
        QPixmap                   pixmap(":/images/FileMissing.png");
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
      treeItem = new FileTreeWidgetItem(QString(""), entryFile2.absoluteFilePath(), InHead);
      if ( mainSystemConfig->GetDiffMissingIsDiff() ) {
        QPixmap                   pixmap(":/images/FileMissing.png");
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

  if ( fileInfo2.size() != fileInfo1.size() ) {
    return false;
  }
  return true;
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
  QString                               fileName1;
  QString                               fileName2;
  FileTreeWidgetItem*                   item;
  
  item = (FileTreeWidgetItem*)InItem;
  fileName1 = item->GetAbsoluteFileName1();
  fileName2 = item->GetAbsoluteFileName2();

  PopulateCodeDisplay(fileName1, codeWindow1);
  PopulateCodeDisplay(fileName2, codeWindow2);
}

/*****************************************************************************!
 * Function : PopulateCodeDisplay
 *****************************************************************************/
void
MainDisplayWindow::PopulateCodeDisplay
(QString InFilename, CodeEditor* InCodeWindow)
{
  QByteArray                            fileContents;
  QString                               fileContentsString;
  QFile                                 file(InFilename);
  file.open(QIODeviceBase::ReadOnly);

  fileContents = file.readAll();
  file.close();
  if ( fileContents.isNull() ) {
    return;
  }
  fileContentsString = QString(fileContents);
  InCodeWindow->setText(fileContentsString);
}
