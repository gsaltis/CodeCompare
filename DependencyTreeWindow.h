/*****************************************************************************
 * FILE NAME    : DependencyTreeWindow.h
 * DATE         : March 31 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _dependencytreewindow_h_
#define _dependencytreewindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QAction>
#include <QLineEdit>
#include <QTreeWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "DirectoryTreeElement.h"
#include "DependencyTreeWidgetItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define DEPENDENCY_TREE_WINDOW_X        200
#define DEPENDENCY_TREE_WINDOW_Y        200
#define DEPENDENCY_TREE_WINDOW_WIDTH    200
#define DEPENDENCY_TREE_WINDOW_HEIGHT   200

/*****************************************************************************!
 * Exported Class : DependencyTreeWindow
 *****************************************************************************/
class DependencyTreeWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  DependencyTreeWindow          ();

 //! Destructor
 public :
  ~DependencyTreeWindow         ();

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
  void                          ProcessTopLevelDirectory(QFileInfo InInfo, QTreeWidget* InTreeWindow);
  void                          ProcessTreeDirectory    (QFileInfo InInfo, QTreeWidgetItem* InTreeItem);
  void                          ConnectWindows          ();
  void                          TreeItemSelected        (DependencyTreeWidgetItem* InItem);

 //! Private Data
 private :
  QPushButton*                  CloseButton;
  QPushButton*                  MakeButton;
  QLineEdit*                    pathLineInput;
  QPushButton*                  pathLineSelectButton;
  QPushButton*                  BrowsePathButton;
  QTreeWidget*                  directoryTreeWindow;
  DirectoryTreeElement*         topElement;
  
 //! Public Slots
 public slots :
  void                          SlotCloseButtonPushed           (void);
  void                          SlotMakeButtonPushed            (void);
  void                          SlotpathLineSelectPushed        (void);
  void                          SlotBrowsePathButtonPushed      (void);

 //! Public Signals
 signals :
  void                          SignalWindowClose       (void);

 //! Public Actions
 public :
  QAction*                      ActionCloseButtonPushed;
  QAction*                      ActionpathLineSelectPushed;
  QAction*                      ActionBrowsePathButtonPushed;

};

#endif /* _dependencytreewindow_h_*/
