<?php


namespace Game;


class WaitingPageView
{
    public function __construct(array &$session, array $get, Site $site, Game $game) {

        //no input provided
        $this->session = $session;
        $this->get = $get;
        $this->site = $site;
        $joinGames = new GameJoins($site);
        $row = $joinGames->get($game->getID());
        $this->player_count = 0;
        $this->row = $row;
        if($row['redID'] !== null){
            $this->player_count += 1;
        }
        if($row['greenID'] !== null){
            $this->player_count += 1;
        }
        if($row['blueID'] !== null){
            $this->player_count += 1;
        }
        if($row['yellowID'] !== null){
            $this->player_count += 1;
        }
    }


    public function present() {
        if($this->player_count > 1) {
            $html = <<<HTML



<div class="content">
    <div class="form">
        <form action="start-post.php" method="post">
            <p> Waiting for more players to join the game...</p>
            <br>
            <h1>Current Players: $this->player_count / 4</h1>
            <br> 
            <br>
            <p><input type="submit" name="formSubmit" value="Start Game" /></p>
        </form>
    </div>
</div>

HTML;
        }
        else{
            $html = <<<HTML



<div class="content">
    <div class="form">
        <form>
            <p> Waiting for more players to join the game...</p>
            <br>
            <h1>Current Players: $this->player_count / 4</h1>
            <br> 
            <br>
            <p><input type="submit" name="formSubmit" value="Start Game" /></p>
        </form>
    </div>
</div>

HTML;
        }

        return $html;
    }

    private $player_count = 1;
    private $session;
    private $get;
    private $site;

}