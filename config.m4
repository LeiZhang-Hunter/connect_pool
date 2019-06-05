dnl config.m4 for extension connect_pool

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(connect_pool, for connect_pool support,
dnl Make sure that the comment is aligned:
dnl [  --with-connect_pool             Include connect_pool support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(connect_pool, whether to enable connect_pool support,
dnl Make sure that the comment is aligned:
[  --enable-connect_pool          Enable connect_pool support], no)

if test "$PHP_CONNECT_POOL" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=\`$PKG_CONFIG foo --cflags\`
  dnl     LIBFOO_LIBDIR=\`$PKG_CONFIG foo --libs\`
  dnl     LIBFOO_VERSON=\`$PKG_CONFIG foo --modversion\`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, CONNECT_POOL_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-connect_pool -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/connect_pool.h"  # you most likely want to change this
  dnl if test -r $PHP_CONNECT_POOL/$SEARCH_FOR; then # path given as parameter
  dnl   CONNECT_POOL_DIR=$PHP_CONNECT_POOL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for connect_pool files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       CONNECT_POOL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$CONNECT_POOL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the connect_pool distribution])
  dnl fi

  dnl # --with-connect_pool -> add include path
  dnl PHP_ADD_INCLUDE($CONNECT_POOL_DIR/include)

  dnl # --with-connect_pool -> check for lib and symbol presence
  dnl LIBNAME=CONNECT_POOL # you may want to change this
  dnl LIBSYMBOL=CONNECT_POOL # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $CONNECT_POOL_DIR/$PHP_LIBDIR, CONNECT_POOL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_CONNECT_POOLLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong connect_pool lib version or lib not found])
  dnl ],[
  dnl   -L$CONNECT_POOL_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(CONNECT_POOL_SHARED_LIBADD)

  dnl # In case of no dependencies
  AC_DEFINE(HAVE_CONNECT_POOL, 1, [ Have connect_pool support ])

  PHP_NEW_EXTENSION(connect_pool,\
  connect_pool.c \
  global/pool_container.c \
  interface/zend_connect_pool_factory.c \
  interface/zend_pdo_connect_pool.c \
  interface/zend_redis_connect_pool.c \
  include/actor/pool_manage.c \
  include/actor/pool_master.c, $ext_shared)
  PHP_ADD_INCLUDE([$ext_srcdir/interface])
  PHP_ADD_INCLUDE([$ext_srcdir/global])
  PHP_ADD_INCLUDE([$ext_srcdir/include])
fi
