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
#include "MainDisplayWindow.h"
#include "trace.h"
#include "gui.h"

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
  QDir                                  dir1;
  QDir                                  dir2;
  QFileInfo                             entryFile1;
  QFileInfo                             entryFile2;
  QFileInfoList                         entryFileList1;
  QFileInfoList                         entryFileList2;
  QString                               fileName1;
  QString                               fileName2;
  QString                               fileName;
  int                                   i1, i2, n, n2, nm;
  QTreeWidgetItem*                      treeItem;
  
  Track1DirectoryName = InTrack1DirectoryName;
  Track2DirectoryName = InTrack2DirectoryName;

  if ( codeWindowContainer1 ) {
    codeWindowContainer1->SetHeaderText(Track1DirectoryName);
  }
  if ( codeWindowContainer2 ) {
    codeWindowContainer2->SetHeaderText(Track2DirectoryName);
  }

  //! Get the directories
  dir1.setPath(Track1DirectoryName);
  dir1.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  entryFileList1 = dir1.entryInfoList();
  n = entryFileList1.size();

  dir2.setPath(Track2DirectoryName);
  dir2.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  entryFileList2 = dir2.entryInfoList();
  n2 = entryFileList2.size();

  i1 = 0;
  i2 = 0;
  nm = n;
  if ( n2 < n ) {
    nm = n2;
  }

  //! Walk the directories
  entryFile1 = entryFileList1[i1];
  entryFile2 = entryFileList2[i2];
  do {
    fileName1 = entryFile1.fileName();
    fileName2 = entryFile2.fileName();
    
    treeItem = new QTreeWidgetItem();

    //! Directory name are equal
    if ( fileName1 == fileName2 ) {
      treeItem->setText(0, fileName1);
      treeItem->setText(1, fileName2);
      sourceFileCompareTree->addTopLevelItem(treeItem);
      SetTracksDirectoryNamesPair(treeItem,
                                  entryFile1.absoluteFilePath(),
                                  entryFile2.absoluteFilePath());
      // SetTrackSubDir(entryFile1, treeItem);
      i1++;
      i2++;
      if ( i1 == nm || i2 == nm ) {
        break;
      }
      entryFile1 = entryFileList1[i1];
      entryFile2 = entryFileList1[i2];
    }

    //! Extra filename in track 1
    else if ( fileName1 < fileName2 ) {
      treeItem->setText(0, fileName1);
      sourceFileCompareTree->addTopLevelItem(treeItem);
      SetTrackSubDirSingle(entryFile1, treeItem, 0);
      i1++;
      if ( i1 == nm ) {
        break;
      }
      entryFile1 = entryFileList1[i1];
    }

    //! Extra filename in track 2
    else {
      treeItem->setText(0, fileName2);
      sourceFileCompareTree->addTopLevelItem(treeItem);
      SetTrackSubDirSingle(entryFile1, treeItem, 1);
      i2++;
      if ( i2 == nm ) {
        break;
      }
      entryFile2 = entryFileList2[i2];
    }
  } while (i1 != nm && i2 != nm );

  //! Get the file names
  dir1.setPath(Track1DirectoryName);
  dir1.setFilter(QDir::Files | QDir::NoDotAndDotDot);
  entryFileList1 = dir1.entryInfoList();
  n = entryFileList1.size();

  dir2.setPath(Track2DirectoryName);
  dir2.setFilter(QDir::Files | QDir::NoDotAndDotDot);
  entryFileList2 = dir2.entryInfoList();
  n2 = entryFileList2.size();

  i1 = 0;
  i2 = 0;
  nm = n;
  if ( n2 < n ) {
    nm = n2;
  }

  //! Walk the file list
  entryFile1 = entryFileList1[i1];
  entryFile2 = entryFileList2[i2];
  do {
    fileName1 = entryFile1.fileName();
    fileName2 = entryFile2.fileName();
    
    treeItem = new QTreeWidgetItem();

    //! File names are equal
    if ( fileName1 == fileName2 ) {
      treeItem->setText(0, fileName1);
      treeItem->setText(1, fileName2);
      sourceFileCompareTree->addTopLevelItem(treeItem);
      i1++;
      i2++;
      if ( i1 == nm || i2 == nm ) {
        break;
      }
      entryFile1 = entryFileList1[i1];
      entryFile2 = entryFileList1[i2];
    }

    //! Extra file name in track 1
    else if ( fileName1 < fileName2 ) {
      treeItem->setText(0, fileName1);
      sourceFileCompareTree->addTopLevelItem(treeItem);
      i1++;
      if ( i1 == nm ) {
        break;
      }
      entryFile1 = entryFileList1[i1];
    }

    //! Extra file name in track 2
    else {
      treeItem->setText(0, fileName2);
      sourceFileCompareTree->addTopLevelItem(treeItem);
      i2++;
      if ( i2 == nm ) {
        break;
      }
      entryFile2 = entryFileList2[i2];
    }
  } while (i1 != nm && i2 != nm );
}

/*****************************************************************************!
 * Function : SetTracksDirectoryNamesPair
 *****************************************************************************/
