#include <iostream>
using namespace std;
#include <unordered_set>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <list>
#include <fstream>
#include "game.h"
#include "cards.h"
#include "player.h"
#include "gameboard.h"

//------------------------------------------------
//  This file controls the main game class that controls
//  taking players turns etc. not fully fleshed out yet
//
//------------------------------------------------

// If you want to do user input, eithier remove inputVector.txt or replace game::game
// with the included function at the bottom of this file
//  Starting to combine a few classes together;
game::game()
{
    std::fstream myinputFile;
    myinputFile.open("inputVector.txt");

    gameover = 0;
    numPlayers = 0;
    // Loop selects number of players
    while (1)
    {
        cout << "Select Number of Players from 2-6" << endl;
        if (myinputFile.is_open())
        {
            myinputFile >> numPlayers;
        }
        else
        {
            cin >> numPlayers;
        }

        if (numPlayers > 6 || numPlayers < 2)
            cout << "Error invalid input, try again!" << endl;
        else
            break;
    }
    // Loop is for character creation
    for (int x = 0; x < numPlayers; x++)
    {
        cout << endl
             << endl;
        int currCharacter;
        bool isCpuChar;

        while (1)
        {
            printPlayers(x);

            if (myinputFile.is_open())
            {
                myinputFile >> currCharacter;
            }
            else
            {
                cin >> currCharacter;
            }

            if (isInputValid(currCharacter))
                break;
            else
                cout << "Invalid Character, try again!" << endl
                     << endl;
        }
        playerOptions.erase(playerOptions.find(currCharacter));

        cout << "Is the player a CPU? 0 for no, 1 for yes: ";

        if (myinputFile.is_open())
        {
            myinputFile >> isCpuChar;
        }
        else
        {
            cin >> isCpuChar;
        }

        if (isCpuChar)
        {
            cpuPlayer *myChar = new cpuPlayer(currCharacter);
            switch (currCharacter)
            {

            case 0:
                myChar->xPath = {17, 18, 18, 18, 17, 19, 6, 9, 8, 7, 2, 1, 6, 4, 6, 9, 16};
                myChar->yPath = {3, 5, 7, 9, 16, 18, 4, 5, 7, 9, 12, 13, 17, 20, 19, 18, 10};
                break;

            case 1:
                myChar->xPath = {7, 9, 6, 4, 7, 1, 7, 7, 6, 19, 16, 18, 18, 16, 9, 9};
                myChar->yPath = {21, 18, 19, 20, 17, 13, 9, 6, 4, 18, 15, 9, 5, 7, 5, 12};
                break;

            case 2:
                myChar->xPath = {19, 18, 15, 9, 6, 8, 7, 1, 6, 4, 9, 19, 16, 18, 19};
                myChar->yPath = {7, 5, 7, 5, 4, 7, 9, 13, 18, 20, 18, 18, 16, 9, 7};
                break;

            case 3:
                myChar->xPath = {6, 6, 8, 7, 1, 6, 4, 18, 15, 9, 18, 18, 17, 19, 9, 9};
                myChar->yPath = {5, 4, 7, 9, 13, 18, 20, 5, 7, 5, 7, 9, 16, 18, 18, 12};
                break;

            case 4:
                myChar->xPath = {5, 4, 18, 16, 9, 6, 19, 16, 18, 14, 9, 8, 7, 1, 7};
                myChar->yPath = {18, 20, 5, 7, 5, 4, 18, 14, 9, 16, 18, 11, 9, 13, 17};
                break;

            case 5:
                myChar->xPath = {17, 9, 6, 4, 7, 1, 3, 7, 11, 9, 16, 18, 18, 18, 16, 19, 6, 8};
                myChar->yPath = {20, 18, 19, 20, 17, 13, 12, 9, 8, 5, 7, 5, 7, 9, 15, 18, 4, 4};
                break;
            }
            listOfPlayers.push_back(myChar);
        }
        else
        {
            humanPlayer *myChar = new humanPlayer(currCharacter);
            listOfPlayers.push_back(myChar);
        }
        for (auto it : listOfPlayers)
        {
            switch (it->playerNumber)
            {
            case 0:
                it->xLocation = 17;
                it->yLocation = 0;
                break;
            case 1:
                it->xLocation = 9;
                it->yLocation = 24;
                break;
            case 2:
                it->xLocation = 24;
                it->yLocation = 7;
                break;
            case 3:
                it->xLocation = 0;
                it->yLocation = 6;
                break;
            case 4:
                it->xLocation = 0;
                it->yLocation = 18;
                break;
            case 5:
                it->xLocation = 15;
                it->yLocation = 24;
                break;

            default:
                printf("wrong player number\n");
                break;
            }
        }

        // player * createCurrPlayer = createPlayer(isCpuChar);
        // player createCurrPlayer(currCharacter);
    }
    // All characters are now created! Start working on the Decks now
}
// This function simply prints out player options
void game::printPlayers(int x)
{
    cout << "Player " << x << " select your character" << endl;
    for (auto z : playerOptions)
    {
        cout << z.first << ":" << z.second << endl;
    }
    cout << "Select from 0-5 (No repeats): ";
}

