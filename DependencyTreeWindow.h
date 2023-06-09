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
#include "BuildLineDisplayForm.h"
#include "BuildLineSet.h"
#include "BuildSystem.h"
#include "CodeTrack.h"

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
  DependencyTreeWindow          (CodeTrack* InCodeTrack);

 //! Destructor
 public :
  ~DependencyTreeWindow         ();

 //! Public Methods
 public :
  void                          SetCodeBaseDirectoryName(QString InCodeBaseDirectoryName);

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
  
 //! Private Data
 private :
  QPushButton*                  CloseButton;
  QPushButton*                  TreeButton;
  QLineEdit*                    pathLineInput;
  QPushButton*                  pathLineSelectButton;
  QPushButton*                  BrowsePathButton;
  QTreeWidget*                  directoryTreeWindow;
  DirectoryTreeElement*         topElement;
  BuildLineDisplayForm*         buildLineDisplayWindow;
  BuildSystem*                  buildSystem;
  CodeTrack*                    codeTrack;
  
 //! Public Slots
 public slots :
  void                          SlotTreeButtonPushed            (void);
  void                          SlotCloseButtonPushed           (void);
  void                          SlotpathLineSelectPushed        (void);
  void                          SlotBrowsePathButtonPushed      (void);
  void                          SlotTreeWidgetItemSelected      (QTreeWidgetItem* InItem, int InColumn);
  void                          SlotSourceDirectorySelected     (QString InSourceDirectoryName);
  
 //! Public Signals
 signals :
  void                          SignalWindowClose       (void);
  void                          SignalTreeWindowOpen    (void);
  void                          SignalBuildLinesSelected (BuildLineSet* InBuildLines);
  void                          SignalBuildSystemSelected (BuildSystem* InSystem);

 //! Public Actions
 public :
  QAction*                      ActionCloseButtonPushed;
  QAction*                      ActionpathLineSelectPushed;
  QAction*                      ActionBrowsePathButtonPushed;

};

#endif /* _dependencytreewindow_h_*/
