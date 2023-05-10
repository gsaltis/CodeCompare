/*****************************************************************************
 * FILE NAME    : stdlib.h
 * DATE         : May 09 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _stdlib_h_
#define _stdlib_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stddef.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define NULL                    (void*)0
#define EXIT_FAILURE            1
#define EXIT_SUCCESS            0
#define RAND_MAX                2147483647
#define MB_CUR_MAX              2

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/
typedef unsigned int                    size_t;
typedef struct
  {
    int quot;                   /* Quotient.  */
    int rem;                    /* Remainder.  */
  } div_t;

typedef struct
  {
    long int quot;              /* Quotient.  */
    long int rem;               /* Remainder.  */
  } ldiv_t;

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
double                  atof                    (const char* str);
int                     atoi                    (const char* str);
long int                atol                    (const char* str);
double                  strtod                  (const char* str, char* *endptr);
long int                strtol                  (const char* str, char* *endptr, int base);
unsigned long int       strtoul                 (const char* str, char* *endptr, int base);
void*                   calloc                  (size_t nitems, size_t size);
void                    free                    (void* ptr);
void*                   malloc                  (size_t size);
void*                   realloc                 (void* ptr, size_t size);
void                    abort                   (void);
int                     atexit                  (void (*func)(void));
void                    exit                    (int status);
void                    _exit                   (int status);
char*                   getenv                  (const char* name);
int                     system                  (const char* string);
void*                   bsearch                 (const void* key, const void* base, size_t nitems, size_t size, int (*compar)(const void* , const void* ));
void                    qsort                   (void* base, size_t nitems, size_t size, int (*compar)(const void* , const void*));
int                     abs                     (int x);
div_t                   div                     (int numer, int denom);
long int                labs                    (long int x);
ldiv_t                  ldiv                    (long int numer, long int denom);
int                     rand                    (void);
void                    srand                   (unsigned int seed);
int                     mblen                   (const char* str, size_t n);
size_t                  mbstowcs                (wchar_t* pwcs, const char* str, size_t n);
int                     mbtowc                  (wchar_t* pwc, const char* str, size_t n);
size_t                  wcstombs                (char* str, const wchar_t* pwcs, size_t n);
int                     wctomb                  (char* str, wchar_t wchar);
char*                   getenv                  (const char* name);
int                     putenv                  (char* string);

#endif /* _stdlib_h_*/
