<?php


namespace Game;


class Games extends Table
{
    /**
     * Constructor
     * @param $site The Site object
     */
    public function __construct(Site $site) {
        parent::__construct($site, "game");
    }

    /**
     * Returns the row containing board and deck json strings for a specific game
     * @param $id id of the game to retrieve
     * @return array containing boad and deck json strings
     */
    public function get($id){
        $sql =<<<SQL
SELECT board, deck from $this->tableName
where id=?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);

        $statement->execute(array($id));
        if($statement->rowCount() === 0) {
            return null;
        }
        return $statement->fetch(\PDO::FETCH_ASSOC);
    }

    /**
     * Create a new game
     * @return id of created game
     */
    public function newGame($boardJson = "", $deckJson = "") {

        // Add a record to the user table
        $sql = <<<SQL
INSERT INTO $this->tableName(board, deck)
values(?, ?)
SQL;

        $statement = $this->pdo()->prepare($sql);
        $statement->execute(array($boardJson, $deckJson));
        return $this->pdo()->lastInsertId();

    }

    /**
     * To be called by clients to retrieve the game id
     * @return last inserted id
     */
    public function getLastId(){
        $sql =<<<SQL
SELECT id from $this->tableName
ORDER BY id DESC
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);

        $statement->execute();
        if($statement->rowCount() === 0) {
            return null;
        }
        $row = $statement->fetch(\PDO::FETCH_ASSOC);
        return $row['id'];
    }
    public function deleteGame($id){
        $sql =<<<SQL
DELETE FROM $this->tableName
WHERE id = ?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        try {

            $ret = $statement->execute(array($id));
        }
        catch(\PDOException $e) {
            return false;
        }
        if($ret == false || $statement->rowCount() == 0){
            return false;
        }

        return true;
    }
    public function updateBoard($id, $boardJson){
        $sql =<<<SQL
UPDATE $this->tableName
SET board = ?
WHERE id = ?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        try {
            $ret = $statement->execute(array($boardJson, $id));
        } catch(\PDOException $e) {
            return false;
        }
        if($ret == false || $statement->rowCount() == 0){
            return false;
        }
        return true;
    }
    public function updateDeck($id, $deckJson){
        $sql =<<<SQL
UPDATE $this->tableName
SET deck = ?
WHERE id = ?
SQL;
        $pdo = $this->pdo();
        $statement = $pdo->prepare($sql);
        try {
            $ret = $statement->execute(array($deckJson, $id));
        } catch(\PDOException $e) {
            return false;
        }
        if($ret == false || $statement->rowCount() == 0){
            return false;
        }
        return true;
    }

}