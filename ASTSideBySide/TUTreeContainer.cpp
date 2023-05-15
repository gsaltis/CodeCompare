/*****************************************************************************
 * FILE NAME    : TUTreeContainer.cpp
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

#define TRACE_USE
/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TUTreeContainer.h"
#include "trace.h"

/*****************************************************************************!
 * Function : TUTreeContainer
 *****************************************************************************/
TUTreeContainer::TUTreeContainer
(TUTree* InTree, QString InErrorFilename) : QWidget()
{
  QPalette pal;
  tree = InTree;
  pal = palette();
  errorFilename = InErrorFilename;
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
  SetErrorText();
}

/*****************************************************************************!
 * Function : ~TUTreeContainer
 *****************************************************************************/
TUTreeContainer::~TUTreeContainer
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TUTreeContainer::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TUTreeContainer::CreateSubWindows()
{
  QPalette                              pal;

  errorWindow = new QTextEdit();

  pal = errorWindow->palette();
  pal.setBrush(QPalette::Base, QBrush(QColor(0, 0, 200)));
  errorWindow->setPalette(pal);
  
  errorWindow->setTextBackgroundColor(QColor(0, 0, 200));
  errorWindow->setTextColor(QColor(244, 244, 244));
  errorWindow->setAutoFillBackground(true);
  errorWindow->setMaximumHeight(300);
  errorWindow->resize(0, 300);
  
  splitter = new TUTreeContainerSplitter();
  splitter->setParent(this);
  splitter->addWidget(tree);
  splitter->setOrientation(Qt::Vertical);
  splitter->addWidget(errorWindow);
  connect(splitter,
          QSplitter::splitterMoved,
          this,
          TUTreeContainer::SlotSplitterMoved);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TUTreeContainer::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TUTreeContainer::resizeEvent
(QResizeEvent* InEvent)
{
  splitter->resize(InEvent->size());
}

/*****************************************************************************!
 * Function : SlotSplitterMoved
 *****************************************************************************/
void
TUTreeContainer::SlotSplitterMoved
(int InPosition, int)
{
  emit SignalSplitterMoved(InPosition);
}

/*****************************************************************************!
 * Function : SlotSetErrorWindowHeight
 *****************************************************************************/
void
TUTreeContainer::SlotSetErrorWindowHeight
(int )
{
}

/*****************************************************************************!
 * Function : SetErrorText
 *****************************************************************************/
void
TUTreeContainer::SetErrorText
()
{
  QFile                                 file(errorFilename);
  QString                               st;

  errorWindow->setText("");
  file.open(QIODeviceBase::ReadOnly);
  
  st = QString(file.readAll());

  file.close();
  errorWindow->setText(st);
}

/*****************************************************************************!
 * Function : SetErrorFilename
 *****************************************************************************/
void
TUTreeContainer::SetErrorFilename
(QString InErrorFilename)
{
  errorFilename = InErrorFilename;
  SetErrorText();
}
