/*****************************************************************************
 * FILE NAME    : DirectoryTreeElement.h
 * DATE         : March 30 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _directorytreeelement_h_
#define _directorytreeelement_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define DIRECTORY_TREE_ELEMENT_X        200
#define DIRECTORY_TREE_ELEMENT_Y        200
#define DIRECTORY_TREE_ELEMENT_WIDTH    200
#define DIRECTORY_TREE_ELEMENT_HEIGHT   200

/*****************************************************************************!
 * Exported Class : DirectoryTreeElement
 *****************************************************************************/
class DirectoryTreeElement : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  DirectoryTreeElement          (QFileInfo InFileInfo);

 //! Destructor
 public :
  ~DirectoryTreeElement         ();

 //! Public Methods
 public :
  void
  AddChild
  (class DirectoryTreeElement*  InChild);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QFileInfo                     fileInfo;
  QString                       makefileCommands;
  QList<DirectoryTreeElement*>  childElements;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _directorytreeelement_h_*/
