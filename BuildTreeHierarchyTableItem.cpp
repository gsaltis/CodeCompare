/*****************************************************************************
 * FILE NAME    : BuildTreeHierarchyTableItem.cpp
 * DATE         : April 15 2023
 * PROJECT      : 
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
#include "BuildTreeHierarchyTableItem.h"

/*****************************************************************************!
 * Function : BuildTreeHierarchyTableItem
 *****************************************************************************/
BuildTreeHierarchyTableItem::BuildTreeHierarchyTableItem
(QString InName, QWidget* InParent) : QFrame(InParent)
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  name = QString(InName);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildTreeHierarchyTableItem
 *****************************************************************************/
BuildTreeHierarchyTableItem::~BuildTreeHierarchyTableItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildTreeHierarchyTableItem::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeHierarchyTableItem::CreateSubWindows()
{
  //! Create label
  nameLabel = new QLabel();
  nameLabel->setParent(this);
  nameLabel->move(BUILD_TREE_HIERARCHY_TABLE_ITEM_X, 0);
  nameLabel->resize(0, BUILD_TREE_HIERARCHY_TABLE_ITEM_HEIGHT);
  nameLabel->setText(name);
  nameLabel->setAlignment(Qt::AlignLeft);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildTreeHierarchyTableItem::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeHierarchyTableItem::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   nameLabelW;
  int                                   nameLabelX;
  int                                   nameLabelH;
  QSize                                 size;  
  int                                   width;

  size = InEvent->size();
  width = size.width();

  nameLabelX = nameLabel->pos().x();
  nameLabelH = nameLabel->size().height();
  nameLabelW = width - (nameLabelX * 2);

  nameLabel->resize(nameLabelW, nameLabelH);
  (void)width;
}
