<?php

namespace Game;

class Game
{
    const RED_X = 13;
    const RED_Y = 11;
    const BLUE_X = 11;
    const BLUE_Y = 2;
    const GREEN_X = 4;
    const GREEN_Y = 13;
    const YELLOW_X = 2;
    const YELLOW_Y = 4;
    const RED_HOME_X = 8;
    const RED_HOME_Y = 13;
    const GREEN_HOME_X = 2;
    const GREEN_HOME_Y = 8;
    const BLUE_HOME_X = 13;
    const BLUE_HOME_Y = 7;
    const YELLOW_HOME_X = 7;
    const YELLOW_HOME_Y = 2;

    public function __construct($playerArray = []) {//playerArray will be passed in based on what colors are selected
        $this->board = new Board();
        $this->deck = new Deck();
        $this->players = $playerArray;
        $this->newCard();
    }

    //Returns board
    public function getBoard()
    {
        return $this->board;
    }
    public function getDeck(){
        return $this->deck;
    }
    private function newCard(){
        $this->curCard = $this->deck->drawCard();
    }
    public function getCurCard(){//returns the current card
        return $this->curCard;
    }
    public function setCurCard($card){//sets the current card, used for testing
        $this->curCard = $card;
    }
    public function nextTurn(){//advances the turn and draws a new card, if curCard is 2 player stays same
        if($this->curCard != 2) {
            $this->curPlayer++;
            if ($this->curPlayer >= count($this->players)) {
                $this->curPlayer = 0;
            }
            $this->selectedPawn = null;

        }
        $this->finishedMoved = false;
        $this->newCard();
    }
    /*
     * Main function for the game logic, will return the valid moves for the selected pawn based on curCard.
     * @returns: Array of all legal moves for a selected pawn, this will include swaps as well
     */
    public function getValidMoves($pawn){
        if($pawn->isHome()){
            return [];
        }
        $pawnColor = $pawn->getOwner();
        $legalMoves = [];
        $curNode = $pawn->getCurrentNode();
        $startNode = $pawn->getStartNode();
        if($pawn->atStart()){
            if($this->curCard != 1 && $this->curCard != 2 && $this->curCard != Deck::SORRY){
                return $legalMoves;
            }
            else if($this->curCard == 1 || $this->curCard == 2){
                $curNode = $curNode->getNext($pawnColor);
                if($curNode->getOccupiedPlayer() != $this->players[$this->curPlayer]->getColor()) {//can't move on top of our own piece
                    array_push($legalMoves, $curNode->getCoordinates());
                }
                return $legalMoves;
            }
        }
        switch ($this->curCard){
            case 1:
            case 2:
            case 3: //The standard movement cards
            case 5:
            case 8:
            case 12:
                for($i = 0; $i < $this->curCard; $i++){
                    $curNode = $curNode->getNext($pawnColor);
                    if($curNode === null){//can happen if movement would take a player past home
                        break 2;//exit both the for loop and the switch
                    }
                }
                if($curNode->getOccupiedPlayer() != $this->players[$this->curPlayer]->getColor()) {//can't move on top of our own piece
                    array_push($legalMoves, $curNode->getCoordinates());
                }
                break;
            case 4://moving backwards
                for($i = 0; $i < 4; $i++){
                    $curNode = $curNode->getPrev();
                    if($curNode === null){//this should never happen, but for safety reasons we'll check anyway
                        break 2;
                    }
                }
                if($curNode->getOccupiedPlayer() != $this->players[$this->curPlayer]->getColor()) {//can't move on top of our own piece
                    array_push($legalMoves, $curNode->getCoordinates());
                }
                break;
            case 7://split movement
                $storeNode = $curNode;
                for($i = 0; $i < 7; $i++){
                    $curNode = $curNode->getNext($pawnColor);
                    if($curNode === null){
                        break; //only a single break here, split movement might be possible;
                    }
                }
                if($curNode !== null && $curNode->getOccupiedPlayer() != $this->players[$this->curPlayer]->getColor()){
                    array_push($legalMoves, $curNode->getCoordinates());
                }
                $curNode = $storeNode;
                for($i = 1; $i < 7; $i++){
                    $curNode = $curNode->getNext($pawnColor);
                    if($curNode === null){
                        break;
                    }
                    if($this->checkValidSplit(7-$i, $pawn, $curNode)){
                        array_push($legalMoves, $curNode->getCoordinates());
                    }
                }
                break;
            case 10: //move forward 10 or back 1
                $storeNode = $curNode;
                for($i = 0; $i < 10; $i++){
                    $curNode = $curNode->getNext($pawnColor);
                    if($curNode === null){
                        break; //only a single break here, backwards movement might be possible;
                    }
                }
                if($curNode !== null && $curNode->getOccupiedPlayer() != $this->players[$this->curPlayer]->getColor()){
                    array_push($legalMoves, $curNode->getCoordinates());
                }
                $backNode = $storeNode->getPrev();
                if($backNode !== null && $backNode->getOccupiedPlayer() != $this->players[$this->curPlayer]->getColor()){
                    array_push($legalMoves, $backNode->getCoordinates());
                }
                break;
            case 11: //move forward 11 or swap
                for($i = 0; $i < 11; $i++){
                    $curNode = $curNode->getNext($pawnColor);
                    if($curNode === null){
                        break; //only a single break here, swaps might be possible;
                    }
                }
                if($curNode !== null && $curNode->getOccupiedPlayer() != $this->players[$this->curPlayer]->getColor()){
                    array_push($legalMoves, $curNode->getCoordinates());
                }
                //swap logic below
                if($pawn->isProtected()){
                    break;
                }
                for($i = 0; $i < count($this->players); $i++){//iterate over player array
                    if($i != $this->curPlayer){//can't swap with own pieces
                        $pieces = $this->players[$i]->getPieces();
                        foreach($pieces as $piece){
                            if(!$piece->isProtected() && !$piece->atStart()){//if piece not home or in start
                                array_push($legalMoves, $piece->getCurrentNode()->getCoordinates());
                            }
                        }
                    }
                }
                break;
            case DECK::SORRY: //Sorry card
                if($curNode !== $startNode){
                    break;
                }
                for($i = 0; $i < count($this->players); $i++){//iterate over player array
                    if($i != $this->curPlayer){//can't swap with own pieces
                        $pieces = $this->players[$i]->getPieces();
                        foreach($pieces as $piece){
                            if(!$piece->isProtected() && !$piece->atStart()){//if piece not home or in start
                                array_push($legalMoves, $piece->getCurrentNode()->getCoordinates());
                            }
                        }
                    }
                }
                break;


        }
        return $legalMoves;
    }
    /*
     * Helper function for getValidMoves(), takes in a parameter equal to the remainder on a split. callingPawn
     * is current moving pawn, since you cannot split with yourself
     * Returns true if legal split, false otherwise.
     * Legal split noted by at least one other pawn having a legal move forward equal to the remainder
     */
    public function checkValidSplit($remainder, $callingPawn, $move1Node){
        $pawnColor = $callingPawn->getOwner();
        foreach($this->players[$this->curPlayer]->getPieces() as $piece){
            if($piece !== $callingPawn && !$piece->atStart()){//can't split if calling pawn or pawn at start
                $curNode = $piece->getCurrentNode();
                for($i = 0; $i < $remainder; $i++){
                    $curNode = $curNode->getNext($pawnColor);
                    if($curNode === null){//can happen if movement would take a player past home
                        break 1;//exit both the for loop
                    }
                }
                if($curNode !== null && $curNode !== $move1Node){
                    if($curNode->getOccupiedPlayer() != $this->players[$this->curPlayer]->getColor() || $curNode->getOccupiedPiece() === $callingPawn){//if occupied by player color, not valid split unless occupied pawn is the calling split pawn as it will move
                        return true;
                    }
                }
            }
        }
        return false;
    }
    /*
     * Check to see if the current player and card combination have any legal moves, this will be used to check if a
     * player's turn is skipped based on the drawn card
     * @returns: true if current player has legal moves, false otherwise
     */
    public function checkIfValidMoves(){
        foreach($this->players[$this->curPlayer]->getPieces() as $piece){
            if(!$piece->isHome()) {
                if (count($this->getValidMoves($piece)) > 0) {
                    return true;
                }
            }
        }
        return false;
    }


