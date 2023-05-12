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
  
  application.setApplicationName("ASTSByS");
  application.setApplicationVersion("0.0.0");
  application.setOrganizationName("Greg Saltis");
  application.setOrganizationDomain("www.gsaltis.com");

  mainSystemConfig = new SystemConfig();
  mainSystemConfig->ReadJSON(MainConfigFilename);

  commandLineParser.setApplicationDescription("CodeCompare");
  commandLineParser.addHelpOption();
  commandLineParser.addVersionOption();
  QCommandLineOption codeBase1NameOption(QStringList() << "1" << "file1",
                                         QCoreApplication::translate("main", "Specifiy a file for first track."),
                                         QCoreApplication::translate("main", "filename"));
  QCommandLineOption codeBase2NameOption(QStringList() << "2" << "file2",
                                         QCoreApplication::translate("main", "Specifiy a file for second track."),
                                         QCoreApplication::translate("main", "filename"));
  commandLineParser.addOption(codeBase1NameOption);
  commandLineParser.addOption(codeBase2NameOption);
  commandLineParser.process(application);

  mainFilename1 = commandLineParser.value(codeBase1NameOption);
  mainFilename2 = commandLineParser.value(codeBase2NameOption);

  if ( mainFilename1.isEmpty() ) {
    QMessageBox::critical(NULL, "Missing File", "Missing file 1");
    exit(EXIT_FAILURE);
  }    
  if ( mainFilename1.isEmpty() ) {
    QMessageBox::critical(NULL, "Missing File", "Missing file 2");
    exit(EXIT_FAILURE);
  }    
  w = new MainWindow(NULL, mainFilename1, mainFilename2, &application);
  w->resize(mainSystemConfig->GetMainWindowSize());
  w->move(mainSystemConfig->GetMainWindowLocation());
  w->show();
  
  return application.exec();
}
