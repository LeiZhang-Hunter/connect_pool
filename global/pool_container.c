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

    //未加载
    handle->config_init = 0;

    handle->check_pdo_run = check_pdo;
    handle->run_pdo_pool = run_pdo_pool;
    handle->check_redis_run = check_redis;
    handle->run_redis_pool = run_redis_pool;
    handle->load_config = load_config;

    //初始化管理进程
    factory_master* master = emalloc(sizeof(factory_master));
    init_master(master);
    handle->master = master;

    //初始化基础配置
    handle->ip = emalloc(INET_ADDRSTRLEN);
    bzero(handle->ip,INET_ADDRSTRLEN);
    handle->reactor_num = 4;
    handle->worker_num = 4;
    handle->backlog = 156;
    handle->recv_buf_size = 0;
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

//加载配置
int load_config(zval* config)
{
    if(!config)
    {
        zend_error(E_ERROR,"load config error");
    }
    if(Z_TYPE((*config)) != IS_ARRAY)
    {
        zend_error(E_ERROR,"config must be array");
    }

    //替换为hashtable
    HashTable* container_config = Z_ARRVAL_P((config));

    //检查配置ip地址
    zval* config_placeholder;
    if((config_placeholder = zend_hash_str_find(container_config,"ip",strlen("ip"))))
    {
        //检查这个ip地址是不是一个字符串不是一个字符串报致命错误
        if(Z_TYPE((*config_placeholder)) == IS_STRING) {
            strcpy(container.ip, Z_STRVAL((*config_placeholder)));
        }else{
            //ip地址必须是字符串
            zend_error(E_ERROR,"ip config must be string");
        }
    }else{
        //不存在ip地址这个配置项目
        zend_error(E_ERROR,"ip config must set");
    }

    //检查端口配置
    if((config_placeholder = zend_hash_str_find(container_config,"port",strlen("port")))) {
        convert_to_long(config_placeholder);
        container.port = (uint16_t)Z_LVAL((*config_placeholder));
    }else{
        //端口必须设置
        zend_error(E_ERROR,"port config must set");
    }

    //检查reactor的数量
    if((config_placeholder = zend_hash_str_find(container_config,"reactor_num",strlen("reactor_num")))) {
        convert_to_long(config_placeholder);
        container.reactor_num = (uint16_t)Z_LVAL((*config_placeholder));
    }

    //检查worker的数量
    if((config_placeholder = zend_hash_str_find(container_config,"worker_num",strlen("worker_num")))) {
        convert_to_long(config_placeholder);
        container.reactor_num = (uint16_t)Z_LVAL((*config_placeholder));
    }

    //检查backlog
    if((config_placeholder = zend_hash_str_find(container_config,"backlog",strlen("backlog")))) {
        convert_to_long(config_placeholder);
        container.reactor_num = (uint16_t)Z_LVAL((*config_placeholder));
    }

    //设置接收的缓冲区大小
    if((config_placeholder = zend_hash_str_find(container_config,"recv_buf_size",strlen("recv_buf_size")))) {
        convert_to_long(config_placeholder);
        container.reactor_num = (uint16_t)Z_LVAL((*config_placeholder));
    }

    //打开加载标志位
    container.config_init = 1;

    return SUCCESS;
}