bool game::isInputValid(int currCharacter)
{
    if (currCharacter > 5 || currCharacter < 0)
    {
        return false;
    }
    else if (listOfPlayers.size() == 0)
        return true;
    else
    {
        for (size_t x = 0; x < listOfPlayers.size(); x++)
        {
            if (listOfPlayers[x]->playerNumber == currCharacter)
            {
                return false;
            }
        }
    }
    return true;
}

void game::playeraccusation(humanPlayer *accuser, string suspect, string weapon, string room) // callingPlayer is necessary because, in game, it isn't very easy to determine which player is calling this. Could move these functions to be a part of the player class instead?
{
    size_t callingPlayer = 0;
    for (size_t i = 0; i < listOfPlayers.size(); i++)
    {
        if (accuser->playerNumber == listOfPlayers[i]->playerNumber)
        {
            callingPlayer = i;
            break;
        }
    }
    size_t visitingPlayer = callingPlayer + 1; // first visit the player 1 digit above the player who is making an accusation
    if (visitingPlayer > listOfPlayers.size())
        visitingPlayer = 0; // if visitingPlayer ends up higher than the # players, loop back down to zero.
    while (visitingPlayer != callingPlayer)
    {                                                                           // as we go around the table...
        for (size_t i = 0; i < listOfPlayers[visitingPlayer]->hand.size(); i++) // for each card in visitingPlayer's hand...
        {
            if (listOfPlayers[visitingPlayer]->hand[i] == suspect)
            {
                cout << "Player " << visitingPlayer << " has a card you accused for: " << suspect << endl; // if it's a match to the suspect accusation, print and return.
                accuser->hand.push_back(suspect);
                return;
            }
            else if (listOfPlayers[visitingPlayer]->hand[i] == weapon)
            {
                cout << "Player " << visitingPlayer << " has a card you accused for: " << weapon << endl; // if it's a match to the weapon accusation, print and return.
                accuser->hand.push_back(weapon);
                return;
            }
            else if (listOfPlayers[visitingPlayer]->hand[i] == room)
            {
                cout << "Player " << visitingPlayer << " has a card you accused for: " << room << endl; // if its a match to the room accusation, print and return.
                accuser->hand.push_back(room);
                return;
            }
        }
        visitingPlayer = visitingPlayer + 1; // if no cards match, move to next player
    }
    cout << "No players had any of the cards you accused for."; // if you reach this point, none of your accusations have been challenged. Print and return.
    return;
}

bool game::cpuaccusation(cpuPlayer *accuser, string suspect, string weapon, string room) // callingPlayer is necessary because, in game, it isn't very easy to determine which player is calling this. Could move these functions to be a part of the player class instead?
{
    size_t callingPlayer = 0;
    for (size_t i = 0; i < listOfPlayers.size(); i++)
    {
        if (accuser->playerNumber == listOfPlayers[i]->playerNumber)
        {
            callingPlayer = i;
            break;
        }
    }
    size_t visitingPlayer = callingPlayer + 1; // first visit the player 1 digit above the player who is making an accusation
    if (!(visitingPlayer < listOfPlayers.size()))
        visitingPlayer = 0; // if visitingPlayer ends up higher than the # players, loop back down to zero.
    if (callingPlayer == visitingPlayer)
        visitingPlayer++;
    while (visitingPlayer != callingPlayer)
    {                                                                           // as we go around the table...
        for (size_t i = 0; i < listOfPlayers[visitingPlayer]->hand.size(); i++) // for each card in visitingPlayer's hand...
        {
            if (listOfPlayers[visitingPlayer]->hand[i] == suspect)
            {
                cout << "Player " << listOfPlayers[visitingPlayer]->playerNumber << " had a response." << endl;
                accuser->hand.push_back(suspect);
                return 1;
            }
            else if (listOfPlayers[visitingPlayer]->hand[i] == weapon)
            {
                cout << "Player " << listOfPlayers[visitingPlayer]->playerNumber << " had a response." << endl;
                accuser->hand.push_back(weapon);
                return 1;
            }
            else if (listOfPlayers[visitingPlayer]->hand[i] == room)
            {
                cout << "Player " << listOfPlayers[visitingPlayer]->playerNumber << " had a response." << endl;
                accuser->hand.push_back(room);
                return 1;
            }
        }
        visitingPlayer = visitingPlayer + 1; // if no cards match, move to next player
        if (!(visitingPlayer < listOfPlayers.size()))
            visitingPlayer = 0;
    }
    cout << "There was no response.";
    return 0;
}

