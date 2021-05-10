<?php


namespace Game;


class Player {
    private $pieces = []; // pieces (Pawn) the player owns
    private $color; // color of the player
    private $numHome = 0; // number of pawns the player has gotten home
    //private $id;		// The internal ID for the user
    //private $email;		// Email address
    //private $name; 		// Name as last, first
    private $user_id;
    private $game_id;

    public function __construct($pieces, $color){
        foreach ($pieces as &$piece) {
            array_push($this->pieces, $piece);
        }

        $this->color = $color;
    }

    public function getPieces() {
        return $this->pieces;
    }
    public function checkWin(){
        foreach($this->pieces as $piece){
            if(!$piece->isHome()){
                return false;
            }
        }
        return true;
    }

    public function getColor() {
        return $this->color;
    }

    public function pieceHome() {
        $this->numHome++;
        if ($this->numHome >= 4) {
            return true;
        }
        return false;
    }

    /**
     * Sets the current nodes of pieces to corresponding value in param nodes. For use maintaining board state online
     * @param $nodes Array of nodes to set piece current nodes
     */
    public function setPieceLocations($nodes){
        for($i = 0; $i < 4; $i++){
            $this->pieces[$i]->setCurrentNode($nodes[$i]);
        }
    }

    /**
     * Returns an array containing the current coordinates of the player's pieces
     * This will be used by the game to store the current board state in the database
     */
    public function getPiecesCords(){
        $cords = [];
        foreach($this->pieces as $piece){
            array_push($cords, $piece->getCurrentNode()->getCoordinates());
        }
        return $cords;
    }
}
