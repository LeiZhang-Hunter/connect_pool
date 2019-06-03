--TEST--
connect_pool_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('connect_pool')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = connect_pool_test1();

var_dump($ret);
?>
--EXPECT--
The extension connect_pool is loaded and working!
NULL
