/*****************************************************************************
 * FILE NAME    : DirTree.h
 * DATE         : May 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _dirtree_h_
#define _dirtree_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTreeWidget>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirTreeItemDir.h"
#include "DirTreeItemFile.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define DIR_TREE_X                      200
#define DIR_TREE_Y                      200
#define DIR_TREE_WIDTH                  200
#define DIR_TREE_HEIGHT                 200

/*****************************************************************************!
 * Exported Class : DirTree
 *****************************************************************************/
class DirTree : public QTreeWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  DirTree                       (QString InFilePath1, QString InFilePath2);

 //! Destructor
 public :
  ~DirTree                      ();

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
  void                          PopulateTree            (void);
  void                          PopulateTree2           (void);
  void                          PopulateTreeDir         (DirTreeItemDir* InItem, QString InFilePath, QFileInfo InFileInfo);
  QString                       GetCommonPrefix         (QString InFilename1, QString InFilename2);
  DirTreeItemDir*               FindDirItem             (QString InDirName);

 //! Private Data
 private :
  QString                       filePath1;
  QString                       filePath2;
  
 //! Public Slots
 public slots :
  void                          SlotFileSelected        (QTreeWidgetItem* InItem, int InIndex);

 //! Public Signals
 signals :
  void                          SignalFileSelected      (QString InFilename);

 //! Public Actions
 public :

};

#endif /* _dirtree_h_*/
