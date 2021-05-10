<?php


namespace Game;


class Players extends Table
{
    /**
     * Constructor
     * @param $site The Site object
     */
    public function __construct(Site $site) {
        parent::__construct($site, "proj2_player");
    }

    /**
     * function to join a game
     */
    public function joinGame() {

    }
}