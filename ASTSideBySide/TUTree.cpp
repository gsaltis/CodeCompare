/*****************************************************************************
 * FILE NAME    : TUTree.cpp
 * DATE         : May 12 2023
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
#include "TUTree.h"

/*****************************************************************************!
 * Function : TUTree
 *****************************************************************************/
TUTree::TUTree
() : QTreeWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TUTree
 *****************************************************************************/
TUTree::~TUTree
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TUTree::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TUTree::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TUTree::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TUTree::resizeEvent
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

/*****************************************************************************!
 * Function : FindElementByNameType
 *****************************************************************************/
TUTreeElement*
TUTree::FindElementByNameType
(QString InName, TUTreeElement::TranslationUnitType InType)
{
  int                                   i;
  int                                   n;
  TUTreeElement*                        topLevel;
  TUTreeElement*                        ch;
  QTreeWidgetItem*                      ti;
  
  ti = topLevelItem(0);
  topLevel = (TUTreeElement*)ti;
  
  n = topLevel->childCount();

  for (i = 0; i < n; i++) {
    ch = (TUTreeElement*)topLevel->child(i);
    if ( ch->text(1) == InName && ch->GetTUType() == InType ) {
      return ch;
    }
  }
  return NULL;
}
