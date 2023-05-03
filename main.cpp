 /*****************************************************************************
 FILE NAME      : main.cpp
 DATE           : March 22 2023
 PROJECT        : CodeCompare
 COPYRIGHT      : Copyright (C) 2023 by Gregory R Saltis
******************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QtGui>
#include <QCommandLineParser>
#include <QSplashScreen>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainWindow.h"
#include "main.h"
#include "SystemConfig.h"
#include "trace.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
QString
MainConfigFilename = "System.json";

SystemConfig*
mainSystemConfig;

QString
mainCodeBase = QString("");

bool
mainStartAnalysis = false;

QApplication*
application;

QColor
MainToolBarBackgroundColor = QColor(240, 240, 240);

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
bool
VerifyCodeTracks
(QString InTrack1Name, QString InTrack2Name);

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  QString                               systemConfigFileName;
  QString                               mainTrack1Directory;
  QString                               mainTrack2Directory;
  MainWindow*                           w;
  QCommandLineParser                    commandLineParser;
  
  application = new QApplication(argc, argv);
  QPixmap                               splashPixmap(":/images/Splash.png");

  application->setApplicationName("CodeCompare");
  application->setApplicationVersion("0.0.0");
  application->setOrganizationName("Greg Saltis");
  application->setOrganizationDomain("www.gsaltis.com");

  QSplashScreen splashScreen(splashPixmap);
  splashScreen.show();
  application->processEvents();
  commandLineParser.setApplicationDescription("CodeCompare");
  commandLineParser.addHelpOption();
  commandLineParser.addVersionOption();
  QCommandLineOption codeBase1NameOption(QStringList() << "1" << "track1",
                                         QCoreApplication::translate("main", "Specifiy a codebase for first track <basepath>."),
                                         QCoreApplication::translate("main", "codepath"));
  QCommandLineOption codeBase2NameOption(QStringList() << "2" << "track2",
                                         QCoreApplication::translate("main", "Specifiy a codebase for seconde track <basepath>."),
                                         QCoreApplication::translate("main", "codepath"));
  QCommandLineOption SystemConfigOption(QStringList() << "s" << "system",
                                         QCoreApplication::translate("main", "Specifiy a System Configuration file>."),
                                         QCoreApplication::translate("main", "system"));
  QCommandLineOption StartAnalysisOption(QStringList() << "a" << "analysis",
                                         QCoreApplication::translate("main", "Start Analysis at start up."));
  commandLineParser.addOption(codeBase1NameOption);
  commandLineParser.addOption(codeBase2NameOption);
  commandLineParser.addOption(SystemConfigOption);
  commandLineParser.addOption(StartAnalysisOption);
  commandLineParser.process(*application);
  mainCodeBase = commandLineParser.value(codeBase1NameOption);
  mainTrack1Directory = commandLineParser.value(codeBase1NameOption);
  mainTrack2Directory = commandLineParser.value(codeBase2NameOption);
  systemConfigFileName = commandLineParser.value(SystemConfigOption);
  mainStartAnalysis = commandLineParser.isSet(StartAnalysisOption);
  
  if ( ! systemConfigFileName.isEmpty() ) {
    MainConfigFilename = systemConfigFileName;
  }
  mainSystemConfig = new SystemConfig();
  mainSystemConfig->ReadJSON(MainConfigFilename);
  w = new MainWindow(mainTrack1Directory, mainTrack2Directory, mainStartAnalysis);
  w->resize(mainSystemConfig->GetMainWindowSize());
  w->move(mainSystemConfig->GetMainWindowLocation());
  w->show();
  splashScreen.finish(w);
  return application->exec();
}

/*****************************************************************************!
 * Function : VerifyCodeTracks
 *****************************************************************************/
bool
VerifyCodeTracks
(QString InTrack1Name, QString InTrack2Name)
{
  if ( InTrack1Name.isEmpty() ) {
    printf("Missing track 1 code directory\n");
    return false;
  }

  if ( InTrack2Name.isEmpty() ) {
    printf("Missing track 2 code directory\n");
    return false;
  }

  QFileInfo fileInfo1(InTrack1Name);
  if ( !fileInfo1.exists() ) {
    printf("\%s\" does not exists\n", InTrack1Name.toStdString().c_str());
    return false;
  }

  QFileInfo fileInfo2(InTrack2Name);
  if ( !fileInfo2.exists() ) {
    printf("\%s\" does not exists\n", InTrack2Name.toStdString().c_str());
    return false;
  }

  return true;
}
