<?php

namespace Game;

class Board
{
    public function __construct() {
        //$this->node = $node;
        $this->constructBoard();
    }

    //populates board. not implemented yet
    private function constructBoard(){
        for ($row = 0; $row < 16; $row++) {
            for ($col = 0; $col < 16; $col++) {
                $this->gameBoard[$row][$col] = new Node($row, $col);
            }
        }

        //creates sliders
        $this->setHome();
        $this->setSliders();
        $this->setStart();
        //sets previous and next nodes for each node
        for ($col = 1; $col < 15; $col++) {
            $this->gameBoard[0][$col]->setPrev($this->gameBoard[0][$col - 1]);
            $this->gameBoard[0][$col]->setNext($this->gameBoard[0][$col + 1]);

        }
        for ($col = 1; $col < 15; $col++) {
            $this->gameBoard[15][$col]->setPrev($this->gameBoard[15][$col + 1]);
            $this->gameBoard[15][$col]->setNext($this->gameBoard[15][$col - 1]);
        }
        for ($row = 1; $row < 15; $row++) {
            $this->gameBoard[$row][0]->setPrev($this->gameBoard[$row + 1][0]);
            $this->gameBoard[$row][0]->setNext($this->gameBoard[$row - 1][0]);
        }
        for ($row = 1; $row < 15; $row++) {
            $this->gameBoard[$row][15]->setPrev($this->gameBoard[$row - 1][15]);
            $this->gameBoard[$row][15]->setNext($this->gameBoard[$row + 1][15]);
        }

        //sets up nodes on the edge
        $this->gameBoard[0][0]->setPrev($this->gameBoard[1][0]);
        $this->gameBoard[0][0]->setNext($this->gameBoard[0][1]);
        $this->gameBoard[15][0]->setPrev($this->gameBoard[15][1]);
        $this->gameBoard[15][0]->setNext($this->gameBoard[14][0]);
        $this->gameBoard[0][15]->setPrev($this->gameBoard[0][14]);
        $this->gameBoard[0][15]->setNext($this->gameBoard[1][15]);
        $this->gameBoard[15][15]->setPrev($this->gameBoard[14][15]);
        $this->gameBoard[15][15]->setNext($this->gameBoard[15][14]);


        //tile[6][11] replaces [6][15] due to the image shifting the tiles over
        $this->gameBoard[6][11]->setPrev($this->gameBoard[5][15]);
        $this->gameBoard[6][11]->setNext($this->gameBoard[7][15]);

        $this->gameBoard[7][15]->setPrev($this->gameBoard[6][11]);
        $this->gameBoard[5][15]->setNext($this->gameBoard[6][11]);


    }

