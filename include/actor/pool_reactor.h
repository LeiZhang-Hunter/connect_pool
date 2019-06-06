//
// Created by zhanglei on 19-6-5.
//

#ifndef CONNECT_POOL_POOL_REACTOR_H
#define CONNECT_POOL_POOL_REACTOR_H

#endif //CONNECT_POOL_POOL_REACTOR_H

typedef struct _reactor{
    int (*create)();
}factory_reactor;

int create_reactor();

void* reactor_thread_loop();

int init_reactor(factory_reactor* reactor_handle);

