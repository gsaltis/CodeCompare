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
#include "CommonFileTree.h"

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
class DirTree : public CommonFileTree
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
  bool                          GetExpanded             (void);
  bool                          GetDisplayAllItems      (void);

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
  void                          PopulateTreeDir2        (DirTreeItemDir* InItem, QString InFilePath);
  DirTreeItemDir*               FindDirItem             (QString InDirName);
  void                          GetAllFileNames         (QString InBasePath, QString InFilePath, QStringList& InFilenames);
  bool                          FilesAreSame            (QString InFilename1, QString InFilename2);
  void                          GetAllDifferingFilenames(QString InFilePath1, QString InFilePath2, QStringList InFilenames, QStringList& InDifferingNames);
  bool                          LineIsCopyrightLine     (QString InLine);
  void                          HideItems               (QStringList InDifferingItems);
  void                          HideDirItems            (DirTreeItem* InItem, QStringList InDifferingItems);
  
 //! Private Data
 private :
  bool                          expanded;
  bool                          displayAllItems;
  QList<DirTreeItemFile*>       fileItems;

 //! Public Slots
 public slots :
  void                          SlotFileSelected        (QTreeWidgetItem* InItem, int InIndex);
  void                          SlotToggleTreeView      (void);
  void                          SlotToggleChangedItems  (void);

 //! Public Signals
 signals :
  void                          SignalFileSelected      (QString InFilename);
  
 //! Public Actions
 public :

};

#endif /* _dirtree_h_*/
