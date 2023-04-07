/*****************************************************************************
 * FILE NAME    : BuildLineBaseDisplayForm.cpp
 * DATE         : April 06 2023
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
#include "BuildLineBaseDisplayForm.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildLineBaseDisplayForm
 *****************************************************************************/
BuildLineBaseDisplayForm::BuildLineBaseDisplayForm
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShadow(QFrame::Sunken);
  setFrameShape(QFrame::Box);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildLineBaseDisplayForm
 *****************************************************************************/
BuildLineBaseDisplayForm::~BuildLineBaseDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineBaseDisplayForm::initialize()
{
  labelWidth = 150;
  labelHeight = 20;
  labelX = 10;
  elementX = labelWidth + labelX + 10;
  elementW = 120;
  ySkip = 22;
  
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildLineBaseDisplayForm::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineBaseDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineBaseDisplayForm::resizeEvent
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
 * Function : CreateEditSection
 *****************************************************************************/
void
BuildLineBaseDisplayForm::CreateEditSection
(QLabel* &InNameLabel, QString InName, QString InText, QTextEdit* &InTextEdit, int &InY)
{
  int                                   h, w;
  
  InNameLabel      = new QLabel(InName + QString(" :"), this);
  InNameLabel->move(labelX, InY);
  InNameLabel->resize(labelWidth, labelHeight);
  InNameLabel->setFont(QFont("", 10, QFont::Bold));
  InNameLabel->setAlignment(Qt::AlignRight);

  w = size().width();
  w -= elementX;
  w -= 10;

  h = size().height();
  h -= InY;
  h -= 10;
  
  InTextEdit = new QTextEdit(this);
  InTextEdit->setText(InText);
  InTextEdit->move(elementX, InY);
  InTextEdit->resize(w, h);
  InY += h;
}

/*****************************************************************************!
 * Function : CreateGroupSection
 *****************************************************************************/
void
BuildLineBaseDisplayForm::CreateGroupSection
(QLabel* &InNameLabel, QString InName,
 QStringList sl, QFrame* &InNameAreas, QScrollArea* &InScrollArea,
 int &InY)
{
  int                                   n, h, h2, y2;
  
  InNameLabel      = new QLabel(InName + QString(" :"), this);
  InNameLabel->move(labelX, InY);
  InNameLabel->resize(labelWidth, labelHeight);
  InNameLabel->setFont(QFont("", 10, QFont::Bold));
  InNameLabel->setAlignment(Qt::AlignRight);

  n = sl.count();
  h = n * 20;
  h2 = h;
  if ( n == 0 ) {
    h = 20;
    h2 = 20;
  } else if ( n > 6 ) {
    h = 120;
  }
  
  InScrollArea = new QScrollArea(this);
  InScrollArea->move(elementX, InY);
  InScrollArea->resize(elementW, h+3);
  InScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  InNameAreas = new QFrame();
  InScrollArea->setWidget(InNameAreas);
  InNameAreas->resize(elementW, h2);

  y2 = 0;
  for ( int i = 0; i < n ; i++ ) {
    QLabel* l = new QLabel(sl[i], InNameAreas);
    l->move(5, y2);
    y2 += 20;
  }
  InY += h + 5;
}

/*****************************************************************************!
 * Function : CreateLabel
 *****************************************************************************/
void
BuildLineBaseDisplayForm::CreateLabel
(QLabel* &InLabel, QLabel* &InTextLabel, QString InName, QString InNameText, int &InY)
{
  InLabel = new QLabel(InName + QString(" :"), this);
  InLabel->move(labelX, InY);
  InLabel->resize(labelWidth, labelHeight);
  InLabel->setFont(QFont("", 10, QFont::Bold));
  InLabel->setAlignment(Qt::AlignRight);

  InTextLabel = new QLabel(InNameText, this);
  InTextLabel->move(elementX, InY);
  InTextLabel->setAlignment(Qt::AlignLeft);

  InY += ySkip;
}

