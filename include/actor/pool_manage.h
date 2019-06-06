//
// Created by zhanglei on 19-6-4.
//

#ifndef CONNECT_POOL_POOL_MANAGE_H
#define CONNECT_POOL_POOL_MANAGE_H

#endif //CONNECT_POOL_POOL_MANAGE_H

#ifndef CONNECT_POOL_POOL_WORKER_H
#include "actor/pool_worker.h"
#endif

//定义一个工厂池的管理者
typedef struct _pool_factory_manage{

    pid_t manager_pid;

    //创建一个管理者
    pid_t(*create_manager)();

    factory_worker** worker_pool;

    //工作者
    factory_worker* worker;

}pool_factory_manage;

int pool_factory_manage_init(pool_factory_manage* manager);

pid_t create_manager();