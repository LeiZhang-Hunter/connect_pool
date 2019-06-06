//
// Created by zhanglei on 19-6-1.
//

#ifndef CONNECT_POOL_POOL_CONTAINER_H
#define CONNECT_POOL_POOL_CONTAINER_H

#endif //CONNECT_POOL_POOL_GLOBAL_H

#ifndef CONNECT_POOL_POOL_MANAGE_H
#include "actor/pool_master.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(pool_factory)

    char pdo_run_flag;

    char redis_run_flag;

ZEND_END_MODULE_GLOBALS(pool_factory)

ZEND_DECLARE_MODULE_GLOBALS(pool_factory)


#ifdef ZTS
static int alloc_globals_id;
# define CPG(v) ZEND_TSRMG(pool_factory_globals_id, zend_alloc_globals *, v)
#else
#define CPG(v) pool_factory_globals.v
#endif

//定义ip长度
#define INET_ADDRSTRLEN 16

//定义一个操作全局变量的库
typedef struct pool_container_struct{

    uint8_t run;

    uint8_t config_init;

    //设置pdo的运行位
    int (*check_pdo_run)();

    //设置pdo的运行位
    int (*run_pdo_pool)();

    int (*run_redis_pool)();

    int (*check_redis_run)();

    int (*load_config)(zval* config);

    //工厂主的pid
    pid_t master_pid;

    //监听的ip地址
    char* ip;

    //监听的端口
    uint16_t port;

    //reactor的数量
    int reactor_num;

    //worker的数量
    int worker_num;

    //链接堆积量
    int backlog;

    //接收缓冲区大小
    int recv_buf_size;

    //发送缓冲区大小

    //工厂主的master
    factory_master* master;

}pool_container;

#define GET_CONTAINER_MANAGER container.master->manager

#define GET_CONTAINER_WORKER container.master->manager->worker

#define GET_CONTAINER_WORKER_POOL container.master->manager->worker_pool

//初始化这个库包
int init_container(pool_container* handle);

//检查pdo是否开启
int check_pdo();

//运行pdo池
int run_pdo_pool();

//运行redis池子
int run_redis_pool();

//检查redis是否开启
int check_redis();

int load_config(zval* config);

//枚举状态位
enum {
    PDO_RUN = 1,
    REDIS_RUN = 1,
    PDO_STOP = 0,
    REDIS_STOP = 0
};