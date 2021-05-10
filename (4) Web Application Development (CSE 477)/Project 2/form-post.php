<?php
require __DIR__ . '/lib/game.inc.php';
$controller = new Game\GameController($game, $_POST, $site);
$controller->resetPlayers();

//$_POST['color'] is serialized and must be unserialized to use
if (!isset($_POST['newGame'])) {
    $postData = unserialize($_POST['color']); // Server side
    $color = $postData[0];
    $gameId = $postData[1];
    $playerId = $_SESSION['user']->getId();
    if (!isset($_POST["color"])) {
        header("location: join-game.php");
    }
    $gameId = $controller->joinGame($color, $playerId, $gameId);

/*
    $value = $_POST["color"];

    if (isset($value) && $value == "yellow") {
    //yellow player
    $controller->joinGame("yellow", $playerId, $gameId);
    }
    elseif (isset($value) && $value == "green") {
    //green player
    $controller->joinGame("green", $playerId, $gameId);

    }
    elseif (isset($value) && $value == "red") {
    //red player
    $controller->joinGame("red", $playerId, $gameId);
    }
    elseif (isset($value) && $value == "blue") {
    //blue player
    $controller->joinGame("blue", $playerId, $gameId);
    }
    */
}
else{
    //assigns user to red color. Creates new game
    $userId = $_SESSION['user']->getId();
    $gameId = $controller->startGameAsHost('red', $userId);
    $gameJoin = new \Game\GameJoins($site);
}
$key = "team21game" . $game->getID();
$msg = json_encode(array('key' => $key, 'cmd' => 'reload'));
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
$sock_data = socket_connect($socket, '127.0.0.1', 8078);
if (!$sock_data) {
    echo "Failed to connect";
} else {
    socket_write($socket, $msg, strlen($msg));
}
socket_close($socket);

header("location: waiting-page.php");

exit;