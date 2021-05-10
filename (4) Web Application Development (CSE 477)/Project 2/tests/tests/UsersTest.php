<?php

use PHPUnit\Framework\TestCase;


class UsersTest extends \PHPUnit\Framework\TestCase
{
    private static $site;

    public static function setUpBeforeClass() {
        self::$site = new Game\Site();
        $localize = require 'localize.inc.php';
        if(is_callable($localize)) {
            $localize(self::$site);
        }
    }

    public function test_pdo() {
        $users = new Game\Users(self::$site);
        $this->assertInstanceOf('\PDO', $users->pdo());
    }

    public function test_construct()
    {
        $row = array('id' => 12,
            'email' => 'dude@ranch.com',
            'name' => 'Dude, The',
            'password' => '12345678',
        );
        $user = new Game\User($row);
        $this->assertEquals(12, $user->getId());
        $this->assertEquals('dude@ranch.com', $user->getEmail());
    }

    protected function setUp()
    {
        $users = new Game\Users(self::$site);
        $tableName = $users->getTableName();

        $sql = <<<SQL
delete from $tableName;
insert into $tableName(id, email, name, password)
values (2, "dudess@dude.com", "Dudess", "87654321")
SQL;

        self::$site->pdo()->query($sql);
    }

    public function test_add()
    {
        $row = array('id' => 12,
            'email' => 'dude@ranch.com',
            'name' => 'Dude, The',
            'password' => '12345678'
        );
        $user = new Game\User($row);
        $users = new Game\Users(self::$site);
        $this->assertTrue($users->add($user));
    }

    public function test_login() {
        $row = array('id' => 12,
            'email' => 'dude@ranch.com',
            'name' => 'Dude, The',
            'password' => '12345678'
        );

        $user = new Game\User($row);
        $users = new Game\Users(self::$site);
        $users->add('dude@ranch.com', 'Dude', '12345678');
        $this->assertNotEquals(null, $users->login('dude@ranch.com', '12345678'));
    }
}
