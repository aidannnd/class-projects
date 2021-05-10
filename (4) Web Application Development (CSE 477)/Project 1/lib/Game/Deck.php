<?php

namespace Game;

class Deck{
    const DECKSIZE = 45;
    const SORRY = 0;
    private $deck = [];//array representing the current deck
    private $cards_drawn = 0;//will be used as an index into the array
    /*
     * Constructor for Deck
     * @param testing: controls whether or not the deck is shuffled initially for testing purposed
     */
    public function __construct($testing = false)
    {
        for($i = 0; $i < 4; $i++){
            array_push($this->deck, 1);
            array_push($this->deck, 2);
            array_push($this->deck, 3);
            array_push($this->deck, 4);
            array_push($this->deck, 5);
            array_push($this->deck, 7);
            array_push($this->deck, 8);
            array_push($this->deck, 10);
            array_push($this->deck, 11);
            array_push($this->deck, 12);
            array_push($this->deck, $this::SORRY);
        }
        array_push($this->deck, "1");//There are 5 1s in the deck, this is not a mistake
        if(!$testing){
            $this->shuffleDeck();
        }
    }

    /*
     * Shuffle's the deck using php's shuffle function
     */
    private function shuffleDeck(){
        shuffle($this->deck);//using php's built in array shuffle function
    }
    public function getNumDrawn(){
        return $this->cards_drawn;
    }
    public function getCardsRemaining(){//using the function for testing purposes
        return count($this->deck) - $this->cards_drawn;
    }
    public function getDeckArray(){//returns full deck, even if drawn from - for testing purposes
        return $this->deck;
    }
    /*
     * The function to actually draw a card, this is the point of interaction for the Game class
     * @return: integer representing the card drawn
     */
    public function drawCard(){
        $return_card = $this->deck[$this->cards_drawn];//retrieve current card
        $this->cards_drawn++;
        if($this->cards_drawn >= self::DECKSIZE){//if we have drawn 45 cards, shuffle the deck
            $this->shuffleDeck();
            $this->cards_drawn = 0;
        }
        return $return_card;
    }
}