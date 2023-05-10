/*****************************************************************************
 * FILE NAME    : siginfo.h
 * DATE         : May 09 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _siginfo_h_
#define _siginfo_h_

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
#define __ARCH_SI_PREAMBLE_SIZE (3 * sizeof(int))
#define SI_MAX_SIZE     128
#define SI_PAD_SIZE     ((SI_MAX_SIZE - __ARCH_SI_PREAMBLE_SIZE) / sizeof(int))

/*****************************************************************************!
 * Exported Type : sigval
 *****************************************************************************/
typedef union sigval
{
  int sival_int;
  void *sival_ptr;
} sigval_t;

/*****************************************************************************!
 * Exported Type : siginfo
 *****************************************************************************/
typedef struct siginfo
{
  int si_signo;               /* Signal number.  */
  int si_errno;               /* If non-zero, an errno value associated with
                                 this signal, as defined in <errno.h>.  */
  int si_code;                /* Signal code.  */
  int si_addr;
  union
  {
    int _pad[SI_PAD_SIZE];

    /* kill().  */
    struct
    {
      __pid_t si_pid;     /* Sending process ID.  */
      __uid_t si_uid;     /* Real user ID of sending process.  */
    } _kill;

    /* POSIX.1b timers.  */
    struct
    {
      int si_tid;         /* Timer ID.  */
      int si_overrun;     /* Overrun count.  */
      sigval_t si_sigval; /* Signal value.  */
    } _timer;

    /* POSIX.1b signals.  */
    struct
    {
      __pid_t si_pid;     /* Sending process ID.  */
      __uid_t si_uid;     /* Real user ID of sending process.  */
      sigval_t si_sigval; /* Signal value.  */
    } _rt;

    /* SIGCHLD.  */
    struct
    {
      __pid_t si_pid;     /* Which child.  */
      __uid_t si_uid;     /* Real user ID of sending process.  */
      int si_status;      /* Exit value or signal.  */
      __clock_t si_utime;
      __clock_t si_stime;
    } _sigchld;

    /* SIGILL, SIGFPE, SIGSEGV, SIGBUS.  */
    struct
    {
      void *si_addr;      /* Faulting insn/memory ref.  */
    } _sigfault;

    /* SIGPOLL.  */
    struct
    {
      long int si_band;   /* Band event for SIGPOLL.  */
      int si_fd;
    } _sigpoll;
  } _sifields;
} siginfo_t;


/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _siginfo_h_*/
