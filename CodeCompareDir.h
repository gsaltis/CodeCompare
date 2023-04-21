/*****************************************************************************
 * FILE NAME    : CodeCompareDir.h
 * DATE         : April 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codecomparedir_h_
#define _codecomparedir_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <dirent.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : CodeCompareDir
 *****************************************************************************/
class CodeCompareDir : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeCompareDir                (QString InDirectoryName);

 //! Destructor
 public :
  ~CodeCompareDir               ();

 //! Public Methods
 public :
  QStringList                   ReadDirectories();
  QStringList                   ReadFiles();
  
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
  QString                       directoryName;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codecomparedir_h_*/
