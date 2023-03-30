/*****************************************************************************
 * FILE NAME    : CodeBaseOpenDialog.cpp
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
#include <QDialog>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CodeBaseOpenDialog.h"

/*****************************************************************************!
 * Function : CodeBaseOpenDialog
 *****************************************************************************/
CodeBaseOpenDialog::CodeBaseOpenDialog
() : QDialog()
{
  Initialize();
  setWindowTitle(QString("Code Base Open"));
}

/*****************************************************************************!
 * Function : ~CodeBaseOpenDialog
 *****************************************************************************/
CodeBaseOpenDialog::~CodeBaseOpenDialog
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
CodeBaseOpenDialog::Initialize(void)
{
  codeBaseFormWindow = NULL;
  CreateSubWindows();  
  CreateConnections();
  resize(CODE_BASE_OPEN_DIALOG_WIDTH, CODE_BASE_OPEN_DIALOG_HEIGHT);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
CodeBaseOpenDialog::CreateConnections(void)
{
  connect(OKButton, SIGNAL(pressed()), this, SLOT(SlotOKButtonPressed()));  
  connect(CancelButton, SIGNAL(pressed()), this, SLOT(SlotCancelButtonPressed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
CodeBaseOpenDialog::CreateSubWindows(void)
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
  okButtonX = CODE_BASE_OPEN_DIALOG_WIDTH - (okButtonWidth + cancelButtonWidth + (2 * buttonGap));
  cancelButtonX = CODE_BASE_OPEN_DIALOG_WIDTH - (cancelButtonWidth + buttonGap);
  buttonY = CODE_BASE_OPEN_DIALOG_HEIGHT - (buttonGap + buttonHeight);
 
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
  codeBaseFormWindow = new CodeBaseForm();
  codeBaseFormWindow->setParent(this);
}

/*****************************************************************************!
 * Function : SlotOKButtonPressed
 *****************************************************************************/
void
CodeBaseOpenDialog::SlotOKButtonPressed()
{
  accept();
}

/*****************************************************************************!
 * Function : SlotCancelButtonPressed
 *****************************************************************************/
void
CodeBaseOpenDialog::SlotCancelButtonPressed()
{
  reject();
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
CodeBaseOpenDialog::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   x, y, w, h;
  int                                   OKButtonW, CancelButtonW;
  int                                   OKButtonX, CancelButtonX;
  int                                   buttonH, buttonY;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  OKButtonW = OKButton->size().width();
  buttonH = OKButton->size().height();
  CancelButtonW = CancelButton->size().width();
  CancelButtonX = width - (CancelButtonW + 10);
  OKButtonX = width - (CancelButtonW + OKButtonW + 20);
  buttonY = height - (buttonH + 10);
  
  w = width - 20;
  h = 120;
  x = 10;
  y = 30;
  
  if ( codeBaseFormWindow ) {
    codeBaseFormWindow->resize(w, h);
    codeBaseFormWindow->move(x, y);
  }

  OKButton->move(OKButtonX, buttonY);
  OKButton->resize(OKButtonW, buttonH);

  CancelButton->move(CancelButtonX, buttonY);
  CancelButton->resize(CancelButtonW, buttonH);
}
