<?php
require __DIR__ . '/lib/game.inc.php';
require 'format.inc.php';
$gameController = new Game\GameController($game, $_POST, $site);
$games = new Game\Games($site);

$id = $games->getLastId();
echo $gameController->joinGame("yellow", 2, $id);
$game->addPlayer("red");
$game->addPlayer("yellow");
header("location: game.php");
