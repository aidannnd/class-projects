<?php


namespace Game;


class SlideNode extends Node
{
    //Returns slide color
    public function getSlideColor()
    {
        return $this->slideColor;
    }

    public function setSlideColor($slideColor)
    {
        $this->slideColor = $slideColor;
    }
    public function getSlideEnd(){
        return $this->slideEnd;
    }
    public function setSlideEnd($slideEnd)
    {
        $this->slideEnd = $slideEnd;
    }
    public function printSlideEnd()
    {
        return $this->slideEnd->printNodePosition();
    }
    private $slideStart;
    private $slideEnd;
    private $slideColor;

}