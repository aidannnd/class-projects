<?php


namespace Game;

class HomeNode extends Node
{
    public function __construct($row, $col)
    {
        parent::__construct($row, $col);
        parent::setProtected(true);
    }

    public function getGoal()
    {
        return $this->isGoal;
    }

    public function setGoal($isGoal)
    {
        $this->isGoal = $isGoal;
    }

    public function setHomeColor($color) {
        $this->homeColor = $color;
    }

    //Returns home color
    public function getHomeColor()
    {
        return $this->homeColor;
    }

    private $homeColor;
    private $isGoal = false;
}