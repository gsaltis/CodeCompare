/*****************************************************************************
 * FILE NAME    : CodeCompareToolBarButton.cpp
 * DATE         : May 02 2023
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
#include "CodeCompareToolBarButton.h"
#include "trace.h"

/*****************************************************************************!
 * Function : CodeCompareToolBarButton
 *****************************************************************************/
CodeCompareToolBarButton::CodeCompareToolBarButton
(QWidget *InParent, int InX, QIcon InIcon) : QPushButton()
{
  setParent(InParent);
  move(InX, 2);
  setIcon(InIcon);
  setAutoFillBackground(true);
  setMouseTracking(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~CodeCompareToolBarButton
 *****************************************************************************/
CodeCompareToolBarButton::~CodeCompareToolBarButton
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
CodeCompareToolBarButton::initialize()
{
  mouseIn = false;
  resize(28, 28);
  setIconSize(QSize(24, 24));
  setCursor(Qt::PointingHandCursor);
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
CodeCompareToolBarButton::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
CodeCompareToolBarButton::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
CodeCompareToolBarButton::resizeEvent
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
 * Function : enterEvent
 *****************************************************************************/
void
CodeCompareToolBarButton::enterEvent
(QEnterEvent* )
{
  mouseIn = true;
  repaint();
}

/*****************************************************************************!
 * Function : leaveEvent
 *****************************************************************************/
void
CodeCompareToolBarButton::leaveEvent
(QEvent* )
{
  mouseIn = false;
  repaint();
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
CodeCompareToolBarButton::paintEvent
(QPaintEvent *event)
{
  QPushButton::paintEvent(event);

  QPainter painter(this);
  painter.setPen(QPen(QBrush(QColor(255, 255, 255)), 2));
  if ( mouseIn ) {
    painter.setPen(QPen(QBrush(QColor(128, 128, 128)), 2));
  }
  painter.drawRoundedRect(rect(), 4, 4);
}

/*****************************************************************************!
 * Function : mouseMoveEvent
 *****************************************************************************/
void
CodeCompareToolBarButton::mouseMoveEvent
(QMouseEvent *)
{
  if ( !mouseIn ) {
    mouseIn = true;
    repaint();
  }
}
  
