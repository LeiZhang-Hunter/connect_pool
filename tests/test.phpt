<?php
$poolFactory = new ConnectPoolFactory();
$pdo_pool = $poolFactory->selectFactory("pdo");
$pdo_pool->setConfig([
    "ip"=>"127.0.0.1",
    "port"=>"9000",
    "worker_num"=>1,
    "reactor_num"=>1,
]);
//运行pdo池子
$r = $pdo_pool->run();

var_dump($r);
