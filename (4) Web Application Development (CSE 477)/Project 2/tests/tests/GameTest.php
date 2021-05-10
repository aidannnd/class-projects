<?php


use Game\Game as Game;
use Game\Node as Node;
use Game\Pawn as Pawn;
use Game\Player as Player;
use Game\Site as Site;
use Game\Games as Games;
class GameTest extends \PHPUnit\Framework\TestCase
{

    public function test_valid_movement(){//tests all cards for valid movement
        $Node0 = new Node(0,0);
        $Node1 = new Node(0,1);
        $Node2 = new Node(0,2);
        $Node3 = new Node(0,3);
        $Node4 = new Node(0,4);
        $Node5 = new Node(0,5);
        $Node6 = new Node(0,6);
        $Node7 = new Node(0,7);
        $Node8 = new Node(0,8);
        $Node9 = new Node(0,9);
        $Node10 = new Node(0,10);
        $Node11 = new Node(0,11);
        $Node12 = new Node(0,12);
        $Node0->setNext($Node1);
        $Node1->setNext($Node2);
        $Node2->setNext($Node3);
        $Node3->setNext($Node4);
        $Node4->setNext($Node5);
        $Node5->setNext($Node6);
        $Node6->setNext($Node7);
        $Node7->setNext($Node8);
        $Node8->setNext($Node9);
        $Node9->setNext($Node10);
        $Node10->setNext($Node11);
        $Node11->setNext($Node12);
        $Node12->setNext($Node0);
        $Node0->setPrev($Node12);
        $Node1->setPrev($Node0);
        $Node2->setPrev($Node1);
        $Node3->setPrev($Node2);
        $Node4->setPrev($Node3);
        $Node5->setPrev($Node4);
        $Node6->setPrev($Node5);
        $Node7->setPrev($Node6);
        $Node8->setPrev($Node7);
        $Node9->setPrev($Node8);
        $Node10->setPrev($Node9);
        $Node11->setPrev($Node10);
        $Node12->setPrev($Node11);
        $StartNode1 = new Node(1, 1);
        $StartNode2 = new Node(1, 1);
        $StartNode3 = new Node(1, 1);
        $StartNode4 = new Node(1, 1);
        $StartNode1 ->setNext($Node0);
        $StartNode2 ->setNext($Node0);
        $StartNode3 ->setNext($Node0);
        $StartNode4 ->setNext($Node0);
        //the above code sets up a looping board of 13 spaces used to deck game logic
        $piece1 = new Pawn("red", $StartNode1, $StartNode1, 0);
        $pieceRedSplit = new Pawn("red", $StartNode2, $StartNode2, 1);
        $piece2 = new Pawn("blue", $StartNode3, $StartNode3, 0);
        $piece2->setCurrentNode($Node5);
        $piece3 = new Pawn("blue", $StartNode4, $StartNode4, 1);
        $piece3->setCurrentNode($Node8);
        $player1 = new Player([$piece1, $pieceRedSplit], "red");
        $player2 = new Player([$piece2, $piece3], "blue");
        $game = new Game([$player1, $player2]);
        $game->setCurCard(8);
        $this->assertEquals($game->getValidMoves($piece1), []);//can't move out of spawn check
        $game->setCurCard(1);
        $this-> assertEquals($game->getValidMoves($piece1), [$Node0->getCoordinates()]);//can move 1 space out of spawn with a 1
        $game->setCurCard(2);
        $this->  assertEquals($game->getValidMoves($piece1), [$Node0->getCoordinates()]);//can move 1 spaces out of spawn with a 2
        $piece1->setCurrentNode($Node0);
        $game->setCurCard(3);
        $this-> assertEquals($game->getValidMoves($piece1), [$Node3->getCoordinates()]);
        $game->setCurCard(5);
        $this->   assertEquals($game->getValidMoves($piece1), [$Node5->getCoordinates()]);
        $game->setCurCard(8);
        $this-> assertEquals($game->getValidMoves($piece1), [$Node8->getCoordinates()]);
        $game->setCurCard(12);
        $this->   assertEquals($game->getValidMoves($piece1), [$Node12->getCoordinates()]);
        $game->setCurCard(4);
        $this->  assertEquals($game->getValidMoves($piece1), [$Node9->getCoordinates()]);//backwards movement check
        $game->setCurCard(7);
        $this->  assertEquals($game->getValidMoves($piece1), [$Node7->getCoordinates()]);//can't split when other pawn in start
        $pieceRedSplit->setCurrentNode($Node9);
        $this->  assertEquals(7, count($game->getValidMoves($piece1)));//now can split move

        $game->setCurCard(10);
        $this-> assertEquals($game->getValidMoves($piece1), [$Node10->getCoordinates(), $Node12->getCoordinates()]);//forwards 10 and back 1
        $game->setCurCard(11);
        $this-> assertEquals($game->getValidMoves($piece1), [$Node11->getCoordinates(), $Node5->getCoordinates(), $Node8->getCoordinates()]);
        $game->setCurCard(0);
        $this->assertEquals($game->getValidMoves($piece1), []);//can't use sorry if not home
        $piece1->returnToStart();
        $pieceRedSplit->returnToStart();
        $this->assertEquals($game->getValidMoves($piece1), [$Node5->getCoordinates(), $Node8->getCoordinates()]);//can use sorry, since now home
        $this->assertEquals(true, $game->checkIfValidMoves());
        $game->setCurCard(11);
        $this->assertEquals(false, $game->checkIfValidMoves());


    }

