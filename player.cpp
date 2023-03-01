#include <iostream>
using namespace std;
#include <unordered_set>
#include <set>
#include <map>
#include <algorithm> // std::random_shuffle
#include <vector>    // std::vector
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock


#include "cards.h"
#include "game.h"
#include "player.h"
#include "gameboard.h"

//------------------------------------------------
//  This file controls all functions of the players
//  including creation as well as any player-player
//  interaction
//------------------------------------------------

string player::returnRoomName(gameBoard* theBoard, int x, int y) {
    string roomName;
    switch(theBoard->testBoard[x][y]->spaceLocation){
                        case 's': 
                        roomName = "Study";
                        break;

                        case 'h': 
                        roomName = "Hall";
                        break;

                        case 'l': 
                        roomName = "Lounge";
                        break;

                        case 'L': 
                        roomName = "Library";
                        break;

                        case 'd': 
                        roomName = "Dining Room";
                        break;

                        case 'B': 
                        roomName = "Billiard Room";
                        break;

                        case 'c': 
                        roomName = "Conservatory";
                        break;

                        case 'b': 
                        roomName = "Ballroom";
                        break;

                        case 'k': 
                        roomName = "Kitchen";
                        break;

                        default:
                        roomName =  "Hallway";
                        break;
        }
    return roomName;
}

void cpuPlayer::prepUnknowns() {
    for (size_t i = 0; i < hand.size(); i++) {
        for (size_t j = 0; j < unknown_suspects.size(); j ++) {
            if (hand[i] == unknown_suspects[j]){ 
                unknown_suspects.erase(unknown_suspects.begin()+j);
            }
        }
        for (size_t j = 0; j < unknown_rooms.size(); j ++) {
            if (hand[i] == unknown_rooms[j]) {
                unknown_rooms.erase(unknown_rooms.begin()+j);
            }
        }
        for (size_t j = 0; j < unknown_weapons.size(); j ++) {
            if (hand[i] == unknown_weapons[j]) {
                unknown_weapons.erase(unknown_weapons.begin()+j);
            }
        }
    }
}

bool cpuPlayer::testCard(string tested) {
        for (size_t i = 0; i < hand.size(); i ++) {
            if ( tested == hand[i]) return true;
        }
        return false;
}

bool cpuPlayer::timeToStop(string roomName){
    if ((unknown_rooms.size() == 1) && (roomName == unknown_rooms[0])) {
        return 1;
    }
    else return 0;
}

void cpuPlayer::takeTurn(gameBoard* theBoard, game* theGame){
    theBoard->printBoard();
    int removeIt;
    int allaccess = 500;
    bool hasChanged = 0;
    bool ownRoom = 0;
    bool ownWeapon = 0;
    bool ownSuspect = 0;
    int nextX = xLocation;
    int nextY = yLocation;
    string roomName;
    if (turnCounter == xPath.size()-1){ // checks to see if the cpu is at the end of the predetermined path
        turnCounter = 0; // if it is then we set its turnCounter back to the beginning, starting its loop again
    }
    cout << endl;
    roomName = returnRoomName(theBoard, xLocation, yLocation);
    if(!timeToStop(roomName)) {
        nextX = xPath[turnCounter];
        nextY = yPath[turnCounter];
        theBoard->movement(nextX, nextY, allaccess, this);
        turnCounter++;
        xLocation = nextX;
        yLocation = nextY;
    }
    roomName = returnRoomName(theBoard, nextX, nextY);
    ownRoom = testCard(roomName);
    ownWeapon = testCard(unknown_weapons[weaponCounter]);
    ownSuspect = testCard(unknown_suspects[suspectCounter]);
    prepUnknowns();
    hasChanged = 0;
    if (theBoard->testBoard[nextX][nextY]->spaceLocation != NOT_ROOM) {
        hasChanged = theGame->cpuaccusation(this, unknown_suspects[suspectCounter], unknown_weapons[weaponCounter], roomName);
        prepUnknowns();
        if ((!hasChanged) && (!ownRoom) && (ownWeapon) && (ownSuspect)) {
        roomCounter++;
        }
        else if ((!hasChanged) && (ownRoom) && (!ownWeapon) && (ownSuspect)) {
            weaponCounter++;
        }
        else if ((!hasChanged) && (ownRoom) && (ownWeapon) && (!ownSuspect)) {
            suspectCounter++;
        }
        else if((!hasChanged) && (!ownRoom) && (!ownWeapon) && (!ownSuspect)) { //didnt get anything from the accusation and is none of the cards are in their hand
            bool decla = theGame->declaration(this, unknown_suspects[0], unknown_weapons[0], roomName);
            if (decla == 0) {
                std::cout << endl << "Player " << playerNumber + 1 << " guessed incorrectly and is out of the game!" << endl;
                for (size_t i = 0; i < theGame->listOfPlayers.size(); i ++)
                {
                    if( playerNumber == theGame->listOfPlayers[i]->playerNumber)
                    {
                        removeIt = i;
                    }
                }
                theGame->listOfPlayers.erase(theGame->listOfPlayers.begin()+removeIt);
                if (theGame->listOfPlayers.size() == 1){ 
                    theGame->gameover = 1;
                    std::cout << "Congratulations Player " << theGame->listOfPlayers[0]->playerNumber + 1 << " you won!" << endl;
                }
                return;
            }
            else{
                std::cout << endl <<  "Player " << playerNumber +1 << " guessed correctly, they win!" << endl;
                theGame->gameover = 1;
                return; 
            }
        }  
    } 
}


