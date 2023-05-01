/*****************************************************************************
 * FILE NAME    : MonitoredLabel.cpp
 * DATE         : May 01 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
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
#include "MonitoredLabel.h"
#include "trace.h"

/*****************************************************************************!
 * Function : MonitoredLabel
 *****************************************************************************/
MonitoredLabel::MonitoredLabel
() : QLabel()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~MonitoredLabel
 *****************************************************************************/
MonitoredLabel::~MonitoredLabel
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
MonitoredLabel::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
MonitoredLabel::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
MonitoredLabel::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : setText
 *****************************************************************************/
void
MonitoredLabel::setText
(QString InText)
{
  QLabel::setText(InText);
  emit SignalTextChanged(InText);
}
