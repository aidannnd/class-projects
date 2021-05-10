<?php

use Game\Deck as Deck;
use Game\CardView as CardView;
class CardViewTest extends \PHPUnit\Framework\TestCase
{
    public function test_present(){
        $view = new CardView(1);
        $this->assertContains("lib/images/card_1.png", $view->presentCard());
        $view->setCard(2);
        $this-> assertContains("lib/images/card_2.png", $view->presentCard());
        $view->setCard(3);
        $this-> assertContains("lib/images/card_3.png", $view->presentCard());
        $view->setCard(4);
        $this-> assertContains("lib/images/card_4.png", $view->presentCard());
        $view->setCard(5);
        $this-> assertContains("lib/images/card_5.png", $view->presentCard());
        $view->setCard(7);
        $this-> assertContains("lib/images/card_7.png", $view->presentCard());
        $view->setCard(8);
        $this-> assertContains("lib/images/card_8.png", $view->presentCard());
        $view->setCard(10);
        $this-> assertContains("lib/images/card_10.png", $view->presentCard());
        $view->setCard(11);
        $this-> assertContains("lib/images/card_11.png", $view->presentCard());
        $view->setCard(12);
        $this-> assertContains("lib/images/card_12.png", $view->presentCard());
        $view->setCard(Deck::SORRY);
        $this-> assertContains("lib/images/card_sorry.png", $view->presentCard());
    }
}