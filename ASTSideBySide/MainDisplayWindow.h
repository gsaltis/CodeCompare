/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.h
 * DATE         : May 10 2023
 * PROJECT      : ASTSByS
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _maindisplaywindow_h_
#define _maindisplaywindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QSplitter>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QJsonDocument>
#include <QApplication>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TitledWindow.h"
#include "TopTranslationUnitElement.h"
#include "TUTreeElement.h"
#include "TUTree.h"
#include "DirTree.h"
#include "TUTreeContainer.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : MainDisplayWindow
 *****************************************************************************/
class MainDisplayWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  MainDisplayWindow             (QString InFilename1, QString InFilename2,
                                 QApplication* InApplication);

 //! Destructor
 public :
  ~MainDisplayWindow            ();

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
  void                          Initialize                      ();
  void                          InitializeSubWindows            ();
  void                          CreateSubWindows                ();
  void                          resizeEvent                     (QResizeEvent* InEvent);
  void                          ProcessValue                    (TUTreeElement* InItem, QJsonValue InValue);
  void                          PopulateASTTree                 (QTreeWidget* InTree, QString InFilename);
  void                          ProcessTranslationUnitInner     (TUTreeElement* InItem, QJsonArray InArray, QString InFilename);
  void                          FontifyTreeItem                 (TUTreeElement* InTreeItem, QJsonObject InObject, QString InKind);
  QJsonObject                   FindElementInInnerObject        (QJsonArray InInnerObject, QString InName);
  TUTreeElement*                CreateTreeItem                  (TUTreeElement* InItem, TopTranslationUnitElement* InTUElement);
  void                          ExpandFunction                  (TUTree* InTree, TUTreeElement* InElement);

 //! Private Data
 private :
  QSplitter*                    splitter;
  TitledWindow*                 fileWindow1;
  TitledWindow*                 fileWindow2;
  TUTree*                       jsonTree1;
  TUTree*                       jsonTree2;
  TUTreeContainer*              jsonTreeContainer1;
  TUTreeContainer*              jsonTreeContainer2;
  QString                       filename1;
  QString                       filename2;
  QApplication*                 application;
  DirTree*                      dirTree;
  
 //! Public Slots
 public slots :
  void                          SlotJSON1TreeClicked            (QTreeWidgetItem* InItem, int InColumn);
  void                          SlotJSON1TreeExpanded           (QTreeWidgetItem* InItem);
  void                          SlotJSON1TreeCollapsed          (QTreeWidgetItem* InItem);
  void                          SlotJSON2TreeClicked            (QTreeWidgetItem* InItem, int InColumn);
  void                          SlotJSON2TreeExpanded           (QTreeWidgetItem* InItem);
  void                          SlotJSON2TreeCollapsed          (QTreeWidgetItem* InItem);
  void                          SlotSetErrorWindowHeight2       (int InPosition);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _maindisplaywindow_h_*/
