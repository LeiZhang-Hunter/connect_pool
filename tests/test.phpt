<?php
$poolFactory = new ConnectPoolFactory();
$pdo_pool = $poolFactory->selectFactory("pdo");
//运行pdo池子
$pdo_pool->run();

var_dump($pdo_pool);
