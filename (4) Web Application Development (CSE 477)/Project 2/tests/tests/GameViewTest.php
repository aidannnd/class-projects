<?php

class GameViewTest extends \PHPUnit\Framework\TestCase
{
    public function test_construct()
    {
        $game = new Game\Game([]);
        $game->getBoard()->onClick("1, 1");
        $gameView = new Game\GameView($game);
        $this->assertEquals([1, 1], $gameView->getClickedTile());
    }

    public function test_displayBoard()
    {
        $game = new Game\Game([]);
        $gameView = new Game\GameView($game);
        $displayBoard = $gameView->displayBoard();
        $html = <<<HTML
<form method="post" action="game-post.php">
<div class="game">
<div class="board">
HTML;

        $html2 = <<<HTML
<!--I feel like this should be here but it makes it look worse when its in. </div>-->
</div>
<p><input type="submit" name="done" value="Done"></p></form>
HTML;
        $this->assertContains($html, $displayBoard);
        $this->assertContains($html2, $displayBoard);
    }

    public function test_populateArray(){
        $game = new Game\Game([]);
        $gameView = new Game\GameView($game);

        $this->assertEquals(0, count($gameView->getBlankTileArray()));
        $gameView->displayBoard();
        $this->assertEquals(104, count($gameView->getBlankTileArray()));
    }

}