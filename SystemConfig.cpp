/*****************************************************************************
 * FILE NAME    : SystemConfig.cpp
 * DATE         : March 22 2023
 * PROJECT      : CodeCompare
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QJsonDocument>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SystemConfig.h"
#include "trace.h"

/*****************************************************************************!
 * Static Data
 *****************************************************************************/
QString SystemConfig::SystemName = "CodeCompare";

/*****************************************************************************!
 * Function : SystemConfig
 *****************************************************************************/
SystemConfig::SystemConfig
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~SystemConfig
 *****************************************************************************/
SystemConfig::~SystemConfig
()
{
}

/*****************************************************************************!
 * Function : ReadJSON
 *****************************************************************************/
void
SystemConfig::ReadJSON
(QString InFilename)
{
  QJsonObject                           pathsObject;
  QJsonValue                            geomValue;
  QJsonObject                           geomObject;
  QJsonObject                           docObject;
  QJsonDocument                         doc;
  QByteArray                            fileContents;
  QFile                                 file(InFilename);

  file.open(QIODeviceBase::ReadOnly);

  fileContents = file.readAll();
  file.close();
  if ( fileContents.isNull() ) {
    return;
  }

  doc = QJsonDocument::fromJson(fileContents);
  docObject = doc.object();

  geomValue = docObject["MainWindowGeometry"];
  geomObject = geomValue.toObject();
  if ( ! geomObject.isEmpty() ) {
    ReadMainWindowGeometry(geomObject);
  }
  pathsObject = docObject["Paths"].toObject();
  if ( ! pathsObject.isEmpty() ) {
    ReadPaths(pathsObject);
  }
}

/*****************************************************************************!
 * Function : ReadMainWindowGeometry
 *****************************************************************************/
void
SystemConfig::ReadMainWindowGeometry
(QJsonObject &InObject)
{
  MainWindowX = InObject["x"].toInt();
  MainWindowY = InObject["y"].toInt();
  MainWindowWidth = InObject["width"].toInt();
  MainWindowHeight = InObject["height"].toInt();
}

/*****************************************************************************!
 * Function : GetMainWindowLocation
 *****************************************************************************/
QPoint
SystemConfig::GetMainWindowLocation(void)
{
  return QPoint(MainWindowX, MainWindowY);
}

/*****************************************************************************!
 * Function : GetMainWindowSize
 *****************************************************************************/
QSize
SystemConfig::GetMainWindowSize(void)
{
  return QSize(MainWindowWidth, MainWindowHeight);
}

/*****************************************************************************!
 * Function : ReadPaths
 *****************************************************************************/
void
SystemConfig::ReadPaths
(QJsonObject& InObject)
{
  SourceTrackPath = InObject["sourcepath"].toString();
}

/*****************************************************************************!
 * Function : GetSourceTrackPath
 *****************************************************************************/
QString
SystemConfig::GetSourceTrackPath(void)
{
  return SourceTrackPath;
}
