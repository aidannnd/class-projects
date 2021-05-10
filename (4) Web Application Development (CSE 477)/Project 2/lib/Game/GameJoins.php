<?php


namespace Game;


class GameJoins extends Table
{
    /**
     * Constructor
     * @param $site The Site object
     */
    public function __construct(Site $site) {
        parent::__construct($site, "gameJoin");
    }

    public function getAll(){
        $sql =<<<SQL
SELECT * from $this->tableName
order by gameID
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        $statement->execute();
        return $statement->fetchAll(\PDO::FETCH_ASSOC);
    }
    public function get($id){
        $sql =<<<SQL
SELECT * from $this->tableName
where gameID = ?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        $statement->execute(array($id));
        return $statement->fetch(\PDO::FETCH_ASSOC);
    }
    /*
     * Creates a new game in the database, returns true on success, false on id exists
     */
    public function newGame($gameID, $userID, $color){
        $sql =<<<SQL
SELECT * from $this->tableName
where gameID = ?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        $statement->execute(array($gameID));
        if($statement->rowCount() != 0){
            return false;
        }
        $state = "Waiting";
        if($color == "red"){
            $sql =<<<SQL
INSERT INTO $this->tableName (gameID, redID, gameState)
values(?, ?, ?)
SQL;
            $statement = $pdo->prepare($sql);
            $statement->execute(array($gameID, $userID, $state));
            return true;
        }
        else if($color == "blue"){
            $sql =<<<SQL
INSERT INTO $this->tableName (gameID, blueID, gameState)
values(?, ?, ?)
SQL;
            $statement = $pdo->prepare($sql);
            $statement->execute(array($gameID, $userID, $state));
            return true;
        }
        else if($color == "yellow"){
            $sql =<<<SQL
INSERT INTO $this->tableName (gameID, yellowID, gameState)
values(?, ?, ?)
SQL;
            $statement = $pdo->prepare($sql);
            $statement->execute(array($gameID, $userID. $state));
            return true;
        }
        else if($color == "green"){
            $sql =<<<SQL
INSERT INTO $this->tableName (gameID, greenID, gameState)
values(?, ?, ?)
SQL;
            $statement = $pdo->prepare($sql);
            $statement->execute(array($gameID, $userID, $state));
            return true;
        }
        return false;

    }
    public function joinGame($gameID, $userID, $color){
        $sql =<<<SQL
SELECT * from $this->tableName
where gameID = ?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        $statement->execute(array($gameID));
        if($statement->rowCount() == 0){
            return false;
        }
        if($color == "red"){
            $sql =<<<SQL
UPDATE $this->tableName 
SET redID = ?
where gameID = ?
SQL;
            $statement = $pdo->prepare($sql);
            $statement->execute(array($userID, $gameID));
            return true;
        }
        else if($color == "blue"){
            $sql =<<<SQL
UPDATE $this->tableName 
SET blueID = ?
where gameID = ?
SQL;
            $statement = $pdo->prepare($sql);
            $statement->execute(array($userID, $gameID));
            return true;
        }
        else if($color == "yellow"){
            $sql =<<<SQL
UPDATE $this->tableName 
SET yellowID = ?
where gameID = ?
SQL;
            $statement = $pdo->prepare($sql);
            $statement->execute(array($userID, $gameID));
            return true;
        }
       else if($color == "green"){
            $sql =<<<SQL
UPDATE $this->tableName 
SET greenID = ?
where gameID = ?
SQL;
            $statement = $pdo->prepare($sql);
            $statement->execute(array($userID, $gameID));
            return true;
        }

}
    public function startGame($id){
        $sql =<<<SQL
UPDATE $this->tableName 
SET gameState = ?
where gameID = ?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        try {
            $ret = $statement->execute(array("Playing", $id));
        } catch(\PDOException $e) {
            return false;
        }
        if($ret == false || $statement->rowCount() == 0){
            return false;
        }
        return true;
    }





}