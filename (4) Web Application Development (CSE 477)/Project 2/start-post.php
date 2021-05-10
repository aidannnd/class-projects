<?php
require __DIR__ . '/lib/game.inc.php';
$gameJoins = new \Game\GameJoins($site);
$res = $gameJoins->startGame($game->getID());
$key = "team21game" . $game->getID();
$msg = json_encode(array('key' => $key, 'cmd' => 'startGame'));
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
$sock_data = socket_connect($socket, '127.0.0.1', 8078);
if (!$sock_data) {
    echo "Failed to connect";
} else {
    socket_write($socket, $msg, strlen($msg));
}
socket_close($socket);

header("location: waiting-page.php");