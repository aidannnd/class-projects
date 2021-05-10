<?php

use Game\Node as Node;
use Game\Pawn as Pawn;
use Game\Player as Player;

class PlayerTest extends \PHPUnit\Framework\TestCase {
    public function test_construct() {
        $current_node = new Node(2, 2);
        $start_node = new Node(1, 1);
        $pawn1 = new Pawn("yellow", $current_node, $start_node, 0);

        $current_node = new Node(3, 3);
        $start_node = new Node(1, 1);
        $pawn2 = new Pawn("yellow", $current_node, $start_node, 0);

        $pieces = [];
        array_push($pieces, $pawn1);
        array_push($pieces, $pawn2);

        $player = new Player($pieces, "yellow");

        $this->assertEquals($pieces, $player->getPieces());
        $this->assertEquals("yellow", $player->getColor());
    }

    public function test_Red() {
        $pieces = [];
        $red = new Player($pieces, "red");

        $this->assertEquals([], $red->getPieces());
        $this->assertEquals("red", $red->getColor());
        // first piece home false
        $this->assertEquals(false, $red->pieceHome());
    }

    public function test_PieceHome() {
        // construct player
        $current_node = new Node(2, 2);
        $start_node = new Node(1, 1);
        $pawn1 = new Pawn("yellow", $current_node, $start_node, 0);

        $current_node = new Node(3, 3);
        $start_node = new Node(1, 1);
        $pawn2 = new Pawn("yellow", $current_node, $start_node, 0);

        $pieces = [];
        array_push($pieces, $pawn1);
        array_push($pieces, $pawn2);

        $player = new Player($pieces, "yellow");

        // test function
        $player->pieceHome();
        $player->pieceHome();

        $this->assertEquals(false, $player->pieceHome());
        $this->assertEquals(true, $player->pieceHome());
    }

}