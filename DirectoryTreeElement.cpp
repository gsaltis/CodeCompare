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
(QFileInfo InInfo) : QFrame()
{
  fileInfo = InInfo;
  initialize();
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
}

/*****************************************************************************!
 * Function : AddChild
 *****************************************************************************/
void
DirectoryTreeElement::AddChild
(class DirectoryTreeElement*  InChild)
{
  if ( NULL == InChild ) {
    return;
  }
  
  childElements << InChild;
}