    public function addPlayer($player){
        // way to add player pieces should probably change
        $pieces = [];
        $x = 0;
        $y = 0;
        $x2 = 0;
        $y2 = 0;



        for ($i = 0; $i < 4; $i++){
            if ($player == "red"){
                $x = self::RED_X;
                $y = self::RED_Y;
                $x2 = self::RED_HOME_X;
                $y2 = self::RED_HOME_Y;
            }
            elseif ($player == "blue"){
                $x = self::BLUE_X;
                $y = self::BLUE_Y;
                $x2 = self::BLUE_HOME_X;
                $y2 = self::BLUE_HOME_Y;
            }
            elseif ($player == "green") {
                $x = self::GREEN_X;
                $y = self::GREEN_Y;
                $x2 = self::GREEN_HOME_X;
                $y2 = self::GREEN_HOME_Y;
            }
            else{
                $x = self::YELLOW_X;
                $y = self::YELLOW_Y;
                $x2 = self::YELLOW_HOME_X;
                $y2 = self::YELLOW_HOME_Y;
            }
            if ($i==0 || $i==1){
                $x += 1;
                $x2 += 1;
            }
            else {
                $x -= 1;
                $x2 -= 1;
            }
            if($i==0 || $i== 2){
                $y += 1;
                $y2 += 1;
            }
            else{
                $y -= 1;
                $y2 -= 1;
            }

            $node = $this->board->getNodeAt($x, $y);
            $HomeNode = $this->board->getNodeAt($x2, $y2);

            $newpiece = new Pawn($player, $node, $node, $i, $HomeNode);

            $node->setOccupied();
            $node->setOccupiedPiece($newpiece);

            array_push($pieces, $newpiece);
        }

        $newplayer = new Player($pieces, $player);

        array_push($this->players, $newplayer);

        $this->numPlayers += 1;
    }

