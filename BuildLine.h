/*****************************************************************************
 * FILE NAME    : BuildLine.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildline_h_
#define _buildline_h_

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
 * Exported Class : BuildLine
 *****************************************************************************/
class BuildLine : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLine                     ();

 //! Destructor
 public :
  ~BuildLine                    ();

 //! Public Methods
 public :
  void                          ParseLine               (QString InBuildLine);
  QString                       GetTarget               (void);
  QString                       GetAction               (void);
  QStringList                   GetSources              (void);
  QStringList                   GetIncludePaths         (void);
  QStringList                   GetLibraries            (void);
  QStringList                   GetLibraryPaths         (void);
  QStringList                   GetFlags                (void);
  
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
  QString                               action;
  QString                               target;
  QStringList                           sources;
  QStringList                           includePaths;
  QStringList                           flags;
  QStringList                           libs;
  QStringList                           libPaths;
  QString                               lineText;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildline_h_*/
