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
#include <QTextEdit>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeHighlighter.h"

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
class CodeEditor : public QTextEdit
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

 //! Private Data
 private :
  CodeHighlighter*              codeHighlighter;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codeeditor_h_*/
