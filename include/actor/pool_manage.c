//
// Created by zhanglei on 19-6-4.
//
#ifndef CONNECT_POOL_COMMON_H
#include "common.h"
#endif

//初始化管理者
int pool_factory_manage_init(pool_factory_manage* manager)
{
    //初始化管理者
    bzero(manager,sizeof(pool_factory_manage));
    manager->create_manager = create_manager;

    //初始化工作者进程的地址
    factory_worker* worker = emalloc(sizeof(factory_worker));
    init_factory_worker(worker);
    manager->worker = worker;
    return SUCCESS;
}

//创建一个管理者
pid_t create_manager()
{
    php_printf("create manager\n");

    pid_t pid = fork();

    if(pid == 0)
    {
        //子进程里需要做两件事第一件事是创建
    }else if(pid < 0)
    {
        zend_error(E_ERROR,"create manager error");
    }
}