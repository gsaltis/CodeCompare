/*****************************************************************************
 * FILE NAME    : LineNumberArea.cpp
 * DATE         : April 21 2023
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
#include "LineNumberArea.h"
#include "CodeEditor.h"
#include "trace.h"

/*****************************************************************************!
 * Function : LineNumberArea
 *****************************************************************************/
LineNumberArea::LineNumberArea(CodeEditor *editor) : QWidget(editor)
{
  codeEditor = editor;
}

/*****************************************************************************!
 * Function : ~LineNumberArea
 *****************************************************************************/
LineNumberArea::~LineNumberArea
()
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(224, 224, 224)));
  setPalette(pal);
  setAutoFillBackground(true);
}

/*****************************************************************************!
 * Function : sizeHint
 *****************************************************************************/
QSize
LineNumberArea::sizeHint
()
{
  QSize                         s;
  s = QSize(codeEditor->lineNumberAreaWidth(), 0);
  return s;
}
  
/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void LineNumberArea::paintEvent(QPaintEvent *event)
{
  codeEditor->lineNumberAreaPaintEvent(event);
}
