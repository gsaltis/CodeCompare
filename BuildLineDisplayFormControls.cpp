/*****************************************************************************
 * FILE NAME    : BuildLineDisplayFormControls.cpp
 * DATE         : April 07 2023
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
#include "BuildLineDisplayFormControls.h"
#include "trace.h"

/*****************************************************************************!
 * Function : BuildLineDisplayFormControls
 *****************************************************************************/
BuildLineDisplayFormControls::BuildLineDisplayFormControls
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShadow(QFrame::Sunken);
  setFrameShape(QFrame::Box);
  initialize();
}

/*****************************************************************************!
 * Function : ~BuildLineDisplayFormControls
 *****************************************************************************/
BuildLineDisplayFormControls::~BuildLineDisplayFormControls
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BuildLineDisplayFormControls::initialize()
{
  currentLine = 0;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BuildLineDisplayFormControls::CreateSubWindows()
{
  QPixmap                       previousIconPixmap(":/images/Left.png");
  QIcon                         previousIcon(previousIconPixmap);
  QLabel*                       label;
  QPixmap                       nextIconPixmap(":/images/Right.png");
  QIcon                         nextIcon(nextIconPixmap);
  QFont                         f("System", 11, QFont::Normal);
  
  previousButton = new QPushButton(this);
  previousButton->move(0, 0);
  previousButton->resize(30, 30);
  previousButton->setIcon(previousIcon);
  previousButton->setIconSize(QSize(26, 26));
  previousButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
  previousButton->setEnabled(false);

  nextButton = new QPushButton(this);
  nextButton->move(33, 0);
  nextButton->resize(30, 30);
  nextButton->setIcon(nextIcon);
  nextButton->setIconSize(QSize(26, 26));
  nextButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
  nextButton->setEnabled(false);

  currentLineLabel = new QLabel(this);
  currentLineLabel->move(70, 5);
  currentLineLabel->resize(40, 20);
  currentLineLabel->setText("000");
  currentLineLabel->setAlignment(Qt::AlignRight);
  currentLineLabel->setFont(f);
  
  label = new QLabel(this);
  label->move(112, 5);
  label->resize(6, 20);
  label->setText("/");
  label->setAlignment(Qt::AlignRight);
  label->setFont(f);

  lineCountLabel = new QLabel(this);
  lineCountLabel->move(120, 5);
  lineCountLabel->resize(40, 20);
  lineCountLabel->setText("000");
  lineCountLabel->setAlignment(Qt::AlignLeft);
  lineCountLabel->setFont(f);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BuildLineDisplayFormControls::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BuildLineDisplayFormControls::resizeEvent
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
 * Function : CreateConnections
 *****************************************************************************/
void
BuildLineDisplayFormControls::CreateConnections(void)
{
  connect(nextButton,
          SIGNAL(pressed()),
          this,
          SLOT(SlotNextButtonPushed()));
  connect(previousButton,
          SIGNAL(pressed()),
          this,
          SLOT(SlotPreviousButtonPushed()));
}

/*****************************************************************************!
 * Function : SlotNextButtonPushed
 *****************************************************************************/
void
BuildLineDisplayFormControls::SlotNextButtonPushed(void)
{
  int                                   n;
  n = buildLines->GetLineCount();

  if ( currentLine + 1 >= n ) {
    return;
  }
  currentLine++;
  currentLineLabel->setText(QString("%1").arg(currentLine + 1));
  nextButton->setEnabled(currentLine + 1 < n);
  previousButton->setEnabled(currentLine > 0);
  emit SignalBuildLineSelected(buildLines->GetLineByIndex(currentLine));
}

/*****************************************************************************!
 * Function : SlotPreviousButtonPushed
 *****************************************************************************/
void
BuildLineDisplayFormControls::SlotPreviousButtonPushed(void)
{
  int                                   n;
  n = buildLines->GetLineCount();

  if ( currentLine == 0 ) {
    return;
  }
  currentLine--;
  currentLineLabel->setText(QString("%1").arg(currentLine + 1));
  previousButton->setEnabled(currentLine != 0);
  nextButton->setEnabled(currentLine + 1 < n);
  emit SignalBuildLineSelected(buildLines->GetLineByIndex(currentLine));
}

/*****************************************************************************!
 * Function : SlotBuildLinesSet
 *****************************************************************************/
void
BuildLineDisplayFormControls::SlotBuildLinesSet
(BuildLineSet* InLineSet)
{
  int                                   n;
  
  buildLines = InLineSet;

  n = buildLines->GetLineCount();
  currentLineLabel->setText(QString("%1").arg(1));
  lineCountLabel->setText(QString("%1").arg(n));
  currentLine = 0;
  previousButton->setEnabled(false);
  nextButton->setEnabled(n > 0);
  emit SignalBuildLineSelected(buildLines->GetLineByIndex(currentLine));
}
