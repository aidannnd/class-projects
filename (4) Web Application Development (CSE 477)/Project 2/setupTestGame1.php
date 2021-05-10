<?php
require __DIR__ . '/lib/game.inc.php';

$gameController = new Game\GameController($game, $_POST, $site);
$gameController->startGameAsHost("red", 1);
$game->addPlayer("red");
$game->addPlayer("yellow");
header("location: game.php");
