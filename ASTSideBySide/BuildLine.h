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
#include <QString>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Imported Classes
 *****************************************************************************/
class FileTreeFile;

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

  enum Type {
    TypeNone,
    TypeCompile,
    TypeLN,
    TypeAR,
    TypeRanlib,
    TypeFor,
    TypeEcho,
    TypeUnknown
  };
  
//! Public Methods
 public :


  Type                                  GetType                 ();
  virtual void                          ParseLine               (QString InBuildLine) = 0;
  QString                               GetText                 (void);
  static QString                        GetTypeString           (BuildLine::Type InType);
  static QStringList                    GetLineElements         (QString InBuildLine);
  virtual void                          Dump                    (void);
  QString                               GetFilePath             (void);
  void                                  SetFilePath             (QString InFilePath);
  
 //! Public Data
 public :
  
 //! Protected Methods
 protected :

 //! Protected Data
 protected :
  Type                                  buildType;
  QString                               lineText;
  QString                               filePath;
  
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

#endif /* _buildline_h_*/
