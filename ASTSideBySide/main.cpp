/*****************************************************************************
 FILE NAME      : main.cpp
 DATE           : May 10 2023
 PROJECT        : ASTSByS
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
#include <QMessageBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainWindow.h"
#include "main.h"
#include <QCommandLineParser>

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
QString
MainConfigFilename = "System.json";

SystemConfig*
mainSystemConfig;

QString
mainFilename1;

QString
mainFilename2;

QString
mainSource1ASTPath;

QString
mainSource2ASTPath;

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  QApplication                          application(argc, argv);
  MainWindow*                           w;
  QCommandLineParser                    commandLineParser;
  QString                               mainFilename;
  
  application.setApplicationName("ASTSByS");
  application.setApplicationVersion("0.0.0");
  application.setOrganizationName("Greg Saltis");
  application.setOrganizationDomain("www.gsaltis.com");

  mainSystemConfig = new SystemConfig();
  mainSystemConfig->ReadJSON(MainConfigFilename);

  mainSource1ASTPath = mainSystemConfig->GetSourceASTTrack1Path();
  mainSource2ASTPath = mainSystemConfig->GetSourceASTTrack2Path();
  
  commandLineParser.setApplicationDescription("CodeCompare");
  commandLineParser.addHelpOption();
  commandLineParser.addVersionOption();
  QCommandLineOption codeBaseNameOption(QStringList() << "f" << "file",
                                         QCoreApplication::translate("main", "Specifiy a file name."),
                                         QCoreApplication::translate("main", "filename"));
  commandLineParser.addOption(codeBaseNameOption);
  commandLineParser.process(application);
  mainFilename = commandLineParser.value(codeBaseNameOption);

  if ( mainFilename.isEmpty() ) {
    QMessageBox::critical(NULL, "Missing File", "Missing file");
    exit(EXIT_FAILURE);
  }    

  mainFilename1 = mainSource1ASTPath + QString("/") +  mainFilename;
  mainFilename2 = mainSource2ASTPath + QString("/") +  mainFilename;
                                               
  w = new MainWindow(NULL, mainFilename1, mainFilename2, &application);
  w->resize(mainSystemConfig->GetMainWindowSize());
  w->move(mainSystemConfig->GetMainWindowLocation());
  w->show();
  
  return application.exec();
}
