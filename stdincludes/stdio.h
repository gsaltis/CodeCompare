/*****************************************************************************
*  FILE NAME    : stdio.h
*  DATE         : May 09 2023
*  COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
* ****************************************************************************/
#ifndef _stdio_h_
#define _stdio_h_

/*****************************************************************************!
*  Global Headers
* ****************************************************************************/
#include <stddef.h>
#include <stdarg.h>

/*****************************************************************************!
*  Local Headers
* ****************************************************************************/

/*****************************************************************************!
*  Exported Macros
* ****************************************************************************/
#define NULL                    (void*)0

/*****************************************************************************!
*  Exported Types
* ****************************************************************************/
typedef struct _FILE_
{
  int                           fd;
} FILE;
typedef unsigned int            fpos_t;

/*****************************************************************************!
*  Exported Data
* ****************************************************************************/

/*****************************************************************************!
*  Exported Functions
* ****************************************************************************/
int                     fclose                  (FILE* stream);
void                    clearerr                (FILE* stream);
int                     feof                    (FILE* stream);
int                     ferror                  (FILE* stream);
int                     fflush                  (FILE* stream);
int                     fgetpos                 (FILE* stream, fpos_t* pos);
FILE*                   fopen                   (const char* filename, const char* mode);
size_t                  fread                   (void* ptr, size_t size, size_t nmemb, FILE* stream);
FILE*                   freopen                 (const char* filename, const char* mode, FILE* stream);
int                     fseek                   (FILE* stream, long int offset, int whence);
int                     fsetpos                 (FILE* stream, const fpos_t* pos);
long                    int ftell               (FILE* stream);
size_t                  fwrite                  (const void* ptr, size_t size, size_t nmemb, FILE* stream);
int                     remove                  (const char* filename);
int                     rename                  (const char* old_filename, const char* new_filename);
void                    rewind                  (FILE* stream);
void                    setbuf                  (FILE* stream, char* buffer);
int                     setvbuf                 (FILE* stream, char* buffer, int mode, size_t size);
FILE*                   tmpfile                 (void);
char*                   tmpnam                  (char* str);
int                     fprintf                 (FILE* stream, const char* format, ...);
int                     printf                  (const char* format, ...);
int                     snprintf                (char*  s, size_t __maxlen, char*  format, ...);
int                     sprintf                 (char* str, const char* format, ...);
int                     vfprintf                (FILE* stream, const char* format, va_list arg);
int                     vprintf                 (const char* format, va_list arg);
int                     vsprintf                (char* str, const char* format, va_list arg);
int                     fscanf                  (FILE* stream, const char* format, ...);
int                     scanf                   (const char* format, ...);
int                     sscanf                  (const char* str, const char* format, ...);
int                     fgetc                   (FILE* stream);
char*                   fgets                   (char* str, int n, FILE* stream);
int                     fputc                   (int ochar, FILE* stream);
int                     fputs                   (const char* str, FILE* stream);
int                     getc                    (FILE* stream);
int                     getchar                 (void);
char*                   gets                    (char* str);
int                     putc                    (int ochar, FILE* stream);
int                     putchar                 (int ochar);
int                     puts                    (const char* str);
int                     ungetc                  (int ochar, FILE* stream);
void                    perror                  (const char* str);

#endif /* _stdio_h_*/
