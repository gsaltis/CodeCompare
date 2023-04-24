/*****************************************************************************
 * FILE NAME    : FileContentsDiff.h
 * DATE         : April 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _filecontentsdiff_h_
#define _filecontentsdiff_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "FileSectionDiff.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : FileContentsDiff
 *****************************************************************************/
class FileContentsDiff : public QList<FileSectionDiff>
{
 //! Constructors
 public :
  FileContentsDiff              ();              

 //! Destructor
 public :
  ~FileContentsDiff             ();

 //! Public Methods
 public :
  void                          ParseLines              (QString InLines);
  QList<int>                    GetCounts               (void);
  
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

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _filecontentsdiff_h_*/
