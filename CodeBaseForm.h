/*****************************************************************************
 * FILE NAME    : CodeBaseForm.h
 * DATE         : March 23 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codebaseform_h_
#define _codebaseform_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirectoryReadEntry.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CODE_BASE_FORM_X                200
#define CODE_BASE_FORM_Y                200
#define CODE_BASE_FORM_WIDTH            200
#define CODE_BASE_FORM_HEIGHT           200

/*****************************************************************************!
 * Exported Class : CodeBaseForm
 *****************************************************************************/
class CodeBaseForm : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeBaseForm                  ();

 //! Destructor
 public :
  ~CodeBaseForm                 ();

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
  QLabel*                       CreateLabel             (QString InText);
  void                          AddRow                  (QString InLabelText, QWidget* InWidget);
  void                          InsertRow               (int InRow, QString InLabelText, QWidget* InWidget);
  void                          RemoveRow               (int InRow);

 //! Private Data
 private :
  QFormLayout*                  formLayout;
  DirectoryReadEntry*           track1codeBaseEdit;
  DirectoryReadEntry*           track2codeBaseEdit;
  DirectoryReadEntry*           mergecodeBaseEdit;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codebaseform_h_*/
