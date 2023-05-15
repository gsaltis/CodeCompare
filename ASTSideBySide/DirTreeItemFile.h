/*****************************************************************************
 * FILE NAME    : DirTreeItemFile.h
 * DATE         : May 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _dirtreeitemfile_h_
#define _dirtreeitemfile_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirTreeItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : DirTreeItemFile
 *****************************************************************************/
class DirTreeItemFile : public DirTreeItem
{
 //! Constructors
 public :
  DirTreeItemFile               (QString InLabel, QString InFilename);

 //! Destructor
 public :
  ~DirTreeItemFile              ();

 //! Public Methods
 public :
  QString                       GetFilename             ();
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();

 //! Private Data
 private :
  QString                       filename;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _dirtreeitemfile_h_*/
