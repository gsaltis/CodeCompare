/*****************************************************************************
 * FILE NAME    : DirTreeItemDir.h
 * DATE         : May 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _dirtreeitemdir_h_
#define _dirtreeitemdir_h_

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
 * Exported Class : DirTreeItemDir
 *****************************************************************************/
class DirTreeItemDir : public DirTreeItem
{
 //! Constructors
 public :
  DirTreeItemDir                ();

 //! Destructor
 public :
  ~DirTreeItemDir               ();

 //! Public Methods
 public :
  void                          CollapseChildren        (void);
  void                          ExpandChildren          (void);
  DirTreeItem*                  FindItem                (QString InText);
  bool                          GetChanged              (void);
  void                          SetChanged              (bool InChanged);
  
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
    
  bool                          changed;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _dirtreeitemdir_h_*/
