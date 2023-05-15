/*****************************************************************************
 * FILE NAME    : stat.h
 * DATE         : May 09 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _stat_h_
#define _stat_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stddef.h>
#include <sys/time.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Type : stat
 *****************************************************************************/
struct stat
{
  dev_t     st_dev;
  ino_t     st_ino;   
  mode_t    st_mode;  
  nlink_t   st_nlink;
  uid_t     st_uid;
  gid_t     st_gid;
  dev_t     st_rdev;
  off_t     st_size;
  time_t    st_atime;
  time_t    st_mtime;
  time_t    st_ctime; 
  blksize_t st_blksize;
  blkcnt_t  st_blocks;
};

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
int    chmod(const char *, mode_t);
int    fchmod(int, mode_t);
int    fstat(int, struct stat *);
int    lstat(const char *, struct stat *);
int    mkdir(const char *, mode_t);
int    mkfifo(const char *, mode_t);
int    mknod(const char *, mode_t, dev_t);
int    stat(const char *, struct stat *);
mode_t umask(mode_t);

#endif /* _stat_h_*/
