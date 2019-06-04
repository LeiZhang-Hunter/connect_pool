//
// Created by zhanglei on 19-6-4.
//
#include "common.h"

int pool_factory_manage_init(pool_factory_manage* manager)
{
    manager->create_manager = create_manager;
    return SUCCESS;
}

//创建一个管理者
int create_manager()
{

}