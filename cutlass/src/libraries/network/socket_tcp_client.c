  /* Client code in C */

#if 0
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
#include "socket_tcp_client.h"

#if 0
void exit(){
	vTaskDelete(NULL);
}
#endif

// you should to know how many bytes data you need to receive
// this function will return when it received the whole data or
//it received data as many bytes as the paramater  recv_buf_len you passed in
RESULT Tcp_ReadWithSelect(	const int socket_fd,
						  uint8_t* recv_buf,
					const uint32_t recv_buf_len,
					const int32_t want_recv_len,
					const uint32_t timeout_ms){

    fd_set read_fds;
    struct timeval timeout;
    int32_t data_left_len = want_recv_len;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec =(timeout_ms % 1000) * 1000;
    uint8_t *recv_buf_p = recv_buf;
    int size_recv , total_size = 0;
    int every_time_recv_size = 1280;
    while(1)// only if it is interrupted by signal, then redo
    {
		FD_ZERO(&read_fds);
		FD_SET(socket_fd, &read_fds);
        int Ret = select(socket_fd + 1, &read_fds, NULL, NULL, &timeout);
        if (Ret == 0)
        {
        /* Zero fds ready means we timed out */
            printf("recv select  timeout ...\n");

            goto end;
        }
        else if (Ret < 0)
        {
            perror("recv select");
            goto end;
        }
        else
        { // there is date to be read on tcp
        	//recv返回的条件有两种：

            //1. 收到超过data_left_len长度

            //2. 协议层接收到push字段为1的TCP报文，此时recv返回值为实际接收的数据长度

            if((size_recv =  recv(socket_fd ,  recv_buf_p, every_time_recv_size, 0) ) == -1)
            {
            	perror("recv");
                if (errno == EWOULDBLOCK || errno == EAGAIN)
                {
                    printf("recv timeout ...\n");
                    goto end;
                }
                else if (errno == EINTR)
                {
                    printf("recv interrupt by signal...\n");
                    continue;
                }
                else if (errno == ENOENT)
                {
                    printf("recv RST segement...\n");
                    goto end;
                }
                else
                {
                	goto end;
                }
            }
            else if (size_recv == 0)
            {
                printf("recv: peer closed .\r\n");
                if(total_size != 0){
                	printf("received, total_size = %d bytes\n", total_size);
                	printf("recv content:\r\n%s\r\n",recv_buf);
                	goto end;
                }
                goto end;
            }
            else
            {
            	data_left_len -= size_recv;
            	if(data_left_len > 0){
					total_size += size_recv;
					if(total_size + every_time_recv_size >= recv_buf_len){
						goto end;
					}
					recv_buf_p += size_recv;
					if(data_left_len < every_time_recv_size){
						every_time_recv_size = data_left_len;
					}
            		continue;
            	} else if(data_left_len < 0){
            		goto end;
            	} else if(data_left_len == 0){
					printf("received, total_size = %d bytes\n", total_size);
					printf("recv content:%s\r\n",recv_buf);
					return SUCCEED;

            	}
            }
        }
    }
end:
    printf("received, total_size = %d bytes\n", total_size);
	printf("recv content:%s\r\n",recv_buf);
	return FAILED;
}
RESULT Tcp_WriteWithSelect(const int socket_fd,
				const char *data_want_to_send,
				const int data_len_want_to_send,
				const uint32_t timeout_ms){
	int nbytes_copied_to_sending_buffer = 0;
	fd_set write_fds;
	struct timeval timeout = {0};

	timeout.tv_sec = timeout_ms / 1000;
	timeout.tv_usec = (timeout_ms % 1000) * 1000;

	FD_ZERO(&write_fds);
	FD_SET(socket_fd, &write_fds);
	int Ret = select(socket_fd + 1, NULL, &write_fds, NULL, &timeout);
	if (Ret == 0)
	{
	/* Zero fds ready means we timed out */
		printf("send select timeout ...\n");
		return FAILED;
	}
	else if (Ret < 0)
	{
		perror("send select");
		return FAILED;
	}
	else
	{ // there is space in sending buffer to be write on tcp
		//send 函数仅仅只是拷贝，send（）只拷贝，拷贝完就返回，不会等ACK。
		//此次send（）调用所触发的程序错误，可能会在本次返回，也可能在下次调用网络IO函数的时候被返回。
		// TCP协议本身是为了保证可靠传输,并不等于应用程序用tcp发送数据就一定是可靠的，必须要容错；
		nbytes_copied_to_sending_buffer = send(	socket_fd,
												data_want_to_send,
												strlen(data_want_to_send), 0);
		if(nbytes_copied_to_sending_buffer == -1){
			perror("error send failed");
			close(socket_fd);
			return FAILED;
		}else if(nbytes_copied_to_sending_buffer != strlen(data_want_to_send)){
		  printf("didn't copied all data to sending buffer!\n");
		  return FAILED;
		}
	}
	printf("client senddata:len=%d, context:%s\r\n",nbytes_copied_to_sending_buffer,data_want_to_send);
	return SUCCEED;
}

