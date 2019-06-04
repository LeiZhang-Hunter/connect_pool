//
// Created by zhanglei on 19-6-1.
//

#ifndef CONNECT_POOL_COMMON_H
#define CONNECT_POOL_COMMON_H

#endif //CONNECT_POOL_COMMON_H

#include "php.h"
#include "ext/standard/info.h"
#include "php_connect_pool.h"

#ifndef CONNECT_POOL_POOL_CONTAINER_H
#include "pool_container.h"
#endif

extern zend_class_entry* pdo_connect_pool_server_object;
extern zend_class_entry* redis_connect_pool_server_object;

//引入工厂
#ifndef CONNECT_POOL_ZEND_CONNECT_POOL_H
#include "zend_connect_pool_factory.h"
#endif

//引入PDO库
#ifndef CONNECT_POOL_ZEND_PDO_CONNECT_POOL_H
#include "zend_pdo_connect_pool.h"
#endif

//引入REDIS库
#ifndef CONNECT_POOL_ZEND_REDIS_CONNECT_POOL_H
#include "zend_redis_connect_pool.h"
#endif

//引入管理者的库
#ifndef CONNECT_POOL_POOL_MANAGE_H
#include "actor/pool_manage.h"
#endif //CONNECT_POOL_POOL_MANAGE_H