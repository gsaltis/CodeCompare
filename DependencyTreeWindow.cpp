/*****************************************************************************
 * FILE NAME    : DependencyTreeWindow.cpp
 * DATE         : March 31 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFileDialog>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DependencyTreeWindow.h"
#include "main.h"
#include "trace.h"

/*****************************************************************************!
 * Function : DependencyTreeWindow
 *****************************************************************************/
DependencyTreeWindow::DependencyTreeWindow
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~DependencyTreeWindow
 *****************************************************************************/
DependencyTreeWindow::~DependencyTreeWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
DependencyTreeWindow::initialize()
{
  buildSystem = new BuildSystem();
  InitializeSubWindows();  
  CreateSubWindows();
  ActionCloseButtonPushed = new QAction("CloseButtonPushed", this);
  ActionpathLineSelectPushed = new QAction("pathLineSelectPushed", this);
  ActionBrowsePathButtonPushed = new QAction("BrowsePathButtonPushed", this);
  ConnectWindows();
}

/*****************************************************************************!
 * Function : ConnectWindows
 *****************************************************************************/
void
DependencyTreeWindow::ConnectWindows
()
{
  connect(ActionCloseButtonPushed, SIGNAL(triggered()), this, SLOT(SlotCloseButtonPushed()));
  connect(ActionpathLineSelectPushed, SIGNAL(triggered()), this, SLOT(SlotpathLineSelectPushed()));
  connect(ActionBrowsePathButtonPushed, SIGNAL(triggered()), this, SLOT(SlotBrowsePathButtonPushed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
DependencyTreeWindow::CreateSubWindows()
{
  QTreeWidgetItem*                      treeHeader;

  //! Create the CloseButton button  
  CloseButton = new QPushButton();
  CloseButton->setParent(this);
  CloseButton->setText("Close");
  CloseButton->move(10, 10);
  CloseButton->resize(100,20);
  connect(CloseButton, SIGNAL(pressed()), this, SLOT(SlotCloseButtonPushed()));

  //! Create the CloseButton button  
  TreeButton = new QPushButton();
  TreeButton->setParent(this);
  TreeButton->setText("Tree");
  TreeButton->move(10, 10);
  TreeButton->resize(100,20);
  connect(TreeButton, SIGNAL(pressed()), this, SLOT(SlotTreeButtonPushed()));

    //! Create pathLineInput LineEdit
  pathLineInput = new QLineEdit();
  pathLineInput->setParent(this);
  pathLineInput->move(10,10);
  pathLineInput->resize(100,20);
  pathLineInput->setText(mainSystemConfig->GetSourceTrackPath());

  //! Create the pathLineSelect button
  pathLineSelectButton = new QPushButton();
  pathLineSelectButton->setParent(this);
  pathLineSelectButton->setText("Select");
  pathLineSelectButton->move(10, 10);
  pathLineSelectButton->resize(100,20);

  //! Create directory Tree
  directoryTreeWindow = new QTreeWidget();
  directoryTreeWindow->setParent(this);
  directoryTreeWindow->setFrameShadow(QFrame::Sunken);
  directoryTreeWindow->setFrameShape(QFrame::Box);
  directoryTreeWindow->setLineWidth(1);
  directoryTreeWindow->setAutoFillBackground(true);
  connect(directoryTreeWindow,
          SIGNAL(itemClicked(QTreeWidgetItem*, int)),
          this,
          SLOT(SlotTreeWidgetItemSelected(QTreeWidgetItem*, int)));

  buildLineDisplayWindow = new BuildLineDisplayForm();
  buildLineDisplayWindow->setParent(this);

  connect(this,
          SIGNAL(SignalBuildLinesSelected(BuildLineSet*)),
          buildLineDisplayWindow,
          SLOT(SlotBuildLinesSelected(BuildLineSet*)));
  
  QBrush fg(Qt::blue);
  QBrush bg(Qt::darkGray);

  treeHeader = new QTreeWidgetItem(static_cast<QTreeWidget*>(nullptr), QStringList(QString("Name")));
  treeHeader->setData(0, Qt::ForegroundRole, fg);
  treeHeader->setBackground(0, bg); // setData(0, Qt::BackgroundRole, bg);
  treeHeader->setFont(0, QFont("", 10, QFont::Bold));

  directoryTreeWindow->setHeaderItem(treeHeader);
  connect(pathLineSelectButton, SIGNAL(pressed()), this, SLOT(SlotpathLineSelectPushed()));

  //! Create the BrowsePathButton button
  BrowsePathButton = new QPushButton();
  BrowsePathButton->setParent(this);
  BrowsePathButton->setText("");
  BrowsePathButton->move(10, 10);
  BrowsePathButton->resize(100,20);

  BrowsePathButton->setCursor(Qt::PointingHandCursor);
  BrowsePathButton->setToolTip(QString("Browse Source Path"));
  BrowsePathButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

  QPixmap                       iconPixmap(":/images/OpenFile.png");
  QIcon                         icon(iconPixmap);
  BrowsePathButton->setIcon(icon);
  BrowsePathButton->setIconSize(QSize(20, 20));
  connect(BrowsePathButton, SIGNAL(pressed()), this, SLOT(SlotBrowsePathButtonPushed()));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
DependencyTreeWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
DependencyTreeWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   closeButtonX, closeButtonY;
  int                                   closeButtonW, closeButtonH;
  int                                   treeButtonX, treeButtonY;
  int                                   treeButtonW, treeButtonH;
  int                                   pathLineInputX, pathLineInputY;
  int                                   pathLineInputW, pathLineInputH;
  int                                   pathLineSelectButtonX, pathLineSelectButtonY;
  int                                   pathLineSelectButtonW, pathLineSelectButtonH;
  int                                   browsePathButtonX, browsePathButtonY;
  int                                   browsePathButtonW, browsePathButtonH;
  int                                   directoryTreeWindowX, directoryTreeWindowY;
  int                                   directoryTreeWindowW, directoryTreeWindowH;
  int                                   buildLineDisplayWindowX, buildLineDisplayWindowY;
  int                                   buildLineDisplayWindowH, buildLineDisplayWindowW;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  closeButtonW = 60;
  closeButtonH = 20;
  closeButtonX = width - (closeButtonW + 10);
  closeButtonY = height- (closeButtonH + 10);

  treeButtonW = 60;
  treeButtonH = 20;
  treeButtonX = width - (treeButtonW + 20 + closeButtonW);
  treeButtonY = height- (treeButtonH + 10);

  pathLineInputX = 10;
  pathLineInputY = 10;
  pathLineInputW = width - (pathLineInputX * 2 + 85);
  pathLineInputH = 20;

  pathLineSelectButtonW = 60;
  pathLineSelectButtonH = 20;
  pathLineSelectButtonX = width - 65;
  pathLineSelectButtonY = 10;

  browsePathButtonX = width - 90;
  browsePathButtonY = 10;
  browsePathButtonW = 20;
  browsePathButtonH = 20;

  directoryTreeWindowY = pathLineInputY + pathLineInputH + 10;
  directoryTreeWindowX = 10;
  directoryTreeWindowH = height - (pathLineInputH + browsePathButtonH + 40);
  directoryTreeWindowW = (width - 30) * 5 / 8 ;

  buildLineDisplayWindowX = directoryTreeWindowX + directoryTreeWindowW + 10;
  buildLineDisplayWindowY = pathLineInputY + pathLineInputH + 10;
  buildLineDisplayWindowW = (width - 30) - directoryTreeWindowW;
  buildLineDisplayWindowH = directoryTreeWindowH;
  
  CloseButton->move(closeButtonX, closeButtonY);
  CloseButton->resize(closeButtonW, closeButtonH);

  TreeButton->move(treeButtonX, treeButtonY);
  TreeButton->resize(treeButtonW, treeButtonH);
  
  pathLineInput->move(pathLineInputX, pathLineInputY);
  pathLineInput->resize(pathLineInputW, pathLineInputH);

  pathLineSelectButton->move(pathLineSelectButtonX, pathLineSelectButtonY);
  pathLineSelectButton->resize(pathLineSelectButtonW, pathLineSelectButtonH);

  BrowsePathButton->move(browsePathButtonX, browsePathButtonY);
  BrowsePathButton->resize(browsePathButtonW, browsePathButtonH);

  buildLineDisplayWindow->move(buildLineDisplayWindowX, buildLineDisplayWindowY);
  buildLineDisplayWindow->resize(buildLineDisplayWindowW, buildLineDisplayWindowH);
  
  directoryTreeWindow->move(directoryTreeWindowX, directoryTreeWindowY);
  directoryTreeWindow->resize(directoryTreeWindowW, directoryTreeWindowH);
}

/*****************************************************************************!
 * Function : SlotCloseButtonPushed
 *****************************************************************************/
void
DependencyTreeWindow::SlotCloseButtonPushed(void)
{
  emit SignalWindowClose();
}

/*****************************************************************************!
 * Function : SlotTreeButtonPushed
 *****************************************************************************/
void
DependencyTreeWindow::SlotTreeButtonPushed(void)
{
  emit SignalTreeWindowOpen();
}

/*****************************************************************************!
 * Function : SlotpathLineSelectPushed
 *****************************************************************************/
void
DependencyTreeWindow::SlotpathLineSelectPushed(void)
{
  QString                               sourceDirectoryName;

  sourceDirectoryName = pathLineInput->text();

  SlotSourceDirectorySelected(sourceDirectoryName);
}

/*****************************************************************************!
 * Function : SlotBrowsePathButtonPushed
 *****************************************************************************/
void
DependencyTreeWindow::SlotBrowsePathButtonPushed(void)
{
  QString                               sourceDirectoryName;
  sourceDirectoryName = QFileDialog::getExistingDirectory(NULL, QString("Open Source Directory"),
                                                          mainSystemConfig->GetSourceTrackPath());

  pathLineInput->setText(sourceDirectoryName);
}

/*****************************************************************************!
 * Function : ProcessTopLevelDirectory
 *****************************************************************************/
void
DependencyTreeWindow::ProcessTopLevelDirectory
(QFileInfo InInfo, QTreeWidget* InTreeWindow)
{
  QFont                                 font;
  DependencyTreeWidgetItem*             treeItem;
  QString                               makeFileName;
  QString                               fullPath;
  QString                               name = InInfo.fileName();
  QBrush                                fg(Qt::gray);

  fullPath = InInfo.absoluteFilePath();
  makeFileName = fullPath + QString("/Makefile");

  QFileInfo                             info(makeFileName);

  if ( info.exists() ) {
    fg.setColor(Qt::black);
  }
  treeItem = new DependencyTreeWidgetItem(QStringList(name), InInfo, buildSystem);
  treeItem->setData(0, Qt::ForegroundRole, fg);
  if ( info.exists() ) {
    font = treeItem->font(0);
    font.setBold(false);
    treeItem->setFont(0, font);
    treeItem->PerformMake();
  }

  InTreeWindow->addTopLevelItem(treeItem);
  ProcessTreeDirectory(InInfo, treeItem);
}

/*****************************************************************************!
 * Function : ProcessTreeDirectory
 *****************************************************************************/
void
DependencyTreeWindow::ProcessTreeDirectory
(QFileInfo InInfo, QTreeWidgetItem* InTreeItem)
{
  QString                               fullPath;
  fullPath = InInfo.absoluteFilePath();
  QDir dir(fullPath, QString(""), QDir::Name, QDir::Dirs | QDir::NoDotAndDotDot);

  QFileInfoList                         list = dir.entryInfoList();
  DependencyTreeWidgetItem*             treeItem;
  
  for (auto i = list.begin() ; i != list.end(); i++ ) {
    QFileInfo                           info = *i;
    QString                             fileName;
    QString                             fullPath = info.absoluteFilePath();
    QString                             makeFileName;
    
    makeFileName = fullPath + QString("/Makefile");
    QFileInfo                             makeFileInfo(makeFileName);

    QBrush                                fg(Qt::gray);
    if ( makeFileInfo.exists() ) {
      fg.setColor(Qt::black);
    }
    
    fileName = info.fileName();
    treeItem = new DependencyTreeWidgetItem(QStringList(fileName), info, buildSystem);
    treeItem->setData(0, Qt::ForegroundRole, fg);
    InTreeItem->addChild(treeItem);
    if ( makeFileInfo.exists() ) {
      ProcessTreeDirectory(info, treeItem);
      treeItem->PerformMake();
    }
  }
}

/*****************************************************************************!
 * Function : SlotTreeWidgetItemSelected
 *****************************************************************************/
void
DependencyTreeWindow::SlotTreeWidgetItemSelected
(QTreeWidgetItem* InItem, int)
{
  DependencyTreeWidgetItem*             treeItem;
  BuildLineSet*                         buildLines;
  
  treeItem = (DependencyTreeWidgetItem*)InItem;
  buildLines = treeItem->GetBuildLines();
  buildLineDisplayWindow->SlotBuildLinesSelected(buildLines);
  emit SignalBuildLinesSelected(buildLines);
}

/*****************************************************************************!
 * Function : SlotSourceDirectorySelected
 *****************************************************************************/
void
DependencyTreeWindow::SlotSourceDirectorySelected
(QString InSourceDirectoryName)
{
  QDir                                  dir(InSourceDirectoryName,
                                            QString(""), QDir::Name,
                                            QDir::Dirs | QDir::NoDotAndDotDot);

  QFileInfoList                         list = dir.entryInfoList();

  directoryTreeWindow->clear();
  for (auto i = list.begin() ; i != list.end(); i++ ) {
    QFileInfo                           info = *i;
    ProcessTopLevelDirectory(info, directoryTreeWindow);
  }
  emit SignalBuildSystemSelected(buildSystem);  
}


/*****************************************************************************!
 * Function : SetCodeBaseDirectoryName
 *****************************************************************************/
void
DependencyTreeWindow::SetCodeBaseDirectoryName
(QString InCodeBaseDirectoryName)
{
  SlotSourceDirectorySelected(InCodeBaseDirectoryName);
}
