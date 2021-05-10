<?php
require '../lib/game.inc.php';

$controller = new Game\SignUpController($site, $_SESSION, $_POST);

header("location: " . $controller->getRedirect());