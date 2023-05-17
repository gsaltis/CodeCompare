/*****************************************************************************
 * FILE NAME    : CodeDisplayLine.h
 * DATE         : May 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codedisplayline_h_
#define _codedisplayline_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CODE_DISPLAY_LINE_X             0
#define CODE_DISPLAY_LINE_Y             0
#define CODE_DISPLAY_LINE_WIDTH         200
#define CODE_DISPLAY_LINE_HEIGHT        20

/*****************************************************************************!
 * Exported Class : CodeDisplayLine
 *****************************************************************************/
class CodeDisplayLine : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeDisplayLine               (int InLineNumber, QString InText);

 //! Destructor
 public :
  ~CodeDisplayLine              ();

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
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  QString                       Detabify                (QString InString);

 //! Private Data
 private :
  QLabel*                       lineNumberLabel;
  QLabel*                       lineTextLabel;
  QString                       lineText;
  int                           lineNumber;
  int                           lineNumberLabelWidth;
  int                           tabWidth;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codedisplayline_h_*/