void
MainDisplayWindow::SetTracksDirectoryNamesPair
(QTreeWidgetItem* InItem, QString  InDirName1, QString InDirName2)
{
  QDir                                  dir1;
  QDir                                  dir2;
  QFileInfo                             entryFile1;
  QFileInfo                             entryFile2;
  QFileInfoList                         entryFileList1;
  QFileInfoList                         entryFileList2;
  QString                               fileName1;
  QString                               fileName2;
  QString                               fileName;
  int                                   i1, i2, n, n2, nm;
  QTreeWidgetItem*                      treeItem;

  if ( codeWindowContainer1 ) {
    //! Get the directories
    dir1.setPath(InDirName1);
    dir1.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    entryFileList1 = dir1.entryInfoList();
    n = entryFileList1.size();

    dir2.setPath(InDirName2);
    dir2.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    entryFileList2 = dir2.entryInfoList();
    n2 = entryFileList2.size();
    i1 = 0;
    i2 = 0;
    nm = n;
    if ( n2 < n ) {
      nm = n2;
    }

    //! Walk the directories
    if ( n > 0 && n2 > 0 ) {
      entryFile1 = entryFileList1[i1];
      entryFile2 = entryFileList2[i2];
      do {
        fileName1 = entryFile1.fileName();
        fileName2 = entryFile2.fileName();
      
        treeItem = new QTreeWidgetItem();
      
        //! Directory name are equal
        if ( fileName1 == fileName2 ) {
          treeItem->setText(0, fileName1);
          treeItem->setText(1, fileName2);
          InItem->addChild(treeItem);
          // SetTrackSubDir(entryFile1, treeItem);
          i1++;
          i2++;
          if ( i1 == nm || i2 == nm ) {
            break;
          }
          entryFile1 = entryFileList1[i1];
          entryFile2 = entryFileList1[i2];
        }
      
        //! Extra filename in track 1
        else if ( fileName1 < fileName2 ) {
          treeItem->setText(0, fileName1);
          InItem->addChild(treeItem);
          SetTrackSubDirSingle(entryFile1, treeItem, 0);
          i1++;
          if ( i1 == nm ) {
            break;
          }
          entryFile1 = entryFileList1[i1];
        }
      
        //! Extra filename in track 2
        else {
          treeItem->setText(0, fileName2);
          InItem->addChild(treeItem);
          SetTrackSubDirSingle(entryFile1, treeItem, 1);
          i2++;
          if ( i2 == nm ) {
            break;
          }
          entryFile2 = entryFileList2[i2];
        }
      } while (i1 != nm && i2 != nm );
    }
    //! Get the file names
    dir1.setPath(InDirName1);
    dir1.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    entryFileList1 = dir1.entryInfoList();
    n = entryFileList1.size();

    dir2.setPath(InDirName2);
    dir2.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    entryFileList2 = dir2.entryInfoList();
    n2 = entryFileList2.size();

    i1 = 0;
    i2 = 0;
    nm = n;
    if ( n2 < n ) {
      nm = n2;
    }

    //! Walk the file list
    entryFile1 = entryFileList1[i1];
    entryFile2 = entryFileList2[i2];
    do {
      fileName1 = entryFile1.fileName();
      fileName2 = entryFile2.fileName();
    
      treeItem = new QTreeWidgetItem();

      //! File names are equal
      if ( fileName1 == fileName2 ) {
        treeItem->setText(0, fileName1);
        treeItem->setText(1, fileName2);
        InItem->addChild(treeItem);
        i1++;
        i2++;
        if ( i1 == nm || i2 == nm ) {
          break;
        }
        entryFile1 = entryFileList1[i1];
        entryFile2 = entryFileList1[i2];
      }

      //! Extra file name in track 1
      else if ( fileName1 < fileName2 ) {
        treeItem->setText(0, fileName1);
        InItem->addChild(treeItem);
        i1++;
        if ( i1 == nm ) {
          break;
        }
        entryFile1 = entryFileList1[i1];
      }

      //! Extra file name in track 2
      else {
        treeItem->setText(0, fileName2);
        InItem->addChild(treeItem);
        i2++;
        if ( i2 == nm ) {
          break;
        }
        entryFile2 = entryFileList2[i2];
      }
    } while (i1 != nm && i2 != nm );
  }
}

/*****************************************************************************!
 * Function : SetTrackSubDirSingle
 *****************************************************************************/
void
MainDisplayWindow::SetTrackSubDirSingle
(QFileInfo InFileInfo, QTreeWidgetItem* InItem, int InColumn)
{
  QTreeWidgetItem*                      treeItem;
  QString                               fileName;
  QFileInfoList                         entryFileList;
  QString                               absFilePath;
  QDir                                  dir;
  
  absFilePath = InFileInfo.absoluteFilePath();

  dir.setPath(absFilePath);
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  entryFileList = dir.entryInfoList();
  foreach(auto entryFile, entryFileList) {
    fileName = entryFile.fileName();
    treeItem = new QTreeWidgetItem();
    treeItem->setText(0, fileName);
    InItem->addChild(treeItem);
    if ( entryFile.isDir() ) {
      SetTrackSubDirSingle(entryFile, treeItem, InColumn);
    }
  }
  dir.setPath(absFilePath);
  dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
  entryFileList = dir.entryInfoList();
  foreach(auto entryFile, entryFileList) {
    fileName = entryFile.fileName();
    treeItem = new QTreeWidgetItem();
    treeItem->setText(0, fileName);
    InItem->addChild(treeItem);
    if ( entryFile.isDir() ) {
      SetTrackSubDirSingle(entryFile, treeItem, InColumn);
    }
  }
}