char player::playerTurn(){
    char valEntered;
    while(true){
        std::cout << "Choose one of the Following:" << endl;
        std::cout << "m: move player" << endl;
        std::cout << "a: accuse" << endl;
        std::cout << "f: final accusation WARNING If incorrect you no longer play:" << endl;
        std::cout << "e: end turn" << endl;
        std::cout << "Enter chosen input: ";
        std::cin >> valEntered;

        if (valEntered == 'm' || valEntered == 'a' || valEntered == 'f' || valEntered == '~'||valEntered == 'e')break;
        else{
            std::cout << endl << endl <<"Error incorrect input, try again!" << endl;
        }
    }
    return valEntered;
}


void humanPlayer::takeTurn(gameBoard* theBoard, game* theGame){       
    int allaccess = 500;
    int movementX;
    int movementY;
    bool hasMoved = 0;
    bool hasAccused = 0;
    bool turnEnded = 0;
    bool isPlayer = 0;
    string suspectName;
    int suspectNum = 0; // just initialising to get rid of warnings lol lets hope this doesnt break anything
    string weaponName;
    string roomName;
    bool movebool = 0;
    int movementMax = theBoard->rollDice();
    char choice;
    bool decla;
    theBoard->printBoard();
    while(!turnEnded){
        roomName = returnRoomName(theBoard, xLocation, yLocation);
        std::cout << "You are currently in ";
        if (theBoard->testBoard[xLocation][yLocation]->spaceLocation == NOT_ROOM) std::cout << "the hallway." << endl;
        else std::cout << "the " << roomName << endl;
        /* std::cout << "Your hand: ";
        for (int i = 0; i < player->hand.size(); i++) {
            std::cout << player->hand[i] << " ";
        }
        std::cout << endl; */ //here if we want to print the hand everytime
        choice = playerTurn();
        switch (choice){
           case 'm': {
                if(hasMoved != 1) {
                    while(!movebool)
                    {
                         std::cout << "Current Location: " << xLocation << ", " << yLocation << endl;
                        std::cout << "Movement Available: " << movementMax << endl;
                        std::cout << "Where would you like to move to (X,Y): ";
                        std::cin >> movementX;
                        std::cin >> movementY;
                        movebool = theBoard->movement(movementX, movementY, movementMax, this); //change allaccess back into movementMax
                        if(theBoard->testBoard[xLocation][yLocation]->spaceLocation == NOT_ROOM) {       
                        std::cout << "No more available actions, your turn ends." << endl;          
                        turnEnded = 1;  
                        return;
                    }
                    } 
                    hasMoved = 1;
                    
                }
                else {
                    std::cout << "You have already moved this turn, select another option" << endl;
                }
                break;
                
            }
             case 'a': {
                if (hasAccused != 1) {
                    vector<string> suspectDeck = {"Miss Scarlett", "Mr. Green", "Colonel Mustard", "Professor Plum", "Mrs. Peacock", "Mrs. White"};
                    vector<string> weaponsDeck = {"Knife", "Candlestick", "Lead Pipe", "Revolver", "Rope", "Wrench"};
                    char suspect;
                    char weapon;
                    char iterator = 'a';
               //     if(theBoard->testBoard[player->xLocation][player->yLocation]->spaceLocation == 'n'){
                //        std::cout << "You are not in a room you can make an accusation in!" << endl;
                //    } //dont know how to exit out of the accuse case if this is true lmao
                    while(true){
                        std::cout << "Enter suspect to accuse:" << endl;
                        for(auto const &x: suspectDeck){
                            std::cout << iterator << ": " << x << endl;
                            iterator++;
                        }
                        std::cout << "chosen suspect: ";
                        std::cin >> suspect;
                        std::cout << endl;
                        iterator = 'a';

                        if((suspect == 'a')||
                            (suspect == 'b')||
                            (suspect == 'c')||
                            (suspect == 'd')||
                            (suspect == 'e')||
                            (suspect == 'f'))
                            break;
                    }
                    while(true)
                    {
                        std::cout << "Enter weapon:" << endl;
                        for(auto const & x: weaponsDeck){
                            std::cout << iterator << ": " << x << endl;
                            iterator++;
                        }
                        std::cout << "chosen weapon: ";
                        std::cin >> weapon;
                        std::cout << endl;

                        switch(weapon){
                                case 'a': 
                                weaponName = "Knife";
                                break;

                                case 'b': 
                                weaponName = "Candlestick";
                                break;

                                case 'c': 
                                weaponName = "Lead Pipe";
                                break;

                                case 'd': 
                                weaponName = "Revolver";
                                break;

                                case 'e': 
                                weaponName = "Rope";
                                break;

                                case 'f': 
                                weaponName = "Wrench";
                                break;
                            }

                        if((weapon == 'a')||
                        (weapon == 'b')||
                        (weapon == 'c')||
                        (weapon == 'd')||
                        (weapon== 'e')||
                        (weapon == 'f'))
                            break;

                    }

                    switch(suspect) {
                                case 'a': {suspectName = "Miss Scarlett";
                                            suspectNum = 0;
                                            break;
                                }

                                case 'b': {suspectName = "Mr. Green";
                                            suspectNum = 1;
                                            break;
                                }

                                case 'c': {suspectName = "Colonel Mustard";
                                            suspectNum = 2;
                                            break;
                                }

                                case 'd': {suspectName = "Professor Plum";
                                            suspectNum = 3;
                                            break;
                                }

                                case 'e': {suspectName = "Mrs. Peacock";
                                            suspectNum = 4;
                                            break;
                                }

                                case 'f': {suspectName = "Mrs White";
                                            suspectNum = 5;
                                            break;
                                }

                            }
                    //gotta somehow check to see if the accused character is being played or nah
                    for(size_t i = 0; i < theGame->listOfPlayers.size(); i++){
                        if (theGame->listOfPlayers[i]->playerNumber == suspectNum) {
                            isPlayer = 1;
                        }
                        else  isPlayer = 0;

                    }

                    if (isPlayer == 1) {
                        theBoard->movement(xLocation, yLocation, allaccess, theGame->listOfPlayers[suspectNum]);
                    }
                    else {
                        for(int i = 0; i < 25; i++) {
                        for (int j = 0; j < 25; j++){
                            if(theBoard->testBoard[i][j])
                            {
                                for(size_t k = 0; k < theBoard->testBoard[i][j]->playersHere.size(); k++){
                                    if( theBoard->testBoard[i][j]->playersHere[k] == suspectNum){
                                        theBoard->testBoard[i][j]->removePlayer(suspectNum);
                                    }
                                }
                            }   
                        }
                    }
                    theBoard->testBoard[xLocation][yLocation]->addPlayer(suspectNum);
                    } //after all this runs the suspect should have been found and removed from their previous node
                    
                    
                    roomName = returnRoomName(theBoard, xLocation, yLocation);
                    std::cout << "You are accusing " << suspectName << " in the " << roomName << " with the " << weaponName << "." << endl;
                    theGame->playeraccusation(this, suspectName, weaponName, roomName); 
                    hasAccused = 1;
                }
                else {
                    std::cout << "You have already made an accusation this turn, select another option";
                }
                break;
            }
            case 'f': {
                char warning;
                int removeIt;
                std::cout << "WARNING: Once you make your final accusation you are either out of the game or finish the game!" << endl;
                std::cout << "Are you sure you want to continue (Y/N): ";
                std::cin >> warning;
                if(warning == 'y' || warning == 'Y')
                {
                    vector<string> suspectDeck = {"Miss Scarlett", "Mr. Green", "Colonel Mustard", "Professor Plum", "Mrs. Peacock", "Mrs. White"};
                     vector<string> weaponsDeck = {"Knife", "Candlestick", "Lead Pipe", "Revolver", "Rope", "Wrench"};
                     vector<string> roomDeck = {"Kitchen", "Ballroom", "Conservatory", "Library", "Study", "Hall", "Lounge", "Billiard Room", "Dining Room"};
                    char suspect;
                    char weapon;
                    char room;
                    char iterator = 'a';

                    while(true){
                        std::cout << "Enter suspect to accuse:" << endl;
                        for(auto const &x: suspectDeck){
                            std::cout << iterator << ": " << x << endl;
                            iterator++;
                        }
                        std::cout << "chosen suspect: ";
                        std::cin >> suspect;
                        std::cout << endl;
                        iterator = 'a';

                        switch(suspect) {
                                case 'a': {suspectName = "Miss Scarlett";
                                            suspectNum = 0;
                                            break;
                                }

                                case 'b': {suspectName = "Mr. Green";
                                            suspectNum = 1;
                                            break;
                                }

                                case 'c': {suspectName = "Colonel Mustard";
                                            suspectNum = 2;
                                            break;
                                }

                                case 'd': {suspectName = "Professor Plum";
                                            suspectNum = 3;
                                            break;
                                }

                                case 'e': {suspectName = "Mrs. Peacock";
                                            suspectNum = 4;
                                            break;
                                }

                                case 'f': {suspectName = "Mrs White";
                                            suspectNum = 5;
                                            break;
                                }

                            }

                        if((suspect == 'a')||
                            (suspect == 'b')||
                            (suspect == 'c')||
                            (suspect == 'd')||
                            (suspect == 'e')||
                            (suspect == 'f'))
                            break;
                            
                    }

                    while(true)
                    {
                        std::cout << "Enter weapon:" << endl;
                        for(auto const & x: weaponsDeck){
                            std::cout << iterator << ": " << x << endl;
                            iterator++;
                        }
                        std::cout << "chosen weapon: ";
                        std::cin >> weapon;
                        std::cout << endl;
                        iterator = 'a';

                        switch(weapon){
                                case 'a': 
                                weaponName = "Knife";
                                break;

                                case 'b': 
                                weaponName = "Candlestick";
                                break;

                                case 'c': 
                                weaponName = "Lead Pipe";
                                break;

                                case 'd': 
                                weaponName = "Revolver";
                                break;

                                case 'e': 
                                weaponName = "Rope";
                                break;

                                case 'f': 
                                weaponName = "Wrench";
                                break;
                            }

                        if((weapon == 'a')||
                        (weapon == 'b')||
                        (weapon == 'c')||
                        (weapon == 'd')||
                        (weapon== 'e')||
                        (weapon == 'f'))
                            break;
                    }

                    while(true)
                    {
                        std::cout << "Enter room:" << endl;
                        for(auto const & x: roomDeck){
                            std::cout << iterator << ": " << x << endl;
                            iterator++;
                        }
                        std::cout << "chosen room: ";
                        std::cin >> room;
                        std::cout << endl;

                        switch(room){
                        case 'a': 
                        roomName = "Kitchen";
                        break;

                        case 'b': 
                        roomName = "Ballroom";
                        break;

                        case 'c': 
                        roomName = "Conservatory";
                        break;

                        case 'd': 
                        roomName = "Library";
                        break;

                        case 'e': 
                        roomName = "Study";
                        break;

                        case 'f': 
                        roomName = "Hall";
                        break;

                        case 'g': 
                        roomName = "Lounge";
                        break;

                        case 'h': 
                        roomName = "Billiard Room";
                        break;

                        case 'i': 
                        roomName = "Dining Room";
                        break;
                    }
                        if((room == 'a')||
                        (room == 'b')||
                        (room == 'c')||
                        (room == 'd')||
                        (room == 'e')||
                        (room == 'f')||
                        (room == 'g')||
                        (room == 'h')||
                        (room == 'i')) break;
                    }
                    std::cout << "You think it was " << suspectName << " in the " << roomName << " with the " << weaponName << "." << endl;
                    decla = theGame->declaration(this, suspectName, weaponName, roomName);
                    if (decla == 0) {
                        std::cout << endl << "Incorrect! You are out of the game!" << endl;
                        turnEnded = 1;
                        for (size_t i = 0; i < theGame->listOfPlayers.size(); i ++)
                        {
                            if( playerNumber == theGame->listOfPlayers[i]->playerNumber)
                            {
                                removeIt = i;
                            }
                        }
                        theGame->listOfPlayers.erase(theGame->listOfPlayers.begin()+removeIt);
                        if (theGame->listOfPlayers.size() == 1){ 
                            theGame->gameover = 1;
                            std::cout << "Congratulations Player " << theGame->listOfPlayers[0]->playerNumber + 1 << " you won!" << endl;
                        }
                        return;
                    }
                    else{
                        std::cout << "That is correct, you win!" << endl;
                        turnEnded = 1;
                        theGame->gameover = 1;
                        return;
                    }
                    
                }
                break;
            }
            case 'e': {
                char yesno;
                std::cout << "Are you sure you want to end your turn (Y/N): ";
                std::cin >> yesno;
                if (yesno == 'y' || yesno == 'Y'){
                    turnEnded = 1;
                }
                break;
            }
            case '~': {
                //code to flip the board (sounded too scary for me)
            }

    }
    }
}
