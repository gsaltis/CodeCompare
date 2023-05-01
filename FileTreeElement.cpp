/*****************************************************************************
 * FILE NAME    : FileTreeElement.cpp
 * DATE         : April 28 2023
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
#include "FileTreeElement.h"

/*****************************************************************************!
 * Function : FileTreeElement
 *****************************************************************************/
FileTreeElement::FileTreeElement
(QString InAbsoluteFileName1, QString InAbsoluteFileName2) : AbsoluteFileName1(InAbsoluteFileName1),
                                                             AbsoluteFileName2(InAbsoluteFileName2)
                                                             
{
}

/*****************************************************************************!
 * Function : GetAbsoluteFileName1
 *****************************************************************************/
QString
FileTreeElement::GetAbsoluteFileName1(void)
{
  return AbsoluteFileName1;  
}

/*****************************************************************************!
 * Function : SetAbsoluteFileName1
 *****************************************************************************/
void
FileTreeElement::SetAbsoluteFileName1
(QString InAbsoluteFileName1)
{
  AbsoluteFileName1 = InAbsoluteFileName1;  
}

/*****************************************************************************!
 * Function : GetAbsoluteFileName2
 *****************************************************************************/
QString
FileTreeElement::GetAbsoluteFileName2(void)
{
  return AbsoluteFileName2;  
}

/*****************************************************************************!
 * Function : SetAbsoluteFileName2
 *****************************************************************************/
void
FileTreeElement::SetAbsoluteFileName2
(QString InAbsoluteFileName2)
{
  AbsoluteFileName2 = InAbsoluteFileName2;  
}

/*****************************************************************************!
 * Function : GetIsDirectory
 *****************************************************************************/
bool
FileTreeElement::GetIsDirectory
()
{
  return IsDirectory;
}

/*****************************************************************************!
 * Function : Read
 *****************************************************************************/
void
FileTreeElement::Read
()
{

}
