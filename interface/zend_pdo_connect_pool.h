//
// Created by zhanglei on 19-6-3.
//

#ifndef CONNECT_POOL_ZEND_PDO_CONNECT_POOL_H
#define CONNECT_POOL_ZEND_PDO_CONNECT_POOL_H

#endif //CONNECT_POOL_ZEND_PDO_CONNECT_POOL_H

zend_class_entry pdo_connect_pool_server;
zend_class_entry* pdo_connect_pool_server_object;

//选择工厂的参数
ZEND_BEGIN_ARG_INFO_EX(pdo_factory_config, 0, 0, 1)
                ZEND_ARG_INFO(0, pdo_config)
ZEND_END_ARG_INFO()

PHP_METHOD(PdoConnectPoolServer,__construct);

PHP_METHOD(PdoConnectPoolServer,setConfig);

PHP_METHOD(PdoConnectPoolServer,run);


PHP_METHOD(PdoConnectPoolServer,__destruct);

void connect_pdo_pool_server_init();