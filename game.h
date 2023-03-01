#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;

#include <map>
#include <vector>    
#include "cards.h"
#include "player.h"
#include "gameboard.h"


//------------------------------------------------
//  This file controls the main game class that controls
//  taking players turns etc. not fully fleshed out yet
//
//------------------------------------------------


class game
{
/*
GAME CLASS:
-Rule of Zero implementation
-The primary class that controls the setup and execution of the game itself, including instantiating and initializing all other classes.

objects:
-playerOptions:
    a map<int, string> that corresponds the strings of characters with a number. Used for identification of players.

-deck:
    a deckOfCards object instantiated within the game class.

-HiddenDeck:
    a vector<string> that holds the result of deck.dealHiddenDeck. This will be the answer that players are searching for during the game.

-listOfPlayers:
    a vector<player*> that holds a list of pointers to every player currently in the game. Used for identifying players, determining the # of players, and accusations.

-numPlayers:
    an integer holding the number of players in the game.

-ourBoard:
    a gameBoard object instantiated within the game class.

-gameover:
    a boolean value that determines when the game has ended. When conditions have been met, it is pushed to 1. Otherwise, it is 0.

functions:
-bool isInputValid(int currCharacter):
    used during the creation of the game. It checks to see if the inputted player character is a valid input, or if it has been 
    taken by another player/is an out of range number.

-void printPlayers(int x):
    prints the character selection text for player x during game setup.

-game():
    the constructor for the game class.

-void prepCards():
    prepares the cards for the game by calling all relevant cards.h functions to build and deal the deck.

-void showCards():
    systematically goes through every human player and, by passing the terminal around the group, shows them their cards for the game. 

-void playGame():
    begins the game itself. It will iterate through the amount of players, with them taking turns until the 
    game is over through a player winning, or no players being left to continue playing.

-void playeraccusation(humanPlayer* player, string suspect, string weapon, string room):
    handles the human player accusations for the game. The function goes through every other player’s hand, and checks 
    for matching Suspect, Weapon, and Room, in that order. Once found, it informs the player of the card it found. If it 
    reaches the end without any matches, it prints a message saying such.

-bool cpuaccusation(cpuPlayer* player, string suspect, string weapon, string room):
    functions as the CPU version of playeraccusation, with no input to the terminal as to what is found. 

-bool declaration(player* player, string suspect, string weapon, string room):
    functions similarly to accusation, but it is instead comparing itself with the HiddenDeck. If the cards do 
    not match completely, then declaration returns 0 and guessedIncorrectly will be pushed to 1 as a result. If 
    declaration returns 1, the player guessed correctly and the game ends.
*/

    bool isInputValid(int currCharacter); 
    void printPlayers(int x);
    map<int,string> playerOptions = {{0,"Miss Scarlett"},{1,"Mr. Green"},{2,"Colonel Mustard"},{3,"Professor Plum"}, {4,"Mrs. Peacock"},{5,"Mrs. White"}};

public:
    deckOfCards deck;
    vector<string> HiddenDeck; 
    vector<player *> listOfPlayers; 
    int numPlayers;
    gameBoard ourBoard;
    bool gameover;


    game();
    void prepCards();
    void showCards();
    void playGame();
    void playeraccusation(humanPlayer* player, string suspect, string weapon, string room);
    bool cpuaccusation(cpuPlayer* accuser, string suspect, string weapon, string room); 
    bool declaration(player* player, string suspect, string weapon, string room); 
    
};
#endif
