/*****************************************************************************
 * FILE NAME    : fcntl.h
 * DATE         : May 09 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _fcntl_h_
#define _fcntl_h_

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
#define F_DUPFD                1
#define F_GETFD                2
#define F_SETFD                3
#define F_GETFL                4
#define F_SETFL                5
#define F_GETLK                6
#define F_SETLK                7
#define F_SETLKW               8
#define F_GETOWN               9
#define F_SETOWN               10
#define FD_CLOEXEC             11
#define F_RDLCK                12
#define F_UNLCK                13
#define F_WRLCK                14

#define O_CREAT                 000000100
#define O_EXCL                  000000200
#define O_NOCTTY                000000400
#define O_TRUNC                 000001000

#define O_APPEND                000010000
#define O_DSYNC                 000020000
#define O_NONBLOCK              000400000
#define O_RSYNC                 001000000
#define O_SYNC                  002000000

#define O_ACCMODE               004000000

#define O_RDONLY                000000001
#define O_RDWR                  000000002
#define O_WRONLY                000000004

#define POSIX_FADV_NORMAL       1
#define POSIX_FADV_SEQUENTIAL   2
#define POSIX_FADV_RANDOM       3
#define POSIX_FADV_WILLNEED     4
#define POSIX_FADV_DONTNEED     5
#define POSIX_FADV_NOREUSE      6

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
int                     creat                   (const char *, mode_t);
int                     fcntl                   (int, int, ...);
int                     open                    (const char *, int, ...);

int                     posix_fadvise           (int, off_t, off_t, int);
int                     posix_fallocate         (int, off_t, off_t);

#endif /* _fcntl_h_*/
