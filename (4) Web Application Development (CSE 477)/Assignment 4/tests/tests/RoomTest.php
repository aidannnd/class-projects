<?php

/**
 * @file RoomTest.php
 * Unit tests for the class Room
 */
class RoomTest extends \PHPUnit\Framework\TestCase
{
    public function test_construct() {
        $room = new Wumpus\Room(0, 1);

        $this->assertInstanceOf('Wumpus\Room', $room);
    }

    public function test_getNum() {
        $room = new Wumpus\Room(55, 23);
        $this->assertEquals(23, $room->getNum());
    }

    public function test_getNdx() {
        $room = new Wumpus\Room(55, 23);
        $this->assertEquals(55, $room->getNdx());
    }

    public function test_addNeighbor() {
        $room = new Wumpus\Room(0, 23);
        $room0 = new Wumpus\Room(1, 7);
        $room1 = new Wumpus\Room(2, 3);
        $room2 = new Wumpus\Room(3, 9);

        $room->addNeighbor($room0);
        $room->addNeighbor($room1);
        $room->addNeighbor($room2);

        $neighbors = $room->getNeighbors();
        $this->assertEquals($room0, $neighbors[0]);
        $this->assertEquals($room1, $neighbors[1]);
        $this->assertEquals($room2, $neighbors[2]);
    }

    public function test_content() {
        // Create some rooms
        $room0 = new Wumpus\Room(0, 7);
        $room1 = new Wumpus\Room(1, 23);
        $room2 = new Wumpus\Room(2, 8);
        $room3 = new Wumpus\Room(3, 19);
        $room4 = new Wumpus\Room(4, 2);

        $room0->addNeighbor($room1);
        $room1->addNeighbor($room0);
        $room0->addNeighbor($room3);
        $room3->addNeighbor($room0);
        $room1->addNeighbor($room2);
        $room2->addNeighbor($room1);
        $room2->addNeighbor($room4);
        $room4->addNeighbor($room2);

        // This content should never been seen...
        // Room 4 is three rooms away
        for($i=1; $i<=8; $i++) {
            $room4->addContent($i);
        }

        // Ensure does not contain anything, yet
        $this->assertTrue($room0->isEmpty());
        $this->assertFalse($room0->contains(1));

        // Add some content to rooms
        $room0->addContent(2);  // Current room
        $room1->addContent(3);  // 1 room away
        $room3->addContent(4);  // 1 room away
        $room1->addContent(5);  // 1 room away
        $room2->addContent(6);  // 2 rooms away

        // Test current room only
        $this->assertFalse($room0->contains(1));
        $this->assertTrue($room0->contains(2));
        $this->assertFalse($room0->contains(3));

        // Test one room away
        $this->assertFalse($room0->contains(1, 1));
        $this->assertTrue($room0->contains(2, 1));
        $this->assertTrue($room0->contains(3, 1));
        $this->assertTrue($room0->contains(4, 1));
        $this->assertTrue($room0->contains(5, 1));
        $this->assertFalse($room0->contains(6, 1));
        $this->assertFalse($room0->contains(7, 1));

        // Test two rooms away
        $this->assertFalse($room0->contains(1, 2));
        $this->assertTrue($room0->contains(2, 2));
        $this->assertTrue($room0->contains(3, 2));
        $this->assertTrue($room0->contains(4, 2));
        $this->assertTrue($room0->contains(5, 2));
        $this->assertTrue($room0->contains(6, 2));
        $this->assertFalse($room0->contains(7, 2));
    }
}