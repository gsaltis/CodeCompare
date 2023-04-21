/*****************************************************************************
 * FILE NAME    : FileTreeWidgetItem.cpp
 * DATE         : April 20 2023
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
#include "FileTreeWidgetItem.h"

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName, int InColumn) : QTreeWidgetItem()
{
  if ( InColumn == 0 ) {
    SetAbsoluteFileName1(InAbsoluteFileName);
    return;
  }
  SetAbsoluteFileName2(InAbsoluteFileName);
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName, QTreeWidget* InTree) : QTreeWidgetItem()
{
  SetAbsoluteFileName1(InAbsoluteFileName);
  InTree->addTopLevelItem(this);
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName, QTreeWidgetItem* InParent, int InColumn) : QTreeWidgetItem()
{
  if ( InColumn == 0 ) {
    SetAbsoluteFileName1(InAbsoluteFileName);
    InParent->addChild(this);
    return;
  }
  SetAbsoluteFileName2(InAbsoluteFileName);
  InParent->addChild(this);
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName1, QString InAbsoluteFileName2) : QTreeWidgetItem()
{
  SetAbsoluteFileNames(InAbsoluteFileName1, InAbsoluteFileName2);
}

/*****************************************************************************!
 * Function : FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::FileTreeWidgetItem
(QString InAbsoluteFileName1, QString InAbsoluteFileName2, QTreeWidgetItem* InParent) : QTreeWidgetItem()
{
  SetAbsoluteFileNames(InAbsoluteFileName1, InAbsoluteFileName2);
  InParent->addChild(this);
}

/*****************************************************************************!
 * Function : ~FileTreeWidgetItem
 *****************************************************************************/
FileTreeWidgetItem::~FileTreeWidgetItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
FileTreeWidgetItem::initialize()
{
}

/*****************************************************************************!
 * Function : GetAbsoluteFileName1
 *****************************************************************************/
QString
FileTreeWidgetItem::GetAbsoluteFileName1(void)
{
  return absoluteFileName1;  
}

/*****************************************************************************!
 * Function : SetAbsoluteFileName1
 *****************************************************************************/
void
FileTreeWidgetItem::SetAbsoluteFileName1
(QString InAbsoluteFileName1)
{
  absoluteFileName2 = InAbsoluteFileName1;

  setText(0, QString(""));
  QFileInfo                             fileInfo1(absoluteFileName1);
  setText(1, fileInfo1.fileName());
  absoluteFileName1 = InAbsoluteFileName1;
}

/*****************************************************************************!
 * Function : GetAbsoluteFileName2
 *****************************************************************************/
QString
FileTreeWidgetItem::GetAbsoluteFileName2(void)
{
  return absoluteFileName2;  
}

/*****************************************************************************!
 * Function : SetAbsoluteFileName2
 *****************************************************************************/
void
FileTreeWidgetItem::SetAbsoluteFileName2
(QString InAbsoluteFileName2)
{
  absoluteFileName2 = InAbsoluteFileName2;

  QFileInfo                             fileInfo2(absoluteFileName2);
  setText(0, fileInfo2.fileName());
}

/*****************************************************************************!
 * Function : SetAbsoluteFileNames
 *****************************************************************************/
void
FileTreeWidgetItem::SetAbsoluteFileNames
(QString InAbsoluteFileName1, QString InAbsoluteFileName2)
{
  absoluteFileName1 = InAbsoluteFileName1;
  absoluteFileName2 = InAbsoluteFileName2;

  QFileInfo                             fileInfo1(absoluteFileName1);
  setText(0, fileInfo1.fileName());

  QFileInfo                             fileInfo2(absoluteFileName2);
  setText(1, fileInfo2.fileName());
}
