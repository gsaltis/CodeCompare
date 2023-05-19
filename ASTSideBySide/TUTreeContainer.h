/*****************************************************************************
 * FILE NAME    : TUTreeContainer.h
 * DATE         : May 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _tutreecontainer_h_
#define _tutreecontainer_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QStackedWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TUTree.h"
#include "TUTreeContainerSplitter.h"
#include "CodeDisplay.h"
#include "CodeEditor.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TUTreeContainer
 *****************************************************************************/
class TUTreeContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TUTreeContainer               (TUTree* InTree, QString InErrorFilename);

 //! Destructor
 public :
  ~TUTreeContainer              ();

 //! Public Methods
 public :
  void                          SetErrorFilename        (QString InErrorFilename);
  void                          DisplayErrorWindow      (void);
  void                          DisplayTextWindow       (void);
  void                          SetTextSection          (QString InText);
  void                          ClearTextWindow         ();
  
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
  void                          SetErrorText            ();

 //! Private Data
 private :
  TUTreeContainerSplitter*      splitter;
  TUTree*                       tree;
  QTextEdit*                    errorWindow;
  QString                       errorFilename;
  QStackedWidget*               displayArea;
  CodeDisplay*                  codeDisplay;
  CodeEditor*                   codeEditor;
  
 //! Public Slots
 public slots :
  void                          SlotSplitterMoved       (int InPosition, int InIndex);
  void                          SlotSetErrorWindowHeight (int InHeight);

 //! Public Signals
 signals :
  void                          SignalSplitterMoved     (int InPosition);

 //! Public Actions
 public :

};

#endif /* _tutreecontainer_h_*/
