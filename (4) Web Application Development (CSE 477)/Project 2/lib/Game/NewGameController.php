<?php


namespace Game;


class NewGameController
{
    /**
     * NewGameController constructor.
     * @param Site $site The Site object
     * @param array $post $_POST
     */
    public function __construct(Site $site,  User $user, array $post) {
//        $this->game = $game;
//        $this->games = new Games($site);
//        $this->gameJoins = new GameJoins($site);

        $root = $site->getRoot();
        if(!isset($post['newGame'])) {
            $this->redirect = "$root/waiting-page.php";
            return;
        }
    }

    /**
     * @return string
     */
    public function getRedirect()
    {
        return $this->redirect;
    }

    private $redirect;	// Page we will redirect the user to.
//    private $game;
//    private $games;
//    private $gameJoins;
}