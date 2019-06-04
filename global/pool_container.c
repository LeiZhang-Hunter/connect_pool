//
// Created by zhanglei on 19-6-1.
//
#ifndef CONNECT_POOL_COMMON_H
#include "common.h"
#endif

//检查全局变量库
int init_container(pool_container* handle)
{
    if(!handle)
    {
        return FAILURE;
    }

    handle->check_pdo_run = check_pdo;
    handle->run_pdo_pool = run_pdo_pool;
    handle->check_redis_run = check_redis;
    handle->run_redis_pool = run_redis_pool;
    handle->set_manager_pid = set_manager_pid;
    return SUCCESS;
}

//检查pdo是否开启
int run_pdo_pool()
{
    CPG(pdo_run_flag) = PDO_RUN;
    return SUCCESS;
}

int run_redis_pool()
{
    CPG(redis_run_flag) = REDIS_RUN;
}

//检查pdo是否开启
int check_pdo()
{
    if(CPG(pdo_run_flag) == PDO_RUN)
    {
        return PDO_RUN;
    }

    return PDO_STOP;
}

//检查redis是否开启
int check_redis()
{
    if(CPG(redis_run_flag) == REDIS_RUN)
    {
        return REDIS_RUN;
    }

    return REDIS_STOP;
}

int set_manager_pid()
{

}