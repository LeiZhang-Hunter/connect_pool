//
// Created by zhanglei on 19-6-5.
//
#ifndef CONNECT_POOL_COMMON_H
#include "common.h"
#endif

//初始化reactor
int init_reactor(factory_reactor* reactor_handle)
{
    reactor_handle->create = create_reactor;
}

//创建reactor线程
int create_reactor()
{
    pthread_t tid;
    pthread_create(&tid,NULL,&reactor_thread_loop,NULL);
}

//reactor循环
void* reactor_thread_loop()
{
    //脱离主线程
    pthread_detach(pthread_self());

    php_printf("111");
    exit(0);
}