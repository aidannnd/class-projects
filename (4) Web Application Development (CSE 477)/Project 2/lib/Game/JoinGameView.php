<?php


namespace Game;


use phpDocumentor\Reflection\Types\Null_;

class JoinGameView
{
    public function __construct(array &$session, array $get, Site $site) {
        //no input provided
        $this->session = $session;
        $this->get = $get;
        $this->site = $site;
    }

    public function present() {
        $html = <<<HTML
<div class="content">
    <div class="form">
        <form action="form-post.php" method="post">
HTML;
        $joinGames = new GameJoins($this->site);
        $all = $joinGames->getAll();
        foreach ($all as $row) {
            $id = $row['gameID'];
            $red = $row['redID'];
            $green = $row['greenID'];
            $blue = $row['blueID'];
            $yellow = $row['yellowID'];
            $state = $row['gameState'];
            $num = 0;


// Checks game state
if ($state == "Waiting") {
    $html .= <<<HTML
<h1>Game $id</h1>
<ul>
HTML;

    if ($red == Null) {
        //post value is a serialized array with the color and game id
        $postValue = serialize(array("red", $id, $_SESSION['user']->getId()));
        $html .= <<<HTML
<li><p><input type="radio" name="color" value=$postValue id="$red"><label for="$red">Red</label></p></li>
HTML;
        $num += 1;
    }

    if ($green == Null) {
        $postValue = serialize(array("green", $id, $_SESSION['user']->getId()));
        $html .= <<<HTML
<li><p><input type="radio" name="color" value=$postValue id=$green><label for=$green>Green</label></p></li>
HTML;
        $num += 1;
    }

    if ($blue == Null) {
        $postValue = serialize(array("blue", $id,$_SESSION['user']->getId()));
        $html .= <<<HTML
<li><p><input type="radio" name="color" value=$postValue id="$blue"><label for="$blue">Blue</label></p></li>
HTML;
        $num += 1;
    }

    if ($yellow == Null) {
        $postValue = serialize(array("yellow", $id, $_SESSION['user']->getId()));
        $html .= <<<HTML
<li><p><input type="radio" name="color" value=$postValue id="$yellow"><label for="$yellow">Yellow</label></p></li>
HTML;
        $num += 1;
    }

    $html .= <<<HTML
</ul>
<p>$num more players can join this game.</p>
HTML;

}
        }
        $html .= <<<HTML
<br>
            <p>Select a color to join the game. Or Start a new Game!</p>
            <br>
<!--            SUBMITS VALUE OF THE TABLE NUMBER-->
            <p><input type="submit" name="formSubmit" value="Join Game" />
            <input type="submit" name="newGame" value="Start New Game" /></p>

</form></div>
</div>
HTML;
        return $html;
    }


    public function protect($site, $user) {
        if($user === null) {
            $this->protectRedirect = "../project2/index.php";
            return false;
        }

        if($user->getLoggedIn()) {
            return true;
        }

        $this->protectRedirect = "../project2/index.php";
        return false;
    }

    /**
     * Get any redirect page
     */
    public function getProtectRedirect() {
        return $this->protectRedirect;
    }

    private $protectRedirect = null;
    private $session;
    private $get;
    private $site;
}