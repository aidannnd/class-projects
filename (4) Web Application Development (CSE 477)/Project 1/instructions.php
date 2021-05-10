<?php
require 'format.inc.php';
require __DIR__ . '/lib/game.inc.php';
?>
<!doctype html>
<html lang="en-us">
<head>
    <meta charset="utf-8">
    <title>Sorry Help Page</title>
    <link href="game.css" type="text/css" rel="stylesheet" />
</head>
<body>
<?php echo present_header("Sorry! Instructions"); ?>

<div class="content">
    <h1>About Team 21</h1>
    <ul><li><p>
                Members: Aidan Delfuoco, Colin Duyck, Michael Lin, Morgan Mundell, Varsha Vinod.
            </p></li></ul>
    <h1>Set Up</h1>
    <ul>
    <li><p>Each player chooses a color from the <a href="index.php">start page.</a></p></li>
    <li><p>There can be between 2-4 players.</p></li>
    </ul><br>
    <h1>How to Play</h1>
    <ul>
        <li><p>Each player has four pawns of the chosen color. Players will have turns in order.</p></li>
        <li><p>Each turn a player must pick up a card from the pile. To move a pawn from start, a 1 or
                2 must be drawn.</p></li>
        <li><p>Pawns will be moved by a cards instruction. Most cards will move a pawn forward x amount
                of spaces.</p></li>
        <li><p>There are five special cards. </p></li>
        <li><p>A Sorry card allows the player to switch positions of one of their pawns in start with
                another pawn on the board.</p></li>
        <li><p>A 4 card makes the player move one pawn backwards four spaces.</p></li>
        <li><p>A 7 card allows a player to split the move between two of their pawns.</p></li>
        <li><p>A 10 card allows a player to either move a pawn ten spaces forward or one space back.</p></li>
        <li><p>An 11 card allows a player to move one pawn eleven spaces forward or switch positions
                with an opponent pawn.</p></li>
        <li><p>A pawn may jump over another pawn when moving.</p></li>
        <li><p>Only one pawn may occupy a square.</p></li>
        <li><p>A pawn that lands on an opponents pawn moves that pawn back to its own Start.</p></li>
        <li><p>The last five squares before each player's Home are "Safety Zones". Pawns inside the
                Safety Zones are immune to being switched by opponents' pawns</p></li>
        <li><p>A player wins the game when all four of their pawns are home.</p></li>
    </ul>
    <br>
    <h1>This Project was developed by Team 21. Team 21 is</h1>
    <ul>
        <li><p>Colin Duyck</p></li>
        <li><p>Michael Lin</p></li>
        <li><p>Aiden Delfuoco</p></li>
        <li><p>Morgan Mundell</p></li>
        <li><p>Varsha Vinod</p></li>
    </ul>

</div>


</body>
</html>