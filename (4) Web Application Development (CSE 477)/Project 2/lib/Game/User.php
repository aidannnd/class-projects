<?php


namespace Game;


class User
{
    /**
     * Constructor
     * @param $row Row from the user table in the database
     */
    public function __construct($row) {
        $this->id = $row['id'];
        $this->email = $row['email'];
        $this->name = $row['name'];
        $this->password = $row['password'];
    }

    /**
     * @return mixed
     */
    public function getId()
    {
        return $this->id;
    }

    /**
     * @return mixed
     */
    public function getEmail()
    {
        return $this->email;
    }

    /**
     * @return mixed
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * @return mixed
     */
    public function getPlayer()
    {
        return $this->player;
    }

    public function getPassword()
    {
        return $this->password;
    }

    public function setLoggedIn($status)
    {
        $this->loggedin = $status;
    }

    public function getLoggedIn()
    {
        return $this->loggedin;
    }


    private $id;        // The internal ID for the user
    private $email;		// Email address
    private $name; 		// Name as last, first
    private $player;    // Player object
    private $password;
    private $loggedin = false;
    const SESSION_NAME = 'user';

}