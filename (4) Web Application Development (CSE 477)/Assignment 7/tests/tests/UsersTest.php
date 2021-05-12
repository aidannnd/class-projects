<?php


class UsersTest extends \PHPUnit\Framework\TestCase {
    private static $site;

    public static function setUpBeforeClass() {
        self::$site = new Felis\Site();
        $localize  = require 'localize.inc.php';
        if(is_callable($localize)) {
            $localize(self::$site);
        }
    }

    public function test_pdo() {
        $users = new Felis\Users(self::$site);
        $this->assertInstanceOf('\PDO', $users->pdo());
    }

    protected function setUp() {
        $users = new Felis\Users(self::$site);
        $tableName = $users->getTableName();

        $sql = <<<SQL
delete from $tableName;
insert into $tableName(id, email, name, phone, address, 
                      notes, password, joined, role)
values (7, "dudess@dude.com", "Dudess, The", "111-222-3333", 
        "Dudess Address", "Dudess Notes", "87654321", 
        "2015-01-22 23:50:26", "S"),
        (8, "cbowen@cse.msu.edu", "Owen, Charles", "999-999-9999", 
        "Owen Address", "Owen Notes", "super477", 
        "2015-01-01 23:50:26", "A"),
        (9, "bart@bartman.com", "Simpson, Bart", "999-999-9999", 
        "", "", "bart477", "2015-02-01 01:50:26", "C"),
        (10, "marge@bartman.com", "Simpson, Marge", "", "",
        "", "marge", "2015-02-01 01:50:26", "C")
SQL;

        self::$site->pdo()->query($sql);
    }

    public function test_login() {
        $users = new Felis\Users(self::$site);

        // Test a valid login based on email address
        $user = $users->login("dudess@dude.com", "87654321");
        $this->assertInstanceOf('Felis\User', $user);

        // additional tests
        $this->assertEquals($user->getID(), 7);
        $this->assertEquals($user->getEmail(), "dudess@dude.com");
        $this->assertEquals($user->getName(), "Dudess, The");
        $this->assertEquals($user->getPhone(), "111-222-3333");
        $this->assertEquals($user->getAddress(), "Dudess Address");
        $this->assertEquals($user->getNotes(), "Dudess Notes");
        $this->assertEquals($user->getJoined(), "1421988626");
        $this->assertEquals($user->getRole(), "S");

        // Test a valid login based on email address
        $user = $users->login("cbowen@cse.msu.edu", "super477");
        $this->assertInstanceOf('Felis\User', $user);

        // Test a failed login
        $user = $users->login("dudess@dude.com", "wrongpw");
        $this->assertNull($user);


    }

    public function test_get() {
        $users = new Felis\Users(self::$site);

        $this->assertInstanceOf('Felis\User', $users->get(7));
        $this->assertNull($users->get(20));
    }
}