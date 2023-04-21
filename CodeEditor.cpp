/*****************************************************************************
 * FILE NAME    : CodeEditor.cpp
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
#include "CodeEditor.h"
#include "trace.h"

/*****************************************************************************!
 * Function : CodeEditor
 *****************************************************************************/
CodeEditor::CodeEditor
() : QTextEdit()
{
  initialize();
}

/*****************************************************************************!
 * Function : CodeEditor
 *****************************************************************************/
CodeEditor::CodeEditor
(QWidget* InParent) : QTextEdit(InParent)
{
  initialize();
}

/*****************************************************************************!
 * Function : ~CodeEditor
 *****************************************************************************/
CodeEditor::~CodeEditor
()
{
}

/*****************************************************************************!
 * Function : SetFileDisplayTabWidth
 *****************************************************************************/
void
CodeEditor::SetFileDisplayTabWidth
(int InTabWidth)
{
  QFont                                 f;
  f = font();
  QFontMetrics                          fm(f);
  int width = fm.averageCharWidth();
  setTabStopDistance(InTabWidth * width);
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
CodeEditor::initialize(void)
{
  setFont(QFont("Courier", 9));
  SetFileDisplayTabWidth(4);
  codeHighlighter = new CodeHighlighter(document());
}
