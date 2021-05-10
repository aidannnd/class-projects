<?php

use Game\SlideNode as SlideNode;

class SlideNodeTest extends \PHPUnit\Framework\TestCase
{
    public function test_SlideEnd()
    {
        $node = new SlideNode(4,5);
        $node->setSlideEnd(true);
        $this->assertEquals(true, $node->getSlideEnd());
    }

    public function test_SlideColor()
    {
        $node = new SlideNode(4,5);
        $node->setSlideColor("blue");
        $this->assertEquals("blue", $node->getSlideColor());
    }
}