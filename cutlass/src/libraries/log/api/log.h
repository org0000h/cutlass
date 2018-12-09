/*
* log.h
*
*  Created on: 2017.10.19
*      Author: asia
*
*  API:  PRINT_LOG_ERR(format, ...)
		 PRINT_LOG_WARN(format, ...)
		 PRINT_LOG_INFO(format, ...)
*
*/

#ifndef TINY_LOG
#define TINY_LOG

#include "printf.h"
/*#define USE_SYSLOG*/

#ifdef USE_SYSLOG
#include <syslog.h>
#endif

/* log level for printing */
#define LOG_LEVEL INFO

/*log level*/
#define	INFO 0
#define	WARN 1
#define	ERR  2
#define NONE 3

extern const char *LEVEL_STRING[];


#define _SYSLOG_LOG(level, format, ...)  syslog(level,"%4s[ %s() %s: %d]:  "format"\n",\
             LEVEL_STRING[level],  __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)

/* for MCU*/
#define print printf
#define _PRINT_LOG(level,format, ...)   print("%4s[%s(): %d]: "format"\n",\
        LEVEL_STRING[level],__FUNCTION__, __LINE__,  ##__VA_ARGS__)



/*  */

#if (LOG_LEVEL <= INFO)
#ifdef USE_SYSLOG
#define PRINT_LOG_INFO(format, ...)     _SYSLOG_LOG(INFO,format,  ##__VA_ARGS__)
#else
#define PRINT_LOG_INFO(format, ...)  _PRINT_LOG(INFO,format,  ##__VA_ARGS__)
#endif
#else
#define PRINT_LOG_INFO(format, ...)  ((void)0)
#endif

#if (LOG_LEVEL <= WARN )
#ifdef USE_SYSLOG
#define PRINT_LOG_WARN(format, ...)     _SYSLOG_LOG(WARN,format,  ##__VA_ARGS__)
#else
#define PRINT_LOG_WARN(format, ...)     _PRINT_LOG(WARN,format,  ##__VA_ARGS__)
#endif
#else
#define PRINT_LOG_WARN(format, ...)    ((void)0)
#endif

#if (LOG_LEVEL <= ERR )
#ifdef USE_SYSLOG
#define PRINT_LOG_ERR(format, ...)      _SYSLOG_LOG(ERR,format,  ##__VA_ARGS__)
#else
#define PRINT_LOG_ERR(format, ...)      _PRINT_LOG(ERR,format,  ##__VA_ARGS__)
#endif
#else
#define PRINT_LOG_ERR(format, ...)     ((void)0)
#endif


//void conectRsyslog(void);
//
//void DisconectRsyslog(void);

#endif /* MYWORK_MYLOG_LOG_H_ */


