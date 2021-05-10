<?php

namespace Game;

class CardView{
    private $value;
    const CARDBACK = 15;
    public function __construct($card){
        $this->value = $card;
    }

    public function setCard($card){
        $this->value = $card;
    }
    /*
     * Returns HTML for the image of the corresponding card
     */
    public function presentCard(){
        $html = "";
        switch($this->value){
            case 1:
                $html .= "lib/images/card_1.png";
                break;
            case 2:
                $html .= "lib/images/card_2.png";
                break;
            case 3:
                $html .= "lib/images/card_3.png";
                break;
            case 4:
                $html .= "lib/images/card_4.png";
                break;
            case 5:
                $html .= "lib/images/card_5.png";
                break;
            case 7:
                $html .= "lib/images/card_7.png";
                break;
            case 8:
                $html .= "lib/images/card_8.png";
                break;
            case 10:
                $html .= "lib/images/card_10.png";
                break;
            case 11:
                $html .= "lib/images/card_11.png";
                break;
            case 12:
                $html .= "lib/images/card_12.png";
                break;
            case Deck::SORRY:
                $html .= "lib/images/card_sorry.png";
                break;
            case $this::CARDBACK:
                $html .= "lib/images/card_back.png";
                break;
            default:
                $html .= "''";
                break;
        }
        return $html;
    }
}