/*****************************************************************************
 * FILE NAME    : setjmp.h
 * DATE         : May 09 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _setjmp_h_
#define _setjmp_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define _JBLEN 1
#define _JBTYPE int

/*****************************************************************************!
 * Exported Type
 *****************************************************************************/
typedef _JBTYPE jmp_buf[_JBLEN];

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
int                     setjmp                  (jmp_buf environment);
void                    longjmp                 (jmp_buf environment, int value);

#endif /* _setjmp_h_*/
