//
// Created by zhanglei on 19-6-10.
//

#ifndef CONNECT_POOL_SOCKET_LIB_H
#define CONNECT_POOL_SOCKET_LIB_H

#endif //CONNECT_POOL_SOCKET_LIB_H


typedef struct _socket_lib{

    int sockfd;

    //创建套接字
    int (*create)();

    //建立连接
//    int (*connect)();

    //绑定端口
    int (*bind)(int sockfd,char* ip,in_port_t port);

    //创建套接字
    int (*listen)(int sockfd,int backlog);

    int (*accept)(int sockfd,struct sockaddr_in *cliaddr,socklen_t *addrlen);

}factory_socket;

int create();

int bind_socket(int sockfd,char* ip,in_port_t port);

int listen_socket(int sockfd,int backlog);

int accept_socket(int sockfd,struct sockaddr_in *cliaddr,socklen_t *addrlen);

int init_factory_socket(factory_socket* socket_handle);

