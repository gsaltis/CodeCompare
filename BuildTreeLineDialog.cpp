/*****************************************************************************
 * FILE NAME    : BuildTreeLineDialog.cpp
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
#include <QDialog>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildTreeLineDialog.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildTreeLineDialog
 *****************************************************************************/
BuildTreeLineDialog::BuildTreeLineDialog
(BuildLine* InBuildLine) : QDialog()
{
  buildLine = InBuildLine;
  Initialize();
}

/*****************************************************************************!
 * Function : ~BuildTreeLineDialog
 *****************************************************************************/
BuildTreeLineDialog::~BuildTreeLineDialog
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
BuildTreeLineDialog::Initialize(void)
{
  CreateSubWindows();  
  CreateConnections();
  resize(BUILD_TREE_LINE_DIALOG_WIDTH, BUILD_TREE_LINE_DIALOG_HEIGHT);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BuildTreeLineDialog::CreateConnections(void)
{
  connect(OKButton, SIGNAL(pressed()), this, SLOT(SlotOKButtonPressed()));  
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildTreeLineDialog::CreateSubWindows(void)
{
  int                                   y;
  int                                   ySkip;
  int                                   labelX;
  int                                   labelWidth;
  int                                   labelHeight;
  int                                   elementX;
  QStringList                           sl;
  
  labelWidth = 150;
  labelHeight = 20;
  labelX = 10;

  ySkip = 22;
  y = 30;

  elementX = labelWidth + labelX + 10;
  
  actionNameLabel       = new QLabel("Action :", this);
  actionNameLabel->move(labelX, y);
  actionNameLabel->resize(labelWidth, labelHeight);
  actionNameLabel->setFont(QFont("", 10, QFont::Bold));
  actionNameLabel->setAlignment(Qt::AlignRight);

  actionLabel = new QLabel(buildLine->GetAction(), this);
  actionLabel->move(elementX, y);
  actionLabel->setAlignment(Qt::AlignLeft);
  
  y += ySkip;
  
  //!
  targetNameLabel       = new QLabel("Target :", this);
  targetNameLabel->move(labelX, y);
  targetNameLabel->resize(labelWidth, labelHeight);
  targetNameLabel->setFont(QFont("", 10, QFont::Bold));
  targetNameLabel->setAlignment(Qt::AlignRight);

  targetLabel = new QLabel(buildLine->GetTarget(), this);
  targetLabel->move(elementX, y);
  targetLabel->setAlignment(Qt::AlignLeft);
  y += ySkip;

  //!
  CreateGroupSection(sourcesNameLabel, "Sources", buildLine->GetSources(),
                     sourcesNames, sourcesNamesScrollArea, y);
  
  //!
  CreateGroupSection(libsNameLabel, "Libraries", buildLine->GetLibraries(),
                     libsNames, libsNamesScrollArea, y);

  //!
  CreateGroupSection(libPathsNameLabel, "Include Header Paths", buildLine->GetIncludePaths(),
                     includesPaths, includesPathsScrollArea, y);

  //!
  CreateGroupSection(libPathsNameLabel, "Library Paths", buildLine->GetLibraryPaths(),
                     libsPaths, libsPathsScrollArea, y);

  //!
  CreateGroupSection(flagsNameLabel, "Flags", buildLine->GetFlags(),
                     flags, flagsScrollArea, y);

  OKButton = new QPushButton(QString("OK"), this);
  OKButton->resize(60, 20);
}

/*****************************************************************************!
 * Function : SlotOKButtonPressed
 *****************************************************************************/
void
BuildTreeLineDialog::SlotOKButtonPressed()
{
  accept();
}

/*****************************************************************************!
 * Function : SlotCancelButtonPressed
 *****************************************************************************/
void
BuildTreeLineDialog::SlotCancelButtonPressed()
{
  reject();
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildTreeLineDialog::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;  
  int                                   width;
  int                                   height;
  int                                   OKButtonX, OKButtonY, OKButtonW, OKButtonH;
  int                                   elementX, elementW, elementH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  elementX = sourcesNamesScrollArea->pos().x();
  elementH = sourcesNamesScrollArea->size().height();
  elementW = width - (elementX + 10);
  sourcesNamesScrollArea->resize(elementW, elementH);
  elementH = sourcesNames->size().height();
  sourcesNames->resize(elementW-3, elementH);
  
  elementH = libsNamesScrollArea->size().height();
  libsNamesScrollArea->resize(elementW, elementH);
  elementH = libsNames->size().height();
  libsNames->resize(elementW-3, elementH);

  elementH = includesPathsScrollArea->size().height();  
  includesPathsScrollArea->resize(elementW, elementH);
  elementH = includesPaths->size().height();
  includesPaths->resize(elementW-3, elementH);

  elementH = libsPathsScrollArea->size().height();  
  libsPathsScrollArea->resize(elementW, elementH);
  elementH = libsPaths->size().height();
  libsPaths->resize(elementW-3, elementH);
  
  elementH = flagsScrollArea->size().height();
  flagsScrollArea->resize(elementW, elementH);
  elementH = flags->size().height();
  flags->resize(elementW-3, elementH);
  
  OKButtonW = OKButton->size().width();
  OKButtonH = OKButton->size().height();
  OKButtonX = width - (OKButtonW + 10);
  OKButtonY = height - (OKButtonH + 10);
  
  OKButton->move(OKButtonX, OKButtonY);
}

/*****************************************************************************!
 * Function : CreateGroupSection
 *****************************************************************************/
void
BuildTreeLineDialog::CreateGroupSection
(QLabel* &InNameLabel, QString InName,
 QStringList sl, QFrame* &InNameAreas, QScrollArea* &InScrollArea,
 int &InY)
{
  int                                   n, h, h2, y2;
  int                                   labelWidth, labelHeight, labelX;
  int                                   elementX, elementW;
  
  labelWidth = 150;
  labelHeight = 20;
  labelX = 10;

  elementX = labelWidth + labelX + 10;
  elementW = 120;
  
  InNameLabel      = new QLabel(InName + QString(" :"), this);
  InNameLabel->move(labelX, InY);
  InNameLabel->resize(labelWidth, labelHeight);
  InNameLabel->setFont(QFont("", 10, QFont::Bold));
  InNameLabel->setAlignment(Qt::AlignRight);

  n = sl.count();
  h = n * 20;
  h2 = h;
  if ( n == 0 ) {
    h = 20;
    h2 = 20;
  } else if ( n > 6 ) {
    h = 120;
  }
  
  InScrollArea = new QScrollArea(this);
  InScrollArea->move(elementX, InY);
  InScrollArea->resize(elementW, h+3);
  InScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  InNameAreas = new QFrame();
  InScrollArea->setWidget(InNameAreas);
  InNameAreas->resize(elementW, h2);

  y2 = 0;
  for ( int i = 0; i < n ; i++ ) {
    QLabel* l = new QLabel(sl[i], InNameAreas);
    l->move(5, y2);
    y2 += 20;
  }
  InY += h + 5;
}
