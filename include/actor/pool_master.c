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

    if(!container.reactor_num)
    {
        zend_error(E_ERROR,"you must init reactor number");
    }
    //申请一个线程池
    factory_reactor** reactor_pool = alloc_reactor_pool(container.reactor_num);

    //
    if(!reactor_pool)
    {
        zend_error(E_ERROR,"create reactor pool error");
    }


    for(i=0;i<container.reactor_num;i++) {
        int res = socketpair(AF_UNIX, SOCK_STREAM, 0, pipe);
        php_printf("pipe:%d\n",res);
        if(res != -1) {
            init_reactor(reactor_pool[i]);
            reactor_pool[i]->reactor_index = i;
            reactor_pool[i]->reactor_pipe = pipe;
//            master_handle->reactor_pipe[i] = pipe;
        }else{
            zend_error(E_ERROR,"reactor create pipe error:%d,msg:%s",errno,strerror(errno));
        }
    }

    //将reactor初始化进入容器
    container.reactor_pool = reactor_pool;

    pid_t pid = fork();

    if(pid == 0)
    {
        //创建管理者进程和reactor线程
        pid = fork();
//        php_printf("run begin2,%d\n",pid);

        if(pid > 0)
        {
            //返回了管理者的pid
            php_printf("run reactor\n");

            master_handle->run_reactor();


        }else if(pid == 0){
            //创建reactor线程
            php_printf("run manager\n");

//            master_handle->manager->create_manager();

//            exit(0);

        }else{
            zend_error(E_ERROR,"create reactor error,errno:%d,error msg:%s",errno,strerror(errno));
        }
    }else if(pid > 0)
    {
        //装载master的pid
        container.master_pid = pid;

        factory_socket socket_lib;

        init_factory_socket(&socket_lib);

        int sockfd;

        //管道的编号
        int pipe_index;

        socklen_t clilen;

        int connfd;

        sockfd = socket_lib.create();

        socket_lib.bind(sockfd,container.ip,container.port);

        socket_lib.listen(sockfd,container.backlog);

        //这里使用select就可以了因为我们这里只需要检测一个套接字
        fd_set set;

        FD_ZERO(&set);

        FD_SET(sockfd,&set);

        int *reactor_pipe;

        while(container.run)
        {
            select(sockfd+1,&set,NULL,NULL,NULL);

            if(FD_ISSET(sockfd,&set))
            {
                //套接字准备就绪了准备发送到对应的reactor线程
                struct sockaddr_in cliaddr;
                clilen = sizeof(cliaddr);
                connfd = socket_lib.accept(sockfd,&cliaddr,&clilen);

                //剩下的EINTR错误码我们可以不需要再那么关心了
                if(connfd > 0) {
                    //获取管道的索引
                    pipe_index = GET_REACTOR_INDEX(connfd);

                    reactor_pipe = container.reactor_pool[pipe_index]->reactor_pipe;

                    php_printf("fd:%d\n",connfd);

                    //关闭读端
//                    close(reactor_pipe[0]);

//                    char buf[1024];

//                    sprintf(buf,"%d\r\n\r\n",connfd);

//                    write(reactor_pipe[1],buf, sizeof(buf));
                }
            }
        }
//        return  pid;
    }else{
//        php_printf("run begin3\n");
        zend_error(E_ERROR,"create master failed");
    }
}

//运行reactor线程
int run_reactor()
{
    php_printf("aaa\n");
    int i = 0;

    pthread_t thread_id;
    for(i=0;i<container.reactor_num;i++) {
        thread_id =container.master->reactor->create(i);
        container.reactor_pool[i]->thread_id = thread_id;
    }
}