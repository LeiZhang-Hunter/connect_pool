//
// Created by zhanglei on 19-6-5.
//

#ifndef CONNECT_POOL_COMMON_H

#include "common.h"
#endif

//初始化工厂的工作者
int init_factory_worker(factory_worker* worker_handle)
{
    if(!worker_handle)
    {
        return  FAILURE;
    }

    bzero(worker_handle,sizeof(factory_worker));

    worker_handle->create_worker = create_worker;

    return SUCCESS;
}

//创建工作者
pid_t create_worker()
{

}