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
(FileTreeFile* InFileItem, QWidget* InParent, int InY, int InWidth, FileSectionDiff* InDiff) :
  QWidget(InParent), fileItem(InFileItem)
{
  int                                   n;
  int                                   height;
  QPalette pal;
  move(0, InY);
  setParent(InParent);

  baseColor = QColor(51, 102, 153);
  selectedColor = baseColor.darker(150);
  
  setMouseTracking(true);
  diff = InDiff;
  n = diff->GetTargetLinesChangedCount() + diff->GetLinesChangedCount();
  height = SOURCE_DIFFERENCES_ITEM_HEIGHT * n;
  height = height == 0 ? SOURCE_DIFFERENCES_ITEM_HEIGHT : height;
  resize(InWidth, height);
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(baseColor));
  setPalette(pal);
  setAutoFillBackground(true);
  setCursor(Qt::PointingHandCursor);
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
  int                                   y;
  QStringList                           sourceLines;
  QStringList                           targetLines;
  QString                               line2String;
  QString                               line1String;
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
  sourceLines = fileItem->GetFileLines1Section(startLine-1, endLine-1);
  line1String = QString("%1").arg(startLine);
  
  if ( startLine != endLine ) {
    line1String += QString(" - %1").arg(endLine);
  }
    
  startLine = diff->GetTargetStartLine();
  endLine = diff->GetTargetEndLine();
  targetLines = fileItem->GetFileLines2Section(startLine-1, endLine-1);
  line2String = QString("%1").arg(startLine);
  if ( startLine != endLine ) {
    line2String += QString(" - %1").arg(endLine);
  }
    
  //! Create label
  LineNumbers1Label = new QLabel();
  LineNumbers1Label->setParent(this);
  LineNumbers1Label->move(10, 10);
  LineNumbers1Label->resize(100, 20);
  LineNumbers1Label->setText(line1String);
  LineNumbers1Label->setAlignment(Qt::AlignRight);
  LineNumbers1Label->setFont(QFont("Segoe UI", 10, QFont::Bold));

  //! Create label
  LineNumbers2Label = new QLabel();
  LineNumbers2Label->setParent(this);
  LineNumbers2Label->move(10, 10);
  LineNumbers2Label->resize(100, 20);
  LineNumbers2Label->setText(line2String);
  LineNumbers2Label->setAlignment(Qt::AlignRight);
  LineNumbers2Label->setFont(QFont("Segoe UI", 10, QFont::Bold));

  //! Create label
  y = 0;
  CreateSourceLines(sourceLines, y, QColor(238, 153, 153));
  CreateSourceLines(targetLines, y, QColor(153, 238, 153));
}

/*****************************************************************************!
 * Function : CreateSourceLines
 *****************************************************************************/
void
SourceDifferencesItem::CreateSourceLines
(QStringList InLines, int &InY, QColor InColor)
{
  int                                   n;
  QPalette                              pal;
  QLabel*                               label;

  n = InLines.count();
  for ( int i = 0 ; i < n; i++ ) {
    label = new QLabel(this);
    label->move(10, InY);
    label->resize(100, SOURCE_DIFFERENCES_ITEM_HEIGHT);
    label->setText(InLines[i]);
    label->setAlignment(Qt::AlignLeft);
    label->setFont(QFont("Segoe UI", 10, QFont::Normal));
    DifferenceLineLabels << label;
    pal = label->palette();
    pal.setBrush(QPalette::WindowText, QBrush(InColor));
    label->setPalette(pal);
    label->setAutoFillBackground(true);
    InY += 20;
  }
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
  int                                   lineNumber1LabelX, lineNumber1LabelY;
  int                                   lineNumber1LabelW, lineNumber1LabelH;
  int                                   lineNumber2LabelX, lineNumber2LabelY;
  int                                   lineNumber2LabelW, lineNumber2LabelH;
  int                                   diffLabelX, diffLabelY;
  int                                   diffLabelW, diffLabelH;
  int                                   skipX = 5;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();
  typeLabelW = 100;
  lineNumber1LabelW = 140;
  lineNumber2LabelW = 140;
  diffLabelW = width - (typeLabelW + lineNumber1LabelW + lineNumber2LabelW + skipX * 3);

  typeLabelY = lineNumber1LabelY = lineNumber2LabelY = diffLabelY = 0;
  typeLabelH = lineNumber1LabelH = lineNumber2LabelH = diffLabelH = height;
  
  typeLabelX = 0;
  lineNumber1LabelX = typeLabelW + skipX;
  lineNumber2LabelX = typeLabelW + lineNumber1LabelX + skipX * 2;
  diffLabelX = typeLabelW + lineNumber1LabelW + lineNumber2LabelW + skipX * 3;

  TypeNameLabel->move(typeLabelX, typeLabelY);
  TypeNameLabel->resize(typeLabelW, typeLabelH);

  LineNumbers1Label->move(lineNumber1LabelX, lineNumber1LabelY);
  LineNumbers1Label->resize(lineNumber1LabelW, lineNumber1LabelH);

  LineNumbers2Label->move(lineNumber2LabelX, lineNumber2LabelY);
  LineNumbers2Label->resize(lineNumber2LabelW, lineNumber2LabelH);

  for ( int i = 0 ; i < DifferenceLineLabels.count(); i++ ) {
    DifferenceLineLabels[i]->move(diffLabelX, diffLabelY);
    DifferenceLineLabels[i]->resize(diffLabelW, SOURCE_DIFFERENCES_ITEM_HEIGHT);
    diffLabelY += SOURCE_DIFFERENCES_ITEM_HEIGHT;
  }
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
SourceDifferencesItem::mousePressEvent
(QMouseEvent* InEvent)
{
  Qt::KeyboardModifiers                 mods = InEvent->modifiers();
  Qt::MouseButton                       button = InEvent->button();

  if ( mods != Qt::NoModifier ) {
    return;
  }

  if ( button != Qt::LeftButton ) {
    return;
  }
  emit SignalDifferenceSelected(diff);
}

/*****************************************************************************!
 * Function : mouseMoveEvent
 *****************************************************************************/
void
SourceDifferencesItem::mouseMoveEvent
(QMouseEvent* InEvent)
{
  Qt::KeyboardModifiers                 mods = InEvent->modifiers();
  Qt::MouseButton                       button = InEvent->button();

  if ( mods != Qt::NoModifier ) {
    return;
  }

  if ( button != Qt::LeftButton ) {
    return;
  }
  emit SignalDifferenceSelected(diff);
}

/*****************************************************************************!
 * 
 *****************************************************************************/
void
SourceDifferencesItem::enterEvent
(QEnterEvent* )
{
  QPalette pal = palette();
  pal.setBrush(QPalette::Window, QBrush(selectedColor));
  setPalette(pal);
}

/*****************************************************************************!
 * 
 *****************************************************************************/
void
SourceDifferencesItem::leaveEvent
(QEvent* )
{
  QPalette pal = palette();
  pal.setBrush(QPalette::Window, QBrush(baseColor));
  setPalette(pal);
}