int isconnected(int sockfd, fd_set *rd, fd_set *wr)
{
    if (!FD_ISSET(sockfd, rd) && !FD_ISSET(sockfd, wr)) {
	return 0;
    }
    int err;
    socklen_t len = sizeof(err);
    if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &err, &len) < 0) {
	return 0;
    }
    errno = err;		/* in case we're not connected */
    return err == 0;
}
int connect_timeout(int sockfd, const struct sockaddr *addr,
                    socklen_t addrlen, struct timeval *timeout)
{
    int flags = fcntl( sockfd, F_GETFL, 0 );
    if (flags == -1) {
    	return -1;
    }
    if (fcntl( sockfd, F_SETFL, flags | O_NONBLOCK ) < 0) {
    	return -1;
    }

    int status = connect(sockfd, addr, addrlen);
    if (status == -1 && errno != EINPROGRESS) {
    	return -1;
    }
    if (status == 0) {
		if (fcntl(sockfd, F_SETFL, flags) <  0) {
			return -1;
		}
		return 1;
    }
    fd_set read_events;
    fd_set write_events;
    FD_ZERO(&read_events);
    FD_SET(sockfd, &read_events);
    write_events = read_events;
    int rc = select(sockfd + 1, &read_events, &write_events, NULL, timeout );
    if (rc < 0) {
    	return -1;
    } else if (rc == 0) {
    	return 0;
    }
    if (!isconnected(sockfd, &read_events, &write_events) )
    {
    	return -1;
    }
    if ( fcntl( sockfd, F_SETFL, flags ) < 0 ) {
    	return -1;
    }
    return 1;
}
static int ConnectRetrySync(	const int domain,
								const int type,
								const int protocol,
								const struct sockaddr *addr,
								const socklen_t alen,
								const int tcpHandshake_wait_time_ms,
								const int retry_times){
	if(!addr){
		return -1;
	}

	int numsec,fd;
	int retry_total = 1;
	int Exponent = 0;
	Exponent = (retry_times < 0) ? 0 : retry_times;
	Exponent = (retry_times > 10) ? 10 : retry_times;
	for (int i = 0; i < Exponent; i++){
		retry_total *= 2;
	}
	for(numsec = 1; numsec < retry_total; numsec <<= 1){
		if((fd = socket(domain,type,protocol)) < 0){
			return(-1);
		}
		printf("connecting ....\r\n");
		char *ips = inet_ntoa(((struct sockaddr_in *)addr)->sin_addr);
		printf("ip:%s\r\n",ips);

		struct timeval timeout = {0};

		timeout.tv_sec = tcpHandshake_wait_time_ms / 1000;
		timeout.tv_usec = (tcpHandshake_wait_time_ms % 1000) * 1000;

		if(connect_timeout(fd,addr,alen,&timeout) == 1){
			return fd;
		}
		perror("connect failed");
		close(fd);
		if(numsec < retry_total/2){
			sleep(numsec);
		}
	}
	return -1;
}

RESULT Tcp_SetupConnectionRetyrSync(	  int *socket_fd,
									const char *domain_name,
									const char *service_or_port,
									const int single_wait_time_ms,
									const int retry_times){
	struct addrinfo *ailist, *rp;
	struct addrinfo remote_ip_filter;
	/*
	*remote ip filter,if 0, doesn't filt item
	*/
	memset(&remote_ip_filter, 0, sizeof(struct addrinfo));
	remote_ip_filter.ai_flags = AI_CANONNAME;
	remote_ip_filter.ai_family = AF_INET;
	remote_ip_filter.ai_socktype = SOCK_STREAM;
	remote_ip_filter.ai_protocol = IPPROTO_TCP;
	remote_ip_filter.ai_addrlen = INET_ADDRSTRLEN;
	remote_ip_filter.ai_canonname = NULL;
	remote_ip_filter.ai_addr = NULL;
	remote_ip_filter.ai_next = NULL;
	if( 0 != getaddrinfo(domain_name,service_or_port,&remote_ip_filter,&ailist)){
		printf("get address failed\r\n");
		return FAILED;
	}

	for (rp = ailist; rp != NULL; rp = rp->ai_next) {
		*socket_fd = ConnectRetrySync(	rp->ai_family,
										rp->ai_socktype,
										rp->ai_protocol,
										rp->ai_addr,
										sizeof(struct sockaddr_in),
										single_wait_time_ms,
										retry_times);
		if(*socket_fd != -1){
			break;
		}
	}
	freeaddrinfo(ailist);           /* No longer needed */
	if (rp == NULL) {               /* No address succeeded */
		printf("Could not connect\n");
		*socket_fd = -1;
		return FAILED;
	} else {
		return SUCCEED;
	}
}
int main(int argc,char **argv){

		#define RECV_BUFFER_LEN 40000 // you have to make it big enough to receive the whole data from server
		char *send_data = "GET / HTTP/1.1\r\n\r\n";
		int socket_fd = -1;
		int len_of_copied_data_to_sending_buffer = 0;
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
//		printf("1\r\n");
//		sleep(2);
//		if(FAILED == Tcp_WriteWithSelect(socket_fd,send_data,strlen(send_data),100)){
//			printf("failed 3\r\n");
//					return -1;
//		}
//		printf("2\r\n");
//		sleep(2);
//		if(FAILED == Tcp_WriteWithSelect(socket_fd,send_data,strlen(send_data),100)){
//			printf("failed 3\r\n");
//					return -1;
//		}
//		printf("3\r\n");
		if(FAILED == Tcp_ReadWithSelect(socket_fd, recv_buf, RECV_BUFFER_LEN, 20000, 1000)){
			return -1;
		}

		shutdown(socket_fd, SHUT_RDWR);
		close(socket_fd);
		return 0;
}


