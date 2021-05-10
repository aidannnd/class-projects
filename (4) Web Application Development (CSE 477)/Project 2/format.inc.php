<?php

/**
 * Create the HTML for the header block
 * @param $title The page title
 * @return string HTML for the header block
 */
function present_header($title) {
    $html = <<<HTML
<header>
<nav><p><a href="login.php">Login</a> |
<a href="signup.php">Sign Up</a> |
<a href="instructions.php">Help Page</a></p></nav>
<h1><a href="index.php">$title</a></h1>
</header>
HTML;

    return $html;
}

