/*****************************************************************************
 * FILE NAME    : SourceDifferencesItem.cpp
 * DATE         : April 25 2023
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
#include "SourceDifferencesItem.h"
#include "trace.h"

/*****************************************************************************!
 * Function : SourceDifferencesItem
 *****************************************************************************/
SourceDifferencesItem::SourceDifferencesItem
(QWidget* InParent, int InY, int InWidth, FileSectionDiff* InDiff) : QWidget(InParent), diff(InDiff)
{
  QPalette pal;
  move(0, InY);
  setParent(InParent);
  resize(InWidth, SOURCE_DIFFERENCES_ITEM_HEIGHT);
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 0)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
  show();
}

/*****************************************************************************!
 * Function : ~SourceDifferencesItem
 *****************************************************************************/
SourceDifferencesItem::~SourceDifferencesItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SourceDifferencesItem::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SourceDifferencesItem::CreateSubWindows()
{
  QString                               lineString;
  int                                   endLine;
  int                                   startLine;
  //! Create label
  TypeNameLabel = new QLabel();
  TypeNameLabel->setParent(this);
  TypeNameLabel->move(10, 10);
  TypeNameLabel->resize(100, 20);
  TypeNameLabel->setText(diff->GetTypeString());
  TypeNameLabel->setAlignment(Qt::AlignRight);
  TypeNameLabel->setFont(QFont("Segoe UI", 10, QFont::Bold));

  startLine = diff->GetStartLine();
  endLine = diff->GetEndLine();
  lineString = QString("%1").arg(startLine);
  if ( startLine != endLine ) {
    lineString += QString(" - %1").arg(endLine);
  }
    
  //! Create label
  LineNumbersLabel = new QLabel();
  LineNumbersLabel->setParent(this);
  LineNumbersLabel->move(10, 10);
  LineNumbersLabel->resize(100, 20);
  LineNumbersLabel->setText(lineString);
  LineNumbersLabel->setAlignment(Qt::AlignRight);
  LineNumbersLabel->setFont(QFont("Segoe UI", 10, QFont::Bold));

  //! Create label
  DifferenceLineLabel = new QLabel();
  DifferenceLineLabel->setParent(this);
  DifferenceLineLabel->move(10, 10);
  DifferenceLineLabel->resize(100, 20);
  DifferenceLineLabel->setText("Difference");
  DifferenceLineLabel->setAlignment(Qt::AlignLeft);
  DifferenceLineLabel->setFont(QFont("Segoe UI", 10, QFont::Bold));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SourceDifferencesItem::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SourceDifferencesItem::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   typeLabelX, typeLabelY;
  int                                   typeLabelW, typeLabelH;
  int                                   lineNumberLabelX, lineNumberLabelY;
  int                                   lineNumberLabelW, lineNumberLabelH;
  int                                   diffLabelX, diffLabelY;
  int                                   diffLabelW, diffLabelH;
  int                                   skipX = 5;
  

  size = InEvent->size();
  width = size.width();
  height = size.height();
  typeLabelW = 100;
  lineNumberLabelW = 140;
  diffLabelW = width - (typeLabelW + lineNumberLabelW + skipX * 2);

  typeLabelY = lineNumberLabelY = diffLabelY = 0;
  typeLabelH = lineNumberLabelH = diffLabelH = height;
  typeLabelX = 0;
  lineNumberLabelX = typeLabelW + skipX;
  diffLabelX = typeLabelW + lineNumberLabelW + skipX * 2;

  TypeNameLabel->move(typeLabelX, typeLabelY);
  TypeNameLabel->resize(typeLabelW, typeLabelH);

  LineNumbersLabel->move(lineNumberLabelX, lineNumberLabelY);
  LineNumbersLabel->resize(lineNumberLabelW, lineNumberLabelH);

  DifferenceLineLabel->move(diffLabelX, diffLabelY);
  DifferenceLineLabel->resize(diffLabelW, diffLabelH);
}
