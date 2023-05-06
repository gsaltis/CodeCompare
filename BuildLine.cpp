/*****************************************************************************
 * FILE NAME    : BuildLine.cpp
 * DATE         : April 03 2023
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
#include "BuildLine.h"
#include "FileTreeFile.h"

/*****************************************************************************!
 * Function : BuildLine
 *****************************************************************************/
BuildLine::BuildLine
() : QWidget()
{
  fileTreeElement = NULL;
  buildType = TypeNone;
}

/*****************************************************************************!
 * Function : ~BuildLine
 *****************************************************************************/
BuildLine::~BuildLine
()
{
}

/*****************************************************************************!
 * Function : GetType
 *****************************************************************************/
BuildLine::Type
BuildLine::GetType
()
{
  return buildType;
}
  
/*****************************************************************************!
 * Function : GetText
 *****************************************************************************/
QString
BuildLine::GetText
(void)
{
  return QString(lineText);
}

/*****************************************************************************!
 * Function : GetLineElements
 *****************************************************************************/
QStringList
BuildLine::GetLineElements
(QString InBuildLine)
{
  QStringList                           elements;

  elements = InBuildLine.split(QRegularExpression("\\s+|\n"));
  return elements;
}

/*****************************************************************************!
 * Function : Dump
 *****************************************************************************/
void
BuildLine::Dump(void)
{
  printf("%2d %s\n", buildType, lineText.toStdString().c_str());
}

/*****************************************************************************!
 * Function : GetFilePath
 *****************************************************************************/
QString
BuildLine::GetFilePath(void)
{
  return filePath;  
}

/*****************************************************************************!
 * Function : SetFilePath
 *****************************************************************************/
void
BuildLine::SetFilePath
(QString InFilePath)
{
  filePath = InFilePath;  
}

/*****************************************************************************!
 * Function : AddTranslationUnitType
 *****************************************************************************/
void
BuildLine::AddTranslationUnitType
(TranslationUnitType* InType)
{
  translationUnit << InType;
}

/*****************************************************************************!
 * Function : GetTranslationUnit
 *****************************************************************************/
TranslationUnit
BuildLine::GetTranslationUnit
()
{
  return translationUnit;
}

/*****************************************************************************!
 * Function : GetFileTreeElement
 *****************************************************************************/
FileTreeFile*
BuildLine::GetFileTreeElement(void)
{
  return fileTreeElement;  
}

/*****************************************************************************!
 * Function : SetFileTreeElement
 *****************************************************************************/
void
BuildLine::SetFileTreeElement
(FileTreeFile* InFileTreeElement)
{
  fileTreeElement = InFileTreeElement;  
}
