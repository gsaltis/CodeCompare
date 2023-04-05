/*****************************************************************************
 * FILE NAME    : DependencyTreeWidgetItem.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _dependencytreewidgetitem_h_
#define _dependencytreewidgetitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QTreeWidgetItem>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : DependencyTreeWidgetItem
 *****************************************************************************/
class DependencyTreeWidgetItem : public QTreeWidgetItem
{
 //! Constructors
 public :
  DependencyTreeWidgetItem      (QStringList InNames, QFileInfo InInfo);

 //! Destructor
 public :
  ~DependencyTreeWidgetItem     ();

 //! Public Methods
 public :
  QFileInfo                     GetFileInfo             (void);
  void                          SetFileInfo             (QFileInfo InFileInfo);
  void                          ParseMakefileOutput     (QString InMakeOutput);
  void                          PerformMake             ();
  BuildLine*                    GetBuildLine            (void);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          ParseMakefileOutputLine (QString InOutputLine);

 //! Private Data
 private :
  QFileInfo                     fileInfo;
  BuildLine*                    buildLine;
  QString                       buildString;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _dependencytreewidgetitem_h_*/
