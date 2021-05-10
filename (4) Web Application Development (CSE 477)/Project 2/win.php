<?php
require 'format.inc.php';
require __DIR__ . '/lib/game.inc.php';
if(!$game->getGameEnded()){
    header("location: index.php");
}
if($game->getWinner() == $game->getPlayerColor()){
   // $games = new \Game\Games($site);
   // $games->deleteGame($game->getID());
}
?>

<!doctype html>
<html lang="en-us">
<head>
    <meta charset="utf-8">
    <title>Win</title>
    <link href="lib/scss/game.css" type="text/css" rel="stylesheet" />
</head>
<body>

<?php echo present_header("Sorry!"); ?>
<?php
echo '<div class="win">';
echo '<h1>';
echo strtoupper($game->getWinner()), " WINS!";
echo '</h1>';
echo '<p><a href="join-game.php">New Game</a></p>';
echo '</div>'?>

<div class="content">

</div>

</body>
</html>
