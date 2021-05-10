<?php
require 'format.inc.php';
require __DIR__ . '/lib/game.inc.php';
$view = new Game\WaitingPageView($_SESSION, $_GET, $site, $game);
if(count($game->getPlayers()) != 0){
    header("location: game.php");
}
?>
<!doctype html>
<html lang="en-us">
<head>
    <meta charset="utf-8">
    <title>Waiting Page</title>
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
                    else if(msg.cmd === "startGame"){
                        window.location.href = 'startGame.php';
                    }
                } catch (e) {
                }
            };
        }
    </script>
</head>
<body>

<?php echo present_header("Sorry! Waiting Page"); ?>

<?php
echo $view->present($site);
$gameID = $game->getID();
echo "<input type='hidden' id='gameId' name='gameId' value='$gameID'>";
?>
<script>
    var id = document.getElementById("gameId").value;
    pushInit("team21game" + id);
</script>
</body>
</html>