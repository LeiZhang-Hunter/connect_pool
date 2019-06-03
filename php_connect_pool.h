/* connect_pool extension for PHP */

#ifndef PHP_CONNECT_POOL_H
# define PHP_CONNECT_POOL_H

extern zend_module_entry connect_pool_module_entry;
# define phpext_connect_pool_ptr &connect_pool_module_entry

# define PHP_CONNECT_POOL_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_CONNECT_POOL)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_CONNECT_POOL_H */

