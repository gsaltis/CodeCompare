/*****************************************************************************
 * FILE NAME    : DirectoryReadEntry.h
 * DATE         : March 23 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _directoryreadentry_h_
#define _directoryreadentry_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QAction>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define DIRECTORY_READ_ENTRY_X          200
#define DIRECTORY_READ_ENTRY_Y          200
#define DIRECTORY_READ_ENTRY_WIDTH      200
#define DIRECTORY_READ_ENTRY_HEIGHT     200

/*****************************************************************************!
 * Exported Class : DirectoryReadEntry
 *****************************************************************************/
class DirectoryReadEntry : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  DirectoryReadEntry            ();

 //! Destructor
 public :
  ~DirectoryReadEntry           ();

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

 //! Private Data
 private :
  QLineEdit*                    directoryNameEdit;
  QPushButton*                  browseButton;

 //! Public Slots
 public slots :
  void                          SlotbrowseButtonPushed  (void);

 //! Public Signals
 signals :

 //! Public Actions
 public :
  QAction*                      ActionbrowseButtonPushed;

};

#endif /* _directoryreadentry_h_*/
