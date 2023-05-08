/*****************************************************************************
 * FILE NAME    : BuildCompileLine.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildcompileline_h_
#define _buildcompileline_h_

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
#include "CodeTrack.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : BuildCompileLine
 *****************************************************************************/
class BuildCompileLine : public BuildLine
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildCompileLine                     ();

 //! Destructor
 public :
  ~BuildCompileLine                    ();

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
  bool                          GetIsTargetObject       (void);
  virtual void                  Dump                    (void);
  void                          BuildAST                (CodeTrack* InCodeTrack);
  

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
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildcompileline_h_*/
