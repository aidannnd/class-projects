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
    <link href="game.css" type="text/css" rel="stylesheet" />
</head>
<body>
<?php echo present_header("Sorry!"); ?>
<?php
echo '<div class="cur"><p>Current Player: ' ;
echo $game->getCurPlayerColor();
echo "</p></div>";
?>

<?php echo $view->displayBoard();
$game->getPlayers()[$game->getCurrPlayer()]->getColor();?>




</body>
</html>