    public function getNumPlayers(){
        return $this->numPlayers;
    }
    public function getPlayers(){
        return $this->players;
    }
    public function setSelectedPawn($pawn){
        $this->selectedPawn = $pawn;
    }
    public function getFinishedMoved(){
        return $this->finishedMoved;
    }
    public function parseClickedNode($clickedNode){//function called by the game controller when a Node is clicked
        if($clickedNode->getOccupiedPlayer() == $this->players[$this->curPlayer]->getColor() && !$clickedNode->getOccupiedPiece()->isHome()){//we have clicked on a tile containing the current player's piece and the piece is not home
            $this->selectedPawn = $clickedNode->getOccupiedPiece();
        }
        else if($this->selectedPawn !== null && !$this->finishedMoved){//we have clicked on a different tile, likely trying to make a move
            if(!$this->splitting){
                $storeNode = $this->selectedPawn->getCurrentNode();
                $moveArray = $this->getValidMoves($this->selectedPawn);
                if(in_array($clickedNode->getCoordinates(), $moveArray)){
                    $this->executeMovement($clickedNode);
                    if($this->curCard != 7){
                        $this->finishedMoved = true;
                    }
                    else{
                        for($i = 1; $i < 7; $i++){
                            $storeNode = $storeNode->getNext($this->selectedPawn->getOwner());
                            if($storeNode === $clickedNode){
                                $this->splitting = true;
                                $this->splitRemainder = 7 - $i;
                                $this->splittingPawn = $this->selectedPawn;
                                break;
                            }
                            if($storeNode === null){
                                break;
                            }

                        }
                        if(!$this->splitting){//we moved as normal
                            $this->finishedMoved = true;
                        }
                    }
                }
            }
            else if($this->selectedPawn !== $this->splittingPawn){//second portion of a split
                if($this->checkAndExecuteSplit($clickedNode)){
                    $this->splitting = false;
                    $this->splittingPawn = null;
                    $this->finishedMoved = true;
                }
            }


        }
    }
    private function checkAndExecuteSplit($targetNode){//executes the second part of a split if valid. Returns true on success, false on failure
        $curNode= $this->selectedPawn->getCurrentNode();
        $pawnColor = $this->selectedPawn->getOwner();
        for($i = 0; $i < $this->splitRemainder; $i++){
            $curNode = $curNode->getNext($pawnColor);
            if($curNode === null){//can happen if movement would take a player past home
                return false;
            }
        }
        if($curNode !== $targetNode){
            return false;
        }
        if($curNode->getOccupiedPlayer() != $this->players[$this->curPlayer]->getColor()) {//can't move on top of our own piece
            $this->executeMovement($targetNode);
            return true;
        }
        return false;
    }
    private function executeMovement($targetNode){//moves selectedPawn to targetNode and handles any game logic. Assumes targetNode is a valid move.
        $swapping = false;
        if($targetNode->getOccupied()){
            if($this->curCard == 11){//swapping
                $swapTarget = $targetNode->getOccupiedPiece();
                $swapTarget->setCurrentNode($this->selectedPawn->getCurrentNode(), true);
                $swapping = true;
                $newSwapNode = $swapTarget->getCurrentNode();
                $swapPlayerColor = $swapTarget->getOwner();
                if(is_a($newSwapNode, "\Game\SlideNode")){
                    if($newSwapNode->getSlideColor() != $swapPlayerColor){
                        $curNode = $newSwapNode;
                        $slideEnd = $newSwapNode->getSlideEnd();
                        while($curNode !== $slideEnd){
                            $curNode = $curNode->getNext();
                            if($curNode->getOccupied()){
                                $curNode->getOccupiedPiece()->returnToStart();
                            }

                        }
                        $swapTarget->setCurrentNode($slideEnd);
                    }
                }

            }
            else{
                $targetNode->getOccupiedPiece()->returnToStart();
            }
        }
        $this->selectedPawn->setCurrentNode($targetNode, $swapping);
        if(is_a($targetNode, "\Game\HomeNode")) {
            if($targetNode->getGoal()){
                $targetNode->setOccupiedPiece(null);
                $this->selectedPawn->setHome(true);//this will also send the pawn to its correct home location
                $this->selectedPawn->setProtected(true);

                // check if game ends
                if($this->players[$this->curPlayer]->pieceHome()){
                    $this->gameEnded = true;
                    $this->winner = $this->players[$this->curPlayer]->getColor();
                }
            }

        }

        if(is_a($targetNode, "\Game\SlideNode")){
            if($targetNode->getSlideColor() != $this->players[$this->curPlayer]->getColor()){
                $curNode = $targetNode;
                $slideEnd = $targetNode->getSlideEnd();
                while($curNode !== $slideEnd){
                    $curNode = $curNode->getNext();
                    if($curNode->getOccupied()){
                        $curNode->getOccupiedPiece()->returnToStart();
                    }

                }
                $this->selectedPawn->setCurrentNode($slideEnd);
            }
        }




    }

