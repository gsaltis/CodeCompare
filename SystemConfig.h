/*****************************************************************************
 * FILE NAME    : SystemConfig.h
 * DATE         : March 22 2023
 * PROJECT      : CodeCompare
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _systemconfig_h_
#define _systemconfig_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : SystemConfig
 *****************************************************************************/
class SystemConfig : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SystemConfig                  ();

 //! Destructor
 public :
  ~SystemConfig                 ();

 //! Public Methods
 public :
  void                          ReadJSON                (QString InFilename);
  QPoint                        GetMainWindowLocation   (void);
  QSize                         GetMainWindowSize       (void);
  QString                       GetSourceTrackPath      (void);
  QString                       GetSourceTrack1Path     (void);
  QString                       GetSourceTrack2Path     (void);
  QString                       GetMakeExeName          (void);
  QString                       GetMakeTarget           (void);
  QStringList                   GetMakeArgs             (void);
  bool                          GetMakeNeedLIBDLTarget  (void);
  void                          SetMakeNeedLIBDLTarget  (bool InMakeNeedLIBDLTarget);
  QString                       GetClangExecutable      ();
  QStringList                   GetClangOptions         ();
  QStringList                   GetClangIncludePaths    ();
  QStringList                   GetClangHeaderOptions   ();
  QStringList                   GetClangHeaderExcludePaths (void);
  QStringList                   GetClangCodeGatherOptions();
  bool                          GetDiffMissingIsDiff    ();
  QString                       GetDiff                 ();
  QString                       GetBuildDirectoryName   ();
  
 //! Public Data
 public :
  static QString                SystemName;

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          ReadMainWindowGeometry  (QJsonObject &InObject);
  void                          ReadPaths               (QJsonObject &InObject);
  void                          ReadMakeInformation     (QJsonObject &InObject);
  void                          ReadClangInformation    (QJsonObject &InObject);
  void                          Initialize              (void);
  void                          ReadDiffInformation     (QJsonObject &InObject);
  void                          ReadBuildInformation    (QJsonObject &InObject);

 //! Private Data
 private :
  int                           MainWindowX;
  int                           MainWindowY;
  int                           MainWindowWidth;
  int                           MainWindowHeight;
  QString                       SourceTrackPath;
  QString                       SourceTrack1Path;
  QString                       SourceTrack2Path;
  QString                       MakeExeName;
  QString                       MakeTarget;
  QStringList                   MakeArgs;
  bool                          MakeNeedLIBDLTarget;

  QString                       ClangPath;
  QStringList                   ClangOptions;
  QStringList                   ClangIncludePaths;              // Pairs options/value
  QStringList                   ClangHeaderGatherOptions;  
  QStringList                   ClangCodeGatherOptions;
  QStringList                   ClangHeaderExcludePaths;
  QString                       BuildDirectoryName;
  QString                       DiffExeName;
  bool                          DiffMissingIsDiff;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _systemconfig_h_*/
