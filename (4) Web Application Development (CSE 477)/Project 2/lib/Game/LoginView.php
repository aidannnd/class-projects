<?php


namespace Game;


class LoginView
{
    public function __construct(array &$session, array $get) {

        //no input provided
        $this->session = $session;
        $this->get = $get;
    }

    public function invalid()
    {
        //no input provided
        if(empty($this->session['user']) and empty($this->get))
        {
            return "";
        }
        if(is_null($this->session['user']))
        {
            return "<p class=\"msg\">Invalid login credentials</p>";
        }
    }

    public function presentForm() {
        $html = <<<HTML
<form method="post" action="post/login.php">
    <fieldset>
        <legend>Login</legend>
        <p>
            <label for="email">Email</label><br>
            <input type="email" id="email" name="email" placeholder="Email">
        </p>
        <p>
            <label for="password">Password</label><br>
            <input type="password" id="password" name="password" placeholder="Password">
        </p>
        <p>
            <input type="submit" value="Log in"> </a>
        </p>

    </fieldset>
</form>
HTML;

        return $html;
    }

    private $session;
    private $get;
}