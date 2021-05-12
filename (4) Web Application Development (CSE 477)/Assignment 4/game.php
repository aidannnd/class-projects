<?php
require 'lib/game.inc.php';
$view = new Wumpus\WumpusView($wumpus);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stalking the Wumpus</title>
    <link href="main.css" type="text/css" rel="stylesheet" />
</head>
<body>

<header>
    <nav>
        <p><a href="welcome.php">New Game</a> <a href="game.php">Game</a> <a href="instructions.php">Instructions</a></p>
    </nav>
    <h1>Stalking the Wumpus</h1>
</header>

<article>
    <figure><img src="images/cave.jpg" width="600" height="325" alt="Cave 1"/></figure>

    <?php
    echo $view->presentStatus();
    ?>

    <div class="rooms">
        <?php
        echo $view->presentRoom(0);
        echo $view->presentRoom(1);
        echo $view->presentRoom(2);
        ?>
    </div>

    <div class="endheader">
        <h2>
            <?php
            echo $view->presentArrows();
            ?>
        </h2>
    </div>

</article>

</body>
</html>