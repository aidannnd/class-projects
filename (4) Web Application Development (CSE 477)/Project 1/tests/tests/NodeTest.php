<?php

use Game\Node as Node;
//use Game\HomeNode;

class NodeTest extends \PHPUnit\Framework\TestCase
{
    public function test_construct()
    {
//        $game = new Game\Game();
        $node = new Node(4, 5);
        $this->assertInstanceOf('Game\Node', $node);
    }

    public function test_PlayerColor()
    {
        $node = new Node(4,5);
        $node->setPlayerColor('yellow');
        $this->assertEquals('yellow', $node->getPlayerColor());
    }

    public function test_Occupied()
    {
        $node = new Node(4,5);
        $node->setOccupied('occupied');
        $this->assertEquals('occupied', $node->getOccupied());
    }

    public function test_getCoordinates()
    {
        $node = new Node(4,5);
        $this->assertEquals([4,5], $node->getCoordinates());
    }

    public function test_getCoordArray()
    {
        $node = new Node(4,5);
        $this->assertEquals([4,5], $node->getCoordinates());
    }

    public function test_OccupiedPiece()
    {
        $node = new Node(4,5);
        $node->setOccupied(true);
        $this->assertEquals(true, $node->getOccupied());
    }

    public function test_Next()
    {
        $node = new Node(4,5);
        $node->setNext($node);
        $this->assertEquals($node, $node->getNext());
    }

    public function test_Prev()
    {
        $node = new Node(4,5);
        $node->setPrev($node);
        $this->assertEquals($node, $node->getPrev());
    }

    public function test_protected()
    {
        $node = new Node(4,5);
        $node->setProtected(true);
        $this->assertTrue($node->isProtected());
    }

    public function test_printNodePosition()
    {
        $node = new Node(null, 6);
        $this->assertEquals("", $node->printNodePosition());
        $node = new Node(4,5);
        $str = "current position";
        $this->assertEquals("4, 5 <br>", $node->printNodePosition());
    }


    public function test_AlmostHomeColor()
    {
        $node = new Node(4,5);
        $node->setAlmostHomeColor("none");
        $this->assertEquals("none", $node->getAlmostHomeColor());
    }

    public function test_AlmostHome()
    {
        $node = new Node(4,5);
        $node->setAlmostHome(true);
        $this->assertEquals(true, $node->isAlmostHome());
    }

    public function test_setNextGoingHome()
    {
        $node = new Node(4,5);
        $node->setNextGoingHome($node);
        $this->assertEquals($node, $node->getNextGoingHome());
    }
}