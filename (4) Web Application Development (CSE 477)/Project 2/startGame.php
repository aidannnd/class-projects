<?php
require __DIR__ . '/lib/game.inc.php';

$controller = new \Game\GameController($game, $_POST, $site);
$controller->clearPlayers();
$controller->addPlayersFromTable();
header("location: game.php");