/*****************************************************************************
 * FILE NAME    : unistd.h
 * DATE         : May 09 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _unistd_h_
#define _unistd_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stddef.h>
#include <stdlib.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define R_OK                            1

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/
extern char   *optarg;
extern int    optind, opterr, optopt;

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
int          access(const char *, int);
unsigned int alarm(unsigned int);
int          brk(void *);
int          chdir(const char *);
int          chroot(const char *);
int          chown(const char *, uid_t, gid_t);
int          close(int);
size_t       confstr(int, char *, size_t);
char        *crypt(const char *, const char *);
char        *ctermid(char *);
char        *cuserid(char *s);
int          dup(int);
int          dup2(int, int);
void         encrypt(char[64], int);
int          execl(const char *, const char *, ...);
int          execle(const char *, const char *, ...);
int          execlp(const char *, const char *, ...);
int          execv(const char *, char *const []);
int          execve(const char *, char *const [], char *const []);
int          execvp(const char *, char *const []);
void        _exit(int);
int          fchown(int, uid_t, gid_t);
int          fchdir(int);
int          fdatasync(int);
pid_t        fork(void);
long int     fpathconf(int, int);
int          fsync(int);
int          ftruncate(int, off_t);
char        *getcwd(char *, size_t);
int          getdtablesize(void);
gid_t        getegid(void);
uid_t        geteuid(void);
gid_t        getgid(void);
int          getgroups(int, gid_t []);
long         gethostid(void);
char        *getlogin(void);
int          getlogin_r(char *, size_t);
int          getopt(int, char * const [], const char *);
int          getpagesize(void);
char        *getpass(const char *);
pid_t        getpgid(pid_t);
pid_t        getpgrp(void);
pid_t        getpid(void);
pid_t        getppid(void);
pid_t        getsid(pid_t);
uid_t        getuid(void);
char        *getwd(char *);
int          isatty(int);
int          lchown(const char *, uid_t, gid_t);
int          link(const char *, const char *);
int          lockf(int, int, off_t);
off_t        lseek(int, off_t, int);
int          nice(int);
long int     pathconf(const char *, int);
int          pause(void);
int          pipe(int [2]);
size_t       pread(int, void *, size_t, off_t);
int          pthread_atfork(void (*)(void), void (*)(void), void(*)(void));
size_t       pwrite(int, const void *, size_t, off_t);
size_t       read(int, void *, size_t);
int          readlink(const char *, char *, size_t);
int          rmdir(const char *);
void        *sbrk(intptr_t);
int          setgid(gid_t);
int          setpgid(pid_t, pid_t);
pid_t        setpgrp(void);
int          setregid(gid_t, gid_t);
int          setreuid(uid_t, uid_t);
pid_t        setsid(void);
int          setuid(uid_t);
unsigned int sleep(unsigned int);
void         swab(const void *, void *, size_t);
int          symlink(const char *, const char *);
void         sync(void);
long int     sysconf(int);
pid_t        tcgetpgrp(int);
int          tcsetpgrp(int, pid_t);
int          truncate(const char *, off_t);
char        *ttyname(int);
int          ttyname_r(int, char *, size_t);
useconds_t   ualarm(useconds_t, useconds_t);
int          unlink(const char *);
int          usleep(useconds_t);
pid_t        vfork(void);
size_t       write(int, const void *, size_t);

#endif /* _unistd_h_*/
