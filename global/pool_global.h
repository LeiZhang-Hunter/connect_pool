//
// Created by zhanglei on 19-6-1.
//

#ifndef CONNECT_POOL_POOL_GLOBAL_H
#define CONNECT_POOL_POOL_GLOBAL_H

#endif //CONNECT_POOL_POOL_GLOBAL_H


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


//定义一个操作全局变量的库
typedef struct pool_globals_lib{

    int (*check_pdo_run)();

    int (*run_pdo_pool)();

    int (*run_redis_pool)();

    int (*check_redis_run)();
}globals_lib;

//初始化这个库包
int init_globals_lib(globals_lib* handle);

//检查pdo是否开启
int check_pdo();

//运行pdo池
int run_pdo_pool();

//运行redis池子
int run_redis_pool();

//检查redis是否开启
int check_redis();

//枚举状态位
enum {
    PDO_RUN = 1,
    REDIS_RUN = 1,
    PDO_STOP = 0,
    REDIS_STOP = 0
};