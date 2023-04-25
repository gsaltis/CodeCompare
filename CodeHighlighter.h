/*****************************************************************************
 * FILE NAME    : CodeHighlighter.h
 * DATE         : April 03 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _codehighlighter_h_
#define _codehighlighter_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

/*****************************************************************************!
 * Namespaces
 *****************************************************************************/
QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

/*****************************************************************************!
 * Exported Class :  CodeHighlighter
 *****************************************************************************/
class CodeHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

 //! Constructors
 public :
    CodeHighlighter(QTextDocument *parent = nullptr);

 //! Destructor
 public :

 //! Private Types
 private :
  struct HighlightingRule
  {
    QRegularExpression pattern;
    QTextCharFormat format;
  };
    
 //! Public Methods
 public :
  
 //! Public Data
 public :

 //! Protected Methods
 protected :
    void highlightBlock(const QString &text) override;

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
    QList<HighlightingRule> highlightingRules;
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;
    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :
};

#endif // _codehighlighter_h_
