<?php
require 'format.inc.php';
require __DIR__ . '/lib/game.inc.php';
?>
<!doctype html>
<html lang="en-us">
<head>
    <meta charset="utf-8">
    <title>Sorry Help Page</title>
    <link href="lib/scss/game.css" type="text/css" rel="stylesheet" />
</head>
<body>
<?php echo present_header("Sorry! Welcome"); ?>
<div class="content">
    <h1>Welcome to Sorry! the game</h1>
    <p>Please <a href="login.php">login</a> or <a href="signup.php">sign up</a> in order to play!</p>
    <p>Once you are logged in you can <a href="join-game.php">join a game!</a></p>
    <p>Please visit the <a href="instructions.php">help page</a> before you begin. </p>
    <p>Enjoy your games of sorry!</p>
</div>


</body>
</html>