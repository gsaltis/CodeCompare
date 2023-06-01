/*****************************************************************************
 * FILE NAME    : CommonFileTree.h
 * DATE         : May 23 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _commonfiletree_h_
#define _commonfiletree_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QTreeWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeTrack.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define COMMON_FILE_TREE_X              200
#define COMMON_FILE_TREE_Y              200
#define COMMON_FILE_TREE_WIDTH          200
#define COMMON_FILE_TREE_HEIGHT         200

/*****************************************************************************!
 * Exported Class : CommonFileTree
 *****************************************************************************/
class CommonFileTree : public QTreeWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  CommonFileTree                (QString InFilePath1, QString InFilePath2);

 //! Destructor
 public :
  ~CommonFileTree               ();

 //! Public Methods
 public :
  bool                          GetExpanded             (void);
  bool                          GetDisplayAllItems      (void);

 //! Public Data
 public :

 //! Protected Methods
 protected :
  QString                       GetCommonPrefix         (QString InFilename1, QString InFilename2);
  void                          InitializeHeaders       (void);

 //! Protected Data
 protected :
  QString                       filePath1;
  QString                       filePath2;
  QString                       headerName1;
  QString                       headerName2;
  bool                          expanded;
  bool                          displayAllItems;
  CodeTrack                     track1;
  CodeTrack                     track2;
  
 //! Private Methods
 private :
  void                          initialize              ();

  //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _commonfiletree_h_*/
