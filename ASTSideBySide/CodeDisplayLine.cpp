/*****************************************************************************
 * FILE NAME    : CodeDisplayLine.cpp
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
#include "CodeDisplayLine.h"
#include "trace.h"

/*****************************************************************************!
 * Function : CodeDisplayLine
 *****************************************************************************/
CodeDisplayLine::CodeDisplayLine
(int InLineNumber, QString InText) : QWidget()
{
  tabWidth = 4;
  lineNumberLabelWidth = 40;
  QPalette pal;
  lineText = InText;
  lineNumber = InLineNumber;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(0, 0, 32)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~CodeDisplayLine
 *****************************************************************************/
CodeDisplayLine::~CodeDisplayLine
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
CodeDisplayLine::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
CodeDisplayLine::CreateSubWindows()
{
  QPalette                              pal;
  QFont                                 font = QFont("Courier New", 10, QFont::Normal);
  
  //! Create label  
  lineNumberLabel = new QLabel();
  lineNumberLabel->setParent(this);
  lineNumberLabel->move(0, 0);
  lineNumberLabel->resize(lineNumberLabelWidth, 20);
  lineNumberLabel->setText(QString("%1").arg(lineNumber));
  lineNumberLabel->setAlignment(Qt::AlignRight);
  lineNumberLabel->setFont(font);
  lineNumberLabel->setAutoFillBackground(true);
  pal = lineNumberLabel->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(109, 122, 138)));

  lineNumberLabel->setPalette(pal);

  pal.setBrush(QPalette::WindowText, QBrush(QColor(255, 255, 32)));
  lineNumberLabel->setPalette(pal);
    
  //! Create label  
  lineTextLabel = new QLabel();
  lineTextLabel->setParent(this);
  lineTextLabel->move(lineNumberLabelWidth, 0);
  lineTextLabel->resize(100, 20);
  lineTextLabel->setText(Detabify(lineText));
  lineTextLabel->setAlignment(Qt::AlignLeft);
  lineTextLabel->setFont(font);
  pal = lineTextLabel->palette();
  pal.setBrush(QPalette::WindowText, QBrush(QColor(255, 255, 255)));
  lineTextLabel->setPalette(pal);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
CodeDisplayLine::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
CodeDisplayLine::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   lineNumberLabellX, lineNumberLabellY;
  int                                   lineNumberLabellW, lineNumberLabellH;
  int                                   lineTextLabelX, lineTextLabelY;
  int                                   lineTextLabelW, lineTextLabelH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  lineNumberLabellX = 0;
  lineNumberLabellY = 0;
  lineNumberLabellW = lineNumberLabelWidth;
  lineNumberLabellH = height;

  lineTextLabelX = lineNumberLabellW + 5;
  lineTextLabelY = 0;
  lineTextLabelW = width - (lineNumberLabellW + 5);
  lineTextLabelH = height;

  lineNumberLabel->move(lineNumberLabellX, lineNumberLabellY);
  lineNumberLabel->resize(lineNumberLabellW, lineNumberLabellH);
  
  lineTextLabel->move(lineTextLabelX, lineTextLabelY);
  lineTextLabel->resize(lineTextLabelW, lineTextLabelH);
}

/*****************************************************************************!
 * Function : Detabify
 *****************************************************************************/
QString
CodeDisplayLine::Detabify
(QString InString)
{
  int                                   i;
  int                                   n2, n3;
  QString                               tabString;
  int                                   n = InString.length();
  QString                               returnString = QString("");
  QChar                                 ch;

  for ( i = 0 ; i < n; i++ ) {
    ch = InString[i];

    if ( ch == QChar('\t') ) {
      n2 = returnString.length() % tabWidth;
      if ( n2 == 0 ) {
        tabString.fill(QChar(' '), tabWidth);
        returnString += tabString;
        continue;
      }
      n3 = tabWidth - n2;
      
      tabString.fill(QChar(' '), n3);
      returnString += tabString;
      continue;
    }
    returnString.append(ch);
  }
  return returnString;
}
