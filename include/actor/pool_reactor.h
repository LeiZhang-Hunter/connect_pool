//
// Created by zhanglei on 19-6-5.
//


#ifndef CONNECT_POOL_POOL_REACTOR_H
#define CONNECT_POOL_POOL_REACTOR_H

#endif //CONNECT_POOL_POOL_REACTOR_H


typedef struct _reactor{
    int reactor_index;
    pthread_t (*create)(int index);
    int* reactor_pipe;
    pthread_t thread_id;
}factory_reactor;

#define GET_REACTOR_INDEX(sockfd) sockfd%container.reactor_num

pthread_t create_reactor(int index);

//申请一个reactor线程池
factory_reactor** alloc_reactor_pool(int number);

void* reactor_thread_loop();

int init_reactor(factory_reactor* reactor_handle);

