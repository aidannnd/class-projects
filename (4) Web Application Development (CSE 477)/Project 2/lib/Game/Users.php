<?php


namespace Game;


use phpDocumentor\Reflection\Types\This;

class Users extends Table
{
    /**
     * Constructor
     * @param $site The Site object
     */
    public function __construct(Site $site) {
        parent::__construct($site, "user");
    }

    /**
     * Test for a valid login.
     * @param $email User email
     * @param $password Password credential
     * @return User object if successful, null otherwise.
     */
    public function login($email, $password) {
        $sql =<<<SQL
SELECT * from $this->tableName
where email=? 
SQL;

        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);

        $statement->execute(array($email));
        if ($statement->rowCount() === 0) {
            return null;
        }

        // Test salted password
        $row = $statement->fetch(\PDO::FETCH_ASSOC);
        $hash = $row['password'];
        $salt = $row['salt'];

        if ($hash !== hash("sha256", $password . $salt)) {
            return null;
        }

        return new User($row);

    }

    /**
     * @brief Generate a random salt string of characters for password salting
     * @param $len Length to generate, default is 16
     * @returns Salt string
     */
    public static function random_salt($len = 16) {
        $chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789`~!@#$%^&*()-=_+';
        $l = strlen($chars) - 1;
        $str = '';
        for ($i = 0; $i < $len; ++$i) {
            $str .= $chars[rand(0, $l)];
        }
        return $str;
    }

    /**
     * @brief Encrypt a password using salt
     */
    private function hash_pw($password, $salt) {
        return hash("sha256", $password . $salt);
    }

    public function password($mail, $password) {
        $salt = $this->random_salt();
        $hash = $this->hash_pw($password , $salt);

        $sql = <<<SQL
UPDATE $this->tableName
SET password=?, salt=?
WHERE email=?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        try {
            $statement->execute([$hash, $salt, $mail]);
            if($statement->rowCount() != 0) {
                $statement->fetch(\PDO::FETCH_ASSOC);
                return true;
            }
            else {
                return false;
            }
        }
        catch (\PDOException $exception) {
            return false;
        }
    }

    /**
     * Determine if a user exists in the system.
     * @param $email An email address.
     * @return true if $email is an existing email address
     */
    public function exists($email) {
        $sql =<<<SQL
SELECT * from $this->tableName
where email=?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        $statement->execute(array($email));
        if($statement->rowCount() != 0) {
            return true;
        }
        return false;
    }

    /**
     * Create a new user.
     * @param User $user The new user data
     * @param Email $mailer An Email object to use
     * @return null on success or error message if failure
     */
    public function add($email, $name, $password) {
        // Ensure we have no duplicate email address
        if($this->exists($email)) {
            return "Email address already exists.";
        }



        // Add a record to the user table
        $tableName = $this->getTableName();
        $sql = <<<SQL
INSERT INTO $tableName(email, name, password)
values (?, ?, ?)
SQL;

        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        $statement->execute(array($email, $name, $password));
        if($statement->rowCount() === 0) {
            return null;
        }
        return new User($statement->fetch(\PDO::FETCH_ASSOC));
    }
}
