/*****************************************************************************
 * FILE NAME    : CodeDisplay.h
 * DATE         : May 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codedisplay_h_
#define _codedisplay_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeDisplayLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CODE_DISPLAY_X                  200
#define CODE_DISPLAY_Y                  200
#define CODE_DISPLAY_WIDTH              200
#define CODE_DISPLAY_HEIGHT             200

/*****************************************************************************!
 * Exported Class : CodeDisplay
 *****************************************************************************/
class CodeDisplay : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeDisplay                   ();

 //! Destructor
 public :
  ~CodeDisplay                  ();

 //! Public Methods
 public :
  void                          ClearLines              (void);
  void                          SetSectionText          (QString InText, int InStartingLine);

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

 //! Private Data
 private :
  QList<CodeDisplayLine*>       lines;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codedisplay_h_*/
