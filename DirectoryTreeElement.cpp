/*****************************************************************************
 * FILE NAME    : DirectoryTreeElement.cpp
 * DATE         : March 30 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirectoryTreeElement.h"

/*****************************************************************************!
 * Function : DirectoryTreeElement
 *****************************************************************************/
DirectoryTreeElement::DirectoryTreeElement
(QFileInfo InInfo, int InIndent, int InY) : QFrame()
{
  fileInfo = InInfo;
  indent = InIndent;
  localY = InY;
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(0, 0, 0, 0)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
  move(0, localY);
}

/*****************************************************************************!
 * Function : ~DirectoryTreeElement
 *****************************************************************************/
DirectoryTreeElement::~DirectoryTreeElement
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
DirectoryTreeElement::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
DirectoryTreeElement::CreateSubWindows()
{
  QLabel*                               label;

  //! Create label   
  label = new QLabel();
  label->setParent(this);
  label->move(indent, 0);
  label->resize(100, 20);
  label->setText(fileInfo.fileName());
  label->setAlignment(Qt::AlignLeft);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
DirectoryTreeElement::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
DirectoryTreeElement::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;

  
}
