/*****************************************************************************
 * FILE NAME    : FileSectionDiff.h
 * DATE         : April 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _filesectiondiff_h_
#define _filesectiondiff_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : FileSectionDiff
 *****************************************************************************/
class FileSectionDiff
{
 //! Constructors
 public :
  FileSectionDiff               (QStringList InLines, int &InCurrentLine);

 //! Destructor
 public :
  ~FileSectionDiff              ();

 //! Public Types
  enum Type
  {
    None,
    Change,
    Delete,
    Add
  };
  
 //! Public Methods
 public :
  void                                  ParseLine               (QStringList InLines, int &InIndex);
  Type                                  GetType                 ();
  QString                               GetTypeString           ();
  int                                   GetLinesChangedCount    ();
  int                                   GetStartLine            ();
  int                                   GetEndLine              ();
  int                                   GetTargetStartLine      ();
  int                                   GetTargetEndLine        ();
  int                                   GetTargetLinesChangedCount  ();
  QStringList                           GetSourceChangeLines    ();
  QStringList                           GetTargetChangeLines    ();
  
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
  Type                                  type;
  QStringList                           sourceChangeLines;
  QStringList                           targetChangeLines;
  int                                   sourceStartLine;
  int                                   sourceEndLine;
  int                                   sourceLineCount;
  int                                   targetStartLine;
  int                                   targetEndLine;
  int                                   targetLineCount;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _filesectiondiff_h_*/
