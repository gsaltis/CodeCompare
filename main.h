/*****************************************************************************
 * FILE NAME    : main.h
 * DATE         : March 22 2023
 * PROJECT      : CodeCompare
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _main_h_
#define _main_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QGuiApplication>
#include <QSplashScreen>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SystemConfig.h"

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/
extern SystemConfig*
mainSystemConfig;

extern QString
mainCodeBase;

extern QApplication*
application;

extern QColor
MainToolBarBackgroundColor;

extern QSplashScreen*
splashScreen;

#endif /* _main_h_*/
