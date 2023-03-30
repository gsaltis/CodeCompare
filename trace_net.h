/*****************************************************************************
 * FILE NAME    : trace_net.h
 * DATE         : December 09 2021
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/
#ifndef _trace_net_h_
#define _trace_net_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/
#define TRACE_NET_ADDRESS                               "192.168.100.113"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TRACE_FUNCTION_START()                          \
  do                                                    \
  {                                                     \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);        \
    struct sockaddr_in                  servaddr;       \
    struct timeval                      tv;             \
    struct tm*                          t2;             \
    int                                 i;              \
    char*                               s;              \
    if ( sockfd < 0 ) {                                 \
      break;                                            \
    }                                                   \
    memset(&servaddr, 0, sizeof(servaddr));             \
    servaddr.sin_family = AF_INET;                      \
    servaddr.sin_port = htons(8080);                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                      \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);  \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;         \
    s = TraceOutputBuffer;                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                \
      sprintf(s, " |");                                         \
      s += 2;                                                   \
    }                                                           \
    sprintf(s, TraceIndent > 2 ? "__" : "  ");                  \
    s += 2;                                                     \
    gettimeofday(&tv, NULL);                                    \
    t2 = localtime(&(tv.tv_sec));                               \
    sprintf(s, "ENTER %*s : %06d %02d:%02d:%02d.%06d\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec); \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer), \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,            \
           sizeof(servaddr));                                           \
    TraceIndent += 2;                                                   \
    close(sockfd);                                                      \
    } while (false);
#define TRACE_FUNCTION_POINT()                          \
  do {                                                  \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);        \
    struct sockaddr_in                  servaddr;       \
    struct timeval                      tv;             \
    struct tm*                          t2;             \
    int                                 i;              \
    char*                               s2;             \
    if ( sockfd < 0 ) {                                 \
      break;                                            \
    }                                                   \
    memset(&servaddr, 0, sizeof(servaddr));             \
    servaddr.sin_family = AF_INET;                      \
    servaddr.sin_port = htons(8080);                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                      \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);  \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;         \
    s2 = TraceOutputBuffer;                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                \
      sprintf(s2, " |");                                         \
      s2 += 2;                                                   \
    }                                                           \
    sprintf(s2, TraceIndent > 2 ? "__" : "  ");                  \
    s2 += 2;                                                     \
    gettimeofday(&tv, NULL);                                    \
    t2 = localtime(&(tv.tv_sec));                               \
     sprintf(s2, "POINT %*s : %06d %02d:%02d:%02d.%06d\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec); \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer), \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,    \
           sizeof(servaddr));                                   \
    close(sockfd);                                                      \
  } while (false);

#define TRACE_FUNCTION_END()                            \
  do                                                    \
  {                                                     \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);        \
    struct sockaddr_in                  servaddr;       \
    struct timeval                      tv;             \
    struct tm*                          t2;             \
    int                                 i;              \
    char*                               s;              \
    if ( sockfd < 0 ) {                                 \
      break;                                            \
    }                                                   \
    memset(&servaddr, 0, sizeof(servaddr));             \
    servaddr.sin_family = AF_INET;                      \
    servaddr.sin_port = htons(8080);                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                      \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);  \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;         \
    TraceIndent -= 2;                                           \
    s = TraceOutputBuffer;                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                \
      sprintf(s, " |");                                         \
      s += 2;                                                   \
    }                                                           \
    sprintf(s, TraceIndent > 2 ? "__" : "  ");                  \
    s += 2;                                                     \
    gettimeofday(&tv, NULL);                                    \
    t2 = localtime(&(tv.tv_sec));                               \
    sprintf(s, "END   %*s : %06d %02d:%02d:%02d.%06d\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec); \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer), \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,            \
           sizeof(servaddr));                                           \
    close(sockfd);                                                      \
    } while (false);
#define TRACE_FUNCTION_END_VALUE_BOOL(b)
#define TRACE_FUNCTION_BOOL(b)                \
  do {                                                  \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);        \
    struct sockaddr_in                  servaddr;       \
    struct timeval                      tv;             \
    struct tm*                          t2;             \
    int                                 i;              \
    char*                               s2;             \
    if ( sockfd < 0 ) {                                 \
      break;                                            \
    }                                                   \
    memset(&servaddr, 0, sizeof(servaddr));             \
    servaddr.sin_family = AF_INET;                      \
    servaddr.sin_port = htons(8080);                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                      \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);  \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;         \
    s2 = TraceOutputBuffer;                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                \
      sprintf(s2, " |");                                         \
      s2 += 2;                                                   \
    }                                                           \
    sprintf(s2, TraceIndent > 2 ? "__" : "  ");                  \
    s2 += 2;                                                     \
    gettimeofday(&tv, NULL);                                    \
    t2 = localtime(&(tv.tv_sec));                               \
    sprintf(s2, "VALUE %*s : %06d %02d:%02d:%02d.%06d : %s : %s\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, #b, b ? "TRUE" : "FALSE"); \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer), \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,    \
           sizeof(servaddr));                                   \
    close(sockfd);                                                      \
  } while (false);
#define TRACE_FUNCTION_END_VALUE_INT(i)
#define TRACE_FUNCTION_END_VALUE_HEX(i)

//!
#define TRACE_FUNCTION_POINTER(n)                       \
  do {                                                  \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);        \
    struct sockaddr_in                  servaddr;       \
    struct timeval                      tv;             \
    struct tm*                          t2;             \
    int                                 i;              \
    char*                               s2;             \
    if ( sockfd < 0 ) {                                 \
      break;                                            \
    }                                                   \
    memset(&servaddr, 0, sizeof(servaddr));             \
    servaddr.sin_family = AF_INET;                      \
    servaddr.sin_port = htons(8080);                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                      \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);  \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;         \
    s2 = TraceOutputBuffer;                                      \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                \
      sprintf(s2, " |");                                         \
      s2 += 2;                                                   \
    }                                                           \
    sprintf(s2, TraceIndent > 2 ? "__" : "  ");                  \
    s2 += 2;                                                     \
    gettimeofday(&tv, NULL);                                    \
    t2 = localtime(&(tv.tv_sec));                               \
    sprintf(s2, "POINTER %*s : %06d %02d:%02d:%02d.%06d : %s : %p\n", (TRACE_FUNCTION_NAME_LENGTH - 2) - TraceIndent, __FUNCTION__, __LINE__, (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, #n, (int)n); \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer), \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,    \
           sizeof(servaddr));                                   \
    close(sockfd);                                                      \
  } while (false);

//!
#define TRACE_FUNCTION_INT(n)                                                                                                                           \
  do {                                                                                                                                                  \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);                                                                                                        \
    struct sockaddr_in                  servaddr;                                                                                                       \
    struct timeval                      tv;                                                                                                             \
    struct tm*                          t2;                                                                                                             \
    int                                 i;                                                                                                              \
    char*                               s2;                                                                                                             \
    if ( sockfd < 0 ) {                                                                                                                                 \
      break;                                                                                                                                            \
    }                                                                                                                                                   \
    memset(&servaddr, 0, sizeof(servaddr));                                                                                                             \
    servaddr.sin_family = AF_INET;                                                                                                                      \
    servaddr.sin_port = htons(8080);                                                                                                                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                                                                                            \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);                                                                                          \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;                                                                                                 \
    s2 = TraceOutputBuffer;                                                                                                                             \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                                                                        \
      sprintf(s2, " |");                                                                                                                                \
      s2 += 2;                                                                                                                                          \
    }                                                                                                                                                   \
    sprintf(s2, TraceIndent > 2 ? "__" : "  ");                                                                                                         \
    s2 += 2;                                                                                                                                            \
    gettimeofday(&tv, NULL);                                                                                                                            \
    t2 = localtime(&(tv.tv_sec));                                                                                                                       \
    sprintf(s2, "VALUE %*s : %06d %02d:%02d:%02d.%06d : %s : 0x%08X %d\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,            \
            (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, #n, (int)n, (int)n);                                                   \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer),                                                                          \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,                                                                                            \
           sizeof(servaddr));                                                                                                                           \
    close(sockfd);                                                                                                                                      \
  } while (false);

//!
#define TRACE_FUNCTION_CHAR(n)                                                                                                                          \
  do {                                                                                                                                                  \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);                                                                                                        \
    struct sockaddr_in                  servaddr;                                                                                                       \
    struct timeval                      tv;                                                                                                             \
    struct tm*                          t2;                                                                                                             \
    int                                 i;                                                                                                              \
    char*                               s2;                                                                                                             \
    if ( sockfd < 0 ) {                                                                                                                                 \
      break;                                                                                                                                            \
    }                                                                                                                                                   \
    memset(&servaddr, 0, sizeof(servaddr));                                                                                                             \
    servaddr.sin_family = AF_INET;                                                                                                                      \
    servaddr.sin_port = htons(8080);                                                                                                                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                                                                                            \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);                                                                                          \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;                                                                                                 \
    s2 = TraceOutputBuffer;                                                                                                                             \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                                                                        \
      sprintf(s2, " |");                                                                                                                                \
      s2 += 2;                                                                                                                                          \
    }                                                                                                                                                   \
    sprintf(s2, TraceIndent > 2 ? "__" : "  ");                                                                                                         \
    s2 += 2;                                                                                                                                            \
    gettimeofday(&tv, NULL);                                                                                                                            \
    t2 = localtime(&(tv.tv_sec));                                                                                                                       \
    if ( isprint(n) ) {                                                                                                                                 \
      sprintf(s2, "VALUE %*s : %06d %02d:%02d:%02d.%06d : %s : %c\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                 \
              (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, #n, n);                                                              \
    } else {                                                                                                                                            \
      sprintf(s2, "VALUE %*s : %06d %02d:%02d:%02d.%06d : %s : 0x%02x\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,             \
              (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, #n, n);                                                              \
    }                                                                                                                                                   \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer),                                                                          \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,                                                                                            \
           sizeof(servaddr));                                                                                                                           \
    close(sockfd);                                                                                                                                      \
  } while (false);                                                                                                                                      \

//!
#define TRACE_FUNCTION_CHAR_HEX(n)                                                                                                                      \
  do {                                                                                                                                                  \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);                                                                                                        \
    struct sockaddr_in                  servaddr;                                                                                                       \
    struct timeval                      tv;                                                                                                             \
    struct tm*                          t2;                                                                                                             \
    int                                 i;                                                                                                              \
    char*                               s2;                                                                                                             \
    if ( sockfd < 0 ) {                                                                                                                                 \
      break;                                                                                                                                            \
    }                                                                                                                                                   \
    memset(&servaddr, 0, sizeof(servaddr));                                                                                                             \
    servaddr.sin_family = AF_INET;                                                                                                                      \
    servaddr.sin_port = htons(8080);                                                                                                                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                                                                                            \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);                                                                                          \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;                                                                                                 \
    s2 = TraceOutputBuffer;                                                                                                                             \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                                                                        \
      sprintf(s2, " |");                                                                                                                                \
      s2 += 2;                                                                                                                                          \
    }                                                                                                                                                   \
    sprintf(s2, TraceIndent > 2 ? "__" : "  ");                                                                                                         \
    s2 += 2;                                                                                                                                            \
    gettimeofday(&tv, NULL);                                                                                                                            \
    t2 = localtime(&(tv.tv_sec));                                                                                                                       \
    sprintf(s2, "VALUE %*s : %06d %02d:%02d:%02d.%06d : %s : 0x%02X\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,               \
            (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, #n, n);                                                                \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer),                                                                          \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,                                                                                            \
           sizeof(servaddr));                                                                                                                           \
    close(sockfd);                                                                                                                                      \
  } while (false);                                                                                                                                      \

//!
#define TRACE_FUNCTION_STRING(q)                                                                                                                        \
  do {                                                                                                                                                  \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);                                                                                                        \
    struct sockaddr_in                  servaddr;                                                                                                       \
    struct timeval                      tv;                                                                                                             \
    struct tm*                          t2;                                                                                                             \
    int                                 i;                                                                                                              \
    char*                               s2;                                                                                                             \
    if ( sockfd < 0 ) {                                                                                                                                 \
      break;                                                                                                                                            \
    }                                                                                                                                                   \
    memset(&servaddr, 0, sizeof(servaddr));                                                                                                             \
    servaddr.sin_family = AF_INET;                                                                                                                      \
    servaddr.sin_port = htons(8080);                                                                                                                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                                                                                            \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);                                                                                          \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;                                                                                                 \
    s2 = TraceOutputBuffer;                                                                                                                             \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                                                                        \
      sprintf(s2, " |");                                                                                                                                \
      s2 += 2;                                                                                                                                          \
    }                                                                                                                                                   \
    sprintf(s2, TraceIndent > 2 ? "__" : "  ");                                                                                                         \
    s2 += 2;                                                                                                                                            \
    gettimeofday(&tv, NULL);                                                                                                                            \
    t2 = localtime(&(tv.tv_sec));                                                                                                                       \
    sprintf(s2, "VALUE %*s : %06d %02d:%02d:%02d.%06d : %s : %s\n", TRACE_FUNCTION_NAME_LENGTH - TraceIndent, __FUNCTION__, __LINE__,                   \
            (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, #q, q);                                                                \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer),                                                                          \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,                                                                                            \
           sizeof(servaddr));                                                                                                                           \
    close(sockfd);                                                                                                                                      \
  } while (false);                                                                                                                                      \

//!
#define TRACE_FUNCTION_MESSAGE(q)                                                                                                                        \
  do {                                                                                                                                                  \
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);                                                                                                        \
    struct sockaddr_in                  servaddr;                                                                                                       \
    struct timeval                      tv;                                                                                                             \
    struct tm*                          t2;                                                                                                             \
    int                                 i;                                                                                                              \
    char*                               s2;                                                                                                             \
    if ( sockfd < 0 ) {                                                                                                                                 \
      break;                                                                                                                                            \
    }                                                                                                                                                   \
    memset(&servaddr, 0, sizeof(servaddr));                                                                                                             \
    servaddr.sin_family = AF_INET;                                                                                                                      \
    servaddr.sin_port = htons(8080);                                                                                                                    \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                                                                                            \
    memset(TraceOutputBuffer, 0x20, TRACE_OUTPUT_BUFFER_SIZE);                                                                                          \
    TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE] = 0x00;                                                                                                 \
    s2 = TraceOutputBuffer;                                                                                                                             \
    for ( i = 0 ; i < TraceIndent-2 ; i += 2 ) {                                                                                                        \
      sprintf(s2, " |");                                                                                                                                \
      s2 += 2;                                                                                                                                          \
    }                                                                                                                                                   \
    sprintf(s2, TraceIndent > 2 ? "__" : "  ");                                                                                                         \
    s2 += 2;                                                                                                                                            \
    gettimeofday(&tv, NULL);                                                                                                                            \
    t2 = localtime(&(tv.tv_sec));                                                                                                                       \
    sprintf(s2, "MESSAGE %*s : %06d %02d:%02d:%02d.%06d : %s\n", (TRACE_FUNCTION_NAME_LENGTH - 2) - TraceIndent, __FUNCTION__, __LINE__,                \
            (int)t2->tm_hour, (int)t2->tm_min, (int)t2->tm_sec, (int)tv.tv_usec, q);                                                                    \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer),                                                                          \
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,                                                                                            \
           sizeof(servaddr));                                                                                                                           \
    close(sockfd);                                                                                                                                      \
  } while (false);                                                                                                                                      \

#define TRACE_FUNCTION_CALLS(n)
#define TRACE_FUNCTION_HEX(n)
#define TRACE_FUNCTION_STRINGN(n, m)

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _trace_net_h_*/
