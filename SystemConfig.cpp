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
  QJsonObject                           diffObject;
  QJsonObject                           buildObject;
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

  diffObject = docObject["Diff"].toObject();
  if ( ! diffObject.isEmpty() ){
    ReadDiffInformation(diffObject);
  }

  buildObject = docObject["Build"].toObject();
  if ( ! buildObject.isEmpty() ){
    ReadBuildInformation(buildObject);
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
  SourceTrack1Path = InObject["track1path"].toString();
  SourceTrack2Path = InObject["track2path"].toString();
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
 * Function : GetSourceTrack1Path
 *****************************************************************************/
QString
SystemConfig::GetSourceTrack1Path(void)
{
  return SourceTrack1Path;
}

/*****************************************************************************!
 * Function : GetSourceTrack2Path
 *****************************************************************************/
QString
SystemConfig::GetSourceTrack2Path(void)
{
  return SourceTrack2Path;
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
 * Function : ReadBuildInformation
 *****************************************************************************/
void
SystemConfig::ReadBuildInformation
(QJsonObject &InObject)
{
  BuildDirectoryName = InObject["builddir"].toString();
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

/*****************************************************************************!
 * Function : 
 *****************************************************************************/
QStringList
SystemConfig::GetClangCodeGatherOptions
()
{
  return ClangCodeGatherOptions;
}


/*****************************************************************************!
 * Function : ReadDiffInformation
 *****************************************************************************/
void
SystemConfig::ReadDiffInformation
(QJsonObject &InObject)
{
  DiffExeName = InObject["diff"].toString();
  DiffMissingIsDiff = InObject["missing"].toBool();
}

/*****************************************************************************!
 * Function : GetDiff
 *****************************************************************************/
QString
SystemConfig::GetDiff
()
{
  return DiffExeName;
}

/*****************************************************************************!
 * Function : GetDiffMissingIsDiff
 *****************************************************************************/
bool
SystemConfig::GetDiffMissingIsDiff
()
{
  return DiffMissingIsDiff;
}

/*****************************************************************************!
 * Function : GetBuildDirectoryName
 *****************************************************************************/
QString
SystemConfig::GetBuildDirectoryName
()
{
  return BuildDirectoryName;
}
