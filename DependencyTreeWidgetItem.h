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
#include "BuildLineSet.h"
#include "BuildSystem.h"
#include "CodeTrack.h"

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
  DependencyTreeWidgetItem      (QStringList InNames, QFileInfo InInfo, BuildSystem* InBuildSystem,
                                 CodeTrack* InCodeTrack);

 //! Destructor
 public :
  ~DependencyTreeWidgetItem     ();

 //! Public Methods
 public :
  QFileInfo                     GetFileInfo             (void);
  void                          SetFileInfo             (QFileInfo InFileInfo);
  void                          ParseMakefileOutput     (QString InMakeOutput, QString InFullPath);
  void                          PerformMake             ();
  BuildLineSet*                 GetBuildLines           (void);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  BuildLine*                    ParseMakefileOutputLine (QString InOutputLine);

 //! Private Data
 private :
  BuildLineSet*                 buildLines;
  BuildSystem*                  buildSystem;
  QFileInfo                     fileInfo;
  QString                       buildString;
  CodeTrack*                    codeTrack;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _dependencytreewidgetitem_h_*/
