//
// Created by zhanglei on 19-6-4.
//

#ifndef CONNECT_POOL_POOL_MASTER_H
#define CONNECT_POOL_POOL_MASTER_H

#endif //CONNECT_POOL_POOL_MASTER_H

#ifndef CONNECT_POOL_POOL_MANAGE_H
#include "pool_manage.h"
#endif

//引入reactor包
#ifndef CONNECT_POOL_POOL_REACTOR_H
#include "actor/pool_reactor.h"
#endif

typedef struct pool_master{
    pid_t (*create_master)(struct pool_master*master_handle );

    //管理者的地址
    pool_factory_manage* manager;

    pid_t master_pid;

    int** reactor_pipe;

    factory_reactor* reactor;

    int (*run_reactor)();

}factory_master;

pid_t create_master(factory_master* master_handle);

int init_master(factory_master* master_handle);

//运行reactor线程
int run_reactor();