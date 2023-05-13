/*****************************************************************************
 * FILE NAME    : TUTreeContainerSplitter.cpp
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
#include "TUTreeContainerSplitter.h"
#include "trace.h"

/*****************************************************************************!
 * Function : TUTreeContainerSplitter
 *****************************************************************************/
TUTreeContainerSplitter::TUTreeContainerSplitter
() : QSplitter()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TUTreeContainerSplitter
 *****************************************************************************/
TUTreeContainerSplitter::~TUTreeContainerSplitter
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TUTreeContainerSplitter::initialize()
{
}

/*****************************************************************************!
 * Function : ResizeErrorWindow
 *****************************************************************************/
void
TUTreeContainerSplitter::ResizeErrorWindow
(int InHeight)
{
  moveSplitter(1, InHeight);
}
