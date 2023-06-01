/*****************************************************************************
 * FILE NAME    : SourceLine.h
 * DATE         : May 31 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sourceline_h_
#define _sourceline_h_

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
#define SOURCE_LINE_X                   200
#define SOURCE_LINE_Y                   200
#define SOURCE_LINE_WIDTH               200
#define SOURCE_LINE_HEIGHT              200

/*****************************************************************************!
 * Exported Class : SourceLine
 *****************************************************************************/
class SourceLine : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SourceLine                    (QString InFileName, QString InFullFileName);

 //! Destructor
 public :
  ~SourceLine                   ();

 //! Public Methods
 public :
  QString                       GetSourceFileName       (void);
  QString                       GetFullSourceFileName   (void);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                                  Initialize              ();

 //! Private Data
 private :
  QString                               SourceFileName;
  QString                               SourceFullFileName;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _sourceline_h_*/