bool game::declaration(player *player, string suspect, string weapon, string room) // 0 is a false declaration, player is out. 1 is a true declaration, player wins and game is over.
{
    int callingPlayer = player->playerNumber;
    for (size_t i = 0; i < listOfPlayers.size(); i++)
    {
        if (player->playerNumber == listOfPlayers[i]->playerNumber)
        {
            callingPlayer = i;
            break;
        }
    }
    for (int i = 0; i < 3; i++) // for each card in visitingPlayer's hand...
    {
        if (HiddenDeck[i] == suspect)
        {
            continue;
        }
        else if (HiddenDeck[i] == weapon)
        {
            continue;
        }
        else if (HiddenDeck[i] == room)
        {
            continue;
        }

        else
        {
            listOfPlayers[callingPlayer]->guessedIncorrectly = true;
            return 0;
        }
    }
    return 1;
}

void game::prepCards()
{
    this->HiddenDeck = this->deck.dealHiddenDeck();
    this->deck.prepRemainderDeck();
    this->deck.dealOutAll(this);
}

void game::showCards()
{
    int check = 0;
    for (size_t x = 1; x <= this->listOfPlayers.size(); x++)
    {
        if (this->listOfPlayers[x - 1]->isCpuChar)
            continue;
        cout << "Please pass the terminal to player " << x << ". Press 1 and hit enter when ready: ";
        while (check != 1)
            cin >> check;
        cout << "Hello Player " << x << "! These are your cards. Write them down: " << endl;
        for (size_t y = 0; y < this->listOfPlayers[x - 1]->hand.size(); y++)
        {
            cout << this->listOfPlayers[x - 1]->hand[y] << " ";
        }
        check = 0;
        cout << endl
             << "Enter 1 when finished";
        while (check != 1)
            cin >> check;
        check = 0;
        system("clear");
    }
}

void game::playGame()
{
    for (size_t i = 0; i < this->listOfPlayers.size(); i++)
    {
        while (!this->gameover)
        {
            if (!this->listOfPlayers[i]->guessedIncorrectly)
            {
                cout << endl
                     << endl
                     << endl
                     << "Player " << i + 1 << " it is your turn!" << endl;
                if (this->ourBoard.testBoard[this->listOfPlayers[i]->xLocation][this->listOfPlayers[i]->yLocation]->spaceLocation != NOT_ROOM)
                {
                    cout << "You are currently in the: ";
                    switch (this->ourBoard.testBoard[this->listOfPlayers[i]->xLocation][this->listOfPlayers[i]->yLocation]->spaceLocation)
                    {
                    case STUDY:
                        cout << "Study. (S)" << endl;
                        break;

                    case HALL:
                        cout << "Hall. (H)" << endl;
                        break;

                    case LOUNGE:
                        cout << "Lounge. (N)" << endl;
                        break;

                    case LIBRARY:
                        cout << "Library. (L)" << endl;
                        break;

                    case DINING_ROOM:
                        cout << "Dining Room. (D)" << endl;
                        break;

                    case BILLIARD_ROOM:
                        cout << "Billiard Room. (I)" << endl;
                        break;

                    case CONSERVATORY:
                        cout << "Conservatory. (C)" << endl;
                        break;

                    case BALLROOM:
                        cout << "BallRoom. (B)" << endl;
                        break;

                    case KITCHEN:
                        cout << "Kitchen. (K)" << endl;
                        break;

                    default:
                        cout << "Who knows. :(" << endl;
                        break;
                    }
                }

                this->listOfPlayers[i]->takeTurn(&this->ourBoard, this);
            }
        }
    }
}

