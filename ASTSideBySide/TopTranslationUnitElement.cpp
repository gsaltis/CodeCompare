/*****************************************************************************
 * FILE NAME    : TopTranslationUnitElement.cpp
 * DATE         : May 11 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TopTranslationUnitElement.h"

/*****************************************************************************!
 * Function : TopTranslationUnitElement
 *****************************************************************************/
TopTranslationUnitElement::TopTranslationUnitElement
(QString InKind, QString InName, QJsonValue InContent) : QWidget()
{
  kind = InKind;
  name = InName;
  content = InContent;
}

/*****************************************************************************!
 * Function : ~TopTranslationUnitElement
 *****************************************************************************/
TopTranslationUnitElement::~TopTranslationUnitElement
()
{
}

