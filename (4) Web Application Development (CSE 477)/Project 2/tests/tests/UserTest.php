<?php

use PHPUnit\Framework\TestCase;

class UserTest extends \PHPUnit\Framework\TestCase
{
    public function test_construct() {
        $row = array('id' => 12,
            'email' => 'dude@ranch.com',
            'name' => 'Dude, The',
            'password' => '12345678'
        );
        $user = new Game\User($row);
        $this->assertEquals(12, $user->getId());
        $this->assertEquals('dude@ranch.com', $user->getEmail());

    }
}