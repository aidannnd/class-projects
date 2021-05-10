<?php

namespace Game;

class GameView
{

    public function __construct(Game $game) {
        $this->game = $game;
        $clickedTileStr = $game->getBoard()->getClickedTile();
        $this->clickedTile = explode(", ", $clickedTileStr);
    }

    //returns html for board (work in progress)
    public function displayBoard()
    {
        $this->populateArray();
        $html = <<<HTML
<form method="post" action="game-post.php">
<div class="game">
<div class="board">
HTML;

        $html .= $this->getTiles();
        $html .= <<<HTML
<!--I feel like this should be here but it makes it look worse when its in. </div>-->
</div>
<p><input type="submit" name="done" value="Done"></p></form>
HTML;
        return $html;
    }

    //Displays current tile clicked
    public function printClick()
    {
        return $this->game->getBoard()->getClickedTile();
    }
    private function getTiles(){
        $html = "";
        $gameBoardCount = $this->game->getBoard()->getGameBoard();
        for ($row = 0; $row < sizeof($gameBoardCount); $row++)
        {
            $html .= '<div class="row">';
            for ($col = 0; $col < sizeof($gameBoardCount); $col++) {
                //static card
                if($col == 5 and $row == 6){
                    $html .= '<img src="lib/images/card_back.png" alt="card" width="128" height="255">';

                }
                //current card
                if($col == 7 and $row == 6){
                    $currentCard = $this->game->getCurCard();
                    $cardView = new CardView($currentCard);
                    $card = $cardView->presentCard();
                    $html .= <<<HTML
                    <img src=$card alt="current card" width="128" height="255">
HTML;
                }

                //adds tiles that can not be clicked
                if(in_array("$row, $col", $this->blankTileArray)) {
                $html .= <<<HTML
<div class="cell2">
<form type="submit" name="cell"></form>
</div>
HTML;
                }
                //adds tiles that can be clicked
                else {
                    // check if the clicked node has just been occupied
                    $curNode = $this->game->getBoard()->getGameBoard()[$row][$col];
                    if ($curNode !== NULL and $curNode->getOccupied()) {
                        // cell should be occupied, place game piece
                        $color = $curNode->getPlayerColor();

                        // get the color in order of players currently in the game
                        /*
                        $color = $this->game->getPlayers()[$this->playersIndex]->getColor();
                        $this->playersIndex++;
                        echo count($this->game->getPlayers());
                        if ($this->playersIndex == count($this->game->getPlayers())) {
                            $this->playersIndex = 0;
                        }
*/
                        $html .= <<<HTML
<div class="cell">
<button type="submit" name="cell" value="$row, $col"
style="background: url('lib/images/$color.png'); background-size: contain;" ></button>
</div>
HTML;
                    } else { // selected node is not occupied
                        $html .= <<<HTML
<div class="cell">
<button type="submit" name="cell" value="$row, $col"
style="background: url('lib/images/empty.png'); background-size: contain;" ></button>
</div>
HTML;
                    }

                }
            }
            $html .= '</div>';
        }
        return $html;
    }

    //blankTileArray contains the squares on the board that can not be clicked.
    private function populateArray()
    {
        for ($col = 10; $col < 15; $col++){
            array_push($this->blankTileArray ,"$col, 14");
        }
        for ($col = 1; $col < 6; $col++){
            array_push($this->blankTileArray ,"$col, 1");
        }
        for ($col = 1; $col < 4; $col++){
            array_push($this->blankTileArray ,"$col, 6");
        }
        for ($col = 12; $col < 15; $col++){
            array_push($this->blankTileArray ,"$col, 9");
        }

        for ($row = 10; $row < 15; $row++){
            array_push($this->blankTileArray ,"1, $row");
        }
        for ($row = 3; $row < 12; $row++){
            array_push($this->blankTileArray ,"4, $row");
        }
        for ($row = 3; $row < 12; $row++){
            array_push($this->blankTileArray ,"5, $row");
        }
        for ($row = 4; $row < 11; $row++){
            array_push($this->blankTileArray ,"6, $row");
        }
        //tile [6,11] is replacing [6,15]
        for ($row = 12; $row < 16; $row++){
            array_push($this->blankTileArray ,"6, $row");
        }
        for ($row = 4; $row < 12; $row++){
            array_push($this->blankTileArray ,"7, $row");
        }
        for ($row = 4; $row < 12; $row++){
            array_push($this->blankTileArray ,"8, $row");
        }
        for ($row = 1; $row < 12; $row++){
            array_push($this->blankTileArray ,"9, $row");
        }
        for ($row = 4; $row < 13; $row++){
            array_push($this->blankTileArray ,"10, $row");
        }
        for ($row = 4; $row < 13; $row++){
            array_push($this->blankTileArray ,"11, $row");
        }
        for ($row = 1; $row < 6; $row++){
            array_push($this->blankTileArray ,"14, $row");
        }
        array_push($this->blankTileArray ,"12, 4");
        array_push($this->blankTileArray ,"12, 5");
        array_push($this->blankTileArray ,"3, 10");
        array_push($this->blankTileArray ,"3, 11");


    }
    public function printArray()
    {
        return print_r($this->blankTileArray);
    }

    public function printColor()
    {
        if(is_null($this->clickedTile)){
            return "null";
        }
        $row = intval($this->clickedTile[0]);
        $col = intval($this->clickedTile[1]);
        $node =  $this->game->getBoard()->getGameBoard()[$row][$col];
        return get_class($node);
    }

    public function printHomeColor()
    {
        if(is_null($this->clickedTile)){
            return "null";
        }
        $row = intval($this->clickedTile[0]);
        $col = intval($this->clickedTile[1]);
        $node =  $this->game->getBoard()->getGameBoard()[$row][$col];
        if(is_a($node,"Game\HomeNode")){
            return $node->getHomeColor();
        }

        return "Not a Home Node";
    }

    public function printEndSlider()
    {
        if(is_null($this->clickedTile)){
            return "null";
        }
        $row = intval($this->clickedTile[0]);
        $col = intval($this->clickedTile[1]);
        $node =  $this->game->getBoard()->getGameBoard()[$row][$col];
        if(is_a($node,"Game\SlideNode")){
            return $node->printSlideEnd();
        }
        return "Not a Slider";
    }

    public function printAlmostHome()
    {
        $row = intval($this->clickedTile[0]);
        $col = intval($this->clickedTile[1]);
        $node =  $this->game->getBoard()->getGameBoard()[$row][$col];
        return $node->isAlmostHome();
    }

    public function printNeighbors(){
        if(is_null($this->clickedTile)){
            return "null";
        }
        $row = intval($this->clickedTile[0]);
        $col = intval($this->clickedTile[1]);
        $node =  $this->game->getBoard()->getGameBoard()[$row][$col];
        $str = "";
        if(!is_null($node->getPrev())) {
            $str = "Previous Node: ";
            $str .= $node->getPrev()->printNodePosition();
        }
        if(!is_null($node->getNext())){
            $str .= "Next Node: ";
            $str .= $node->getNext()->printNodePosition();
        }

        return $str;
    }

    private $game;
    private $clickedTile;
    private $blankTileArray = array();
    private $playersIndex = 0;

    /**
     * @return array
     */
    public function getClickedTile()
    {
        return $this->clickedTile;
    }

    /**
     * @return array
     */
    public function getBlankTileArray()
    {
        return $this->blankTileArray;
    }
}
