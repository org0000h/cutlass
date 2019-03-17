//
//  net_tcp.h
//  cutlass
//
//  Created by 亚洲 on 2019/3/17.
//  Copyright © 2019 亚洲. All rights reserved.
//

#ifndef net_tcp_h
#define net_tcp_h

#include <stdio.h>
typedef enum{
    SUCCEED = 200,
    FAILED = -1,
}RESULT;

RESULT Tcp_SetupConnectionRetyrSync(      int     *socket_fd,
                                    const char     *domain_name,
                                    const char     *service_or_port,
                                    const int     single_wait_time_ms,
                                    const int     retry_times);

RESULT Tcp_WriteWithSelect(    const int         socket_fd,
                           const char         *data_want_to_send,
                           const int         data_len_want_to_send,
                           const uint32_t     timeout_ms);

/*
 *you should to know how many bytes data you need to receive
 *this function will return when it received the whole data or
 *if you don't know how many data you will received,you can set a
 *large received buffer and  want_recv_len,then by setting a big timeout_ms
 *you will get the whole data (except it is really timeout!!).But this function
 *will still return FAILED
 *it received data as many bytes as the paramater  recv_buf_len you passed in
 */
RESULT Tcp_ReadWithSelect(    const int         socket_fd,
                          uint8_t*     recv_buf,
                          const uint32_t     recv_buf_len,
                          const int32_t want_recv_len,
                          const uint32_t     timeout_ms);
#endif /* net_tcp_h */
