//
// Created by zhanglei on 19-6-3.
//

#ifndef CONNECT_POOL_ZEND_PDO_CONNECT_POOL_H
#define CONNECT_POOL_ZEND_PDO_CONNECT_POOL_H

#endif //CONNECT_POOL_ZEND_PDO_CONNECT_POOL_H

zend_class_entry pdo_connect_pool_server;
zend_class_entry* pdo_connect_pool_server_object;

PHP_METHOD(PdoConnectPoolServer,__construct);


PHP_METHOD(PdoConnectPoolServer,__destruct);

void connect_pdo_pool_server_init();