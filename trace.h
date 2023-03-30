/*****************************************************************************
 * FILE NAME    : trace.h
 * DATE         : April 09 2021
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/
#ifndef _trace_h_
#define _trace_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TRACE_OUTPUT_BUFFER_SIZE                2048
#define TRACE_FUNCTION_NAME_LENGTH              70

#ifdef TRACE_USE
#include "trace_printf.h"
#endif

#ifdef TRACE_FILE
#include "trace_file.h"
#endif

#ifdef TRACE_NET
#include "trace_net.h"
#endif

#ifndef TRACE_USE
#ifndef TRACE_FILE
#ifndef TRACE_NET
#include "trace_none.h"
#endif
#endif
#endif

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/
extern int
TraceIndent;

extern char*
TraceFileName;

extern char
TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE +1];

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
void
TraceInitializeFile
(void);

void
TraceInitializeNetwork
(void);

void
TraceOn
(void);

void
TraceOff
(void);

#endif /* _trace_h_*/
