/*****************************************************************************
 * FILE NAME    : FileTreeDirectory.h
 * DATE         : April 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _filetreedirectory_h_
#define _filetreedirectory_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "FileTreeElement.h"
#include "FileTreeFile.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : FileTreeDirectory
 *****************************************************************************/
class FileTreeDirectory : public FileTreeElement , QList<FileTreeFile>
{
 //! Constructors
 public :
  FileTreeDirectory             (QString InAbsoluteFileName1, QString InAbsoluteFileName2,
                                 CodeTrack* InTrack1, CodeTrack* InTrack2);

 //! Destructor
 public :
  ~FileTreeDirectory            ();

 //! Public Methods
 public :
  void                 Read                             () override;
  int                  GetFileCount                     () override;
  QList<int>           GetChangeLinesCount              () override;

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

#endif /* _filetreedirectory_h_*/
