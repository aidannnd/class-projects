<?php


namespace Game;


class Player {
    private $pieces = []; // pieces (Pawn) the player owns
    private $color; // color of the player
    private $numHome = 0; // number of pawns the player has gotten home

    public function __construct($pieces, $color){
        foreach ($pieces as &$piece) {
            array_push($this->pieces, $piece);
        }

        $this->color = $color;
    }

    public function getPieces() {
        return $this->pieces;
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
}