    //sets up slider nodes
    private function setSliders(){
        //Yellow sliders
        $this->setSliders2(0,1, 4, "yellow");
        $this->setSliders2(0,9, 13, "yellow");

        //Red sliders
        $this->setSliders2(15,14, 11, "red");
        $this->setSliders2(15,6, 2, "red");

        //blue sliders
        $this->setSliders2(14,0, 11, "blue", true);
        $this->setSliders2(6,0, 2, "blue", true);

        //green sliders
        $this->setSliders2(1,15, 4, "green", true);
        $this->setSliders2(9,15, 13, "green", true);


    }
    public function setSliders2($x, $y, $z, $color, $vertical = false){
        unset($this->gameBoard[$x][$y]);
        $this->gameBoard[$x][$y] = new SlideNode($x, $y);
        $this->gameBoard[$x][$y]->setSlideColor($color);
        if($vertical) {
            $this->gameBoard[$x][$y]->setSlideEnd($this->gameBoard[$z][$y]);
        }
        else{
            $this->gameBoard[$x][$y]->setSlideEnd( $this->gameBoard[$x][$z]);
        }
    }
    private function setStart()
    {
        //yellow start
        $this->gameBoard[1][3]->setNext($this->gameBoard[0][4]);
        $this->gameBoard[1][5]->setNext($this->gameBoard[0][4]);
        $this->gameBoard[3][3]->setNext($this->gameBoard[0][4]);
        $this->gameBoard[3][5]->setNext($this->gameBoard[0][4]);

        //green start
        $this->gameBoard[3][12]->setNext($this->gameBoard[4][15]);
        $this->gameBoard[3][14]->setNext($this->gameBoard[4][15]);
        $this->gameBoard[5][12]->setNext($this->gameBoard[4][15]);
        $this->gameBoard[5][14]->setNext($this->gameBoard[4][15]);

        //red start
        $this->gameBoard[12][10]->setNext($this->gameBoard[15][11]);
        $this->gameBoard[12][12]->setNext($this->gameBoard[15][11]);
        $this->gameBoard[14][12]->setNext($this->gameBoard[15][11]);
        $this->gameBoard[14][10]->setNext($this->gameBoard[15][11]);


        //green start
        $this->gameBoard[10][1]->setNext($this->gameBoard[11][0]);
        $this->gameBoard[10][3]->setNext($this->gameBoard[11][0]);
        $this->gameBoard[12][1]->setNext($this->gameBoard[11][0]);
        $this->gameBoard[12][3]->setNext($this->gameBoard[11][0]);

        $this->gameBoard[0][2]->setAlmostHome();
        $this->gameBoard[0][2]->setAlmostHomeColor("yellow");
        $this->gameBoard[0][2]->setNextGoingHome($this->gameBoard[1][2]);

        $this->gameBoard[2][15]->setAlmostHome();
        $this->gameBoard[2][15]->setAlmostHomeColor("green");
        $this->gameBoard[2][15]->setNextGoingHome($this->gameBoard[2][14]);

        $this->gameBoard[15][13]->setAlmostHome();
        $this->gameBoard[15][13]->setAlmostHomeColor("red");
        $this->gameBoard[15][13]->setNextGoingHome($this->gameBoard[14][13]);

        $this->gameBoard[13][0]->setAlmostHome();
        $this->gameBoard[13][0]->setAlmostHomeColor("blue");
        $this->gameBoard[13][0]->setNextGoingHome($this->gameBoard[13][1]);

    }
    //set up home nodes
    private function setHome()
    {
        //red home
        for ($row = 9; $row < 15; $row++) {
            unset($this->gameBoard[$row][13]);
            $this->gameBoard[$row][13] = new HomeNode($row, 13);
            $this->gameBoard[$row][13]->setHomeColor("red");
        }
        for ($row = 9; $row < 15; $row++) {

            $this->gameBoard[$row][13]->setPrev($this->gameBoard[$row + 1][13]);
            $this->gameBoard[$row][13]->setNext($this->gameBoard[$row - 1][13]);

        }
        $this->gameBoard[9][13]->setGoal(true);
        $this->gameBoard[9][13]->setNext(null);

        //yellow home
        for ($row = 1; $row < 7; $row++) {
            unset($this->gameBoard[$row][2]);
            $this->gameBoard[$row][2] = new HomeNode($row, 2);
            $this->gameBoard[$row][2]->setHomeColor("yellow");

        }
        for ($row = 1; $row < 7; $row++) {

            $this->gameBoard[$row][2]->setPrev($this->gameBoard[$row - 1][2]);
            $this->gameBoard[$row][2]->setNext($this->gameBoard[$row + 1][2]);


        }
        $this->gameBoard[6][2]->setGoal(true);
        $this->gameBoard[6][2]->setNext(null);

        //green home
        for ($col = 9; $col < 15; $col++) {
            unset($this->gameBoard[2][$col]);
            $this->gameBoard[2][$col] = new HomeNode(2, $col);
            $this->gameBoard[2][$col]->setHomeColor("green");
        }
        for ($col = 9; $col < 15; $col++) {

            $this->gameBoard[2][$col]->setPrev($this->gameBoard[2][$col + 1]);
            $this->gameBoard[2][$col]->setNext($this->gameBoard[2][$col - 1]);

        }
        $this->gameBoard[2][9]->setGoal(true);
        $this->gameBoard[2][9]->setNext(null);

        //blue home
        for ($col = 1; $col < 7; $col++) {
            unset($this->gameBoard[13][$col]);
            $this->gameBoard[13][$col] = new HomeNode(13, $col);
            $this->gameBoard[13][$col]->setHomeColor("blue");
        }
        for ($col = 1; $col < 7; $col++) {
            $this->gameBoard[13][$col]->setPrev($this->gameBoard[13][$col - 1]);
            $this->gameBoard[13][$col]->setNext($this->gameBoard[13][$col + 1]);
        }
        $this->gameBoard[13][6]->setGoal(true);
        $this->gameBoard[13][6]->setNext(null);
//        $this->gameBoard[0][2]->setAlmost(;);

        //set almost home

    }
    //sets clicked tile
    public function onClick($tile)
    {
        $this->clickedTile = $tile;
    }

    public function getGameBoard()
    {
        return $this->gameBoard;
    }

    public function getClickedTile()
    {
        return $this->clickedTile;
    }

    public function getNodeAt($x, $y){
        return $this->gameBoard[$x][$y];
    }

    private $clickedTile;
    private $gameBoard = array();

}