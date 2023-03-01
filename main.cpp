#include <iostream>
#include <stdlib.h>
using namespace std;
#include "game.h"

//------------------------------------------------
//  This file is the function that is ran at runtime
//  the main function will instantiate and call all
//  other functions and classes
//------------------------------------------------

int main()
{
    game newGame;   //Instantiate the game
    newGame.prepCards();    //Deal the cards
    newGame.showCards();    //Show cards to players
    newGame.playGame();     //play actual game
    return 0;
}