/// Replace the game constructor with this if you wish to play a game with human characters,
/// To get this game working in gradescope we created an input file and used
/// the file to read "user " input instead of inputs on the command line
/*
game::game()
{

    gameover = 0;
    numPlayers = 0;
    // Loop selects number of players
    while (1)
    {
        cout << "Select Number of Players from 2-6" << endl;
        cin >> numPlayers;
        if (numPlayers > 6 || numPlayers < 2)
            cout << "Error invalid input, try again!" << endl;
        else
            break;
    }
    // Loop is for character creation
    for (int x = 0; x < numPlayers; x++)
    {
        cout << endl
             << endl;
        int currCharacter;
        bool isCpuChar;

        while (1)
        {
            printPlayers(x);
            cin >> currCharacter;

            if (isInputValid(currCharacter))
                break;
            else
                cout << "Invalid Character, try again!" << endl
                     << endl;
        }
        playerOptions.erase(playerOptions.find(currCharacter));

        cout << "Is the player a CPU? 0 for no, 1 for yes: ";

        cin >> isCpuChar;
        if (isCpuChar)
        {
            cpuPlayer *myChar = new cpuPlayer(currCharacter);
            switch (currCharacter)
            {

            case 0:
                myChar->xPath = {17, 18, 18, 18, 17, 19, 6, 9, 8, 7, 2, 1, 6, 4, 6, 9, 16};
                myChar->yPath = {3, 5, 7, 9, 16, 18, 4, 5, 7, 9, 12, 13, 17, 20, 19, 18, 10};
                break;

            case 1:
                myChar->xPath = {7, 9, 6, 4, 7, 1, 7, 7, 6, 19, 16, 18, 18, 16, 9, 9};
                myChar->yPath = {21, 18, 19, 20, 17, 13, 9, 6, 4, 18, 15, 9, 5, 7, 5, 12};
                break;

            case 2:
                myChar->xPath = {19, 18, 15, 9, 6, 8, 7, 1, 6, 4, 9, 19, 16, 18, 19};
                myChar->yPath = {7, 5, 7, 5, 4, 7, 9, 13, 18, 20, 18, 18, 16, 9, 7};
                break;

            case 3:
                myChar->xPath = {6, 6, 8, 7, 1, 6, 4, 18, 15, 9, 18, 18, 17, 19, 9, 9};
                myChar->yPath = {5, 4, 7, 9, 13, 18, 20, 5, 7, 5, 7, 9, 16, 18, 18, 12};
                break;

            case 4:
                myChar->xPath = {5, 4, 18, 16, 9, 6, 19, 16, 18, 14, 9, 8, 7, 1, 7};
                myChar->yPath = {18, 20, 5, 7, 5, 4, 18, 14, 9, 16, 18, 11, 9, 13, 17};
                break;

            case 5:
                myChar->xPath = {17, 9, 6, 4, 7, 1, 3, 7, 11, 9, 16, 18, 18, 18, 16, 19, 6, 8};
                myChar->yPath = {20, 18, 19, 20, 17, 13, 12, 9, 8, 5, 7, 5, 7, 9, 15, 18, 4, 4};
                break;
            }
            listOfPlayers.push_back(myChar);
        }
        else
        {
            humanPlayer *myChar = new humanPlayer(currCharacter);
            listOfPlayers.push_back(myChar);
        }
        for (auto it : listOfPlayers)
        {
            switch (it->playerNumber)
            {
            case 0:
                it->xLocation = 17;
                it->yLocation = 0;
                break;
            case 1:
                it->xLocation = 9;
                it->yLocation = 24;
                break;
            case 2:
                it->xLocation = 24;
                it->yLocation = 7;
                break;
            case 3:
                it->xLocation = 0;
                it->yLocation = 6;
                break;
            case 4:
                it->xLocation = 0;
                it->yLocation = 18;
                break;
            case 5:
                it->xLocation = 15;
                it->yLocation = 24;
                break;

            default:
                printf("wrong player number\n");
                break;
            }
        }

        // player * createCurrPlayer = createPlayer(isCpuChar);
        // player createCurrPlayer(currCharacter);
    }
    // All characters are now created! Start working on the Decks now
}

*/