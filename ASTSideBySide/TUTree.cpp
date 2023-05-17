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
#include <QHeaderView>
#include <QTreeWidgetItem>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TUTree.h"

/*****************************************************************************!
 * Function : TUTree
 *****************************************************************************/
TUTree::TUTree
(QString InFilename) : QTreeWidget()
{
  QPalette pal;
  filename = InFilename;
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
  QTreeWidgetItem*                              headerItem;
  QHeaderView*                                  headerView;

  InitializeSubWindows();  
  CreateSubWindows();
  setColumnCount(3);
  headerView = header();
  headerView->resizeSection(0, 300);
  headerView->resizeSection(1, 300);

  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Name");
  headerItem->setText(1, "Value");
  headerItem->setText(2, "Compare");
  setHeaderItem(headerItem);
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

/*****************************************************************************!
 * Function : GetFilename
 *****************************************************************************/
QString
TUTree::GetFilename(void)
{
  
  return filename;
}

/*****************************************************************************!
 * Function : SetFilename
 *****************************************************************************/
void
TUTree::SetFilename
(QString InFilename)
{  
  filename = InFilename;
}

/*****************************************************************************!
 * Function : GetFileSection
 *****************************************************************************/
QString
TUTree::GetFileSection
(int InBegin, int InEnd)
{
  int                                   length;
  QFile                                 file(filename);
  if ( ! file.open(QIODeviceBase::ReadOnly) ) {
    return QString();
  }

  QString s = QString(file.readAll());
  file.close();

  length = InEnd - InBegin;
  if ( length < 1 ) {
    return QString();
  }

  if ( InBegin + length >= s.length() ) {
    return QString();
  }

  if ( s[InBegin + length] == QChar(';') ) {
    length++;
  }
  return s.sliced(InBegin, length);
}
