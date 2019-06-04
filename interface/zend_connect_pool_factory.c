//
// Created by zhanglei on 19-6-1.
//

#ifndef CONNECT_POOL_COMMON_H
#include "common.h"
#endif

const zend_function_entry connect_pool_factory_struct[] = {
    PHP_ME(ConnectPoolFactory,__construct,NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(ConnectPoolFactory,selectFactory,select_factory_arg, ZEND_ACC_PUBLIC)
//    PHP_ME(ConnectPoolFactory,selectFactory,select_factory_arg, setConfig)
    PHP_ME(ConnectPoolFactory,__destruct,NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
    PHP_FE_END
};

pool_container container;

PHP_METHOD(ConnectPoolFactory,__construct)
{
    init_container(&container);
}

//选择模式
PHP_METHOD(ConnectPoolFactory,selectFactory)
{
    zval select_mode;
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(select_mode)
    ZEND_PARSE_PARAMETERS_END();

    zval val_object;

    char* a = Z_STRVAL((select_mode));

    //检查pdo模式下池子运行状况启动池子
    if(strcmp(Z_STRVAL((select_mode)),"pdo") == 0)
    {
        if(container.check_pdo_run() == PDO_RUN)
        {
            zend_error(E_WARNING, "pdo connect pool has been run");
            RETURN_FALSE
        }
        //设置标志位为运行状态
        container.run_pdo_pool();

        if(!pdo_connect_pool_server_object)
        {
            zend_error(E_WARNING,"init pdo connect pool object is error");
            RETURN_NULL()
        }


        object_init_ex(&val_object,pdo_connect_pool_server_object);
        RETURN_ZVAL(&val_object,1,0);
    }

    //检查redis模式下池子运行状况启动池子
    if(strcmp(Z_STRVAL((select_mode)),"redis") == 0)
    {
        if(container.check_redis_run() == REDIS_RUN)
        {
            zend_error(E_WARNING, "redis connect pool has been run");
            RETURN_FALSE
        }

        //设置redis的标志位为启动
        container.run_redis_pool();

        if(!redis_connect_pool_server_object)
        {
            zend_error(E_WARNING, "init redis connect pool is error");
            RETURN_FALSE
        }
        object_init_ex(&val_object,redis_connect_pool_server_object);
        RETURN_ZVAL(&val_object,1,0);
    }
}

PHP_METHOD(ConnectPoolFactory,setConfig)
{

}


PHP_METHOD(ConnectPoolFactory,__destruct)
{

}

//初始化链接池的工厂
void connect_pool_factory_init()
{
    INIT_CLASS_ENTRY(zend_connect_pool_factory,"ConnectPoolFactory",connect_pool_factory_struct);
    zend_connect_pool_factory_instance = zend_register_internal_class_ex(&zend_connect_pool_factory,NULL);
}



