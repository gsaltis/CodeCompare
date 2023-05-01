/*****************************************************************************
 * FILE NAME    : SourceDifferencesItem.h
 * DATE         : April 25 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sourcedifferencesitem_h_
#define _sourcedifferencesitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "FileSectionDiff.h"
#include "FileTreeFile.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SOURCE_DIFFERENCES_ITEM_X       0
#define SOURCE_DIFFERENCES_ITEM_Y       0
#define SOURCE_DIFFERENCES_ITEM_WIDTH   200
#define SOURCE_DIFFERENCES_ITEM_HEIGHT  20

/*****************************************************************************!
 * Exported Class : SourceDifferencesItem
 *****************************************************************************/
class SourceDifferencesItem : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SourceDifferencesItem         (FileTreeFile* InFileItem, QWidget* InParent, int InY, int InWidth, FileSectionDiff* InDiff);

 //! Destructor
 public :
  ~SourceDifferencesItem        ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          mousePressEvent         (QMouseEvent* InEvent);
  
 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateSourceLines       (QStringList InLines, int &InY, QColor InColor);

 //! Private Data
 private :
  QLabel*                       TypeNameLabel;
  QLabel*                       LineNumbers1Label;
  QLabel*                       LineNumbers2Label;
  QList<QLabel*>                DifferenceLineLabels;
  FileSectionDiff*              diff;
  FileTreeFile*                 fileItem;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :
  void                          SignalDifferenceSelected (FileSectionDiff* InDiff);

 //! Public Actions
 public :

};

#endif /* _sourcedifferencesitem_h_*/