    public function test_movement_proper(){
        $Node0 = new Node(0,0);
        $Node1 = new Node(0,1);
        $Node2 = new Node(0,2);
        $Node3 = new Node(0,3);
        $Node4 = new Node(0,4);
        $Node5 = new Node(0,5);
        $Node6 = new Node(0,6);
        $Node7 = new Node(0,7);
        $Node8 = new Node(0,8);
        $Node9 = new Node(0,9);
        $Node10 = new Node(0,10);
        $Node11 = new Node(0,11);
        $Node12 = new Node(0,12);
        $Node0->setNext($Node1);
        $Node1->setNext($Node2);
        $Node2->setNext($Node3);
        $Node3->setNext($Node4);
        $Node4->setNext($Node5);
        $Node5->setNext($Node6);
        $Node6->setNext($Node7);
        $Node7->setNext($Node8);
        $Node8->setNext($Node9);
        $Node9->setNext($Node10);
        $Node10->setNext($Node11);
        $Node11->setNext($Node12);
        $Node12->setNext($Node0);
        $Node0->setPrev($Node12);
        $Node1->setPrev($Node0);
        $Node2->setPrev($Node1);
        $Node3->setPrev($Node2);
        $Node4->setPrev($Node3);
        $Node5->setPrev($Node4);
        $Node6->setPrev($Node5);
        $Node7->setPrev($Node6);
        $Node8->setPrev($Node7);
        $Node9->setPrev($Node8);
        $Node10->setPrev($Node9);
        $Node11->setPrev($Node10);
        $Node12->setPrev($Node11);
        $RedStartNode1 = new Node(1, 1);
        $RedStartNode1 ->setNext($Node0);
        $BlueStartNode1 = new Node(2,2);
        $BlueStartNode1->setNext($Node6);
        $RedStartNode2 = new Node(1, 1);
        $RedStartNode2 ->setNext($Node0);
        $BlueStartNode2 = new Node(2,2);
        $BlueStartNode2->setNext($Node6);
        //the above code sets up a looping board of 13 spaces used to deck game logic
        $redPiece1 = new Pawn("red", $RedStartNode1, $RedStartNode2, 0);
        $redPiece2 = new Pawn("red", $RedStartNode2, $RedStartNode2, 1);
        $bluePiece1 = new Pawn("blue", $BlueStartNode1, $BlueStartNode1, 0);

        $bluePiece2 = new Pawn("blue", $BlueStartNode2, $BlueStartNode2, 1);

        $player1 = new Player([$redPiece1, $redPiece2], "red");
        $player2 = new Player([$bluePiece1, $bluePiece2], "blue");
        $game = new Game([$player1, $player2]);
        $game->setCurCard(6);
        $game->setSelectedPawn($redPiece1);
        $game->parseClickedNode($Node4);
        $this->assertEquals($RedStartNode1, $redPiece1->getCurrentNode());//Can't move off, its a 6
        $game->nextTurn();
        $game->setCurCard(1);
        $game->setSelectedPawn($bluePiece1);
        $game->parseClickedNode($Node6);
        $this->assertEquals($Node6, $bluePiece1->getCurrentNode());//Can move off its a 1

        $game->nextTurn();

        $redPiece1->setCurrentNode($Node5);
        $bluePiece1->setCurrentNode($Node10);
        $game->setCurCard(5);
        $game->setSelectedPawn($redPiece1);
        $game->parseClickedNode($Node10);
        $this->assertEquals($BlueStartNode1, $bluePiece1->getCurrentNode());//Should have been sent home
        $this->assertEquals($Node10, $redPiece1->getCurrentNode());//Movement
        $game->nextTurn();
        $game->setCurCard(11);
        $bluePiece1->setCurrentNode($Node5);
        $game->parseClickedNode($Node5);//testing setting clicked pawn through node
        $game->parseClickedNode($Node10);
        $this->assertEquals($Node5, $redPiece1->getCurrentNode());//Swapped
        $this->assertEquals($Node10, $bluePiece1->getCurrentNode());//Swapped
        $game->nextTurn();
        $game->nextTurn();
        $bluePiece1->setCurrentNode($Node6);
        $bluePiece2->setCurrentNode($Node11);
        $game->setCurCard(7);
        $game->setSelectedPawn($bluePiece1);
        $game->parseClickedNode($Node10);
        $game->setSelectedPawn($bluePiece2);
        $game->parseClickedNode($Node1);
        $this->assertEquals($Node10, $bluePiece1->getCurrentNode());//Split move 5
        $this->assertEquals($Node1, $bluePiece2->getCurrentNode());//Split move 2

        // $game->nextTurn();

    }
    public function test_slide_nodes(){
        $Node0 = new Node(0,0);
        $Node1 = new Node(0,1);
        $Node2 = new Node(0,2);
        $Node3 = new Node(0,3);
        $Node4 = new Node(0,4);
        $Node5 = new \Game\SlideNode(0,5);
        $Node6 = new Node(0,6);
        $Node7 = new Node(0,7);
        $Node8 = new Node(0,8);
        $Node9 = new Node(0,9);
        $Node10 = new Node(0,10);
        $Node11 = new Node(0,11);
        $Node12 = new Node(0,12);
        $Node0->setNext($Node1);
        $Node1->setNext($Node2);
        $Node2->setNext($Node3);
        $Node3->setNext($Node4);
        $Node4->setNext($Node5);
        $Node5->setNext($Node6);
        $Node6->setNext($Node7);
        $Node7->setNext($Node8);
        $Node8->setNext($Node9);
        $Node9->setNext($Node10);
        $Node10->setNext($Node11);
        $Node11->setNext($Node12);
        $Node12->setNext($Node0);
        $Node0->setPrev($Node12);
        $Node1->setPrev($Node0);
        $Node2->setPrev($Node1);
        $Node3->setPrev($Node2);
        $Node4->setPrev($Node3);
        $Node5->setPrev($Node4);
        $Node6->setPrev($Node5);
        $Node7->setPrev($Node6);
        $Node8->setPrev($Node7);
        $Node9->setPrev($Node8);
        $Node10->setPrev($Node9);
        $Node11->setPrev($Node10);
        $Node12->setPrev($Node11);
        $Node5->setSlideColor("red");
        $Node5->setSlideEnd($Node9);
        $RedStartNode1 = new Node(1, 1);
        $RedStartNode1 ->setNext($Node0);
        $BlueStartNode1 = new Node(2,2);
        $BlueStartNode1->setNext($Node6);
        $RedStartNode2 = new Node(1, 1);
        $RedStartNode2 ->setNext($Node0);
        $BlueStartNode2 = new Node(2,2);
        $BlueStartNode2->setNext($Node6);
        //the above code sets up a looping board of 13 spaces used to deck game logic
        $redPiece1 = new Pawn("red", $RedStartNode1, $RedStartNode1, 0);
        $redPiece2 = new Pawn("red", $RedStartNode2, $RedStartNode2, 1);
        $bluePiece1 = new Pawn("blue", $BlueStartNode1, $BlueStartNode1, 0);

        $bluePiece2 = new Pawn("blue", $BlueStartNode2, $BlueStartNode2, 1);

        $player1 = new Player([$redPiece1, $redPiece2], "red");
        $player2 = new Player([$bluePiece1, $bluePiece2], "blue");
        $game = new Game([$player1, $player2]);
        $redPiece1->setCurrentNode($Node2);
        $game->setCurCard(3);
        $game->setSelectedPawn($redPiece1);
        $game->parseClickedNode($Node5);
        $this->assertEquals($Node5, $redPiece1->getCurrentNode());//same color as slide can't slide
        $game->nextTurn();
        $bluePiece1->setCurrentNode($Node2);
        $redPiece1->setCurrentNode($Node7);
        $game->setCurCard(3);
        $game->setSelectedPawn($bluePiece1);
        $game->parseClickedNode($Node5);
        $this->assertEquals($Node9, $bluePiece1->getCurrentNode());//should slide
        $this->assertEquals($RedStartNode1, $redPiece1->getCurrentNode());//should be sent home

    }
    public function test_added_players() {
        $game = new Game([]);

        $players = [];
        $game->addPlayer("red");

        $this->assertEquals(1, $game->getNumPlayers());
        $this->assertNotEquals($players, $game->getPlayers());

        $player_array = $game->getPlayers();
        $first_player = $player_array[0];
        $pieces_array = $first_player->getPieces();
        $this->assertEquals("red", $first_player->getColor());

        $pieces = [];
        $node = $game->getBoard()->getNodeAt(13, 11);
        for ($i = 0, $i < 4; $i++;){

            $newpiece = new Pawn("red", $node, $node, $i);
            array_push($pieces, $newpiece);
        }

       // $this->assertEquals($pieces, $pieces_array);

    }
    public function test_json_functions(){
        $game = new Game([]);
        $game->addPlayer("red");
        $game->addPlayer("blue");
        $Node0 = new Node(0,0);//some extra nodes to set pieces to, can check that pieces were actually moved or not
        $Node1 = new Node(0,1);
        $json = $game->getBoardStateJson();
        $game->getPlayers()[0]->getPieces()[0]->setCurrentNode($Node0);
        $game->setBoardStateJson($json);
        $this->assertEquals(true, $game->getPlayers()[0]->getPieces()[0]->atStart());
    }

}