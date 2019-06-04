//
// Created by zhanglei on 19-6-4.
//

#ifndef CONNECT_POOL_POOL_MANAGE_H
#define CONNECT_POOL_POOL_MANAGE_H

#endif //CONNECT_POOL_POOL_MANAGE_H

//定义一个工厂池的管理者
typedef struct _pool_factory_manage{

    //创建一个管理者
    int(*create_manager)();

}pool_factory_manage;

int pool_factory_manage_init(pool_factory_manage* manager);

int create_manager();