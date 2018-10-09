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

#include<stdio.h>



/* if define this ,then log will be turned on .
if not,the log code will not be compiled to the program. */
#define LOG_ON

/* log level for printing */
#define LOG_LEVEL INFO

/*#define USE_SYSLOG*/






/* ============usually shouldn't be changed by user down below=================== */

#ifdef LOG_ON

/*log level*/
#define ERR  0
#define WARN 1
#define INFO 2

#define SYSLOG_LOG_INFO(format, ...)  syslog(LOG_INFO,"%s[ %s() %s: %d]:  "format"\n",\
             "INFO",  __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)

#define SYSLOG_LOG_WARN(format, ...)  syslog(LOG_WARNING,"%s[ %s %s: %d]:  "format"\n",\
                "WARN",__FUNCTION__, __FILE__, __LINE__,  ##__VA_ARGS__)

#define SYSLOG_LOG_ERR(format, ...)  syslog(LOG_ERR,"%s[ %s %s: %d]:  "format"\n",\
			 "ERR",__FUNCTION__, __FILE__, __LINE__,  ##__VA_ARGS__)

/* for MCU*/
#define NORM_LOG_INFO(format, ...)   printf("%s[%s() %s: %d]: "format"\n",\
				"INFO",__FUNCTION__, __FILE__, __LINE__,  ##__VA_ARGS__)

#define NORM_LOG_WARN(format, ...)  printf("%s[%s() %s: %d]: "format"\n",\
				"WARN",__FUNCTION__, __FILE__, __LINE__,  ##__VA_ARGS__)

#define NORM_LOG_ERR(format, ...)     printf("%s[%s() %s: %d]: "format"\n",\
				"▲ERR", __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)

/*  */
#ifdef USE_SYSLOG
	#include <syslog.h>
	#if (LOG_LEVEL == INFO)
		#define PRINT_LOG_ERR(format, ...)   SYSLOG_LOG_ERR(format,  ##__VA_ARGS__)
		#define PRINT_LOG_WARN(format, ...)  SYSLOG_LOG_WARN(format,  ##__VA_ARGS__)
		#define PRINT_LOG_INFO(format, ...)  SYSLOG_LOG_INFO(format,  ##__VA_ARGS__)
	#elif (LOG_LEVEL == WARN )
		#define PRINT_LOG_ERR(format, ...)   SYSLOG_LOG_ERR(format,  ##__VA_ARGS__)
		#define PRINT_LOG_WARN(format, ...)  SYSLOG_LOG_WARN(format,  ##__VA_ARGS__)
		#define PRINT_LOG_INFO(format, ...)  ((void)0)
	#elif (LOG_LEVEL == ERR )
		#define PRINT_LOG_ERR(format, ...)   SYSLOG_LOG_ERR(format,  ##__VA_ARGS__)
		#define PRINT_LOG_WARN(format, ...)  ((void)0)
		#define PRINT_LOG_INFO(format, ...)  ((void)0)
    #endif
#else
	#if (LOG_LEVEL == INFO)
		#define PRINT_LOG_ERR(format, ...)   NORM_LOG_ERR(format,  ##__VA_ARGS__)
		#define PRINT_LOG_WARN(format, ...)  NORM_LOG_WARN(format,  ##__VA_ARGS__)
		#define PRINT_LOG_INFO(format, ...)  NORM_LOG_INFO(format,  ##__VA_ARGS__)
	#elif (LOG_LEVEL == WARN )
		#define PRINT_LOG_ERR(format, ...)   NORM_LOG_ERR(format,  ##__VA_ARGS__)
		#define PRINT_LOG_WARN(format, ...)  NORM_LOG_WARN(format,  ##__VA_ARGS__)
		#define PRINT_LOG_INFO(format, ...)  ((void)0)
	#elif (LOG_LEVEL == ERR )
		#define PRINT_LOG_ERR(format, ...)   NORM_LOG_ERR(format,  ##__VA_ARGS__)
		#define PRINT_LOG_WARN(format, ...)  ((void)0)
		#define PRINT_LOG_INFO(format, ...)  ((void)0)
	#endif
#endif/* use syslog or not */

#else /* Don't compile log to the program*/
	#define PRINT_LOG_ERR(format, ...)  ((void)0)
	#define PRINT_LOG_WARN(format, ...) ((void)0)
	#define PRINT_LOG_INFO(format, ...) ((void)0)

#endif /* log ON OFF switch */ 


void conectRsyslog(void);

void DisconectRsyslog(void);

#endif /* MYWORK_MYLOG_LOG_H_ */


