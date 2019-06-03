//
// Created by zhanglei on 19-6-3.
//

#ifndef CONNECT_POOL_ZEND_REDIS_CONNECT_POOL_H
#define CONNECT_POOL_ZEND_REDIS_CONNECT_POOL_H

#endif //CONNECT_POOL_ZEND_REDIS_CONNECT_POOL_H


zend_class_entry redis_connect_pool_server;
zend_class_entry* redis_connect_pool_server_object;

PHP_METHOD(RedisConnectPoolServer,__construct);


PHP_METHOD(RedisConnectPoolServer,__destruct);

void connect_redis_pool_server_init();