<?php
require __DIR__ . '/lib/game.inc.php';
//$game = new Game\Game([]);
$controller = new Game\GameController($game, $_POST);


// reset game
$controller->resetPlayers();


if(isset($_POST["yellow"])){
    //red player
    $controller->addPlayer("yellow");
}

if(isset($_POST["green"])){
    //green player
    $controller->addPlayer("green");
}

if(isset($_POST["red"])){
    //red player
    $controller->addPlayer("red");
}



if(isset($_POST["blue"])){
    //red player
    $controller->addPlayer("blue");
}

if ($game->getNumPlayers() >= 2){
    header("location: game-post.php");
}
else {
    header("location: index.php");
}

exit;