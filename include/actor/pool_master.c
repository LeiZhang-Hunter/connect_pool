//
// Created by zhanglei on 19-6-4.
//

#ifndef CONNECT_POOL_COMMON_H

#include "common.h"
#endif

int init_master(factory_master* master_handle)
{
    bzero(master_handle,sizeof(factory_master));
    master_handle->create_master = create_master;

    master_handle->reactor_pipe = emalloc(sizeof(pipe)*container.reactor_num);
    bzero(master_handle->reactor_pipe,sizeof(pipe)*container.reactor_num);

    //初始化管理者的地址
    pool_factory_manage*manager = emalloc(sizeof(pool_factory_manage));
    pool_factory_manage_init(manager);
    master_handle->manager = manager;

    //初始化reactor的地址
    master_handle->reactor = emalloc(sizeof(factory_reactor));
    init_reactor(master_handle->reactor);
    master_handle->run_reactor = run_reactor;
}

//创建master
pid_t create_master(factory_master* master_handle)
{
    if(container.config_init == 0)
    {
        zend_error(E_ERROR,"you must set config");
    }

    //申请master线程和reactor线程通讯的管道
    int i = 0;
    int pipe[2];

    php_printf("reactor_num:%d\n",container.reactor_num);
    for(i=0;i<container.reactor_num;i++) {
        int res = socketpair(AF_UNIX, SOCK_STREAM, 0, pipe);
        php_printf("pipe:%d\n",res);
        if(res != -1) {
            master_handle->reactor_pipe[i] = pipe;
        }else{
            zend_error(E_ERROR,"reactor create pipe error:%d,msg:%s",errno,strerror(errno));
        }
    }
//    php_printf("%d\n",master_handle->reactor_pipe[0][0]);
//    php_printf("%d\n",master_handle->reactor_pipe[0][1]);
    pid_t pid = fork();

    if(pid == 0)
    {
        //创建管理者进程和reactor线程
        pid = fork();

        if(pid > 0)
        {
            //返回了管理者的pid
            master_handle->manager->create_manager();



        }else if(pid == 0){
            //创建reactor线程
            master_handle->run_reactor();
        }
    }else if(pid > 0)
    {
        //装载master的pid
        container.master_pid = pid;
        return  pid;
    }else{
        zend_error(E_ERROR,"create master failed");
    }
}

//运行reactor线程
int run_reactor()
{
    int i = 0;
    for(i=0;i<container.reactor_num;i++) {
        int res = socketpair(AF_UNIX, SOCK_STREAM, 0, pipe);
        php_printf("pipe:%d\n",res);
        if(res != -1) {
            //开启线程
            container.master->reactor->create();
        }else{
            zend_error(E_ERROR,"reactor create pipe error:%d,msg:%s",errno,strerror(errno));
        }
    }
}