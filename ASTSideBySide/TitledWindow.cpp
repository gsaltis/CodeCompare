/*****************************************************************************
 * FILE NAME    : TitledWindow.cpp
 * DATE         : April 16 2023
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
#include "TitledWindow.h"
#include "trace.h"

/*****************************************************************************!
 * Function : TitledWindow
 *****************************************************************************/
TitledWindow::TitledWindow
(QWidget* InContainer, QString InText) : QFrame()
{
  QPalette pal;
  pal = palette();
  setObjectName("TitledWindow");
  setStyleSheet("#TitledWindow { border : solid 1px white; background : white }");
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  headerText = InText;
  container = InContainer;
  container->setParent(this);
  toolbar = NULL;
  initialize();
}

/*****************************************************************************!
 * Function : TitledWindow
 *****************************************************************************/
TitledWindow::TitledWindow
(QWidget* InContainer, QToolBar* InToolBar, QString InText) : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  headerText = InText;
  container = InContainer;
  container->setParent(this);
  toolbar = InToolBar;
  toolbar->setParent(this);
  initialize();
}

/*****************************************************************************!
 * Function : ~TitledWindow
 *****************************************************************************/
TitledWindow::~TitledWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TitledWindow::initialize()
{
  setFrameShadow(QFrame::Sunken);
  setFrameStyle(QFrame::Panel);
  setLineWidth(1);
  headerHeight = 20;
  headerAlignment = Qt::AlignTop;
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TitledWindow::CreateSubWindows()
{
  QPalette                              pal;
  header = new QWidget();
  header->setParent(this);

  headerBackground = QBrush(QColor(192, 192, 192));
  headerFont = QFont();

  pal = header->palette();
  pal.setBrush(QPalette::Window, headerBackground);
  header->setPalette(pal);
  header->setAutoFillBackground(true);
  
  //! Create label
  headerLabel = new QLabel();
  headerLabel->setParent(header);
  headerLabel->move(5, 0);
  headerLabel->resize(100, headerHeight);
  headerLabel->setText(headerText);
  headerLabel->setAlignment(Qt::AlignLeft);
  headerLabel->setFont(headerFont);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TitledWindow::InitializeSubWindows()
{
  header = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TitledWindow::resizeEvent
(QResizeEvent* InEvent)
{
  SetSize(InEvent->size());
}

/*****************************************************************************!
 * Function : SetHeaderText
 *****************************************************************************/
void
TitledWindow::SetHeaderText
(QString InText)
{
  headerLabel->setText(InText);
}

/*****************************************************************************!
 * Function : SetHeaderBackground
 *****************************************************************************/
void
TitledWindow::SetHeaderBackground
(QBrush InBackground)
{
  QPalette                              pal;

  pal = header->palette();
  pal.setBrush(QPalette::Window, InBackground);
  header->setPalette(pal);
  headerBackground = QBrush(InBackground);
}

/*****************************************************************************!
 * Function : SetHeaderFont
 *****************************************************************************/
void
TitledWindow::SetHeaderFont
(QFont InHeaderFont)
{
  headerLabel->setFont(InHeaderFont);
  headerFont = QFont(InHeaderFont);
}

/*****************************************************************************!
 * Function : SetHeaderAlignment
 *****************************************************************************/
void
TitledWindow::SetHeaderAlignment
(Qt::AlignmentFlag InHeaderAlignment)
{
  headerAlignment = InHeaderAlignment;
  SetSize(size());
}

/*****************************************************************************!
 * Function : SetSize
 *****************************************************************************/
void
TitledWindow::SetSize
(QSize InSize)
{
  int                                   headerY;
  int                                   containerH;
  int                                   containerY;
  int                                   width;
  int                                   height;
  int                                   toolbarH, toolbarW, toolbarX, toolbarY;

  height = InSize.height();
  width  = InSize.width();
  toolbarY = toolbarX = toolbarW = toolbarH = 0;
  if ( toolbar ) {
    toolbarH = toolbar->size().height();
    toolbarX = 23;
  }
  containerH = height - (headerHeight + toolbarH + (toolbar ? 1 : 0));
  headerY = 0 ;
  containerY = headerHeight;
  toolbarW = width - 2;
  
  if ( headerAlignment == Qt::AlignBottom ) {
    toolbarY = 0;
    containerY = toolbarH;
    headerY = height - headerHeight;
  }

  if ( container ) {
    container->resize(width, containerH);
    container->move(0, containerY);
    toolbarY = height - (toolbarH + 1);
  }

  if ( toolbar ) {
    toolbar->move(toolbarX, toolbarY);
    toolbar->resize(toolbarW, toolbarH);
  }
  
  header->resize(width, headerHeight);
  headerLabel->resize(width - (headerLabel->pos().x() * 2), header->size().height());
  header->move(0, headerY);
}

/*****************************************************************************!
 * Function : SetHeaderHeight
 *****************************************************************************/
void
TitledWindow::SetHeaderHeight
(int InHeaderHeight)
{
  headerHeight = InHeaderHeight;
  SetSize(size());
}

/*****************************************************************************!
 * Function : GetHeaderForeground
 *****************************************************************************/
QColor
TitledWindow::GetHeaderForeground(void)
{
  
  return headerForeground;
}

/*****************************************************************************!
 * Function : SetHeaderForeground
 *****************************************************************************/
void
TitledWindow::SetHeaderForeground
(QColor InHeaderForeground)
{
  QPalette                              pal;

  pal = headerLabel->palette();
  pal.setBrush(QPalette::WindowText, InHeaderForeground);
  headerLabel->setPalette(pal);
  headerForeground = QColor(InHeaderForeground);
}

/*****************************************************************************!
 * Function : SetContainer
 *****************************************************************************/
void
TitledWindow::SetContainer
(QWidget* InContainer)
{
  if ( container ) {
    container->hide();
    container->setParent(NULL);
  }
  container = InContainer;
  container->setParent(this);
  container->show();
  SetSize(size());
}
