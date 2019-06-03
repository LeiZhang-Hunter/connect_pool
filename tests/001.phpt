--TEST--
Check if connect_pool is loaded
--SKIPIF--
<?php
if (!extension_loaded('connect_pool')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "connect_pool" is available';
?>
--EXPECT--
The extension "connect_pool" is available
