/*****************************************************************************
 * FILE NAME    : trace_printf.h
 * DATE         : December 09 2021
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/
#ifndef _trace_printf_h_
#define _trace_printf_h_

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
#define TRACE_FUNCTION_START()                                                                  \
  {                                                                                             \
    struct timeval tv;                                                                          \
    struct tm* t2;                                                                              \
    time_t                              t;                                                      \
    int i;                                                                                      \
    QString                             f;                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("%c ", '|');                                                                       \
    }                                                                                           \
    printf("|_");                                                                               \
    gettimeofday(&tv, NULL);                                                                    \
    t = (time_t)tv.tv_sec;                                                                      \
    t2 = localtime(&t);                                                                         \
    f = QString(__FILE__) + QString(":") + QString(__FUNCTION__);                               \
    printf("ENTER : %*s : %04d %02d:%02d:%02d.%06d\n",                                          \
           TRACE_FUNCTION_NAME_LENGTH - TraceIndent,                                            \
           f.toStdString().c_str(),                                                             \
           __LINE__,                                                                            \
           (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec);                \
    fflush(stdout);                                                                             \
    TraceIndent += 2;                                                                           \
  }                                                                                             \

//!
#define TRACE_FUNCTION_LOCATION()                                                               \
  {                                                                                             \
    struct timeval tv;                                                                          \
    struct tm* t2;                                                                              \
    int i;                                                                                      \
    time_t                              t;                                                      \
    QString                             f;                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("|_");                                                                               \
    gettimeofday(&tv, NULL);                                                                    \
    t2 = localtime((time_t*)&(tv.tv_sec));                                                      \
    t = (time_t)tv.tv_sec;                                                                      \
    t2 = localtime(&t);                                                                         \
    f = QString(__FILE__) + QString(":") + QString(__FUNCTION__);                               \
    printf("LOCATION : %*s : %04d %02d:%02d:%02d.%06d\n",                                       \
           (TRACE_FUNCTION_NAME_LENGTH - 3) - TraceIndent,                                      \
           f.toStdString().c_str(),                                                             \
           __LINE__,                                                                            \
           (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec);                \
    fflush(stdout);                                                                             \
  }                                                                                             \
  
//!
#define TRACE_FUNCTION_QSIZE(n)                                                                 \
  {                                                                                             \
    struct timeval tv;                                                                          \
    struct tm* t2;                                                                              \
    int i;                                                                                      \
    time_t                              t;                                                      \
    QString                             f;                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("|_");                                                                               \
    gettimeofday(&tv, NULL);                                                                    \
    t2 = localtime((time_t*)&(tv.tv_sec));                                                      \
    t = (time_t)tv.tv_sec;                                                                      \
    t2 = localtime(&t);                                                                         \
    f = QString(__FILE__) + QString(":") + QString(__FUNCTION__);                               \
    printf("QSIZE : %*s : %04d %02d:%02d:%02d.%06d : %35s : width : %4d  height : %4d\n",       \
           (TRACE_FUNCTION_NAME_LENGTH - 2) - TraceIndent,                                      \
           f.toStdString().c_str(),                                                             \
           __LINE__,                                                                            \
           (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec,                 \
           #n, n.width(), n.height());                                                          \
    fflush(stdout);                                                                             \
  }                                                                                             \

//!
#define TRACE_FUNCTION_END()                                                                    \
  {                                                                                             \
    struct timeval tv;                                                                          \
    struct tm* t2;                                                                              \
    int i;                                                                                      \
    time_t                              t;                                                      \
    QString                             f;                                                      \
    for ( i = 0 ; i < TraceIndent-4 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("|_");                                                                               \
    gettimeofday(&tv, NULL);                                                                    \
    t = (time_t)tv.tv_sec;                                                                      \
    t2 = localtime(&t);                                                                         \
    f = QString(__FILE__) + QString(":") + QString(__FUNCTION__);                               \
    TraceIndent -= 2;                                                                           \
    printf("EXIT  : %*s : %04d %02d:%02d:%02d.%06d\n",                                          \
           TRACE_FUNCTION_NAME_LENGTH - TraceIndent,                                            \
           f.toStdString().c_str(),                                                             \
           __LINE__,                                                                            \
           (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec);                \
    fflush(stdout);                                                                             \
  }                                                                                             \

//!
#define TRACE_FUNCTION_END_VALUE_BOOL(b)                                                        \
  {                                                                                             \
    struct timeval tv;                                                                          \
    struct tm* t2;                                                                              \
    time_t                              t;                                                      \
    gettimeofday(&tv, NULL);                                                                    \
    t = (time_t)tv.tv_sec;                                                                      \
    t2 = localtime(&t);                                                                         \
    TraceIndent -= 2;                                                                           \
    printf("%*sEXIT  : %*s : %04d %02d:%02d:%02d.%06d -------- Return Value : %s\n",            \
           TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,  \
           (int)t2->tm_min, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, b ? "true" : "false"); \
    fflush(stdout);                                                                             \
    return b;                                                                                   \
  }                                                                                             \

//!
#define TRACE_FUNCTION_END_VALUE_INT(i)                                                         \
  {                                                                                             \
    struct timeval tv;                                                                          \
    struct tm* t2;                                                                              \
    time_t                              t;                                                      \
    gettimeofday(&tv, NULL);                                                                    \
    t = (time_t)tv.tv_sec;                                                                      \
    t2 = localtime(&t);                                                                         \
    TraceIndent -= 2;                                                                           \
    printf("%*SEXIT  : %*s : %04d %02d:%02d:%02d.%06d -------- Return Value : %d\n",            \
           TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,  \
           (int)t2->tm_min, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, i);              \
    fflush(stdout);                                                                             \
    return i;                                                                                   \
  }                                                                                             \

//!
#define TRACE_FUNCTION_END_VALUE_HEX(i)                                                         \
  {                                                                                             \
    struct timeval tv;                                                                          \
    struct tm* t2;                                                                              \
    time_t                              t;                                                      \
    gettimeofday(&tv, NULL);                                                                    \
    t = (time_t)tv.tv_sec;                                                                      \
    t2 = localtime(&t);                                                                         \
    TraceIndent -= 2;                                                                           \
    printf("%*sExit  : %*s : %04d %02d:%02d:%02d.%06d -------- Return Value : %p\n",            \
           TraceIndent, " ", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,  \
           (int)t2->tm_min, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, (void*)i);       \
    fflush(stdout);                                                                             \
    return i;                                                                                   \
  }                                                                                             \

//!
#define TRACE_FUNCTION_INT(n)                                                                   \
  {                                                                                             \
    int i;                                                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("|_");                                                                               \
    printf("VALUE : %*s : %04d   %35s : %d\n",                                                  \
           TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                    \
           #n, (int)n);                                                                         \
  }                                                                                             \

//!
#define TRACE_FUNCTION_FLOAT(n)                                                                 \
  {                                                                                             \
    int i;                                                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("|_");                                                                               \
    printf("VALUE : %*s : %04d   %35s : %.05f\n",                                               \
           TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                    \
           #n, (float)n);                                                                       \
  }                                                                                             \

//!
#define TRACE_FUNCTION_STRING(n)                                                                \
  {                                                                                             \
    int i;                                                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("  ");                                                                               \
    printf("VALUE : %*s : %04d   %35s : \"%s\"\n",                                              \
           TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                    \
           #n, n);                                                                              \
  }                                                                                             \

//!
#define TRACE_FUNCTION_QSTRING(n)                                                               \
  {                                                                                             \
    int i;                                                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("  ");                                                                               \
    printf("VALUE : %*s : %04d   %35s : \"%s\"\n",                                              \
           TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                    \
           #n, n.toStdString().c_str());                                                        \
  }                                                                                             \

//!
#define TRACE_FUNCTION_POINTER(n)                                                               \
  {                                                                                             \
    int i;                                                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("  ");                                                                               \
    printf("VALUE : %*s : %04d   %35s : %p\n",                                                  \
           TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                    \
           #n, n);                                                                              \
  }                                                                                             \

//!
#define TRACE_FUNCTION_STRINGN(n, m)                                                            \
  {                                                                                             \
    string s;                                                                                   \
    int i;                                                                                      \
    s = StringNCopy(n, m);                                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("  ");                                                                               \
    printf("Value : %*s : %04d   %35s : \"%s\"\n",                                              \
           TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                    \
           #n, s);                                                                              \
    FreeMemory(s);                                                                              \
  }                                                                                             \

//!
#define TRACE_FUNCTION_CHAR(n)                                                                  \
  {                                                                                             \
    int i;                                                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("|_");                                                                               \
    if ( isprint(n) ) {                                                                         \
      printf("VALUE : %*s : %04d   %35s : %c\n",                                                \
             TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                  \
             #n, n);                                                                            \
    } else {                                                                                    \
      printf("VALUE : %*s : %04d   %35s : 0x%02X\n",                                            \
             TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                  \
             #n, n);                                                                            \
    }                                                                                           \
  }                                                                                             \

//!
#define TRACE_FUNCTION_CHAR_HEX(n)                                                              \
  {                                                                                             \
    int i;                                                                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                \
      printf("| ");                                                                             \
    }                                                                                           \
    printf("|_");                                                                               \
    printf("VALUE : %*s : %04d   %35s : 0x%02X\n",                                              \
           TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                    \
           #n, n);                                                                              \
  }                                                                                             \

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _trace_printf_h_*/
