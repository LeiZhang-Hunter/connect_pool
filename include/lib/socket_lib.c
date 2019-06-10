//
// Created by zhanglei on 19-6-10.
//

#ifndef CONNECT_POOL_COMMON_H
#include "common.h"
#endif

int init_factory_socket(factory_socket* socket_handle)
{
    if(!socket_handle)
    {
        return FAILURE;
    }

    bzero(socket_handle,sizeof(factory_socket));

    socket_handle->create = create;

    socket_handle->bind = bind_socket;

    socket_handle->listen = listen_socket;

    socket_handle->accept = accept_socket;

    return SUCCESS;
}

//创建套接字
int create()
{
    int res = socket(AF_INET,SOCK_STREAM,0);

    if(res == -1)
    {
        zend_error(E_ERROR,"create server socket error,errno:%d,error msg:%s",errno,strerror(errno));
    }else{
        return  res;
    }
}

//绑定套接字
int bind_socket(int sockfd,char* ip,in_port_t port)
{
    struct sockaddr_in socket_addr;

    socket_addr.sin_family = AF_INET;

    socket_addr.sin_port = htons(port);

    socket_addr.sin_addr.s_addr = inet_addr(ip);

    int res = bind(sockfd,(struct sockaddr*)&socket_addr,sizeof(socket_addr));

    if(res == -1)
    {
        zend_error(E_ERROR,"bind  socket error,errno:%d,errormsg:%s",errno,strerror(errno));
    }else{
        return  res;
    }
}

//监听套接字
int listen_socket(int sockfd,int backlog)
{
    int res = listen(sockfd,backlog);
    if(res == -1)
    {
        zend_error(E_ERROR,"listen  socket error,errno:%d,errormsg:%s",errno,strerror(errno));
    }else{
        return  res;
    }
}

//接收套接字
int accept_socket(int sockfd,struct sockaddr_in *cliaddr,socklen_t *addrlen)
{
    bzero(cliaddr,sizeof(struct sockaddr_in));
    int connfd = accept(sockfd,cliaddr,addrlen);
    if(connfd == -1)
    {
        //如果被信号中断掉直接false就可以
        if(errno == EINTR)
        {
            return FAILURE;
        }
        zend_error(E_WARNING,"accept  socket error,errno:%d,errormsg:%s",errno,strerror(errno));
        return FAILURE;
    }else{
        return  connfd;
    }
}