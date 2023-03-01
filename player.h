#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

class gameBoard;
class game;


enum characterNames
{
    Miss_Scarlett,
    Mr_Green,
    Colonel_Mustard,
    Professor_Plum,
    Mrs_Peacock,
    Mrs_White
};



class player
{
/*
PLAYER CLASS:
-Rule of Zero implementation
-Controls the player's information as well as their interaction with the game, including the turn-taking process.

objects:
-playerName:
    a string identifying the player as their chosen character.

-hand:
    a vector<string> which is a list of each card in a player’s hand for the game.

-guessedIncorrectly:
    a boolean variable which is 0 for the game until a player makes an incorrect declaration, which moves this bool to 1. Makes them unable to take any turns.

-playerNumber:
    an int serving as a secondary identifier for the player, specifically in what order the players were inputted on game startup. Controls accusations & turn order.

-isCpuChar:
    a bool which is 1 if the player is a CPU. 0 if human.

-xLocation & yLocation:
    integers that update to represent the player's location on the board.

functions:
-char playerTurn():
    prompts the player to input a character signifying the action they choose to take on their turn. Returns that character.

-string returnRoomName(gameBoard* theBoard, int x, int y):
    returns the name of the room corresponding to coordinate x, y.

-virtual void takeTurn(gameBoard* theBoard, game* theGame) = 0:
    the placeholder virtual function for takeTurn; this will be overridden by player’s derived classes, which will specify takeTurn 
    according to whether the player is a CPU or a human. It controls the turn taking process of a player for the game.

-player (int playerNum):
    the default constructor for this class. sets guessedIncorrectly to 0 and playerNumber to playerNum.
*/

public:
    string playerName;
    vector<string> hand;
    bool guessedIncorrectly;
    int playerNumber;
    bool isCpuChar;
    int xLocation; 
    int yLocation; 

    char playerTurn();
    string returnRoomName(gameBoard* theBoard, int x, int y);
    virtual void takeTurn(gameBoard* theBoard, game* theGame) = 0;

    player( int playerNum)
    {
        guessedIncorrectly = false;
        playerNumber = playerNum;
    }

};




class cpuPlayer:public player{
/*
CPUPLAYER CLASS:
-Rule of Zero implementation
-Derived class of player; controls CPU logic and their turn-taking functionality.

objects:
-turnCounter
    a size_t variable indicating the number of turns that have passed.

-weaponCounter, suspectCounter, roomCounter:
    integers that count up the amount of weapons, suspects, and rooms encountered by the CPU.

-unknown_suspects, unknown_rooms, unknown_weapons:
    a vector<string> list of every suspect, room, and weapon card NOT encountered by the CPU.

-xPath, yPath
    vector<int> lists that dictate the path a CPU will take throughout the game.

functions:
-bool timeToStop(string roomName):
    instructs the cpu to stop once there is only one room left in the unknown_rooms string (meaning that they know the room in hiddenDeck).

-void prepUnknowns():
    Removes the initial cards in the CPU's hand from the list of unknowns.

-bool testCard(string tested):
    checks to see if the card "tested" is in the CPU's hand.

-void takeTurn(gameBoard* theBoard, game* theGame):
    the CPU version of takeTurn, which steps through predetermined logic paths to automate how the CPU plays.

-cpuPlayer(int playerNum):player(playerNum):
    the CPU version of the constructor, which additionally sets isCpuChar = true.

*/

    public:
    size_t turnCounter = 0;
    int weaponCounter = 0;
    int suspectCounter = 0;
    int roomCounter = 0;
    vector<string> unknown_suspects = {"Miss Scarlett", "Mr. Green", "Colonel Mustard", "Professor Plum", "Mrs. Peacock", "Mrs. White"};
    vector<string> unknown_rooms = {"Kitchen", "Ballroom", "Conservatory", "Library", "Study", "Hall", "Lounge", "Billiard Room", "Dining Room"};
    vector<string> unknown_weapons = {"Knife", "Candlestick", "Lead Pipe", "Revolver", "Rope", "Wrench"};
    vector<int> xPath;
    vector<int> yPath;
    bool timeToStop(string roomName);
    void prepUnknowns();
    bool testCard(string tested); 
    void takeTurn(gameBoard* theBoard, game* theGame);
    

    cpuPlayer(int playerNum):player(playerNum){
        playerNumber = playerNum;
        guessedIncorrectly = false;
        isCpuChar = true;
    }

};

class humanPlayer:public player{
/*
HUMANPLAYER CLASS:
-Rule of Zero implementation
-Derived class of player; controls human player interaction with the game through the terminal.

functions:
-void takeTurn(gameBoard* theBoard, game* theGame):
    the human version of takeTurn, which prompts the player through the terminal to interact with the game and issue commands to execute.

-cpuPlayer(int playerNum):player(playerNum):
    the human version of the constructor, which additionally sets isCpuChar = false.
    
*/

    public:


    void takeTurn(gameBoard* theBoard, game* theGame);

    humanPlayer(int playerNum):player(playerNum){
        guessedIncorrectly = false;
        isCpuChar = false;
    }
    
};

#endif





