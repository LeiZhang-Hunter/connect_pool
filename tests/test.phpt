<?php
$poolFactory = new ConnectPoolFactory();
$r = $poolFactory->selectFactory("pdo");
var_dump($r);die;
