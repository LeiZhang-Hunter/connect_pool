//
// Created by zhanglei on 19-6-3.
//
#ifndef CONNECT_POOL_COMMON_H

#include <SAPI.h>
#include "../common.h"
#endif

zend_function_entry connect_pdo_pool_server_struct[] = {
        PHP_ME(PdoConnectPoolServer,__construct,NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        PHP_ME(PdoConnectPoolServer,run,NULL, ZEND_ACC_PUBLIC)
        PHP_ME(PdoConnectPoolServer,__destruct,NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
        PHP_FE_END
};

PHP_METHOD(PdoConnectPoolServer,__construct)
{

}

//运行pdo的池子
PHP_METHOD(PdoConnectPoolServer,run)
{
    //检查是否在cli模式下运行
    if(strcasecmp("cli",sapi_module.name) != 0)
    {
        zend_error(E_WARNING,"server process must run in cli");
        RETURN_FALSE
    }


}

PHP_METHOD(PdoConnectPoolServer,__destruct)
{

}

//初始化链接池
void connect_pdo_pool_server_init(){
    INIT_CLASS_ENTRY(pdo_connect_pool_server,"PdoConnectPoolServer",connect_pdo_pool_server_struct);
    pdo_connect_pool_server_object = zend_register_internal_class_ex(&pdo_connect_pool_server,NULL);
}