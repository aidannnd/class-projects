<?php


class GamesTest extends \PHPUnit\Framework\TestCase
{
    private static $site;
    public static function setUpBeforeClass() {
        self::$site = new Game\Site();
        $localize  = require 'localize.inc.php';
        if(is_callable($localize)) {
            $localize(self::$site);
        }
    }
    protected function setUp() {
        $games = new Game\Games(self::$site);
        $tableName = $games->getTableName();

        $sql = <<<SQL
delete from $tableName;
SQL;
        self::$site->pdo()->query($sql);
    }
    public function test_pdo(){
        $games = new Game\Games(self::$site);
        $this->assertInstanceOf('\PDO', $games->pdo());
    }
    public function test_newGame(){
        $games = new Game\Games(self::$site);
        $game = new Game\Game();
        $game->addPlayer("red");
        $game->addPlayer("blue");

        $gameId = $games->newGame();
        $this->assertNotNull($gameId);

        $deck = new Game\Deck(true);
        $this->assertEquals($gameId, $games->getLastId());

        $boardJson = $game->getBoardStateJson();
        $deckJson = $deck->getDeckJson();
        $games->updateBoard($gameId, $boardJson);
        $games->updateDeck($gameId, $deckJson);

        $res = $games->get($gameId);
        $this->assertEquals($res['board'], $boardJson);
        $this->assertEquals($res['deck'], $deckJson);
    }
}