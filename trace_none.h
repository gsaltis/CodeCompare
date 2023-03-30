/*****************************************************************************
 * FILE NAME    : trace_none.h
 * DATE         : December 09 2021
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/
#ifndef _trace_none_h_
#define _trace_none_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TRACE_FUNCTION_START()
#define TRACE_FUNCTION_POINT()
#define TRACE_FUNCTION_END() 
#define TRACE_FUNCTION_END_VALUE_BOOL(b)
#define TRACE_FUNCTION_END_VALUE_INT(i)
#define TRACE_FUNCTION_END_VALUE_HEX(i)
#define TRACE_FUNCTION_INT(n)
#define TRACE_FUNCTION_STRING(n)
#define TRACE_FUNCTION_STRINGN(n, m)
#define TRACE_FUNCTION_CALLS(n)
#define TRACE_FUNCTION_HEX(n)

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _trace_none_h_*/
