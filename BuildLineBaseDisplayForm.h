/*****************************************************************************
 * FILE NAME    : BuildLineBaseDisplayForm.h
 * DATE         : April 06 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _buildlinebasedisplayform_h_
#define _buildlinebasedisplayform_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BUILD_LINE_BASE_DISPLAY_FORM_X  200
#define BUILD_LINE_BASE_DISPLAY_FORM_Y  200
#define BUILD_LINE_BASE_DISPLAY_FORM_WIDTH 200
#define BUILD_LINE_BASE_DISPLAY_FORM_HEIGHT 200

/*****************************************************************************!
 * Exported Class : BuildLineBaseDisplayForm
 *****************************************************************************/
class BuildLineBaseDisplayForm : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  BuildLineBaseDisplayForm      ();

 //! Destructor
 public :
  ~BuildLineBaseDisplayForm     ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void
  CreateGroupSection
  (QLabel* &InNameLabel, QString InName, QStringList sl, QFrame* &InNameAreas, QScrollArea* &InScrollArea, int &InY);

  void
  CreateLabel
  (QLabel* &InLabel, QLabel* &InTextLabel, QString InName, QString InNameText, int &InY);

  void
  CreateEditSection
  (QLabel* &InNameLabel, QString InName, QString InText, QTextEdit* &InTextEdit, int &InY);

  void
  initialize
  ();
  
 //! Protected Data
 protected :
  int                                   labelX;
  int                                   labelWidth;
  int                                   labelHeight;
  int                                   elementX;
  int                                   elementW;
  int                                   ySkip;

 //! Private Methods
 private :
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _buildlinebasedisplayform_h_*/
