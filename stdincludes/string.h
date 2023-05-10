/*****************************************************************************
 * FILE NAME    : string.h
 * DATE         : May 09 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _string_h_
#define _string_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
void*           memchr          (const void* str, int c, size_t n);
int             memcmp          (const void* str1, const void* str2, size_t n);
void*           memcpy          (void* dest, const void* src, size_t n);
void*           memmove         (void* dest, const void* src, size_t n);
void*           memset          (void* str, int c, size_t n);
char*           strcat          (char* dest, const char* src);
char*           strncat         (char* dest, const char* src, size_t n);
char*           strchr          (const char* str, int c);
int             strcmp          (const char* str1, const char* str2);
int             strncmp         (const char* str1, const char* str2, size_t n);
int             strcoll         (const char* str1, const char* str2);
char*           strcpy          (char* dest, const char* src);
char*           strncpy         (char* dest, const char* src, size_t n);
size_t          strcspn         (const char* str1, const char* str2);
char*           strerror        (int errnum);
size_t          strlen          (const char* str);
char*           strpbrk         (const char* str1, const char* str2);
char*           strrchr         (const char* str, int c);
size_t          strspn          (const char* str1, const char* str2);
char*           strstr          (const char* haystack, const char* needle);
char*           strtok          (char* str, const char* delim);
size_t          strxfrm         (char* dest, const char* src, size_t n);

#endif /* _string_h_*/
