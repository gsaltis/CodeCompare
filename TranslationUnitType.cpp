/*****************************************************************************
 * FILE NAME    : TranslationUnitType.cpp
 * DATE         : May 05 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
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
#include "TranslationUnitType.h"

/*****************************************************************************!
 * Function : TranslationUnitType
 *****************************************************************************/
TranslationUnitType::TranslationUnitType
(QString InName, int InLineStart, int InLineEnd) : QWidget()
{
  name = InName;
  lineStart = InLineStart;
  lineEnd = InLineEnd;
  type = None;
}

/*****************************************************************************!
 * Function : ~TranslationUnitType
 *****************************************************************************/
TranslationUnitType::~TranslationUnitType
()
{
}

