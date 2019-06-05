cmake_minimum_required(VERSION 3.7)

project(connect_pool)

set(CMAKE_CXX_STANDARD 11)


#定义php源码路径，这里根据自己的真实路径来更改
set(PHP_SOURCE /home/zhanglei/ourc/php-7.3.2)
# Add -O0 to remove optimizations when using gcc
IF(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

#引入php需要的扩展源码，这里也是根据自己需要的来更改
include_directories(/home/zhanglei/ourc/php-7.3.2/ext/connect_pool/)
include_directories(/home/zhanglei/ourc/php-7.3.2/ext/connect_pool/include/)
include_directories(/home/zhanglei/ourc/php-7.3.2/ext/connect_pool/interface)
include_directories(/home/zhanglei/ourc/php-7.3.2/ext/connect_pool/global)
include_directories(${PHP_SOURCE}/main/)
include_directories(${PHP_SOURCE}/Zend/)
include_directories(${PHP_SOURCE}/sapi/)
include_directories(${PHP_SOURCE}/pear/)
include_directories(${PHP_SOURCE}/sapi/)
include_directories(${PHP_SOURCE}/TSRM/)
include_directories(${PHP_SOURCE}/)

set(SOURCE_FILES
        connect_pool.c
        interface/zend_connect_pool_factory.h
        interface/zend_connect_pool_factory.c
        interface/zend_pdo_connect_pool.h
        interface/zend_pdo_connect_pool.c
        interface/zend_redis_connect_pool.h
        interface/zend_redis_connect_pool.c
        global/pool_container.h
        global/pool_container.c
        include/actor/pool_master.h
        include/actor/pool_master.c
        include/actor/pool_manage.h
        include/actor/pool_manage.c
        include/actor/pool_worker.h
        include/actor/pool_worker.c
        )

add_executable(connect_pool ${SOURCE_FILES})
#CFLAGS='-g -O0'
add_custom_target(makefile COMMAND  make clean && phpize && ./configure CFLAGS='-g -O0'  && make && make install WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
