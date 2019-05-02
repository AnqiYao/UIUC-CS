<?php

const DSN="mysql:host=localhost;dbname=anime_cleaned;";
const USER="root";
const PASSWORD="root";
error_reporting(E_ALL ^ E_WARNING);
error_reporting(E_ALL ^ E_NOTICE);

header("content-type:text/html;charset=utf-8");
$pdo=new PDO(DSN,USER,PASSWORD);
$pdo->exec("set names utf8");
$pdo->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE,PDO::FETCH_ASSOC);
$pdo->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
 ?>
