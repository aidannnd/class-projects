<?php
require __DIR__ . '/lib/game.inc.php';
$game = new Game\Game([]);
$controller = new Game\NewGameController($game, $_POST, $site);
