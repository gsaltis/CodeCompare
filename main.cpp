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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainWindow.h"
#include "main.h"
#include "SystemConfig.h"

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

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  QApplication                          application(argc, argv);
  MainWindow*                           w;

  application.setApplicationName("CodeCompare");
  application.setApplicationVersion("0.0.0");
  application.setOrganizationName("Greg Saltis");
  application.setOrganizationDomain("www.gsaltis.com");

  mainSystemConfig = new SystemConfig();
  mainSystemConfig->ReadJSON(MainConfigFilename);
  w = new MainWindow(NULL);
  w->resize(mainSystemConfig->GetMainWindowSize());
  w->move(mainSystemConfig->GetMainWindowLocation());
  w->show();
  
  return application.exec();
}
