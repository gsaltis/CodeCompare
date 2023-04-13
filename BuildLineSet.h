/*****************************************************************************
 * FILE NAME    : BuildLineSet.h
 * DATE         : April 07 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildlineset_h_
#define _buildlineset_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : BuildLineSet
 *****************************************************************************/
class BuildLineSet : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLineSet                  ();

 //! Destructor
 public :
  ~BuildLineSet                 ();

 //! Public Methods
 public :
  int
  GetLineCount
  ();

  BuildLine*
  GetLineByIndex
  (int InIndex);

  void
  AppendLine
  (BuildLine* InLine);
  void                          Dump                    (void);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
  QList<BuildLine*>             lines;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildlineset_h_*/
