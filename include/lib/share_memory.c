//
// Created by zhanglei on 19-6-5.
//
#ifndef CONNECT_POOL_COMMON_H

#include "common.h"
#endif

void* share_alloc(size_t size)
{
    int tmpfd = -1;
    int flag = MAP_SHARED;

#ifdef MAP_ANONYMOUS
    flag |= MAP_ANONYMOUS;
#else
    char *mapfile;
    if (mapfile == NULL) {
        mapfile = "/dev/zero";
    }
    if ((tmpfd = open(mapfile, O_RDWR)) < 0) {
        return FAILURE;
    }
    strncpy(object->mapfile, mapfile, SW_SHM_MMAP_FILE_LEN);
    object->tmpfd = tmpfd;
#endif
    void* mem = mmap(NULL,size, PROT_READ | PROT_WRITE,flag,tmpfd,0);

#ifndef MAP_FAILED
    if(mem == MAP_FAILED){
#else
    if(!mem){
#endif
        zend_error(E_ERROR,"mmap create mem error");
        return FAILURE;
    }else{

        bzero(mem,size);
        return  mem;
    }
}