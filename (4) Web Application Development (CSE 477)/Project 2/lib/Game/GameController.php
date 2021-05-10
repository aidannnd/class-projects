<?php


namespace Game;


class GameController
{
    public function __construct(Game $game, $post, $site)
    {
        $this->game = $game;
        $this->games = new Games($site);
        $this->gameJoins = new GameJoins($site);
        //checks to see if the player has moved or has no valid moves, then calls next turn
        if(isset($post['done'] )&& $game->isMyTurn() ) {

            if($game->getFinishedMoved() || !$game->checkIfValidMoves()){
                //$game->nextTurn();
                $games = new Games($site);
                $games->updateBoard($game->getID(),$game->getBoardStateJson());
                if($game->getDeck()->isFreshShuffle()){
                    $games->updateDeck($game->getID(), $game->getDeck()->getDeckJson());
                }

                //Contact all clients to advance the turn
                $key = "team21game" . $game->getID();
                $msg = json_encode(array('key' => $key, 'cmd' => 'nextTurn'));
                $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
                $sock_data = socket_connect($socket, '127.0.0.1', 8078);
                if (!$sock_data) {
                    echo "Failed to connect";
                } else {
                    socket_write($socket, $msg, strlen($msg));
                }
                socket_close($socket);
            }
        }

        //sets current clicked tile
        if(isset($post['cell']) && $game->isMyTurn()) {
            $clickedTile = strip_tags($post['cell']);
            $game->getBoard()->onClick($clickedTile);

            $values = explode(", ", $clickedTile);
            $curNode = $this->game->getBoard()->getGameBoard()[$values[0]][$values[1]];
            $game->parseClickedNode($curNode);
            //$curNode->setOccupied();
           // $curNode->setPlayerColor('yellow');
        }
    }
    public function networkTurn(){
        $res = $this->games->get($this->game->getID());
        $this->game->updateFromTable($res['board'], $res['deck']);
        $this->game->nextTurn();
    }
    public function isReset()
    {
        return $this->reset;
    }

    public function setReset($reset){
      $this->reset = $reset;
    }

    public function addPlayer($color){
        $this->game->addPlayer($color);
    }
    public function addPlayersFromTable(){
        $row = $this->gameJoins->get($this->game->getID());
        if($row['redID'] !== null){
            $this->addPlayer("red");
        }
        if($row['greenID'] !== null){
            $this->addPlayer("green");
        }
        if($row['blueID'] !== null){
            $this->addPlayer("blue");
        }
        if($row['yellowID'] !== null){
            $this->addPlayer("yellow");
        }
    }
    public function startGameAsHost($color, $userID){
        $this->game->clearPlayers();
        $gameID = $this->games->newGame($this->game->getBoardStateJson(), $this->game->getDeck()->getDeckJson());
        $this->game->setGameID($gameID);

        $this->gameJoins->newGame($gameID, $userID, $color);
        $this->game->setPlayerColor($color);
        return $gameID;
    }
    public function joinGame($color, $userID, $gameID){
        $this->game->setPlayerColor($color);
        $this->game->setGameID($gameID);
        $this->game->clearPlayers();
        $this->gameJoins->joinGame($gameID, $userID, $color);

        $res = $this->games->get($gameID);
        $this->game->joinGameSetup($res['deck']);//resets the deck and sets properly
        return $res['deck'];
    }
    public function resetPlayers(){
        $this->game->resetPlayers();
    }
    public function clearPlayers(){
        $this->game->clearPlayers();
    }
    public function checkGameEnded(){
        return $this->game->getGameEnded();
    }

    private $game;                  // The Game object we are controlling
    private $reset = false;         // True if we need to reset the game
    private $games;
    private $gameJoins;


}