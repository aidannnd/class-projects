<?php
require __DIR__ . "/../vendor/autoload.php";

// Start the PHP session system
session_start();

define("GAME_SESSION", 'game');

// If there is a Game session, use that. Otherwise, create one
if(!isset($_SESSION[GAME_SESSION])) {
    $_SESSION[GAME_SESSION] = new Game\Game([]); //TODO:Generate player array with correct starting nodes
}

//user
$user = null;
if(isset($_SESSION[Game\User::SESSION_NAME])) {
    $user = $_SESSION[Game\User::SESSION_NAME];
}

$game = $_SESSION[GAME_SESSION];
$site = new Game\Site();
$localize = require 'localize.inc.php';
if(is_callable($localize)) {
    $localize($site);
}
