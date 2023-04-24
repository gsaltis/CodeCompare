/*****************************************************************************
 * FILE NAME    : LineNumberArea.h
 * DATE         : April 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _linenumberarea_h_
#define _linenumberarea_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define LINE_NUMBER_AREA_X              200
#define LINE_NUMBER_AREA_Y              200
#define LINE_NUMBER_AREA_WIDTH          200
#define LINE_NUMBER_AREA_HEIGHT         200

/*****************************************************************************!
 * Imported Class
 *****************************************************************************/
class CodeEditor;

/*****************************************************************************!
 * Exported Class : LineNumberArea
 *****************************************************************************/
class LineNumberArea : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  LineNumberArea(CodeEditor *editor)
  {
    codeEditor = editor;
  }

 //! Destructor
 public :
  ~LineNumberArea               ();

 //! Public Methods
 public :
  QSize sizeHint();

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void paintEvent(QPaintEvent *event) override;

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
    CodeEditor *codeEditor;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _linenumberarea_h_*/
