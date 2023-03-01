#include <iostream>
using namespace std;
#include <string>
#include <unordered_set>
#include <set>
#include <map>
#include <algorithm> 
#include <vector>    
#include <random>    
#include <chrono>    
#include <list>
#include "cards.h"
#include "player.h"
#include "game.h"

//------------------------------------------------
//  This file controls all functions of the cards
//  will control dealing, guessing as well as adding
//  to the known deck for players
//------------------------------------------------

vector<string> deckOfCards::dealHiddenDeck()
{ 
    vector<string> hiddenDeck;
    shuffle();
    hiddenDeck.push_back(suspectDeck[suspectDeck.size() - 1]); // puts the last card in each deck in the hidden deck
    hiddenDeck.push_back(roomDeck[roomDeck.size() - 1]);
    hiddenDeck.push_back(weaponsDeck[weaponsDeck.size() - 1]);
    suspectDeck.pop_back(); // removes the last card(now in hidden deck) from each deck
    roomDeck.pop_back();
    weaponsDeck.pop_back();
    return hiddenDeck;
}
void deckOfCards::shuffle()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(suspectDeck.begin(), suspectDeck.end(), default_random_engine(seed));
    std::shuffle(roomDeck.begin(), roomDeck.end(), default_random_engine(seed));
    std::shuffle(weaponsDeck.begin(), weaponsDeck.end(), default_random_engine(seed));
}
void deckOfCards::prepRemainderDeck()
{

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    while (suspectDeck.empty() != true)
    {
        remainderDeck.push_back(suspectDeck[suspectDeck.size() - 1]);
        suspectDeck.pop_back();
    }
    while (roomDeck.empty() != true)
    {
        remainderDeck.push_back(roomDeck[roomDeck.size() - 1]);
        roomDeck.pop_back();
    }
    while (weaponsDeck.empty() != true)
    {
        remainderDeck.push_back(weaponsDeck[weaponsDeck.size() - 1]);
        weaponsDeck.pop_back();
    }
    std::shuffle(remainderDeck.begin(), remainderDeck.end(), default_random_engine(seed));
}

string deckOfCards::dealCard(bool &isEmpty)
{ // call this repeatedly for each player in conjunction with dealOutAll.
    string returnValue = "";
    if (remainderDeck.size() == 0)
    {
        isEmpty = true;
        return returnValue;
    }
    else
    {
        returnValue = remainderDeck[remainderDeck.size() - 1];
        return returnValue;
    }
}

void deckOfCards::dealOutAll(game* theGame)
{ // will dealCard for every player, going one at a time until the cards are out. Once isEmpty is true, no more cards will be dealt.
    bool isEmpty = false;
    int numPlayers = theGame->listOfPlayers.size();
    while (!isEmpty)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            string CardPrint = deckOfCards::dealCard(isEmpty);
            theGame->listOfPlayers[i]->hand.push_back(CardPrint); // Takes the i-th player in playerList, and pushes the drawn card into their hand.
            if (!remainderDeck.empty())
            {
                remainderDeck.pop_back();
            }
            else
            {
                return;
            }
            
        }
    }
}


