#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
using namespace std;
#include <vector>    
#include "player.h"
//------------------------------------------------
// These are the characters that we are using to
//  check for location of space (hall, study, etc.)
//
//------------------------------------------------
#define STUDY 's'
#define HALL 'h'
#define LOUNGE 'l'
#define LIBRARY 'L'
#define DINING_ROOM 'd'
#define BILLIARD_ROOM 'B'
#define CONSERVATORY 'c'
#define BALLROOM 'b'
#define KITCHEN 'k'
#define NOT_ROOM 'n'

//------------------------------------------------
//  This file controls all functions of movement
//  as well as the game board in general
//
//------------------------------------------------
class boardNode
{
/*
BOARDNODE CLASS:
-Rule of Zero implementation
-Functions as a single unit of the gameboard space, which facilitates movement. The player will not interact with this themselves; rather, the game does it for them.

objects:
-playersHere:
    a vector<string> which holds the strings of players currently at a given board location. 

-spaceLocation:
    a char variable, which details where on the board the space is attributed to, such as the name of a particular room or a hallway.

-adjSpaces:
    a vector<boardNode*> list which contains pointers to all spaces adjacent to the boardNode in question, to a maximum of 4 nodes.

functions:
-boardNode(char):
    default constructor, creates a board node with the location type passed in as an argument.

-void addAdj(boardNode*):
    adds a given boardNode pointer to the adjSpaces list of the node this function is called from.

-void addPlayer(int):
    adds a player to a node’s playersHere; if the node is not a room, it can only hold a singular player at a time. The input is a number attributed to the player in question.

-void removePlayer(int):
    removes a player from that location in playersHere. The input is a number attributed to the player in question.

-bool isEmpty():
    checks whether there are players at the node this function is called from.

*/
public:
    vector<int> playersHere; 
    char spaceLocation; 
    vector<boardNode*> adjSpaces; 

    boardNode(char); 
    void addAdj(boardNode*);
    void addPlayer(int); 
    void removePlayer(int); 
    bool isEmpty(); 

};

class gameBoard
{
/*
GAMEBOARD CLASS:
-Rule of Zero implementation
-Functions as the entire board upon which players use. This function will be what players interface with in regards to the board.

objects:
-testBoard:
    a vector<vector<boardNode*>> which serves as the 2-dimensional "storage unit" to build the board within.

functions:
-gameBoard():
    default constructor which generates the 24x25 tile board needed for the game.

-int rollDice():
    rolls two 6-sided dice and returns the total. This is used for player movement.

-void printBoard():
    prints the full 24x25 board into the terminal, including colors to depict certain features of the board.

-void movement(int xCord, int yCord, int maxDistance, player *player):
    will find every board node that a player can move to during their turn, with their dice roll. If coordinates are invalid,
    returns an error message. Otherwise the player is removed from their current position and placed in their desired one.

*/

    public:
    vector<vector<boardNode*>> testBoard;

    gameBoard(); 
    int rollDice();
    void printBoard();
    bool movement(int xCord, int yCord, int maxDistance, player *player);
    
};

#endif
