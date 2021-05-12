<?php
require 'format.inc.php';
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>The Wumpus Killed You</title>
    <link href="main.css" type="text/css" rel="stylesheet" />
</head>
<body>

<?php echo present_header("Stalking the Wumpus"); ?>

<article>
    <figure><img src="images/wumpus-wins.jpg" width="600" height="325" alt="Alive Cat"/></figure>

    <div class="welcomeh2">
        <h2>You died and the Wumpus ate your brain!</h2>
        <h2><a href="game.php">New Game</a></h2>
    </div>


</article>

</body>
</html>