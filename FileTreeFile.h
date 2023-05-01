/*****************************************************************************
 * FILE NAME    : FileTreeFile.h
 * DATE         : April 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _filetreefile_h_
#define _filetreefile_h_

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

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : FileTreeFile
 *****************************************************************************/
class FileTreeFile : public FileTreeElement
{
 //! Constructors
 public :
  FileTreeFile                  (QString InAbsoluteFileName1, QString InAbsoluteFileName2,
                                 CodeTrack* InTrack1, CodeTrack* InTrack2);

 //! Destructor
 public :
  ~FileTreeFile                 ();

 //! Public Methods
 public :
  void                          Read                    () override;
  int                           GetFileCount            () override;
  QList<int>                    GetChangeLinesCount     () override;
  bool                          GetIsSourceFile         ();
  FileContentsDiff              GetDiffs                ();
  QStringList                   GetFileLines1           ();
  QStringList                   GetFileLines2           ();
  bool                          GetFilesDiffer          ();
  bool                          GetFilesHaveBeenRead    ();
  void                          SetFilesDiffer          (bool InFilesDiffer);
  void                          DiffFiles               ();
  void                          Initialize              ();
  QStringList                   GetFileLines1Section    (int InStartLine, int InEndLine);
  QStringList                   GetFileLines2Section    (int InStartLine, int InEndLine);
  QStringList                   GetFileLinesSection    (QStringList InLines, int InStartLine, int InEndLine);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  bool
  ReadFileContents
  (QString InFilename, QStringList& InFileLines);

 //! Private Data
 private :
  bool                          IsSourceFile;
  FileContentsDiff              Diffs;
  QStringList                   FileLines1;
  QStringList                   FileLines2;
  bool                          FilesDiffer;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _filetreefile_h_*/
