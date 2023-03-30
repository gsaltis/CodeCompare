/*****************************************************************************
 * FILE NAME    : CodeBaseForm.cpp
 * DATE         : March 23 2023
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
#include "CodeBaseForm.h"

/*****************************************************************************!
 * Function : CodeBaseForm
 *****************************************************************************/
CodeBaseForm::CodeBaseForm
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255, 0)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~CodeBaseForm
 *****************************************************************************/
CodeBaseForm::~CodeBaseForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
CodeBaseForm::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
CodeBaseForm::CreateSubWindows()
{
  formLayout = new QFormLayout(this);  

  track1codeBaseEdit = new DirectoryReadEntry();
  AddRow("Track 1 Code Base", track1codeBaseEdit);

  track2codeBaseEdit = new DirectoryReadEntry();
  AddRow("Track 2 Code Base", track2codeBaseEdit);

  mergecodeBaseEdit = new DirectoryReadEntry();
  AddRow("Code Merge Base", mergecodeBaseEdit);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
CodeBaseForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
CodeBaseForm::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : CreateLabel
 *****************************************************************************/
QLabel*
CodeBaseForm::CreateLabel
(QString InText)
{
  QLabel*                               label;  
  label = new QLabel(InText + QString(" : "));
  label->setMinimumWidth(120);
  label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  return label;
}

/*****************************************************************************!
 * Function : AddRow
 *****************************************************************************/
void
CodeBaseForm::AddRow
(QString InLabelText, QWidget* InWidget)
{
  formLayout->addRow(CreateLabel(InLabelText), InWidget);  
}

/*****************************************************************************!
 * Function : InsertRow
 *****************************************************************************/
void
CodeBaseForm::InsertRow
(int InRow, QString InLabelText, QWidget* InWidget)
{
  formLayout->insertRow(InRow, CreateLabel(InLabelText), InWidget);  
}

/*****************************************************************************!
 * Function : RemoveRow
 *****************************************************************************/
void
CodeBaseForm::RemoveRow
(int InRow)
{
  formLayout->removeRow(InRow);  
}
