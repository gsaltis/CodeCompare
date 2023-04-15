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
  Initialize();
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
  QByteArray                            fileContents;
  QFile                                 file(InFilename);
  QJsonDocument                         doc;
  QJsonObject                           clangObject;
  QJsonObject                           docObject;
  QJsonObject                           geomObject;
  QJsonObject                           makeObject;
  QJsonObject                           pathsObject;
  QJsonValue                            geomValue;

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
  makeObject = docObject["Make"].toObject();
  if ( ! makeObject.isEmpty() ) {
    ReadMakeInformation(makeObject);
  }

  clangObject = docObject["Clang"].toObject();
  if ( ! clangObject.isEmpty() ){
    ReadClangInformation(clangObject);
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

/*****************************************************************************!
 * Function : ReadMakeInformation
 *****************************************************************************/
void
SystemConfig::ReadMakeInformation
(QJsonObject &InObject)
{
  MakeExeName = InObject["make"].toString();
  MakeTarget  = InObject["target"].toString();
  MakeNeedLIBDLTarget = InObject["needlibdl"].toBool();
  
  auto vl = InObject["args"].toArray().toVariantList();
  foreach (QVariant v, vl) {
    MakeArgs << v.toString();
  }
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
SystemConfig::Initialize(void)
{
  MakeExeName = QString("D:\\Qt\\Tools\\mingw900_64\\bin\\make.exe");
  MakeTarget = QString("all");
  MakeArgs << "-n" << "-B";
  MakeNeedLIBDLTarget = true;
}

/*****************************************************************************!
 * Function : GetMakeExeName
 *****************************************************************************/
QString
SystemConfig::GetMakeExeName(void)
{
  return QString(MakeExeName);
}

/*****************************************************************************!
 * Function : GetMakeTarget
 *****************************************************************************/
QString
SystemConfig::GetMakeTarget(void)
{
  return QString(MakeTarget);
}

/*****************************************************************************!
 * Function : GetMakeExeName
 *****************************************************************************/
QStringList
SystemConfig::GetMakeArgs(void)
{
  return QStringList(MakeArgs);
}

/*****************************************************************************!
 * Function : GetMakeNeedLIBDLTarget
 *****************************************************************************/
bool
SystemConfig::GetMakeNeedLIBDLTarget(void)
{
  return MakeNeedLIBDLTarget;  
}

/*****************************************************************************!
 * Function : SetMakeNeedLIBDLTarget
 *****************************************************************************/
void
SystemConfig::SetMakeNeedLIBDLTarget
(bool InMakeNeedLIBDLTarget)
{
  MakeNeedLIBDLTarget = InMakeNeedLIBDLTarget;  
}

/*****************************************************************************!
 * Function : ReadClangInformation
 *****************************************************************************/
void
SystemConfig::ReadClangInformation
(QJsonObject &InObject)
{
  ClangPath = InObject["clang"].toString();

  auto p = InObject["includepaths"].toArray();
  for ( int i = 0 ; i < p.size(); i++ ) {
    auto a = p[i].toObject();
    ClangIncludePaths << a["option"].toString() << a["path"].toString();
  }

  p = InObject["options"].toArray();
  for ( int i = 0 ; i < p.size(); i++ ) {
    ClangOptions << p[i].toString();
  }

  auto c = InObject["headergather"].toObject();
  p = c["options"].toArray();
  for ( int i = 0 ; i < p.size(); i++ ) {
    ClangHeaderGatherOptions << p[i].toString();
  }

  c = InObject["codegather"].toObject();
  p = c["options"].toArray();
  for ( int i = 0 ; i < p.size(); i++ ) {
    ClangCodeGatherOptions << p[i].toString();
  }

  p = InObject["headerexcludepaths"].toArray();
  for ( int i = 0 ; i < p.size(); i++ ) {
    ClangHeaderExcludePaths << p[i].toString();
  }
}

/*****************************************************************************!
 * Function : GetClangExecutable
 *****************************************************************************/
QString
SystemConfig::GetClangExecutable
()
{
  return ClangPath;
}

/*****************************************************************************!
 * Function : GetClangOptions
 *****************************************************************************/
QStringList
SystemConfig::GetClangOptions
()
{
  return ClangOptions;
}

/*****************************************************************************!
 * Function : GetClangIncludePaths
 *****************************************************************************/
QStringList
SystemConfig::GetClangIncludePaths
()
{
  QStringList                           stlist;
  QString                               st;

  for ( int i = 0 ; i < ClangIncludePaths.count(); i += 2 ) {
    st = ClangIncludePaths[i] + ClangIncludePaths[i+1];
    stlist << st;
  }
  return stlist;
}

/*****************************************************************************!
 * Function : GetClangHeaderOptions
 *****************************************************************************/
QStringList
SystemConfig::GetClangHeaderOptions
()
{
  return ClangHeaderGatherOptions;
}


/*****************************************************************************!
 * Function : GetClangHeaderExcludePaths
 *****************************************************************************/
QStringList
SystemConfig::GetClangHeaderExcludePaths(void)
{
  return ClangHeaderExcludePaths;
}
