<?php


namespace tests;


use Game\Player;
use Game\Players;
use Game\Site;

class PlayersTest extends \PHPUnit\Framework\TestCase
{
    private static $site;

    public static function setUpBeforeClass() {
        self::$site = new Site();
        $localize  = require 'localize.inc.php';
        if(is_callable($localize)) {
            $localize(self::$site);
        }
    }

    public function test_pdo() {
        $users = new Players(self::$site);
        $this->assertInstanceOf('\PDO', $users->pdo());
    }
}