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
 * Function : CreateSubWindows
 *****************************************************************************/
void
MainDisplayWindow::CreateSubWindows()
{
  QTreeWidgetItem*                      headerItem;

  splitter = new QSplitter(this);

  codeWindow1 = new QTextEdit(this);
  codeWindow2 = new QTextEdit(this);
  sourceFileCompareTree = new QTreeWidget(this);
  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Track 1");
  headerItem->setText(1, "Track 2");
  sourceFileCompareTree->setColumnCount(2);
  sourceFileCompareTree->setHeaderItem(headerItem);
  
  codeWindowContainer1 = new TitledWindow(codeWindow1, QString("Track 2"));
  codeWindowContainer2 = new TitledWindow(codeWindow2, QString("Track 3"));
  sourceFileCompareContainer = new TitledWindow(sourceFileCompareTree, QString("File Comparison"));
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
  FileTreeWidgetItem*                   directoryItems;
  FileTreeWidgetItem*                   fileItems;
  CodeCompareDir*                       dir1;
  CodeCompareDir*                       dir2;

  TRACE_FUNCTION_START();
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
    directoryItems = new FileTreeWidgetItem("", InHead);
    directoryItems->setText(0, "Directories");
    PopulateTreeDirectory(entryFileList1, entryFileList2, directoryItems);
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
  TRACE_FUNCTION_INT(entryFileList1.size());
  TRACE_FUNCTION_INT(entryFileList2.size());
  if ( entryFileList1.size() > 0 && entryFileList2.size() > 0 ) {
    fileItems = new FileTreeWidgetItem("", InHead);
    fileItems->setText(0, "Files");
    PopulateTreeFiles(entryFileList1, entryFileList2, fileItems);
  }
  TRACE_FUNCTION_END();
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
      PopulateDirectoriesAndFiles(treeItem, filePath1, filePath2);
      i1++;
      i2++;
    }
    //! Extra filename in track 1
    else if ( fileName1 < fileName2 || i2 == n2 ) {
      new FileTreeWidgetItem(entryFile1.absoluteFilePath(), QString(""), InHead);
      i1++;
    }

    //! Extra filename in track 2
    else {
      new FileTreeWidgetItem(QString(""), entryFile2.absoluteFilePath(), InHead);
      i2++;
    }
  } while (i1 != n1 && i2 != n2 );
}

/*****************************************************************************!
 * Function : PopulateTreeFiles
 *****************************************************************************/
void
MainDisplayWindow::PopulateTreeFiles
(QStringList InEntryList1, QStringList InEntryList2, FileTreeWidgetItem* InHead)
{

  QFileInfo                             entryFile1, entryFile2;
  QString                               fileName1, fileName2, st;
  QString                               filePath1, filePath2;
  int                                   i1, i2, n1, n2;

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
      new FileTreeWidgetItem(filePath1, filePath2, InHead);
      i1++;
      i2++;
    }
    //! Extra filename in track 1
    else if ( fileName1 < fileName2 || i2 == n2 ) {
       new FileTreeWidgetItem(entryFile1.absoluteFilePath(), QString(""), InHead);
      i1++;
    }

    //! Extra filename in track 2
    else {
      new FileTreeWidgetItem(QString(""), entryFile2.absoluteFilePath(), InHead);
      i2++;
    }
  } while (i1 != n1 && i2 != n2 );
}
