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
  QString                               mainTrack1Directory;
  QString                               mainTrack2Directory;
  QApplication                          application(argc, argv);
  MainWindow*                           w;
  QCommandLineParser                    commandLineParser;

  application.setApplicationName("CodeCompare");
  application.setApplicationVersion("0.0.0");
  application.setOrganizationName("Greg Saltis");
  application.setOrganizationDomain("www.gsaltis.com");

  commandLineParser.setApplicationDescription("CodeCompare");
  commandLineParser.addHelpOption();
  commandLineParser.addVersionOption();
  QCommandLineOption codeBaseNameOption(QStringList() << "b" << "codebase",
                                       QCoreApplication::translate("main", "Specifiy a codebase <basepath>."),
                                       QCoreApplication::translate("main", "basepath"));
  QCommandLineOption codeBase1NameOption(QStringList() << "1" << "track1",
                                         QCoreApplication::translate("main", "Specifiy a codebase for first track <basepath>."),
                                         QCoreApplication::translate("main", "codepath"));
  QCommandLineOption codeBase2NameOption(QStringList() << "2" << "track2",
                                         QCoreApplication::translate("main", "Specifiy a codebase for seconde track <basepath>."),
                                         QCoreApplication::translate("main", "codepath"));
  commandLineParser.addOption(codeBaseNameOption);
  commandLineParser.addOption(codeBase1NameOption);
  commandLineParser.addOption(codeBase2NameOption);
  commandLineParser.process(application);
  mainCodeBase = commandLineParser.value(codeBaseNameOption);
  mainTrack1Directory = commandLineParser.value(codeBase1NameOption);
  mainTrack2Directory = commandLineParser.value(codeBase2NameOption);
  
  mainSystemConfig = new SystemConfig();
  mainSystemConfig->ReadJSON(MainConfigFilename);
  w = new MainWindow(NULL);
  w->resize(mainSystemConfig->GetMainWindowSize());
  w->move(mainSystemConfig->GetMainWindowLocation());
  w->show();
  if ( ! mainCodeBase.isEmpty() ) {
    w->SetCodeBaseDirectoryName(mainCodeBase);
  } else if ( VerifyCodeTracks(mainTrack1Directory, mainTrack2Directory) ) {
    w->SetTracksDirectoryNames(mainTrack1Directory, mainTrack2Directory);
  } else {
    exit(EXIT_FAILURE);
  }    
  return application.exec();
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

  
