  /* Client code in C */

#if 1
#define _main main
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>

//#define LWIP
#ifdef LWIP
#include "sockets.h"
#endif
#include "net_tcp.h"


int _main(int argc,char **argv){

		#define RECV_BUFFER_LEN 40000 // you have to make it big enough to receive the whole data from server
		char *send_data = "GET / HTTP/1.1\r\n\r\n";
		int socket_fd = -1;
    
		char recv_buf[RECV_BUFFER_LEN] = {0};
		int32_t nread = 0;
		RESULT res = 0;
		if(argc < 2){
			printf("wrong parameter,type for example: \r\n./sc www.baidu.com 80\r\n");
			return -1;
		}
		if(FAILED == Tcp_SetupConnectionRetyrSync(&socket_fd, argv[1], argv[2],atoi(argv[3]),atoi(argv[4]))){
			return -1;
		}

		if(FAILED == Tcp_WriteWithSelect(socket_fd,send_data,strlen(send_data),100)){
			return -1;
		}

		if(FAILED == Tcp_ReadWithSelect(socket_fd, recv_buf, RECV_BUFFER_LEN, 20000, 1000)){
			return -1;
		}

		shutdown(socket_fd, SHUT_RDWR);
		close(socket_fd);
		return 0;
}


