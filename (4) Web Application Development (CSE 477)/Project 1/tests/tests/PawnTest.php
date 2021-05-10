<?php

use Game\Node as Node;
use Game\Pawn as Pawn;

class PawnTest extends \PHPUnit\Framework\TestCase {
    // also tests currentNode, startNode, and getOwner
    public function test_construct() {
        $current_node = new Node(2, 2);
        $start_node = new Node(1, 1);
        $pawn = new Pawn("yellow", $current_node, $start_node, 0);


        $this->assertEquals("yellow", $pawn->getOwner());
        $this->assertEquals($current_node, $pawn->getCurrentNode());
        $this->assertEquals($start_node, $pawn->getStartNode());
    }

    public function test_returnToStart() {
        $current_node = new Node(2, 2);
        $start_node = new Node(1, 1);
        $pawn = new Pawn("yellow", $current_node, $start_node, 0);

        $pawn->returnToStart();

        $this->assertEquals($pawn->getCurrentNode(), $pawn->getStartNode());
    }
}