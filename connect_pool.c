/* connect_pool extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif



#ifndef CONNECT_POOL_COMMON_H
#include "common.h"
#endif

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void connect_pool_test1()
 */
PHP_FUNCTION(connect_pool_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "connect_pool");
}
/* }}} */

/* {{{ string connect_pool_test2( [ string $var ] )
 */
PHP_FUNCTION(connect_pool_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(connect_pool)
{
#if defined(ZTS) && defined(COMPILE_DL_CONNECT_POOL)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(connect_pool)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "connect_pool support", "enabled");
	php_info_print_table_end();

}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_connect_pool_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_connect_pool_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ connect_pool_functions[]
 */
static const zend_function_entry connect_pool_functions[] = {
	PHP_FE(connect_pool_test1,		arginfo_connect_pool_test1)
	PHP_FE(connect_pool_test2,		arginfo_connect_pool_test2)
	PHP_FE_END
};
/* }}} */

PHP_MINIT_FUNCTION(connect_pool)
{
    connect_pool_factory_init();
    return  SUCCESS;
}


/* {{{ connect_pool_module_entry
 */
zend_module_entry connect_pool_module_entry = {
	STANDARD_MODULE_HEADER,
	"connect_pool",					/* Extension name */
	connect_pool_functions,			/* zend_function_entry */
	PHP_MINIT(connect_pool),							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(connect_pool),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(connect_pool),			/* PHP_MINFO - Module info */
	PHP_CONNECT_POOL_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */


#ifdef COMPILE_DL_CONNECT_POOL
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(connect_pool)
#endif

