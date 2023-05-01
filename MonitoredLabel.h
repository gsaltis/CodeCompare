/*****************************************************************************
 * FILE NAME    : MonitoredLabel.h
 * DATE         : May 01 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
 *****************************************************************************/
#ifndef _monitoredlabel_h_
#define _monitoredlabel_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QLabel>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define MONITORED_LABEL_X               200
#define MONITORED_LABEL_Y               200
#define MONITORED_LABEL_WIDTH           200
#define MONITORED_LABEL_HEIGHT          200

/*****************************************************************************!
 * Exported Class : MonitoredLabel
 *****************************************************************************/
class MonitoredLabel : public QLabel
{
  Q_OBJECT;

 //! Constructors
 public :
  MonitoredLabel                ();

 //! Destructor
 public :
  ~MonitoredLabel               ();

 //! Public Methods
 public :
  void                          setText                 (QString InText);

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

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :
  void                          SignalTextChanged       (QString InString);

 //! Public Actions
 public :

};

#endif /* _monitoredlabel_h_*/
