/*****************************************************************************
 * FILE NAME    : TUTree.cpp
 * DATE         : May 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QHeaderView>
#include <QTreeWidgetItem>
#include <sys/stat.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TUTree.h"
#include "trace.h"

/*****************************************************************************!
 * Function : TUTree
 *****************************************************************************/
TUTree::TUTree
(QString InFilename) : QTreeWidget()
{
  QPalette pal;
  filename = InFilename;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TUTree
 *****************************************************************************/
TUTree::~TUTree
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TUTree::initialize()
{
  QTreeWidgetItem*                              headerItem;
  QHeaderView*                                  headerView;

  InitializeSubWindows();  
  CreateSubWindows();
  setColumnCount(3);
  headerView = header();
  headerView->resizeSection(0, 300);
  headerView->resizeSection(1, 300);

  headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Name");
  headerItem->setText(1, "Value");
  headerItem->setText(2, "Compare");
  setHeaderItem(headerItem);
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TUTree::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TUTree::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TUTree::resizeEvent
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
 * Function : FindElementByNameType
 *****************************************************************************/
TUTreeElement*
TUTree::FindElementByNameType
(QString InName, TUTreeElement::TranslationUnitType InType)
{
  TUTreeElement*                        element;
  QString                               key =
    QString("%1.%2").arg(InName).arg(TUTreeElement::TranslationUnitTypeToString(InType));
  element = elements[key];
  return element;
}

/*****************************************************************************!
 * Function : GetFilename
 *****************************************************************************/
QString
TUTree::GetFilename(void)
{
  
  return filename;
}

/*****************************************************************************!
 * Function : SetFilename
 *****************************************************************************/
void
TUTree::SetFilename
(QString InFilename)
{  
  filename = InFilename;
}

/*****************************************************************************!
 * Function : GetFileSection
 *****************************************************************************/
QString
TUTree::GetFileSection
(int InBegin, int InEnd)
{
  FILE*                                 file;
  char*                                 buffer;
  struct stat                           st;
  const char*                           fname;
  char*                                 returnString;
  QString                               rString;
  int                                   bytesRead;
  int                                   n;
  
  TRACE_FUNCTION_START();
  TRACE_FUNCTION_INT(InBegin);
  TRACE_FUNCTION_INT(InEnd);
  fname = filename.toStdString().c_str();
  TRACE_FUNCTION_STRING(fname);

  file = fopen(fname, "rb");
  if ( NULL == file ) {
    TRACE_FUNCTION_END();
    return QString();
  }

  stat(fname, &st);
  TRACE_FUNCTION_INT(st.st_size);
  
  buffer = (char*)malloc(st.st_size + 1);
  if ( NULL == buffer ) {
    fclose(file);
    TRACE_FUNCTION_END();
    return QString();
  }

  bytesRead = fread(buffer, 1, st.st_size, file);
  TRACE_FUNCTION_INT(bytesRead);
  if ( bytesRead != st.st_size ) {
    fclose(file);
    free(buffer);
    TRACE_FUNCTION_END();
    return QString();
  }

  fclose(file);
  buffer[st.st_size] = 0x00;

  n = (InEnd - InBegin) + 1;
  TRACE_FUNCTION_INT(n);
  if ( n < 1 ) {
    free(buffer);
    TRACE_FUNCTION_END();
    return QString();
  }

  returnString = (char*)malloc(n + 1);
  if ( returnString == NULL ) {
    TRACE_FUNCTION_END();
    free(buffer);
    return QString();
  }

  memcpy(returnString, &(buffer[InBegin]), n);
  returnString[n] = 0x00;

  rString = QString(returnString);
  free(returnString);
  free(buffer);
  TRACE_FUNCTION_QSTRING(rString);
  TRACE_FUNCTION_END();
  return rString;
}

/*****************************************************************************!
 * Function : AddElement
 *****************************************************************************/
void
TUTree::AddElement
(TUTreeElement* InElement)
{
  addTopLevelItem(InElement);
  AddElementToElements(InElement);
}

/*****************************************************************************!
 * Function : AddElementToElements
 *****************************************************************************/
void
TUTree::AddElementToElements
(TUTreeElement* InElement)
{
  QString                               key =
    QString("%1.%2").arg(InElement->text(1)).arg(TUTreeElement::TranslationUnitTypeToString(InElement->GetTUType()));
  elements[key] = InElement;
}
