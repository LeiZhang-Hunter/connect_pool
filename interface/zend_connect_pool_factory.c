//
// Created by zhanglei on 19-6-1.
//

#ifndef CONNECT_POOL_COMMON_H
#include "common.h"
#endif

const zend_function_entry connect_pool_factory_struct[] = {
    PHP_ME(ConnectPoolFactory,__construct,NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(ConnectPoolFactory,selectFactory,select_factory_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(ConnectPoolFactory,__destruct,NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
    PHP_FE_END
};

globals_lib factory_global_variable;

PHP_METHOD(ConnectPoolFactory,__construct)
{
    init_globals_lib(&factory_global_variable);
}

//选择模式
PHP_METHOD(ConnectPoolFactory,selectFactory)
{
    zval select_mode;
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(select_mode)
    ZEND_PARSE_PARAMETERS_END();

    char* a = Z_STRVAL((select_mode));
    php_printf("%s\n",Z_STRVAL((select_mode)));

    //检查pdo模式下池子运行状况启动池子
    if(strcmp(Z_STRVAL((select_mode)),"pdo") == 0)
    {
        if(factory_global_variable.check_pdo_run() == PDO_RUN)
        {
            zend_error(E_WARNING, "pdo_connect_pool has been run");
            RETURN_FALSE
        }
        factory_global_variable.run_pdo_pool();
        RETURN_TRUE
    }

    //检查redis模式下池子运行状况启动池子
    if(strcmp(Z_STRVAL((select_mode)),"redis") == 0)
    {
        if(factory_global_variable.check_redis_run() == REDIS_RUN)
        {
            zend_error(E_WARNING, "pdo_connect_pool has been run");
            RETURN_FALSE
        }
        factory_global_variable.run_redis_pool();
        RETURN_TRUE
    }
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



