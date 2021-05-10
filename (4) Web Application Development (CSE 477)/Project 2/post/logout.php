<?php
require '../lib/game.inc.php';
unset($_SESSION['user']);
header("Location: ../index.php");
