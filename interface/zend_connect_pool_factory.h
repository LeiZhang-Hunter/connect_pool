//
// Created by zhanglei on 19-6-1.
//

#ifndef CONNECT_POOL_ZEND_CONNECT_POOL_H
#define CONNECT_POOL_ZEND_CONNECT_POOL_H

#endif //CONNECT_POOL_ZEND_CONNECT_POOL_H

zend_class_entry zend_connect_pool_factory;

zend_class_entry* zend_connect_pool_factory_instance;

//选择工厂的参数
ZEND_BEGIN_ARG_INFO_EX(select_factory_arg, 0, 0, 1)
                ZEND_ARG_INFO(0, select_mode)
ZEND_END_ARG_INFO()

PHP_METHOD(ConnectPoolFactory,__construct);

PHP_METHOD(ConnectPoolFactory,selectFactory);

PHP_METHOD(ConnectPoolFactory,__destruct);

void connect_pool_factory_init();