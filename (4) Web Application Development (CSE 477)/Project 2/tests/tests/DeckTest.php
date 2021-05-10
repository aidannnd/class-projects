<?php

use Game\Deck as Deck;
class DeckTest extends \PHPUnit\Framework\TestCase
{
    const UNSHUFFLED = [1, 2, 3, 4, 5, 7, 8, 10, 11, 12, Deck::SORRY,
                        1, 2, 3, 4, 5, 7, 8, 10, 11, 12, Deck::SORRY,
                        1, 2, 3, 4, 5, 7, 8, 10, 11, 12, Deck::SORRY,
                        1, 2, 3, 4, 5, 7, 8, 10, 11, 12, Deck::SORRY, 1];
    public function test_construct(){
        $deck = new Deck(true);//deck in testing mode, won't shuffle deck
        $this->assertEquals(45, $deck->getCardsRemaining());
        $this->assertEquals(0, $deck->getNumDrawn());
        $this->assertEquals(self::UNSHUFFLED, $deck->getDeckArray());
    }
    public function test_shuffle(){//there technically is a very slim chance that this one fails due to random chance TODO: better way to test this?
        $deck = new Deck();//deck in not testing mode, will shuffle deck
        $this->assertNotEquals($deck->getDeckArray(), self::UNSHUFFLED);
    }

    public function test_drawing(){
        $deck = new Deck(true);//deck in testing mode, won't shuffle deck
        $this->assertEquals(1, $deck->drawCard());
        $this->assertEquals(1, $deck->getNumDrawn());
        $this->assertEquals(2, $deck->drawCard());
        $this->assertEquals(2, $deck->getNumDrawn());
        $this->assertEquals(3, $deck->drawCard());
        $this-> assertEquals(3, $deck->getNumDrawn());
        $this->assertEquals(4, $deck->drawCard());
        $this-> assertEquals(4, $deck->getNumDrawn());
        $this->assertEquals(5, $deck->drawCard());
        $this-> assertEquals(5, $deck->getNumDrawn());
        $this-> assertEquals(7, $deck->drawCard());
        $this->  assertEquals(6, $deck->getNumDrawn());
        $this-> assertEquals(8, $deck->drawCard());
        $this-> assertEquals(7, $deck->getNumDrawn());
        $this-> assertEquals(10, $deck->drawCard());
        $this-> assertEquals(8, $deck->getNumDrawn());
        $this->  assertEquals(11, $deck->drawCard());
        $this-> assertEquals(9, $deck->getNumDrawn());
        $this-> assertEquals(12, $deck->drawCard());
        $this->  assertEquals(10, $deck->getNumDrawn());
        $this-> assertEquals(Deck::SORRY, $deck->drawCard());
        $this-> assertEquals(11, $deck->getNumDrawn());
        for($i = 0; $i < 34; $i++){//draw the remaining cards to check the shuffle resets properly
            $deck->drawCard();
        }
        $this-> assertEquals(0, $deck->getNumDrawn());//should be a fresh deck
    }
    public function test_json(){
        $deck = new Deck(true);
        $unshuffledJson = "[1,2,3,4,5,7,8,10,11,12,0,1,2,3,4,5,7,8,10,11,12,0,1,2,3,4,5,7,8,10,11,12,0,1,2,3,4,5,7,8,10,11,12,0,1]";
        $this->assertEquals($unshuffledJson, $deck->getDeckJson());

        $deck2 = new Deck();
        $deck2->setDeckJson($unshuffledJson);
        $this->assertEquals(self::UNSHUFFLED, $deck2->getDeckArray());


    }

}