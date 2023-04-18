/*****************************************************************************
 * FILE NAME    : BuildTreeJSONCodeContainer.h
 * DATE         : April 14 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreejsoncodecontainer_h_
#define _buildtreejsoncodecontainer_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QTreeWidget>
#include <QTextEdit>
#include <QTreeWidgetItem>
#include <QSplitter>
#include <QJsonValue>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_TREE_JSONCODE_CONTAINER_X 200
#define BUILD_TREE_JSONCODE_CONTAINER_Y 200
#define BUILD_TREE_JSONCODE_CONTAINER_WIDTH 200
#define BUILD_TREE_JSONCODE_CONTAINER_HEIGHT 200

/*****************************************************************************!
 * Exported Class : BuildTreeJSONCodeContainer
 *****************************************************************************/
class BuildTreeJSONCodeContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTreeJSONCodeContainer    ();

 //! Destructor
 public :
  ~BuildTreeJSONCodeContainer   ();

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
  void                          resizeEvent                             (QResizeEvent* InEvent);
  void                          ProcessInnerTranslationUnitArray        (QJsonArray InTUArray, QString InFilename);
  void                          FontifyTreeItem                         (QTreeWidgetItem* InTreeWidget, QString InKind);
  void                          ProcessTopLevelInnerObject              (QTreeWidgetItem* InTreeItem, QJsonArray InArray);
  void                          ProcessCompoundStatement                (QTreeWidgetItem* InTreeItem, QJsonArray InArray);
  void                          ProcessCallExpr         (QTreeWidgetItem* InTreeItem, QJsonObject InObject);
  void                          ProcessDeclStmt         (QTreeWidgetItem* InTreeItem, QJsonObject InObject);
  void                          ProcessSingleItem       (QJsonValue InValue, QTreeWidgetItem* InItem);

 //! Private Data
 private :
  QTreeWidget*                  jsonFileDisplay;
  QTextEdit*                    errorWindow;
  int                           errorWindowHeight;
  QSplitter*                    splitter;
  
 //! Public Slots
 public slots :
  void                          SlotTreeItemSelected    (QString InFilename);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildtreejsoncodecontainer_h_*/
