<?php


namespace Game;


class SignUpView
{
    public function __construct(array &$session, array $get) {

        //no input provided
        $this->session = $session;
        $this->get = $get;
    }

    public function presentForm() {
        $html = <<<HTML
<form method="post" action="post/signup.php">
            <fieldset>
                <legend>Sign Up</legend>
                <p>
                    <label for="name">Name</label><br>
                    <input type="name" id="name" name="name" placeholder="Name">
                </p>
                <p>
                    <label for="email">Email</label><br>
                    <input type="email" id="email" name="email" placeholder="Email">
                </p>
                <p>
                    <label for="password">Password</label><br>
                    <input type="password" id="password" name="password" placeholder="Password">
                </p>
                <p>
                    <input type="submit" value="Sign Up">
                </p>
                <p>Already a member? <a href="./login.php">Login</a></p>

                <p><a href="./">Sorry! Home</a></p>

            </fieldset>
        </form>
</div>
HTML;
        return $html;
    }
    private $session;
    private $get;
}