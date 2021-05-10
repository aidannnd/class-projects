<?php
require __DIR__ . '/lib/game.inc.php';
require 'format.inc.php';
$view = new Game\GameView($game);
if(count($game->getPlayers()) == 0){
    header("location: index.php");
}
?>
<!doctype html>
<html lang="en-us">
<head>
    <meta charset="utf-8">
    <title>Sorry Sliders</title>
    <link href="lib/scss/game.css" type="text/css" rel="stylesheet" />
    <script>
        /**
         * Initialize monitoring for a server push command.
         * @param key Key we will receive.
         */
        function pushInit(key) {
            var conn = new WebSocket('ws://webdev.cse.msu.edu/ws');
            conn.onopen = function (e) {
                console.log("Connection to push established!");
                console.log(key);
                conn.send(key);
            };

            conn.onmessage = function (e) {
                try {
                    var msg = JSON.parse(e.data);
                    if (msg.cmd === "reload") {
                        location.reload();
                    }
                    else if(msg.cmd === "nextTurn"){
                        window.location.href = './post/nextTurn.php';
                    }
                } catch (e) {
                }
            };
        }
    </script>
</head>
<body>
<header>
    <nav><p><a href="index.php">New Game</a> |
            <a href="game.php">Game</a> |
            <a href="instructions.php">Help Page</a></p></nav>
</header>
<?php
echo '<div class="cur"><p>Current Player: ' ;
echo $game->getCurPlayerColor();
echo "</p></div>";
$gameID = $game->getID();
echo "<input type='hidden' id='gameId' name='gameId' value='$gameID'>";
?>

<?php echo $view->displayBoard();
$game->getPlayers()[$game->getCurrPlayer()]->getColor();
?>
<script>
    var id = document.getElementById("gameId").value;
    pushInit("team21game" + id);
</script>
</body>

</html>