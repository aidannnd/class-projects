<?php


use PHPUnit\Framework\TestCase;

use Game\Board as Board;
use Game\Node as Node;


class BoardTest extends TestCase {
    public function test_construct() {
        $board = new Board();
        $this->assertEquals(16, count($board->getGameBoard()));

        //home tests
        $this->assertEquals('red', $board->getGameBoard()[9][13]->getHomeColor());
        $this->assertEquals(true, $board->getGameBoard()[9][13]->getGoal());
        $this->assertEquals('yellow', $board->getGameBoard()[6][2]->getHomeColor());
        $this->assertEquals(true, $board->getGameBoard()[6][2]->getGoal());
        $this->assertEquals('green', $board->getGameBoard()[2][9]->getHomeColor());
        $this->assertEquals(true, $board->getGameBoard()[2][9]->getGoal());
        $this->assertEquals('blue', $board->getGameBoard()[13][6]->getHomeColor());
        $this->assertEquals(true, $board->getGameBoard()[13][6]->getGoal());

        //sliders test
        $this->assertEquals('yellow', $board->getGameBoard()[0][1]->getSlideColor());
        $this->assertEquals('yellow', $board->getGameBoard()[0][9]->getSlideColor());
        $this->assertEquals('red', $board->getGameBoard()[15][14]->getSlideColor());
        $this->assertEquals('red', $board->getGameBoard()[15][6]->getSlideColor());
        $this->assertEquals('blue', $board->getGameBoard()[14][0]->getSlideColor());
        $this->assertEquals('blue', $board->getGameBoard()[6][0]->getSlideColor());
        $this->assertEquals('green', $board->getGameBoard()[1][15]->getSlideColor());
        $this->assertEquals('green', $board->getGameBoard()[9][15]->getSlideColor());

        //start tests
        $this->assertEquals(true, $board->getGameBoard()[0][2]->isAlmostHome());
        $this->assertEquals('yellow', $board->getGameBoard()[0][2]->getAlmostHomeColor());
        $this->assertEquals(false, $board->getGameBoard()[0][1]->isAlmostHome());
        $this->assertEquals('none', $board->getGameBoard()[0][1]->getAlmostHomeColor());
        $this->assertEquals(true, $board->getGameBoard()[2][15]->isAlmostHome());
        $this->assertEquals('green', $board->getGameBoard()[2][15]->getAlmostHomeColor());
        $this->assertEquals(true, $board->getGameBoard()[15][13]->isAlmostHome());
        $this->assertEquals('red', $board->getGameBoard()[15][13]->getAlmostHomeColor());
        $this->assertEquals(true, $board->getGameBoard()[13][0]->isAlmostHome());
        $this->assertEquals('blue', $board->getGameBoard()[13][0]->getAlmostHomeColor());
    }

    public function test_onClick() {
        $board = new Board();
        $node = new Node(1, 1);

        $board->onClick($node);
        $this->assertEquals($node, $board->getClickedTile());
    }

    public function test_getNodeAt() {
        $board = new Board();
        $node = new Node(1, 1);

        $this->assertEquals($node, $board->getNodeAt(1, 1));
    }

}