/*****************************************************************************
 * FILE NAME    : CompileSourceLine.cpp
 * DATE         : May 31 2023
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
#include "CompileSourceLine.h"

/*****************************************************************************!
 * Function : CompileSourceLine
 *****************************************************************************/
CompileSourceLine::CompileSourceLine 
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~CompileSourceLine
 *****************************************************************************/
CompileSourceLine::~CompileSourceLine
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
CompileSourceLine::Initialize()
{
}

/*****************************************************************************!
 * Function : GetSourceFileName
 *****************************************************************************/
QString
CompileSourceLine::GetSourceFileName(void)
{
  return SourceFileName;
}

/*****************************************************************************!
 * Function : GetFullSourceFileName
 *****************************************************************************/
QString
CompileSourceLine::GetFullSourceFileName(void)
{
  return SourceFullFileName;
}

/*****************************************************************************!
 * Function : Set
 *****************************************************************************/
void
CompileSourceLine::Set
(QString InFileName, QString InFullFileName)
{
  SourceFileName = InFileName;
  SourceFullFileName = InFullFileName;
} 
