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
  SourceDifferencesItem         (QWidget* InParent, int InY, int InWidth, FileSectionDiff* InDiff);

 //! Destructor
 public :
  ~SourceDifferencesItem        ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QLabel*                       TypeNameLabel;
  QLabel*                       LineNumbersLabel;
  QLabel*                       DifferenceLineLabel;
  FileSectionDiff*              diff;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _sourcedifferencesitem_h_*/
