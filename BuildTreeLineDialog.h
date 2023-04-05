/*****************************************************************************
 * FILE NAME    : BuildTreeLineDialog.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildtreelinedialog_h_
#define _buildtreelinedialog_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BuildLine.h"
#include "BuildLineDisplayForm.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_TREE_LINE_DIALOG_WIDTH            500
#define BUILD_TREE_LINE_DIALOG_HEIGHT           600

/*****************************************************************************!
 * Exported Class : BuildTreeLineDialog
 *****************************************************************************/
class BuildTreeLineDialog : public QDialog
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildTreeLineDialog           (BuildLine* InBuildLine);

 //! Destructor
 public :
  ~BuildTreeLineDialog          ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              (void);
  void                          CreateConnections       (void);
  void                          CreateSubWindows        (void);
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateGroupSection      (QLabel* &InNameLabel, QString InName,
                                                         QStringList sl, QFrame* &InNameAreas, QScrollArea* &InScrollArea,
                                                         int &InY);

 //! Private Data
 private :
  QPushButton*                  OKButton;
  BuildLineDisplayForm*         form;
  BuildLine*                    buildLine;
  QLabel*                       actionNameLabel;
  QLabel*                       targetNameLabel;
  QLabel*                       sourcesNameLabel;
  QLabel*                       libsNameLabel;
  QLabel*                       includePathsNameLabel;
  QLabel*                       libPathsNameLabel;
  QLabel*                       flagsNameLabel;

  QLabel*                       actionLabel;
  QLabel*                       targetLabel;
  QFrame*                       sourcesNames;
  QFrame*                       libsNames;
  QFrame*                       includesPaths;
  QFrame*                       libsPaths;
  QFrame*                       flags;
  QScrollArea*                  sourcesNamesScrollArea;
  QScrollArea*                  libsNamesScrollArea;
  QScrollArea*                  includesPathsScrollArea;
  QScrollArea*                  libsPathsScrollArea;
  QScrollArea*                  flagsScrollArea;
  
 //! Public Slots
 public slots :
  void                          SlotOKButtonPressed     ();
  void                          SlotCancelButtonPressed ();

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildtreelinedialog_h_*/
