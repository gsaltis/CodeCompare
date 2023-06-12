/*****************************************************************************
 * FILE NAME    : BuildTreeContainer.cpp
 * DATE         : May 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTreeContainer.h"
#include "BuildTreeItemComponent.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildTreeContainer
 *****************************************************************************/
BuildTreeContainer::BuildTreeContainer
(BuildTree* InBuildTree) : QWidget()
{
  QPalette pal;
  buildTree = InBuildTree;
  buildTree->setParent(this);
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTreeContainer
 *****************************************************************************/
BuildTreeContainer::~BuildTreeContainer
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeContainer::initialize()
{
  csvFileName = QString("Build.csv");
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeContainer::CreateSubWindows()
{
  toolBar = new QFrame(this);
  toolBar->setFrameShadow(QFrame::Sunken);
  toolBar->setFrameStyle(QFrame::Panel);
  toolBar->setStyleSheet("QFrame { border : 1px solid #CCC}");

  statusBar = new QFrame(this);
  statusBar->setFrameShadow(QFrame::Sunken);
  statusBar->setFrameStyle(QFrame::Panel);
  statusBar->setStyleSheet("QFrame { border : 1px solid #CCC}");

  FilesCountLabel = new QLabel(statusBar);
  FilesCountLabel->move(5, 1);
  FilesCountLabel->resize(60, 18);
  FilesCountLabel->setText(QString("%1 / %2").arg(0).arg(0));
  FilesCountLabel->setStyleSheet("QLabel { border : 0px solid #00000000}");
    
  //! Create the CollapseButton button  
  CollapseButton = new QPushButton();
  CollapseButton->setParent(toolBar);
  CollapseButton->setText("Ex");
  CollapseButton->move(1, 1);
  CollapseButton->resize(30,30);
  connect(CollapseButton, SIGNAL(pressed()), this, SLOT(SlotCollapseButtonPushed()));

  ChangedItemsButton = new QPushButton();
  ChangedItemsButton->setParent(toolBar);
  ChangedItemsButton->setText("Ch");
  ChangedItemsButton->move(33, 1);
  ChangedItemsButton->resize(30,30);
  connect(ChangedItemsButton, SIGNAL(pressed()), this, SLOT(SlotChangedItemsButtonPushed()));

  GenerateCSVFileButton = new QPushButton();
  GenerateCSVFileButton->setParent(toolBar);
  GenerateCSVFileButton->setText("LI");
  GenerateCSVFileButton->move(65, 1);
  GenerateCSVFileButton->resize(30,30);
  connect(GenerateCSVFileButton, SIGNAL(pressed()), this, SLOT(SlotGenerateCSVFileButtonPushed()));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTreeContainer::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeContainer::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   buildTreeX, buildTreeY, buildTreeW, buildTreeH;
  int                                   toolBarW, toolBarH, toolBarX, toolBarY;
  int                                   statusBarW, statusBarH, statusBarX, statusBarY;
  int                                   FilesCountLabelW, FilesCountLabelH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  toolBarH = 32;
  statusBarH = 20;
  buildTreeH = height - (toolBarH + statusBarH);
  
  buildTreeX = 0;
  buildTreeY = 0;
  buildTreeW = width;

  toolBarX = 0;
  toolBarW = width;
  toolBarY = height - toolBarH;
  
  statusBarX = 0;
  statusBarW = width;
  statusBarY = height - (toolBarH + statusBarH);

  FilesCountLabelW = width - 10;
  FilesCountLabelH = 18;

  FilesCountLabel->resize(FilesCountLabelW, FilesCountLabelH);
  
  buildTree->move(buildTreeX, buildTreeY);
  buildTree->resize(buildTreeW, buildTreeH);

  toolBar->move(toolBarX, toolBarY);
  toolBar->resize(toolBarW, toolBarH);

  statusBar->move(statusBarX, statusBarY);
  statusBar->resize(statusBarW, statusBarH);
}

/*****************************************************************************!
 * Function : SlotCollapseButtonPushed
 *****************************************************************************/
void
BuildTreeContainer::SlotCollapseButtonPushed(void)
{
  emit SignalCollapseTree();
  if ( buildTree->GetExpanded() ) {
    CollapseButton->setText("CO");
    return;
  }
  CollapseButton->setText("EX");
}

/*****************************************************************************!
 * Function : SlotChangedItemsButtonPushed
 *****************************************************************************/
void
BuildTreeContainer::SlotChangedItemsButtonPushed(void)
{
  emit SignalChangedItemsDisplay();
  if ( buildTree->GetDisplayAllItems() ) {
    ChangedItemsButton->setText("CH");
    return;
  }
  ChangedItemsButton->setText("ALL");
}

/*****************************************************************************!
 * Function : SlotGenerateCSVFileButtonPushed
 *****************************************************************************/
void
BuildTreeContainer::SlotGenerateCSVFileButtonPushed
(void)
{
  QString                               fullPath;
  QString                               fn;
  QString                               fileName;
  int                                   i, n, j, k, m, p;
  QTreeWidgetItem*                      item;
  QTreeWidgetItem*                      item2;
  BuildTreeItemComponent*               item3;
  BuildTreeItemSection*                 sectionItem;
  QString                               s;
  int                                   changedCount = 1;
  QString                               changedFlag = "";
  QStringList                           processedFiles;
  
  fileName = QFileDialog::getSaveFileName(NULL, "Save CSV File", csvFileName, "CSV Files (*.csv)");
  if ( fileName == "" ) {
    return;
  }

  csvFileName = fileName;
  
  QFile                                 file(csvFileName);
  if ( !file.open(QIODeviceBase::ReadWrite) ) {
    QMessageBox::critical(NULL, "Could not open file", QString("Could not open the CSV file - ") + file.errorString());
    return;
  }

  n = buildTree->topLevelItemCount();

  for (i = 0; i < n; i++) {
    item = buildTree->topLevelItem(i);
    k = item->childCount();
    for (j = 0; j < k; j++) {
      item2 = item->child(j);
      s = QString(",%1,,\n").arg(item2->text(0));
      sectionItem = (BuildTreeItemSection*)item2;
      if ( ! sectionItem->AnyChanged() ) {
        continue;
      }
      file.write(s.toLatin1());
      p = item2->childCount();
      for (m = 0; m < p; m++) {
        item3 = (BuildTreeItemComponent*)item2->child(m);
        if ( item3->GetChanged() ) {
          fullPath = item3->GetFullFileName();
          QFileInfo fullPathInfo(fullPath);
          fn = buildTree->RemoveLeadingBasePath1(fullPath);
          changedFlag = "*";
          if ( !processedFiles.contains(fn) ) {
            changedFlag = "";
            processedFiles << fn;
          }
          s = QString("%1,,%2,%3,%4\n")
            .arg(changedCount)
            .arg(changedFlag)
            .arg(fn)
            .arg(fullPathInfo.size());
          changedCount++;
          file.write(s.toLatin1());
        }
      }
    }
  }

  file.close();
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BuildTreeContainer::CreateConnections(void)
{
  connect(this, BuildTreeContainer::SignalCollapseTree, buildTree, BuildTree::SlotToggleTreeView);
  connect(this, BuildTreeContainer::SignalChangedItemsDisplay, buildTree, BuildTree::SlotToggleChangedItems);
}

/*****************************************************************************!
 * Function : SlotSetFileCounts
 *****************************************************************************/
void
BuildTreeContainer::SlotSetFileCounts
(int InTotalFiles, int InChangedFiles)
{
  FilesCountLabel->setText(QString("Files : Total:%1 | Changed:%2").arg(InTotalFiles).arg(InChangedFiles));
}
