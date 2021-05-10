<?php


namespace Game;


class GameController
{
    public function __construct(Game $game, $post)
    {
        $this->game = $game;

        //checks to see if the player has moved or has no valid moves, then calls next turn
        if(isset($post['done']) ) {
            if($game->getFinishedMoved() || !$game->checkIfValidMoves()){
                $game->nextTurn();
            }
        }

        //sets current clicked tile
        if(isset($post['cell']) ) {
            $clickedTile = strip_tags($post['cell']);
            $game->getBoard()->onClick($clickedTile);

            $values = explode(", ", $clickedTile);
            $curNode = $this->game->getBoard()->getGameBoard()[$values[0]][$values[1]];
            $game->parseClickedNode($curNode);
            //$curNode->setOccupied();
           // $curNode->setPlayerColor('yellow');
        }
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

    public function resetPlayers(){
        $this->game->resetPlayers();
    }
    public function checkGameEnded(){
        return $this->game->getGameEnded();
    }

    private $game;                  // The Game object we are controlling
    private $reset = false;         // True if we need to reset the game


}