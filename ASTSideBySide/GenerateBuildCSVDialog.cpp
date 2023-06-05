/*****************************************************************************
 * FILE NAME    : GenerateBuildCSVDialog.cpp
 * DATE         : June 02 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "GenerateBuildCSVDialog.h"

/*****************************************************************************!
 * Function : GenerateBuildCSVDialog
 *****************************************************************************/
GenerateBuildCSVDialog::GenerateBuildCSVDialog
() : QDialog()
{
  Initialize();
}

/*****************************************************************************!
 * Function : ~GenerateBuildCSVDialog
 *****************************************************************************/
GenerateBuildCSVDialog::~GenerateBuildCSVDialog
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
GenerateBuildCSVDialog::Initialize(void)
{
  CreateSubWindows();  
  CreateConnections();
  resize(GENERATE_BUILD_CSV_DIALOG_WIDTH, GENERATE_BUILD_CSV_DIALOG_HEIGHT);
  setWindowTitle("Generate Build CSV File");
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
GenerateBuildCSVDialog::CreateConnections(void)
{
  connect(OKButton, SIGNAL(pressed()), this, SLOT(SlotOKButtonPressed()));  
  connect(CancelButton, SIGNAL(pressed()), this, SLOT(SlotCancelButtonPressed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
GenerateBuildCSVDialog::CreateSubWindows(void)
{
  int                                   buttonHeight;
  int                                   buttonGap;
  int                                   cancelButtonX;
  int                                   okButtonX;
  int                                   buttonY;
  int                                   cancelButtonWidth;
  int                                   okButtonWidth;
  
  okButtonWidth = 40;
  cancelButtonWidth = 60;
  buttonGap = 5;
  buttonHeight = 20;
  okButtonX = GENERATE_BUILD_CSV_DIALOG_WIDTH - (okButtonWidth + cancelButtonWidth + (2 * buttonGap));
  cancelButtonX = GENERATE_BUILD_CSV_DIALOG_WIDTH - (cancelButtonWidth + buttonGap);
  buttonY = GENERATE_BUILD_CSV_DIALOG_HEIGHT - (buttonGap + buttonHeight);
 
  OKButton = new QPushButton();
  OKButton->setParent(this);
  OKButton->setText("OK");
  OKButton->move(okButtonX, buttonY);
  OKButton->resize(okButtonWidth, buttonHeight);
  
  CancelButton = new QPushButton();
  CancelButton->setParent(this);
  CancelButton->setText("Cancel");
  CancelButton->move(cancelButtonX, buttonY);
  CancelButton->resize(cancelButtonWidth, buttonHeight);
}

/*****************************************************************************!
 * Function : SlotOKButtonPressed
 *****************************************************************************/
void
GenerateBuildCSVDialog::SlotOKButtonPressed()
{
  accept();
}

/*****************************************************************************!
 * Function : SlotCancelButtonPressed
 *****************************************************************************/
void
GenerateBuildCSVDialog::SlotCancelButtonPressed()
{
  reject();
}
