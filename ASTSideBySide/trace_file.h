/*****************************************************************************
 * FILE NAME    : trace_file.h
 * DATE         : December 09 2021
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/
#ifndef _trace_file_h_
#define _trace_file_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TRACE_OUTPUT_BUFFER_SIZE                2048
#define TRACE_FUNCTION_NAME_LENGTH              60

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TRACE_FUNCTION_NAME_LENGTH              60
#define TRACE_FUNCTION_START()                  \
  {                                             \
    FILE* f = fopen(TraceFileName, "ab");\
    struct timeval tv;                          \
    struct tm* t2;                              \
    int i;                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {  \
      fprintf(f, "%c ", '|');                   \
    }                                           \
    fprintf(f, " _");                           \
    gettimeofday(&tv, NULL);                    \
    t2 = localtime(&(tv.tv_sec));               \
    fprintf(f, "Enter : %*s : %04d %02d:%02d:%02d.%06d\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec); \
    fclose(f);                                  \
    TraceIndent += 2;                           \
  }                                             \

#define TRACE_FUNCTION_POINT()                  \
  {                                             \
    FILE* f = fopen(TraceFileName, "ab");\
    struct timeval tv;                          \
    struct tm* t2;                              \
    int i;                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {  \
      fprintf(f, "| ");                         \
    }                                           \
    fprintf(f, "  ");                           \
    gettimeofday(&tv, NULL);                    \
    t2 = localtime(&(tv.tv_sec));               \
    fprintf(f, "POINT : %*s : %04d %02d:%02d:%02d.%06d\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec); \
    fclose(f);                                  \
  }                                             \

#define TRACE_FUNCTION_END()                    \
  {                                             \
    FILE* f = fopen(TraceFileName, "ab");\
    struct timeval tv;                          \
    struct tm* t2;                              \
    int i;                                      \
    for ( i = 0 ; i < TraceIndent-4 ; i += 2 ) {  \
      fprintf(f, "| ");                         \
    }                                           \
    fprintf(f, "|_");                           \
    gettimeofday(&tv, NULL);                    \
    t2 = localtime(&(tv.tv_sec));               \
    TraceIndent -= 2;                           \
    fprintf(f, "Exit  : %*s : %04d %02d:%02d:%02d.%06d\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec); \
    fclose(f);                                  \
  }                                             \

#define TRACE_FUNCTION_END_VALUE_BOOL(b)        \
  {                                             \
    FILE* f = fopen(TraceFileName, "ab");\
    struct timeval tv;                          \
    struct tm* t2;                              \
    gettimeofday(&tv, NULL);                    \
    t2 = localtime(&(tv.tv_sec));               \
    TraceIndent -= 2;                           \
    fprintf(f, "%*sExit  : %*s : %04d %02d:%02d:%02d.%06d -------- Return Value : %s\n", TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_min, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, b ? "true" : "false"); \
    fclose(f);                                  \
    return b;                                   \
  }                                             \

#define TRACE_FUNCTION_END_VALUE_INT(i)         \
  {                                             \
    FILE* f = fopen(TraceFileName, "ab");\
    struct timeval tv;                          \
    struct tm* t2;                              \
    gettimeofday(&tv, NULL);                    \
    t2 = localtime(&(tv.tv_sec));               \
    TraceIndent -= 2;                           \
    fprintf(f, "%*sExit  : %*s : %04d %02d:%02d:%02d.%06d -------- Return Value : %d\n", TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_min, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, i); \
    fclose(f);                                  \
    return i;                                   \
  }                                             \

#define TRACE_FUNCTION_END_VALUE_HEX(i)         \
  {                                             \
    FILE* f = fopen(TraceFileName, "ab");\
    struct timeval tv;                          \
    struct tm* t2;                              \
    gettimeofday(&tv, NULL);                    \
    t2 = localtime(&(tv.tv_sec));               \
    TraceIndent -= 2;                           \
    fprintf(f, "%*sExit  : %*s : %04d %02d:%02d:%02d.%06d -------- Return Value : %p\n", TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_min, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, (void*)i); \
    fflush(stdout);                             \
    fclose(f);                                  \
    return i;                                   \
  }                                             \

#define TRACE_FUNCTION_INT(n)                   \
  {\
    FILE* f = fopen(TraceFileName, "ab");\
    int i;                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {  \
      fprintf(f, "| ");                            \
    }                                           \
    fprintf(f, "  ");                                                    \
    fprintf(f, "Value : %*s : %04d   %35s : %d\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, #n, (int)n); \
    fclose(f);                                  \
  }\

#define TRACE_FUNCTION_STRING(n)                   \
  {\
    FILE* f = fopen(TraceFileName, "ab");\
    int i;                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {  \
      fprintf(f, "| ");                            \
    }                                           \
    fprintf(f, "  ");                                                    \
    fprintf(f,"Value : %*s : %04d   %35s : \"%s\"\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, #n, n); \
    fclose(f);                                  \
  }\

#define TRACE_FUNCTION_CALLS(n)                   \
  {\
    FILE* f = fopen(TraceFileName, "ab");\
    fprintf(f,"%*sCALLS : %*s : %04d   %35s : %s()\n", TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, #n, n); \
    fclose(f);                                  \
  }\

#define TRACE_FUNCTION_HEX(n)                   \
  {\
    FILE* f = fopen(TraceFileName, "ab");\
    fprintf(f,"%*sValue : %*s : %04d   %35s : %08x\n", TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, #n, n); \
    fclose(f);                                  \
  }\

#define TRACE_FUNCTION_CHAR(n)                  \
  {\
    FILE* f = fopen(TraceFileName, "ab");       \
    if ( isprint(n) ) {                         \
      fprintf(f,"%*sValue : %*s : %04d   %35s : %c\n", TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, #n, n); \
    } else {                                    \
      fprintf(f,"%*sValue : %*s : %04d   %35s : %02x\n", TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, #n, n); \
    }                                           \
    fclose(f);                                  \
  }\

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

#endif /* _trace_file_h_*/