    public function getCurrPlayer(){
        return $this->curPlayer;
    }
    public function getCurPlayerColor(){
        return $this->players[$this->curPlayer]->getColor();
    }

    public function resetPlayers(){
        $this->players = [];
        $this->numPlayers = 0;
        $this->curPlayer = 0;
        $this->board = new Board();
        $this->deck = new Deck();
        $this->newCard();
        $this->gameEnded = false;
        $this->winner = "none";
    }
    public function getGameEnded(){
        return $this->gameEnded;
    }
    public function getWinner(){
        return $this->winner;
    }

    /**
     * Function to generate a json string based on the current board state
     * @return string of encoded json
     */
    public function getBoardStateJson(){
        $playerCords = [];
        foreach($this->players as $player){
            array_push($playerCords, $player->getPiecesCords());
        }
        $jsonStr = json_encode($playerCords);
        return $jsonStr;
    }

    /**
     * Sets the board state based on a json string
     * @param $json Coordinates to player pieces
     */
    public function setBoardStateJson($json){
        $cords = json_decode($json);
        for($i = 0; $i < count($cords); $i++){
            $nodes = [];
            foreach($cords[$i] as $cord){
                $node = $this->board->getNodeAt($cord[0], $cord[1]);
                array_push($nodes, $node);
            }
            $this->players[$i]->setPieceLocations($nodes);
        }
    }

    public function setGameID($id){
        $this->gameID = $id;
    }
    public function getID(){
        return $this->gameID;
    }
    public function updateFromTable($boardJson, $deckJson){

        $this->setBoardStateJson($boardJson);
        $this->deck->setDeckJson($deckJson);
        foreach($this->players as $player){
            if($player->checkWin()){
                $this->winner = $player->getColor();
                $this->gameEnded = true;
            }
        }
    }
    public function setPlayerColor($color){
        $this->playerColor = $color;
    }
    public function isMyTurn(){
        return $this->playerColor == $this->players[$this->curPlayer]->getColor();
    }
    public function joinGameSetup($json){
        $this->deck->restartDeck();
        $this->deck->setDeckJson($json);
        $this->newCard();
    }
    public function getPlayerColor(){
        return $this->playerColor;
    }
    public function clearPlayers(){
        $this->players = [];
        $this->deck->restartDeck();
    }





    private $board;
    private $deck;
    private $curCard; // the most recent value drawn from the deck, storing this so we don't need to ask the deck on a refresh
    private $players; //array storing player objects
    private $curPlayer = 0; //index into the players array for the current turn
    private $numPlayers = 0;  //number of players
    private $selectedPawn; // will be set be the GameController on a click of a tile containing a pawn
    private $finishedMoved = false; //boolean set to true when the player has finished moving for the turn
    private $splitting = false; //set to true when in the middle of a split movement
    private $splitRemainder; //set to the number of moves left in a split
    private $splittingPawn; //the pawn that started the split
    private $gameEnded = false;
    private $winner = "none";
    private $gameID = null; //The game ID for the database
    private $playerColor = "";


}