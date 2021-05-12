<?php

require 'lib/game.inc.php';
$controller = new Wumpus\WumpusController($wumpus, $_GET);
if ($controller->isReset()) {
    unset($_SESSION[WUMPUS_SESSION]);
}

if ($controller->isCheating()) {
    $_SESSION[WUMPUS_SESSION] = new Wumpus\Wumpus(1422668587);
    $wumpus = $_SESSION[WUMPUS_SESSION];
}


header('Location: ' . $controller->getPage());

// debugging
/*
$page = $controller->getPage();
echo "<a href=\"$page\">$page</a>";
//header('Location: ' . $controller->getPage());
*/

//phpinfo();