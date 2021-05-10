<?php
require 'format.inc.php';
require __DIR__ . '/lib/game.inc.php';
$view = new Game\SignUpView($_SESSION, $_GET);
?>
<!doctype html>
<html lang="en-us">
<head>
    <meta charset="utf-8">
    <title>Sorry Sign Up Page</title>
    <link href="lib/scss/game.css" type="text/css" rel="stylesheet" />
</head>
<body>
<?php echo present_header('Sorry! Registration Page'); ?>

<div class="content">
<div class="form">

    <?php
    echo $view->presentForm();
    ?>
</div>

</body>
</html>