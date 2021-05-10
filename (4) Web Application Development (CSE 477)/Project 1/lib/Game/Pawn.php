<?php

namespace Game;

class Pawn {
    private $owner; // color that the pawn belongs too
    private $current_space; // Node the pawn is currently on
    private $start_tile; // Node the pawn starts on
    private $pawn_number; // number 0 through 3 indicating the pawn's index in the player pieces array
    private $protected = false; // true if pawn in protected spaces, ie home stretch
    private $home = false;
    private $home_tile; //Where the pawn belongs in home

    public function __construct($owner, $current_space, $start_tile, $num, $home = null) {
        $this->owner = $owner;
        $this->current_space = $current_space;
        $this->start_tile = $start_tile;
        $this->pawn_number = $num;
        $this->home_tile = $home;
    }

    public function getCurrentNode() {
        return $this->current_space;
    }
    public function setHome($h = true){//sets the home to true and sends the pawn home
        $this->home = $h;
        $this->setCurrentNode($this->home_tile);
    }
    public function isHome(){
        return $this->home;
    }

    public function setCurrentNode($node, $swapping = false) {
        if(!$swapping) {
            $this->current_space->setOccupiedPiece(null);
            $this->current_space->setOccupied(false);
        }

        $this->current_space = $node;
        $this->current_space->setOccupiedPiece($this);
        $this->current_space->setOccupied(true);
        $this->protected = $node->isProtected();
    }

    public function getStartNode() {
        return $this->start_tile;
    }

    public function getOwner() {
        return $this->owner;
    }

    public function getPawnNum() {
        return $this->pawn_number;
    }

    public function returnToStart() {
        $this->current_space->setOccupiedPiece(null);
        $this->current_space->setOccupied(false);
        $this->current_space = $this->start_tile;
        $this->current_space->setOccupiedPiece($this);
        $this->current_space->setOccupied(true);
        $this->protected = false;
    }
    public function atStart(){//returns true if at start, false otherwise
        if($this->current_space === $this->start_tile){
            return true;
        }
        return false;

    }
    public function isProtected(){//returns true if protected, false otherwise
        return $this->protected;
    }
    public function setProtected($prot){//sets protected status
        $this->protected = $prot;
    }
}
