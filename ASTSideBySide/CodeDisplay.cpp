/*****************************************************************************
 * FILE NAME    : CodeDisplay.cpp
 * DATE         : May 16 2023
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
#include "CodeDisplay.h"
#include "trace.h"

/*****************************************************************************!
 * Function : CodeDisplay
 *****************************************************************************/
CodeDisplay::CodeDisplay
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(0, 0, 32)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~CodeDisplay
 *****************************************************************************/
CodeDisplay::~CodeDisplay
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
CodeDisplay::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
CodeDisplay::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
CodeDisplay::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
CodeDisplay::resizeEvent
(QResizeEvent* InEvent)
{
  CodeDisplayLine*                      line;
  QSize                                 size;  
  int                                   width;
  int                                   i, n;
  
  size = InEvent->size();
  width = size.width();

  n = lines.count();
  for ( i = 0 ; i < n ; i++ ) {
    line = lines[i];
    line->resize(width, line->size().height());
  }
}

/*****************************************************************************!
 * Function : ClearLines
 *****************************************************************************/
void
CodeDisplay::ClearLines(void)
{
  foreach ( auto line, lines) {
    line->setParent(NULL);
    delete line;
  }
  lines = QList<CodeDisplayLine*>();
}

/*****************************************************************************!
 * Function : SetSectionText
 *****************************************************************************/
void
CodeDisplay::SetSectionText
(QString InText, int InStartingLine)
{
  int                                   y;
  CodeDisplayLine*                      line;
  int                                   currentLineNumber;
  int                                   i;
  int                                   n;
  QStringList                           textLines;
  QString                               st;
  int                                   width;

  
  ClearLines();

  width = size().width();
  textLines = InText.split("\n");
  n = textLines.count();

  currentLineNumber = InStartingLine;

  y = 0;
  for ( i = 0; i < n ; i++ ) {
    st = textLines[i];
    line = new CodeDisplayLine(currentLineNumber, textLines[i]);
    line->setParent(this);
    line->move(0, y);
    line->show();
    line->resize(width, CODE_DISPLAY_LINE_HEIGHT);
    lines << line;
    y += CODE_DISPLAY_LINE_HEIGHT;
    currentLineNumber++;
  }
}
