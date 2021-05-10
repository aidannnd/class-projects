<?php
require __DIR__ . '/lib/game.inc.php';
$controller = new Game\GameController($game, $_POST, $site);

if($controller->isReset()) {
    unset($_SESSION[GAME_SESSION]);
}
/*
else if($controller->checkGameEnded()){
    header("location: win.php");
}
else{
    header("location: game.php");
}
*/
header("location: game.php");
exit;