<?php


namespace Game;


class Node
{
    public function __construct($row, $col) {
        $this->row = $row;
        $this->col = $col;
    }

    //Returns player color
    public function getPlayerColor()
    {
        return $this->playerColor;
    }

    public function setPlayerColor($color)
    {
        $this->playerColor = $color;
    }

    //Returns occupied
    public function getOccupied()
    {
        return $this->occupied;
    }
    public function getOccupiedPlayer(){//returns a string for the occupied player, "none" if no piece
        if($this->occupiedPiece === null){
            return "none";
        }
        else{
            return $this->occupiedPiece->getOwner();
        }
    }
    public function getCoordinates(){
        return [$this->row, $this->col];
    }

    public function getCoordArray() {
        $array = array($this->row, $this->col);
        return $array;
    }

    //Sets occupied
    public function setOccupied($occ = true)
    {
        $this->occupied = $occ;
    }
    public function setOccupiedPiece($pawn){
        $this->occupiedPiece = $pawn;
        if($pawn !== null){
            $this->playerColor = $pawn->getOwner();
            $this->occupied = true;
        }
        else{
            $this->playerColor = "none";
            $this->occupied = false;
        }

    }
    public function getOccupiedPiece(){
        return $this->occupiedPiece;
    }

    //Returns next, will return pointer to home stretch if conditions met
    public function getNext($pieceColor="default")
    {
        if($this->almost_home && $pieceColor == $this->almostHomeColor){
            return $this->nextGoingHome;
        }
        return $this->next;
    }

    //Returns prev
    public function getPrev()
    {
        return $this->prev;
    }

    public function setNext($node){
        $this->next = $node;
    }
    public function setPrev($node){
        $this->prev = $node;
    }
    public function isProtected(){
        return $this->protected;
    }
    public function setProtected($prot){
        $this->protected = $prot;
    }
    public function printNodePosition()
    {
        if(is_null($this->row))
            return "";
        $str = "$this->row, $this->col <br>";
        return $str;
    }
//    public function nodeInfoDump(){
//        $return = "X: ";
//        $return .= $this->row;
//        $return .= " Y: ";
//        $return .= $this->col;
//        $return .= " Occupied: ";
//        $return .= $this->occupied;
//        if($this->occupied){
//            $return .= " Occupied Piece Color: ";
//            $return .=  $this->playerColor;
//        }
//        return $return;
//    }

    public function setAlmostHome()
    {
        $this->almost_home = true;
    }


    public function setAlmostHomeColor($almostHomeColor)
    {
        $this->almostHomeColor = $almostHomeColor;
    }

    public function setNextGoingHome($node){
        $this->nextGoingHome = $node;
    }

    //created for testing purposes
    public function getNextGoingHome()
    {
        return $this->nextGoingHome;
    }

    public function isAlmostHome()
    {
        return $this->almost_home;
    }
    public function getAlmostHomeColor()
    {
        return $this->almostHomeColor;
    }

    private $next;
    private $prev;
    private $current = [];
    private $almost_home = false;
    private $almostHomeColor = "none";
    private $nextGoingHome = null;
    private $playerColor; // should be a lowercase string for use in GameView
    private $occupied = false;
    private $occupiedPiece = null;
    private $row = 0;
    private $col = 0;
    private $protected = false;
}