/*****************************************************************************
 * FILE NAME    : TranslationUnit.cpp
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
#include "TranslationUnit.h"
#include "trace.h"

/*****************************************************************************!
 * Function : TranslationUnit
 *****************************************************************************/
TranslationUnit::TranslationUnit
() 
{
}

/*****************************************************************************!
 * Function : ~TranslationUnit
 *****************************************************************************/
TranslationUnit::~TranslationUnit
()
{
}

/*****************************************************************************!
 * Function : Write
 *****************************************************************************/
void
TranslationUnit::Write
(QString InFilename)
{
  int                                   n;
  bool                                  lastItem;
  QFile                                 file(InFilename);

  TRACE_FUNCTION_QSTRING(InFilename);
  if ( ! file.open(QIODeviceBase::ReadWrite | QIODeviceBase::Truncate) ) {
    return;
  }

  file.write("[\n");
  n = count();
  for ( int i = 0 ; i < n; i++ ) {
    TranslationUnitType*                t = at(i);
    lastItem = ((i + 1) == n);
    t->Write(&file, lastItem);
  }
  file.write("]\n");
  file.close();
}

