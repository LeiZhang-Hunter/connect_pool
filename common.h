//
// Created by zhanglei on 19-6-1.
//

#ifndef CONNECT_POOL_COMMON_H
#define CONNECT_POOL_COMMON_H

#endif //CONNECT_POOL_COMMON_H

#include "php.h"
#include "ext/standard/info.h"
#include "php_connect_pool.h"
#include <SAPI.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <wait.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef CONNECT_POOL_POOL_CONTAINER_H
#include "pool_container.h"
#endif

extern zend_class_entry* pdo_connect_pool_server_object;
extern zend_class_entry* redis_connect_pool_server_object;

//引入工厂
#ifndef CONNECT_POOL_ZEND_CONNECT_POOL_H
#include "zend_connect_pool_factory.h"
#endif

extern pool_container container;

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

#ifndef CONNECT_POOL_POOL_MASTER_H
#include "actor/pool_master.h"
#endif

#ifndef CONNECT_POOL_POOL_WORKER_H
#include "actor/pool_worker.h"
#endif

#ifndef CONNECT_POOL_SHARE_MEMORY_H

#include "lib/share_memory.h"
#endif


#ifndef CONNECT_POOL_POOL_REACTOR_H
#include "actor/pool_reactor.h"
#endif

#ifndef CONNECT_POOL_SOCKET_LIB_H
#include "lib/socket_lib.h"
#endif