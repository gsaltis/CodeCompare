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
#include <QTreeWidgetItem>
#include <QJsonValue>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildLine.h"
#include "CodeTrack.h"

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
  BuildTreeJSONCodeContainer    (CodeTrack* InCodeTrack);

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
  void                          ProcessInnerTranslationUnitArray        (BuildLine* InBuildLine, QJsonArray InTUArray, QString InFilename);
  void                          FontifyTreeItem                         (QTreeWidgetItem* InTreeWidget, QJsonObject InObject, QString InKind);
  void                          ProcessTopLevelInnerObject              (QTreeWidgetItem* InTreeItem, QJsonArray InArray);
  void                          ProcessCompoundStatement                (QTreeWidgetItem* InTreeItem, QJsonArray InArray);
  void                          ProcessCallExpr         (QTreeWidgetItem* InTreeItem, QJsonObject InObject);
  void                          ProcessDeclStmt         (QTreeWidgetItem* InTreeItem, QJsonObject InObject);
  void                          ProcessSingleItem       (QJsonValue InValue, QTreeWidgetItem* InItem);
  void                          ProcessRangeObject                      (QTreeWidgetItem* InTreeItem, QJsonValue InValue);
  void                          ProcessValue                            (QTreeWidgetItem* InTreeItem, QJsonValue InValue);
  QJsonObject                   FindElementInInnerObject                (QJsonArray InInnerObject, QString InName);
  bool                          AreFileNamesEqual       (QString InFilename1, QString InFilename2);

 //! Private Data
 private :
  QTreeWidget*                  jsonFileDisplay;
  CodeTrack*                    codeTrack;
  
 //! Public Slots
 public slots :
  void                          SlotTreeItemSelected    (BuildLine* InBuildLine, QString InFilename);

 //! Public Signals
 signals :
  void                          SignalBuildTreeJSONErrorOutput (QString InErrorOutput);
  void                          SignalBuildLineProcessed (BuildLine* InBuildLine, QString InFilename);
  void                          SignalSendDisplayMessage (QString InString);

 //! Public Actions
 public :

};

#endif /* _buildtreejsoncodecontainer_h_*/
