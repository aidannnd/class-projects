<?php

require '../lib/game.inc.php';
$controller = new Game\GameController($game, $_POST, $site);
$controller->networkTurn();
$root = $site->getRoot();
if($controller->checkGameEnded()){
    header("location: ../win.php");
}
else{
    header("location: ../game.php");
}