#ifndef CARDS_H
#define CARDS_H

#include <iostream>
using namespace std;
#include <vector>    // std::vector


class game;

class deckOfCards

{
/*
DECKOFCARDS CLASS:
-Rule of Zero implementation
-Controls the implementation and distribution of cards to the players.

objects:
-suspectDeck, roomDeck, weaponsDeck: 
    vector<string>s filled with cards of their respective type. To be shuffled and drawn into a hidden deck (dealHiddenDeck) and remainderDeck (prepRemainderDeck).

-remainderDeck: 
    empty vector<string> upon initialization; to be filled and shuffled with all cards that are not drawn for hidden deck.

functions:
-void shuffle(): 
    randomly shuffles every card within the three card-type decks (suspect, room, weapons). 

-vector<string> dealHiddenDeck(): 
    pops back of each of the three card-type decks (suspect, room, weapons) into a new deck. These three popped make up the correct answer. Returns string of popped cards.

-void prepRemainderDeck(): 
    pops all remaining cards across the three card-type decks into remainderDeck, then randomizes their positions using std::shuffle.

-string dealCard(bool &isEmpty): 
    deals a card to a player. If isEmpty is true, it does not deal a card. Is called multiple times within dealOutAll.

-void dealOutAll(int numPlayers): 
    deals out all cards within prepRemainderDeck to the players, one card at a time. Calls the individual dealCard multiple times as part of its functionality.

*/

public:

    vector<string> suspectDeck = {"Miss Scarlett", "Mr. Green", "Colonel Mustard", "Professor Plum", "Mrs. Peacock", "Mrs. White"};
    vector<string> roomDeck = {"Kitchen", "Ballroom", "Conservatory", "Library", "Study", "Hall", "Lounge", "Billiard Room", "Dining Room"};
    vector<string> weaponsDeck = {"Knife", "Candlestick", "Lead Pipe", "Revolver", "Rope", "Wrench"};
    vector<string> remainderDeck; 

    
    void shuffle();
    vector <string> dealHiddenDeck();
    void prepRemainderDeck();
    string dealCard(bool &isEmpty);
    void dealOutAll(game* theGame);
    
};



#endif
