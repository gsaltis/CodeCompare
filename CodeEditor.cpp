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
() : QPlainTextEdit()
{
  lineNumberArea = new LineNumberArea(this);

  connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
  connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
  connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
  
  updateLineNumberAreaWidth(0);
  highlightCurrentLine();  
  initialize();
}

/*****************************************************************************!
 * Function : CodeEditor
 *****************************************************************************/
CodeEditor::CodeEditor
(QWidget* InParent) : QPlainTextEdit(InParent)
{
  lineNumberArea = new LineNumberArea(this);

  connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
  connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
  connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
  
  updateLineNumberAreaWidth(0);
  highlightCurrentLine();  
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

/*****************************************************************************!
 * Function : lineNumberAreaWidth
 *****************************************************************************/
int
CodeEditor::lineNumberAreaWidth()
{
  int digits = 1;
  int max = qMax(1, blockCount());
  while (max >= 10) {
    max /= 10;
    ++digits;
  }
  
  int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
  
  return space;
}


/*****************************************************************************!
 * Function : lineNumberAreaPaintEvent
 *****************************************************************************/
void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
  QPainter painter(lineNumberArea);
  painter.fillRect(event->rect(), Qt::lightGray);
  
  QTextBlock block = firstVisibleBlock();
  int blockNumber = block.blockNumber();
  int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
  int bottom = top + qRound(blockBoundingRect(block).height());
  
  while (block.isValid() && top <= event->rect().bottom()) {
    if (block.isVisible() && bottom >= event->rect().top()) {
      QString number = QString::number(blockNumber + 1);
      painter.setPen(Qt::black);
      painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                       Qt::AlignRight, number);
    }
    
    block = block.next();
    top = bottom;
    bottom = top + qRound(blockBoundingRect(block).height());
    ++blockNumber;
  }
}

/*****************************************************************************!
 * 
 *****************************************************************************/
void CodeEditor::updateLineNumberAreaWidth(int newBlockCount)
{
  (void)newBlockCount;
  setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

/*****************************************************************************!
 * 
 *****************************************************************************/
void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

/*****************************************************************************!
 * 
 *****************************************************************************/
void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}
