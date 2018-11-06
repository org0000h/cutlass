/*
* log.h
*
*  Created on: 2017.10.19
*      Author: asia
*
*  API:  LOG_ERR(format, ...)
		 LOG_WARN(format, ...)
		 LOG_INFO(format, ...)
*
*/

#ifndef TINY_LOG
#define TINY_LOG

#include<stdio.h>

/* log level for printing */
#define LOG_LEVEL INFO

/*#define USE_SYSLOG*/

/*log level*/
#define	INFO 0
#define	WARN 1
#define	ERR  2
#define NONE 3

extern const char *LEVEL_STRING[];


#define SYSLOG_LOG(level, format, ...)  syslog(level,"%4s[ %s() %s: %d]:  "format"\n",\
             LEVEL_STRING[level],  __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)

/* for MCU*/
#define print printf
#define NORM_LOG(level,format, ...)   print("%4s[%s() %s: %d]: "format"",\
        LEVEL_STRING[level],__FUNCTION__, __FILE__, __LINE__,  ##__VA_ARGS__)

/*  */
#ifdef USE_SYSLOG
#include <syslog.h>

#if (LOG_LEVEL <= INFO)
#define LOG_INFO_LN(format, ...)  SYSLOG_LOG(INFO,format"\n",  ##__VA_ARGS__)
#define LOG_INFO(format, ...)     SYSLOG_LOG(INFO,format,  ##__VA_ARGS__)
#else
#define LOG_INFO_LN(format, ...)  ((void)0)
#define LOG_INFO(format, ...)  ((void)0)
#endif

#if (LOG_LEVEL <= WARN )
#define LOG_WARN_LN(format, ...)  SYSLOG_LOG(WARN,format"\n",  ##__VA_ARGS__)
#define LOG_WARN(format, ...)     SYSLOG_LOG(WARN,format,  ##__VA_ARGS__)
#else
#define LOG_WARN_LN(format, ...)    ((void)0)
#define LOG_WARN(format, ...)    ((void)0)
#endif

#if (LOG_LEVEL <= ERR )
#define LOG_ERR_LN(format, ...)   SYSLOG_LOG(ERR,format"\n",  ##__VA_ARGS__)
#define LOG_ERR(format, ...)      SYSLOG_LOG(ERR,format,  ##__VA_ARGS__)
#else
#define LOG_ERR_LN(format, ...)     ((void)0)
#define LOG_ERR(format, ...)     ((void)0)
#endif


#else /*USE_SYSLOG*/
#if (LOG_LEVEL <= INFO)
#define LOG_INFO_LN(format, ...)  NORM_LOG(INFO,format"\n",  ##__VA_ARGS__)
#define LOG_INFO(format, ...)  NORM_LOG(INFO,format,  ##__VA_ARGS__)
#else
#define LOG_INFO_LN(format, ...) ((void)0)
#define LOG_INFO(format, ...) ((void)0)
#endif

#if (LOG_LEVEL <= WARN )
#define LOG_WARN_LN(format, ...)  NORM_LOG(WARN,format"\n",  ##__VA_ARGS__)
#define LOG_WARN(format, ...)     NORM_LOG(WARN,format,  ##__VA_ARGS__)
#else
#define LOG_WARN_LN(format, ...) ((void)0)
#define LOG_WARN(format, ...) ((void)0)
#endif

#if (LOG_LEVEL <= ERR )
#define LOG_ERR_LN(format, ...)   NORM_LOG(ERR,format"\n",  ##__VA_ARGS__)
#define LOG_ERR(format, ...)   NORM_LOG(ERR,format,  ##__VA_ARGS__)
#else
#define LOG_ERR_LN(format, ...)  ((void)0)
#define LOG_ERR(format, ...)  ((void)0)
#endif

#endif/* use syslog or not */

//#else /* Don't compile log to the program*/
//#define LOG_ERR(format, ...)  ((void)0)
//#define LOG_WARN(format, ...) ((void)0)
//#define LOG_INFO(format, ...) ((void)0)
//
//#endif /* log ON OFF switch */


//void conectRsyslog(void);
//
//void DisconectRsyslog(void);

#endif /* MYWORK_MYLOG_LOG_H_ */


