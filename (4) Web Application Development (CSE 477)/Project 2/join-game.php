<?php
require 'format.inc.php';
require __DIR__ . '/lib/game.inc.php';
$view = new Game\JoinGameView($_SESSION, $_GET, $site);
if(!$view->protect($site, $user)) {
    // user is logged in
    header("location: " . $view->getProtectRedirect());
    exit;
}
?>
<!doctype html>
<html lang="en-us">
<head>
    <meta charset="utf-8">
    <title>Join a Game</title>
    <link href="lib/scss/game.css" type="text/css" rel="stylesheet" />
</head>
<body>

<header>
    <nav><p><a href="./post/logout.php">Log out</a>
            <a href="instructions.php">Help Page</a></p></nav>
    <h1><a href="index.php">Join a Game</a></h1>
</header>
<?php
echo $view->present($site);
?>
</body>
</html>