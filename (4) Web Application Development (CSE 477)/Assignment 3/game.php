<?php
require 'format.inc.php';
require 'wumpus.inc.php';

$room = 1; // the room we are in.
$birds = 7;  // room with the birds
$pits = array(3, 10, 13);    // rooms with a bottomless pit
$wumpus = 16;

$cave = cave_array(); // Get the cave
if(isset($_GET['r']) && isset($cave[$_GET['r']]) ) {
    // we have been passed a room number
    $room = $_GET['r'];
}

// if in birds room (7), move to room 10
if ($room == $birds) {
    $room = 10;
}

// if in pits room (3, 10, 13) or in wumpus room (16), move to lose page
if (in_array($room, $pits) or $room == $wumpus) {
    header("Location: lose.php");
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Stalking the Wumpus</title>
    <link href="main.css" type="text/css" rel="stylesheet" />
</head>
<body>

<?php echo present_header("Stalking the Wumpus"); ?>

<article>
    <figure><img src="images/cave.jpg" width="600" height="325" alt="Cave 1"/></figure>
    <div class="gamephp">
        <?php
        // display date and clock
        echo '<p>' . date("g:ia l, F j, Y") . '</p>';
        ?>
    </div>

    <h2>You are in room <?php echo $room; ?></h2>

    <div class="gamesec">
        <?php
        // determine if birds are in adjacent rooms
        $birdstext = "&nbsp;";
        if ($cave[$room][0] == $birds or $cave[$room][1] == $birds or $cave[$room][2] == $birds) {
            $birdstext = "You hear birds!";
        }

        // determine if birds are in adjacent rooms
        $drafttext = "&nbsp;";

        if (in_array($cave[$room][0], $pits) or in_array($cave[$room][1], $pits) or in_array($cave[$room][2], $pits)) {
            $drafttext = "You feel a draft!";
        }

        // determine if wumpus is in an adjacent room 2 away
        $wumpustext = "&nbsp;";

        for ($i = 0; $i < 3; $i++) {
            if (in_array($wumpus, $cave[$cave[$room][$i]])) {
                $wumpustext = "You smell a wumpus!";
                break;
            }
        }

        // determine if wumpus is in an adjacent room
        if (in_array($wumpus, $cave[$room])) {
            $wumpustext = "You smell a wumpus!";
        }
        ?>

        <h2><?php echo $birdstext ?></h2>
        <h2><?php echo $drafttext ?></h2>
        <h2><?php echo $wumpustext ?></h2>
    </div>

    <div class="rooms">
        <div class="room"><img src="images/cave2.jpg" width="180" height="135" alt="Cave 2"/>
            <p><a href="game.php?r=<?php echo $cave[$room][0]; ?>"><?php echo $cave[$room][0]; ?></a></p>
            <p><a href="game.php?r=<?php echo $room; ?>&a=<?php echo $cave[$room][0]; ?>">Shoot Arrow</a></p>
        </div><div class="room"><img src="images/cave2.jpg" width="180" height="135" alt="Cave 2"/>
            <p><a href="game.php?r=<?php echo $cave[$room][1]; ?>"><?php echo $cave[$room][1]; ?></a>
            </p><p><a href="game.php?r=<?php echo $room; ?>&a=<?php echo $cave[$room][1]; ?>">Shoot Arrow</a></p>
        </div><div class="room"><img src="images/cave2.jpg" width="180" height="135" alt="Cave 2"/>
            <p><a href="game.php?r=<?php echo $cave[$room][2]; ?>"><?php echo $cave[$room][2]; ?></a></p>
            <p><a href="game.php?r=<?php echo $room; ?>&a=<?php echo $cave[$room][2]; ?>">Shoot Arrow</a></p>
        </div>
    </div>

    <?php
    if(isset($_GET['a']) && isset($cave[$_GET['a']]) ) {
        // we have been passed an arrow shot
        $shotroom = $_GET['a'];
        if ($shotroom ==  $wumpus) {
            // the user killed the wumpus
            header("Location: win.php");
            exit;
        }
    }
    ?>

    <div class="endheader">
        <h2>You have 3 arrows remaining.</h2>
    </div>

</article>

</body>
</html>