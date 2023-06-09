/*****************************************************************************
 * FILE NAME    : trace.c
 * DATE         : April 09 2021
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/

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
#include "trace.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
int
TraceIndent = 2;

char*
TraceFileName = NULL;

bool
TraceState = false;

char
TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE +1];

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/

/*****************************************************************************!
 * 
 *****************************************************************************/
void
TraceInitializeFile
(void)
{
  FILE* f = fopen(TraceFileName, "wb");
  if ( NULL == f ) {
    return;
  }
  struct timeval tv;
  struct tm* t2;
  int i;
  for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {
    fprintf(f, "%c ", '|');
  }
  fprintf(f, " _");
  gettimeofday(&tv, NULL);
  t2 = localtime((time_t*)&(tv.tv_sec));
  fprintf(f, "Start : %*s : %04d %02d:%02d:%02d.%06d\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec);
  fclose(f);
}

/*****************************************************************************!
 * Function : TraceInitializeNetwork
 *****************************************************************************/
void
TraceInitializeNetwork
(void)
{

}

/*****************************************************************************!
 * 
 *****************************************************************************/
void
TraceOn
()
{
  TraceState = true;
}

/*****************************************************************************!
 * 
 *****************************************************************************/
void
TraceOff
()
{
  TraceState = false;
}


