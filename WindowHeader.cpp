/*****************************************************************************
 * FILE NAME    : WindowHeader.cpp
 * DATE         : March 22 2023
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
#include "WindowHeader.h"

/*****************************************************************************!
 * Function : WindowHeader
 *****************************************************************************/
WindowHeader::WindowHeader
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~WindowHeader
 *****************************************************************************/
WindowHeader::~WindowHeader
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
WindowHeader::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
WindowHeader::CreateSubWindows()
{

  //! Create label  
  headerText = new QLabel();
  headerText->setParent(this);
  headerText->move(0, 0);
  headerText->resize(100, 20);
  headerText->setText("Nothing");
  headerText->setAlignment(Qt::AlignLeft);
  headerText->setFont(QFont("Segoe UI", 15, QFont::Bold));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
WindowHeader::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
WindowHeader::resizeEvent
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
  QLinearGradient                               grad(0, 0, 0, height);
  grad.setColorAt(0, QColor(128, 128, 128));
  grad.setColorAt(1, QColor(240, 240, 240));
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(grad));
  setPalette(pal);

  headerText->resize(width, height);
}

/*****************************************************************************!
 * Function : SetText
 *****************************************************************************/
void
WindowHeader::SetText
(QString InText)
{
  headerText->setText(InText);
}
