/*****************************************************************************
 * FILE NAME    : CodeBaseOpenDialog.h
 * DATE         : March 23 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codebaseopendialog_h_
#define _codebaseopendialog_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QPushButton>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeBaseForm.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CODE_BASE_OPEN_DIALOG_WIDTH             500
#define CODE_BASE_OPEN_DIALOG_HEIGHT            250

/*****************************************************************************!
 * Exported Class : CodeBaseOpenDialog
 *****************************************************************************/
class CodeBaseOpenDialog : public QDialog
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeBaseOpenDialog            ();

 //! Destructor
 public :
  ~CodeBaseOpenDialog           ();

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
  void                          Initialize              (void);
  void                          CreateConnections       (void);
  void                          CreateSubWindows        (void);
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QPushButton*                  OKButton;
  QPushButton*                  CancelButton;
  CodeBaseForm*                 codeBaseFormWindow;

 //! Public Slots
 public slots :
  void                          SlotOKButtonPressed     ();
  void                          SlotCancelButtonPressed ();

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codebaseopendialog_h_*/
