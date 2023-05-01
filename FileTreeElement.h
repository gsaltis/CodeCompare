/*****************************************************************************
 * FILE NAME    : FileTreeElement.h
 * DATE         : April 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _filetreeelement_h_
#define _filetreeelement_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "FileContentsDiff.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : FileTreeElement
 *****************************************************************************/
class FileTreeElement
{
 //! Constructors
 public :
  FileTreeElement               (QString InAbsoluteFileName1, QString InAbsoluteFileName2);

 //! Destructor
 public :

 //! Public Methods
 public :
  QString                       GetAbsoluteFileName1    (void);
  void                          SetAbsoluteFileName1    (QString InAbsoluteFileName1);
  QString                       GetAbsoluteFileName2    (void);
  void                          SetAbsoluteFileName2    (QString InAbsoluteFileName2);
  virtual void                  Read                    ();
  bool                          GetIsDirectory          ();

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :
  bool                          IsDirectory;
  QString                       AbsoluteFileName1;
  QString                       AbsoluteFileName2;
  bool                          FilesHaveBeenRead;
  
 //! Private Methods
 private :

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _filetreeelement_h_*/
