<?php
require 'format.inc.php';
require __DIR__ . '/lib/game.inc.php';
?>
<!doctype html>
<html lang="en-us">
<head>
    <meta charset="utf-8">
    <title>Sorry Start Page</title>
    <link href="game.css" type="text/css" rel="stylesheet" />
</head>
<body>
<?php echo present_header('Sorry! New Game'); ?>

<div class="content">
    <div class="form">
    <form action="form-post.php" method="post">

        <p><input type="checkbox" name="red" id="red"><label for="red">Red</label></p>
        <p><input type="checkbox" name="green" id="green"><label for="green">Green</label></p>
        <p><input type="checkbox" name="blue" id="blue"><label for="blue">Blue</label></p>
        <p><input type="checkbox" name="yellow" id="yellow"><label for="yellow">Yellow</label></p>
        <br>
        <p>Select at least two players to play the game.</p>
        <br>
        <p><input type="submit" name="formSubmit" value="Submit" /></p>

    </form></div>

</div>

</body>
</html>