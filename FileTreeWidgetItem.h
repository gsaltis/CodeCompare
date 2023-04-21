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
  FileTreeWidgetItem            (QString InAbsoluteFileName, int InColumn = 0);
  FileTreeWidgetItem            (QString InAbsoluteFileName, QTreeWidgetItem* InParent, int InColumn = 0);
  FileTreeWidgetItem            (QString InAbsoluteFileName, QTreeWidget* InParent);
  FileTreeWidgetItem            (QString InAbsoluteFileName1,  QString InAbsoluteFileName2);
  FileTreeWidgetItem            (QString InAbsoluteFileName1,  QString InAbsoluteFileName2, QTreeWidgetItem* InParent);

 //! Destructor
 public :
  ~FileTreeWidgetItem           ();

 //! Public Methods
 public :
  QString                       GetAbsoluteFileName1    (void);
  void                          SetAbsoluteFileName1    (QString InAbsoluteFileName1);
  QString                       GetAbsoluteFileName2    (void);
  void                          SetAbsoluteFileName2    (QString InAbsoluteFileName2);
  void                          SetAbsoluteFileNames    (QString InAbsoluteFileName1, QString InAbsoluteFileName2);
  
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
  QString                       absoluteFileName1;
  QString                       absoluteFileName2;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _filetreewidgetitem_h_*/
