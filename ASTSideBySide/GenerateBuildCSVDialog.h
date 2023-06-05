/*****************************************************************************
 * FILE NAME    : GenerateBuildCSVDialog.h
 * DATE         : June 02 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _generatebuildcsvdialog_h_
#define _generatebuildcsvdialog_h_

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

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define GENERATE_BUILD_CSV_DIALOG_WIDTH         300
#define GENERATE_BUILD_CSV_DIALOG_HEIGHT        400

/*****************************************************************************!
 * Exported Class : GenerateBuildCSVDialog
 *****************************************************************************/
class GenerateBuildCSVDialog : public QDialog
{
  Q_OBJECT;

 //! Constructors
 public :
  GenerateBuildCSVDialog        ();

 //! Destructor
 public :
  ~GenerateBuildCSVDialog       ();

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

 //! Private Data
 private :
  QPushButton*                  OKButton;
  QPushButton*                  CancelButton;

 //! Public Slots
 public slots :
  void                          SlotOKButtonPressed     ();
  void                          SlotCancelButtonPressed ();

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _generatebuildcsvdialog_h_*/
