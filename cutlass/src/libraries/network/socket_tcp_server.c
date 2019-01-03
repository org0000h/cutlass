/* Server code in C */
#if 1
#define _main main
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

typedef enum{
	SUCCEED = 200,
	FAILED = -1,
}RESULT;
// you should to know how many bytes data you need to receive
// this function will return when it received the whole data or it received data as many bytes as the paramater  recv_buf_len you passed in
RESULT Tcp_ReadWithSelect(	const int socket_fd,
						  uint8_t* recv_buf,
					const uint32_t recv_buf_len,
					const uint32_t timeout_ms){

    fd_set read_fds;
    struct timeval timeout;

    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec =(timeout_ms % 1000) * 1000;

    int size_recv , total_size = 0;
    while(1)// only if it is interrupted by signal, then redo
    {
		FD_ZERO(&read_fds);
		FD_SET(socket_fd, &read_fds);
        int Ret = select(socket_fd + 1, &read_fds, NULL, NULL, &timeout);
        if (Ret == 0)
        {
        /* Zero fds ready means we timed out */
            printf("recv select  timeout ...\n");
            return FAILED;
        }
        else if (Ret < 0)
        {
            perror("recv select");
            return FAILED;
        }
        else
        { // there is date to be read on tcp
            if((size_recv =  recv(socket_fd ,  recv_buf, recv_buf_len, 0) ) == -1)
            {
            	perror("recv");
                if (errno == EWOULDBLOCK || errno == EAGAIN)
                {
                    printf("recv timeout ...\n");
                    return FAILED;
                }
                else if (errno == EINTR)
                {
                    printf("recv interrupt by signal...\n");
                    continue;
                }
                else if (errno == ENOENT)
                {
                    printf("recv RST segement...\n");
                    return FAILED;
                }
                else
                {
                    return FAILED;
                }
            }
            else if (size_recv == 0)
            {
                printf("recv: peer closed .\r\n");
                return FAILED;
            }
            else
            {
                total_size += size_recv;
                if(recv_buf_len == size_recv){
                	printf("recv buffer is too small , there is more data to receive!");
                	return FAILED;
                }
                printf("received, total_size = %d bytes\n", total_size);
                printf("recv content:%s\r\n",recv_buf);;
                return SUCCEED;
            }
        }
    }

}

int _main(void)
{
struct sockaddr_in stSockAddr;
int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

if(-1 == SocketFD)
{
  perror("can not create socket");
  exit(EXIT_FAILURE);
}

memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

stSockAddr.sin_family = AF_INET;
stSockAddr.sin_port = htons(1100);
stSockAddr.sin_addr.s_addr = INADDR_ANY;

if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
{
  perror("error bind failed");
  close(SocketFD);
  exit(EXIT_FAILURE);
}

if(-1 == listen(SocketFD, 10))
{
  perror("error listen failed");
  close(SocketFD);
  exit(EXIT_FAILURE);
}

for(;;)
{
  int ConnectFD = accept(SocketFD, NULL, NULL);

  if(0 > ConnectFD)
  {
	perror("error accept failed");
	close(SocketFD);
	exit(EXIT_FAILURE);
  }

 /* perform read write operations ... */
#define RECV_BUFFER_LEN 8000
  char recv_buf[RECV_BUFFER_LEN] = {};

while(1){
  Tcp_ReadWithSelect(	ConnectFD,
  						  recv_buf,
  					 RECV_BUFFER_LEN,
  					1000);
  sleep(1);
}
  //int recv_len = recv(ConnectFD,recv_buf,RECV_BUFFER_LEN, 0);
//  if(recv_len == -1){
//	  perror("error recv failed");
//	  close(ConnectFD);
//	  exit(EXIT_FAILURE);
//  }else if(recv_len == 0){
//	  perror("socket has been closed normally");
//	  close(ConnectFD);
//	  exit(EXIT_FAILURE);
//  }else if(recv_len == RECV_BUFFER_LEN){
//	  printf("maybe hasen't received tatal data!\n");
//	  //try to receive again
//  }
//  printf("server recvdata:len=%d, context:%s\r\n",recv_len,recv_buf);

  char *send_data = "hello from server\n";
  int len_of_copied_data_in_sending_buffer = send(ConnectFD, send_data, strlen(send_data), 0);
  if(len_of_copied_data_in_sending_buffer == -1){
	  perror(" recv failed");
	  close(ConnectFD);
	  exit(EXIT_FAILURE);
  }else if(len_of_copied_data_in_sending_buffer != strlen(send_data)){
	  printf("didn't copied all data to sending buffer!\n");
	  return -1;
  }
  printf("server senddata:len=%d, context:%s\r\n",len_of_copied_data_in_sending_buffer,send_data);
  shutdown(ConnectFD, SHUT_RDWR);

  close(ConnectFD);
}

close(SocketFD);
return 0;
}
