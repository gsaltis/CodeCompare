/*****************************************************************************
 * FILE NAME    : FileTreeWidgetItem.h
 * DATE         : April 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _filetreewidgetitem_h_
#define _filetreewidgetitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "FileContentsDiff.h"
#include "FileTreeElement.h"
#include "FileTreeFile.h"
#include "FileTreeDirectory.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define FILE_TREE_WIDGET_ITEM_X         200
#define FILE_TREE_WIDGET_ITEM_Y         200
#define FILE_TREE_WIDGET_ITEM_WIDTH     200
#define FILE_TREE_WIDGET_ITEM_HEIGHT    200

/*****************************************************************************!
 * Exported Class : FileTreeWidgetItem
 *****************************************************************************/
class FileTreeWidgetItem : public QTreeWidgetItem
{
 //! Constructors
 public :
  FileTreeWidgetItem            (QString InAbsoluteFileName, QTreeWidget* InParent, bool InIsDirectory);
  FileTreeWidgetItem            (QString InAbsoluteFileName1,  QString InAbsoluteFileName2, bool InIsDirectory);
  FileTreeWidgetItem            (QString InAbsoluteFileName1,  QString InAbsoluteFileName2, QTreeWidgetItem* InParent, bool InIsDirectory);

 //! Destructor
 public :
  ~FileTreeWidgetItem           ();

 //! Public Methods
 public :
  QString                       GetAbsoluteFileName1    (void);
  void                          SetAbsoluteFileName1    (void);
  QString                       GetAbsoluteFileName2    (void);
  void                          SetAbsoluteFileName2    (void);
  void                          SetAbsoluteFileNames    (void);
  void                          ParseDiffLines          (QString InDiffLines);
  bool                          GetFilesDiffer          (void);
  void                          SetFilesDiffer          (bool InFilesDiffer);
  bool                          GetIsDirectory          (void);
  void                          SetIsDirectory          (bool InIsDirectory);
  QString                       GetFileName1            ();
  QString                       GetFileName2            ();
  bool                          IsSourceFile            (void);
  QList<int>                    GetChangeLinesCount     ();
  FileContentsDiff              GetDifferences          ();
  bool                          ReadFileContents        (QString InFilename, QStringList& InFileLines);
  void                          ReadFiles               (void);
  QStringList                   GetFile1Lines           ();
  QStringList                   GetFile2Lines           ();
  QStringList                   GetFile1LinesSelection  (int InStartLine, int InEndLine);
  QStringList                   GetFile2LinesSelection  (int InStartLine, int InEndLine);
  FileTreeElement*              GetTreeElement          ();
  void                          DiffFiles               (int &InLinesDifferCount);
  int                           GetFileCount            ();

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
  QStringList                   GetFileLinesSelection   (QStringList InFileLines, int InStartLine, int InEndLine);
  
 //! Private Data
 private :
  FileTreeElement*              TreeElement;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _filetreewidgetitem_h_*/
