/*****************************************************************************
 * FILE NAME    : CodeTrack.h
 * DATE         : May 01 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codetrack_h_
#define _codetrack_h_

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
 * Exported Class : CodeTrack
 *****************************************************************************/
class CodeTrack : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  CodeTrack                     (QString InBasePath);

 //! Destructor
 public :
  ~CodeTrack                    ();

 //! Public Methods
 public :
  QString                       GetBasePath             (void);
  void                          SetBasePath             (QString InBasePath);
  int                           GetBasePathLen          (void);
  bool                          PathBeginsWithBasePath  (QString InPath);
  QString                       RemoveLeadingBasePath   (QString InPath);

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
  QString                       basePath;
  int                           basePathLen;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _codetrack_h_*/
