//
// Created by zhanglei on 19-6-5.
//

#ifndef CONNECT_POOL_POOL_WORKER_H
#define CONNECT_POOL_POOL_WORKER_H

#endif //CONNECT_POOL_POOL_WORKER_H

//工厂的工人
typedef struct pool_factory_worker{

    //工作者在进程池中的索引
    int index;

    //工作者的pid
    pid_t pid;

    pid_t (*create_worker)();

}factory_worker;

int init_factory_worker(factory_worker* worker_handle);

pid_t create_worker();