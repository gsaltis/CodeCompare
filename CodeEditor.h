/*****************************************************************************
 * FILE NAME    : CodeEditor.h
 * DATE         : April 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codeeditor_h_
#define _codeeditor_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QPlainTextEdit>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeHighlighter.h"
#include "LineNumberArea.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CODE_EDITOR_X                   200
#define CODE_EDITOR_Y                   200
#define CODE_EDITOR_WIDTH               200
#define CODE_EDITOR_HEIGHT              200

/*****************************************************************************!
 * Exported Class : CodeEditor
 *****************************************************************************/
class CodeEditor : public QPlainTextEdit
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeEditor                    ();
  CodeEditor                    (QWidget* InParent);

 //! Destructor
 public :
  ~CodeEditor                   ();

 //! Public Methods
 public :
  int                           lineNumberAreaWidth             ();
  void                          lineNumberAreaPaintEvent        (QPaintEvent *event);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          SetFileDisplayTabWidth  (int InTabWidth);
  void                          initialize              (void);
  void                          resizeEvent             (QResizeEvent *e);
  void                          highlightCurrentLine            ();
  void                          updateLineNumberAreaWidth(int newBlockCounte);
  
 //! Private Data
 private :
  CodeHighlighter*              codeHighlighter;
  QWidget *                     lineNumberArea;
  
 //! Public Slots
 public slots :
  void                          updateLineNumberArea    (const QRect &rect, int dy);
  void                          SlotSetCurrentLine      (int InLineNumber);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codeeditor_h_*/
