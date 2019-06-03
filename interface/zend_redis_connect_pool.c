//
// Created by zhanglei on 19-6-3.
//

#ifndef CONNECT_POOL_COMMON_H

#include "../common.h"
#endif

zend_function_entry connect_redis_pool_server_struct[] = {
        PHP_ME(PdoConnectPoolServer,__construct,NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        PHP_ME(PdoConnectPoolServer,__destruct,NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
        PHP_FE_END
};

PHP_METHOD(RedisConnectPoolServer,__construct)
{
}



PHP_METHOD(RedisConnectPoolServer,__destruct)
{

}

//初始化链接池
void connect_redis_pool_server_init(){
    INIT_CLASS_ENTRY(redis_connect_pool_server,"RedisConnectPoolServer",connect_redis_pool_server_struct);
    redis_connect_pool_server_object = zend_register_internal_class_ex(&redis_connect_pool_server,NULL);
}