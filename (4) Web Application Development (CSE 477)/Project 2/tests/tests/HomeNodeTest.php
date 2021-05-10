<?php


use Game\HomeNode as HomeNode;
//use Game\Node as Node;

class HomeNodeTest extends \PHPUnit\Framework\TestCase
{
    public function test_construct()
    {
        $node = new HomeNode(4, 5);
        $this->assertInstanceOf('Game\Node', $node);
    }

    public function test_Goal()
    {
        $node = new HomeNode(4,5);
        $node->setGoal(true);
        $this->assertEquals(true, $node->getGoal());
    }

    public function test_HomeColor()
    {
        $node = new HomeNode(4,5);
        $node->setHomeColor("blue");
        $this->assertEquals("blue", $node->getHomeColor());
    }
}