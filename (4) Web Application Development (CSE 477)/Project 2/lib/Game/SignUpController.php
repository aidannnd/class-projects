<?php


namespace Game;


class SignUpController
{
    public function __construct(Site $site, array &$session, array $post) {

        // Create a Users object to access the table
        $users = new Users($site);
        $email = strip_tags($post['email']);
        $password = strip_tags($post['password']);
        $name = strip_tags($post['name']);
        $user = $users->add($email, $name, $password );

        $session[User::SESSION_NAME] = $user;

        // Salt Password
        $id = $user->getId();
        $users->password($email, $password);

        if($user === null) {
            $this->redirect = "../signup.php?e";
        } else {
            $this->redirect = "../login.php";
        }
    }
    /**
     * @return mixed
     */
    public function getRedirect()
    {
        return $this->redirect;
    }

    private $redirect;	// Page we will redirect the user to.
}
