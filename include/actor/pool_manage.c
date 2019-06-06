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

    //初始化进程的池子
//    factory_worker** worker_pool = (factory_worker**)share_alloc(sizeof(factory_worker)*container.worker_num);
//    manager->worker_pool = worker_pool;
    return SUCCESS;
}

//创建一个管理者
pid_t create_manager()
{

    pid_t pid = fork();

    int worker_num = 0;

    if(pid == 0)
    {
        //子进程里需要做两件事第一件事是创建工作者
        for(worker_num = 0;worker_num<container.worker_num;worker_num++)
        {
            //创建工作者
            GET_CONTAINER_WORKER_POOL[worker_num]->pid = GET_CONTAINER_WORKER->create_worker();
        }


    }else if(pid < 0)
    {
        zend_error(E_ERROR,"create manager error");
    }

    container.master->manager->manager_pid = pid;

    int stat;

    while(container.run == 1)
    {
        //监控工作者进程是否挂掉如果挂掉了那么重新拉起来
        pid = waitpid(-1,&stat,-1);

        //如果是进程挂掉了
        if(pid > 0)
        {
            //重新拉起来一个进程
            GET_CONTAINER_WORKER->create_worker();
        }
    }
}