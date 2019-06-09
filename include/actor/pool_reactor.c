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
pthread_t create_reactor(int index)
{
    php_printf("111\n");
    pthread_t tid;
    int res = pthread_create(&tid,NULL,&reactor_thread_loop,(void*)index);
    if(res != 0)
    {
        zend_error(E_ERROR,"create reactor thread error,errno:%d,error msg:%s",errno,strerror(errno));
    }
    return tid;
}

factory_reactor** alloc_reactor_pool(int number)
{
    factory_reactor** res = (factory_reactor**)emalloc(sizeof(factory_reactor)*number);

    if(res == NULL)
    {
        return  NULL;
    }else{
        return  res;
    }

}

//reactor循环
void* reactor_thread_loop(void* arg)
{
    int index = (int)arg;

    //脱离主线程
    pthread_detach(pthread_self());

    php_printf("reactor:%d\n",index);


    exit(0);
}