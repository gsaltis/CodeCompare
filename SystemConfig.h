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
  QString                       GetMakeExeName          (void);
  QString                       GetMakeTarget           (void);
  QStringList                   GetMakeArgs             (void);
  bool                          GetMakeNeedLIBDLTarget  (void);
  void                          SetMakeNeedLIBDLTarget  (bool InMakeNeedLIBDLTarget);

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
  void                          Initialize              (void);

 //! Private Data
 private :
  int                           MainWindowX;
  int                           MainWindowY;
  int                           MainWindowWidth;
  int                           MainWindowHeight;
  QString                       SourceTrackPath;
  QString                       MakeExeName;
  QString                       MakeTarget;
  QStringList                   MakeArgs;
  bool                          MakeNeedLIBDLTarget;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _systemconfig_h_*/
