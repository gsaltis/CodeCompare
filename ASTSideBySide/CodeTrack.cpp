/*****************************************************************************
 * FILE NAME    : CodeTrack.cpp
 * DATE         : May 01 2023
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
#include "CodeTrack.h"
#include "trace.h"

/*****************************************************************************!
 * Function : CodeTrack
 *****************************************************************************/
CodeTrack::CodeTrack
() : QWidget()
{
  basePath = QString();
  basePathLen = 0;
}

/*****************************************************************************!
 * Function : ~CodeTrack
 *****************************************************************************/
CodeTrack::~CodeTrack
()
{
}

/*****************************************************************************!
 * Function : GetBasePath
 *****************************************************************************/
QString
CodeTrack::GetBasePath(void)
{
  return basePath;  
}

/*****************************************************************************!
 * Function : SetBasePath
 *****************************************************************************/
void
CodeTrack::SetBasePath
(QString InBasePath)
{
  basePath = QDir::toNativeSeparators(InBasePath);
  basePathLen = basePath.length();
}

/*****************************************************************************!
 * Function : GetBasePathLen
 *****************************************************************************/
int
CodeTrack::GetBasePathLen(void)
{
  
  return basePathLen;
}

/*****************************************************************************!
 * Function : PathBeginsWithBasePath
 *****************************************************************************/
bool
CodeTrack::PathBeginsWithBasePath
(QString InPath)
{
  int                                   n;
  QString                               s;
  QString                               b;
  
  n = InPath.length();
  if ( n < basePathLen ) {
    return false;
  }
  s = QDir::toNativeSeparators(InPath.sliced(0, basePathLen));
  b = QDir::toNativeSeparators(basePath);
  return s == b;
}

/*****************************************************************************!
 * Function : RemoveLeadingBasePath
 *****************************************************************************/
QString
CodeTrack::RemoveLeadingBasePath
(QString InPath)
{
  int                                   n;
  QString                               st1;
  QString                               st2;
  
  st1 = QDir::toNativeSeparators(InPath);
  if ( !PathBeginsWithBasePath(st1) ) {
    return InPath;
  }
  n = InPath.length();
  if ( n < basePathLen ) {
    return InPath;
  }
  st2 = InPath.sliced(basePathLen);
  if ( st2[0] == '/' || st2[0] == '\\' ) {
    st2 = st2.sliced(1);
  }
  return st2;
}

