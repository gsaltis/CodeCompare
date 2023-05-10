/*****************************************************************************
 * FILE NAME    : stddef.h
 * DATE         : May 09 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _stddef_h_
#define _stddef_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdbool.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define IN
#define OUT

/*****************************************************************************!
 * Exported Types
 *****************************************************************************/
typedef unsigned long                   DWORD;
typedef void*                           HANDLE;
typedef unsigned char                   BYTE;
typedef unsigned char                   UINT8;
typedef unsigned short                  UINT16;
typedef unsigned long                   UINT32;
typedef signed long                     INT32;
typedef unsigned long                   ULONG;
typedef void*                           LPVOID;
typedef void                            VOID;
typedef void*                           PVOID;
typedef unsigned int                    UINT;
typedef unsigned char                   UCHAR;
typedef long int                        LONG;
typedef char                            CHAR;
typedef unsigned short                  wchar_t;
typedef unsigned int                    __pid_t;
typedef unsigned short                  wchar_t;
typedef unsigned int                    pid_t;
typedef unsigned int                    uid_t;
typedef unsigned int                    gid_t;
typedef unsigned long int               dev_t;
typedef unsigned long int               ino_t;
typedef unsigned int                    mode_t;
typedef unsigned int                    nlink_t;
typedef long int                        off_t;
typedef long int                        blksize_t;
typedef long int                        blkcnt_t;
typedef unsigned int                    uint;
typedef int*                            intptr_t;
typedef unsigned int                    useconds_t;

typedef BOOL (*ENUMSIGNALPROC)( int, float, LPVOID );

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _stddef_h_*/
