<?php


namespace Wumpus;


class WumpusView
{
    /**
     * Constructor
     * @param Wumpus $wumpus The Wumpus object
     */
    public function __construct(Wumpus $wumpus) {
        $this->wumpus = $wumpus;
    }

    /**
     * Generate the HTML for the number of arrows remaining
     * @return string HTML
     */
    public function presentArrows() {
        $a = $this->wumpus->numArrows();
        return "<p>You have $a arrows remaining.</p>";
    }

    /**
     * Generate the HTML for the status section of the page
     */
    public function presentStatus() {
        $room = $this->wumpus->getCurrent()->getNum();

        $html = <<<HTML
<div class="mainh2">
        <h2>You are in room $room</h2>
    </div>
HTML;

        if($this->wumpus->smellWumpus()) {
            $html .= '<h2>You smell a wumpus!</h2>';
        }

        if($this->wumpus->hearBirds()) {
            $html .= '<h2>You hear birds!</h2>';
        }

        if($this->wumpus->feelDraft()) {
            $html .= '<h2>You feel a draft!</h2>';
        }

        if($this->wumpus->wasCarried()) {
            $html .= '<h2>You were carried by the birds to room ';
            $html .= $room;
            $html .= '!</h2>';
        }

        return $html;
    }

    /**
     * Present the links for a room
     * @param int $ndx An index 0 to 2 for the three rooms
     * @return string HTML
     */
    public function presentRoom($ndx) {
        $room = $this->wumpus->getCurrent()->getNeighbors()[$ndx];
        $roomnum = $room->getNum();
        $roomndx = $room->getNdx();
        $roomurl = "game-post.php?m=$roomndx";
        $shooturl = "game-post.php?s=$roomndx";

        $html = <<<HTML
    <div class="room">
    <img src="images/cave2.jpg" width="180" height="135" alt="Cave 2"/>
            <p><a href="$roomurl">$roomnum</a></p>
<p><a href="$shooturl">Shoot Arrow</a></p>
    </div>

HTML;

        return $html;
    }

    private $wumpus;    // The Wumpus object

}