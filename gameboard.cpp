#include <iostream>
using namespace std;
#include <list>
#include <vector>   
#include <unordered_set>
#include <set>
#include <map>
#include <algorithm> 
#include <vector>    
#include <random>    
#include <chrono>    
#include <list>
#include "gameboard.h"
#include "colors.h"

//------------------------------------------------
//  This file controls all functions of movement
//  as well as the game board in general
//------------------------------------------------

boardNode::boardNode(char location)
{
    spaceLocation = location;
}

// adds the passed in adjacent node to the list of adj nodes
void boardNode::addAdj(boardNode *adj)
{
    if (this->adjSpaces.size() > 4)
    {
        cout << "error too many adjacent nodes" << endl;
        return;
    }

    for (size_t i = 0; i < this->adjSpaces.size() && i < 5; i++) // the max number of iterations should be 4, as no node connects to more that 4 other spaces.
    {
        if (this->adjSpaces[i] == adj)
            return;
    }

    this->adjSpaces.push_back(adj);
    adj->adjSpaces.push_back(this);
    return;
}

// puts player into node
void boardNode::addPlayer(int character)
{
    this->playersHere.push_back(character);
    return;
}

// iterates through players here list to remove desired character, max number of iterations is 6 I believe, as we only have 6 characters
void boardNode::removePlayer(int character)
{
    for (auto it = this->playersHere.begin(); it < this->playersHere.end(); it++)
    {
        if (*it == character)
        {
            this->playersHere.erase(it);
        }
    }
    return;
}

// checks if there is a player in the space, returns true if it is empty and false if it has a player present
bool boardNode::isEmpty()
{
    return this->playersHere.empty();
}

//
//  creates the 25x25 gameboard manually
gameBoard::gameBoard()
{
    this->testBoard.resize(25);
    for (int i = 0; i < 25; i++) // fills every part of the 2d matrix with nullptrs, makes sure there is no random trash, and makes it easier to implement out of bounds checks
    {
        this->testBoard[i].assign(25, nullptr);
    }

    boardNode *study = new boardNode(STUDY);
    this->testBoard[6][4] = study;

    boardNode *hall = new boardNode(HALL);
    this->testBoard[9][5] = hall;
    this->testBoard[11][6] = hall;
    this->testBoard[12][6] = hall;
    this->testBoard[13][6] = hall;

    boardNode *lounge = new boardNode(LOUNGE);
    this->testBoard[18][5] = lounge;

    boardNode *library = new boardNode(LIBRARY);
    this->testBoard[7][9] = library;
    this->testBoard[3][11] = library;

    boardNode *billiardRoom = new boardNode(BILLIARD_ROOM);
    this->testBoard[1][13] = billiardRoom;
    this->testBoard[6][15] = billiardRoom;

    boardNode *diningRoom = new boardNode(DINING_ROOM);
    this->testBoard[18][9] = diningRoom;
    this->testBoard[17][12] = diningRoom;

    boardNode *conservatory = new boardNode(CONSERVATORY);
    this->testBoard[4][20] = conservatory;

    boardNode *ballroom = new boardNode(BALLROOM);
    this->testBoard[9][18] = ballroom;
    this->testBoard[15][18] = ballroom;
    this->testBoard[8][19] = ballroom;
    this->testBoard[16][19] = ballroom;

    boardNode *kitchen = new boardNode(KITCHEN);
    this->testBoard[19][18] = kitchen;

    study->addAdj(kitchen);
    lounge->addAdj(conservatory);

    this->testBoard[7][0] = new boardNode(NOT_ROOM);
    this->testBoard[17][0] = new boardNode(NOT_ROOM);

    for (int i = 1; i < 5; i++)
    {
        this->testBoard[7][i] = new boardNode(NOT_ROOM);
        this->testBoard[8][i] = new boardNode(NOT_ROOM);
        this->testBoard[16][i] = new boardNode(NOT_ROOM);
        this->testBoard[17][i] = new boardNode(NOT_ROOM);
    }

    for (int i = 1; i < 9; i++)
    {
        this->testBoard[i][5] = new boardNode(NOT_ROOM);
    }
    this->testBoard[16][5] = new boardNode(NOT_ROOM);
    this->testBoard[17][5] = new boardNode(NOT_ROOM);

    for (int i = 0; i < 9; i++)
    {
        this->testBoard[i][6] = new boardNode(NOT_ROOM);
    }

    for (int i = 16; i < 24; i++)
    {
        this->testBoard[i][6] = new boardNode(NOT_ROOM);
    }

    for (int i = 7; i < 25; i++)
    {
        this->testBoard[i][7] = new boardNode(NOT_ROOM);
    }

    for (int i = 8; i < 24; i++)
    {
        this->testBoard[i][8] = new boardNode(NOT_ROOM);
    }

    for (int i = 9; i < 13; i++)
    {
        this->testBoard[8][i] = new boardNode(NOT_ROOM);
        this->testBoard[9][i] = new boardNode(NOT_ROOM);
        this->testBoard[15][i] = new boardNode(NOT_ROOM);
        this->testBoard[16][i] = new boardNode(NOT_ROOM);
    }

    this->testBoard[7][11] = new boardNode(NOT_ROOM);

    for (int i = 1; i < 8; i++)
    {
        this->testBoard[i][12] = new boardNode(NOT_ROOM);
    }

    for (int i = 13; i < 16; i++)
    {
        this->testBoard[7][i] = new boardNode(NOT_ROOM);
        this->testBoard[8][i] = new boardNode(NOT_ROOM);
        this->testBoard[9][i] = new boardNode(NOT_ROOM);
        this->testBoard[15][i] = new boardNode(NOT_ROOM);
        this->testBoard[16][i] = new boardNode(NOT_ROOM);
    }

    this->testBoard[17][15] = new boardNode(NOT_ROOM);
    this->testBoard[18][15] = new boardNode(NOT_ROOM);
    this->testBoard[19][15] = new boardNode(NOT_ROOM);

    for (int i = 7; i < 24; i++)
    {
        this->testBoard[i][16] = new boardNode(NOT_ROOM);
    }

    for (int i = 1; i < 25; i++)
    {
        this->testBoard[i][17] = new boardNode(NOT_ROOM);
    }

    for (int i = 0; i < 5; i++)
    {
        this->testBoard[i][18] = new boardNode(NOT_ROOM);
    }

    for (int i = 18; i < 21; i++)
    {
        this->testBoard[5][i] = new boardNode(NOT_ROOM);
        this->testBoard[6][i] = new boardNode(NOT_ROOM);
        this->testBoard[7][i] = new boardNode(NOT_ROOM);
        this->testBoard[17][i] = new boardNode(NOT_ROOM);
        this->testBoard[18][i] = new boardNode(NOT_ROOM);
    }

    for (int i = 21; i < 23; i++)
    {
        this->testBoard[6][i] = new boardNode(NOT_ROOM);
        this->testBoard[7][i] = new boardNode(NOT_ROOM);
        this->testBoard[17][i] = new boardNode(NOT_ROOM);
        this->testBoard[18][i] = new boardNode(NOT_ROOM);
    }

    for (int i = 7; i < 10; i++)
    {
        this->testBoard[i][23] = new boardNode(NOT_ROOM);
        this->testBoard[i + (15 - 7)][23] = new boardNode(NOT_ROOM);
    }

    this->testBoard[9][24] = new boardNode(NOT_ROOM);
    this->testBoard[15][24] = new boardNode(NOT_ROOM);


    // creating the links between nodes, every one checks incase a connection gets created twice
    study->addAdj(this->testBoard[6][5]);
    hall->addAdj(this->testBoard[8][5]);
    hall->addAdj(this->testBoard[11][7]);
    hall->addAdj(this->testBoard[12][7]);
    hall->addAdj(this->testBoard[13][7]);
    lounge->addAdj(this->testBoard[17][5]);
    library->addAdj(this->testBoard[8][9]);
    library->addAdj(this->testBoard[3][12]);
    billiardRoom->addAdj(this->testBoard[1][12]);
    billiardRoom->addAdj(this->testBoard[7][15]);
    conservatory->addAdj(this->testBoard[6][20]);
    ballroom->addAdj(this->testBoard[7][19]);
    ballroom->addAdj(this->testBoard[9][17]);
    ballroom->addAdj(this->testBoard[15][17]);
    ballroom->addAdj(this->testBoard[17][19]);
    kitchen->addAdj(this->testBoard[18][18]);
    diningRoom->addAdj(this->testBoard[16][12]);
    diningRoom->addAdj(this->testBoard[18][8]);

    this->testBoard[0][6]->addAdj(this->testBoard[1][6]);

    for (int i = 1; i < 7; i++)
    {
        this->testBoard[i][5]->addAdj(this->testBoard[i][6]);
        this->testBoard[i][5]->addAdj(this->testBoard[i + 1][5]);
        this->testBoard[i][6]->addAdj(this->testBoard[i + 1][6]);
    }

    for (int i = 0; i < 7; i++)
    {
        this->testBoard[7][i]->addAdj(this->testBoard[7][i + 1]);
    }

    for (int i = 11; i < 23; i++)
    {
        this->testBoard[7][i]->addAdj(this->testBoard[7][i + 1]);
    }

    for (int i = 1; i < 17; i++)
    {
        this->testBoard[8][i]->addAdj(this->testBoard[8][i + 1]);
    }

    for (int i = 1; i < 8; i++)
    {
        this->testBoard[7][i]->addAdj(this->testBoard[8][i]);
        this->testBoard[7][i + 10]->addAdj(this->testBoard[8][i + 10]);
    }

    for (int i = 1; i < 7; i++)
    {
        this->testBoard[i][12]->addAdj(this->testBoard[i + 1][12]);
        this->testBoard[16][i]->addAdj(this->testBoard[17][i]);
        this->testBoard[16][i]->addAdj(this->testBoard[16][i + 1]);
        this->testBoard[17][i]->addAdj(this->testBoard[17][i + 1]);
        this->testBoard[i][17]->addAdj(this->testBoard[i + 1][17]);
        this->testBoard[i][18]->addAdj(this->testBoard[i + 1][18]);
        this->testBoard[i][17]->addAdj(this->testBoard[i][18]);
    }

    this->testBoard[0][18]->addAdj(this->testBoard[1][18]);
    this->testBoard[5][19]->addAdj(this->testBoard[6][19]);
    this->testBoard[5][20]->addAdj(this->testBoard[6][20]);
    this->testBoard[5][18]->addAdj(this->testBoard[5][19]);
    this->testBoard[6][18]->addAdj(this->testBoard[6][19]);
    this->testBoard[5][19]->addAdj(this->testBoard[5][20]);
    this->testBoard[6][19]->addAdj(this->testBoard[6][20]);
    this->testBoard[6][19]->addAdj(this->testBoard[6][20]);
    this->testBoard[6][20]->addAdj(this->testBoard[6][21]);
    this->testBoard[6][22]->addAdj(this->testBoard[6][21]);

    for (int i = 19; i < 23; i++)
    {
        this->testBoard[6][i]->addAdj(this->testBoard[7][i]);
        this->testBoard[17][i]->addAdj(this->testBoard[18][i]);
    }

    this->testBoard[7][23]->addAdj(this->testBoard[8][23]);
    this->testBoard[8][23]->addAdj(this->testBoard[9][23]);
    this->testBoard[9][23]->addAdj(this->testBoard[9][24]);

    for (int i = 7; i < 18; i++)
    {
        this->testBoard[8][i]->addAdj(this->testBoard[9][i]);
    }

    for (int i = 9; i < 23; i++)
    {
        this->testBoard[i][7]->addAdj(this->testBoard[i + 1][7]);
        this->testBoard[i][8]->addAdj(this->testBoard[i + 1][8]);
        this->testBoard[i][7]->addAdj(this->testBoard[i][8]);
    }

    this->testBoard[23][7]->addAdj(this->testBoard[23][8]);
    this->testBoard[17][0]->addAdj(this->testBoard[17][1]);

    for (int i = 17; i < 23; i++)
    {
        this->testBoard[i][6]->addAdj(this->testBoard[i + 1][6]);
    }
    for (int i = 18; i < 24; i++)
    {
        this->testBoard[i][6]->addAdj(this->testBoard[i][7]);
    }
    this->testBoard[23][7]->addAdj(this->testBoard[24][7]);

    for (int i = 8; i < 17; i++)
    {
        this->testBoard[9][i]->addAdj(this->testBoard[9][i + 1]);
    }

    for (int i = 9; i < 23; i++)
    {
        this->testBoard[i][16]->addAdj(this->testBoard[i + 1][16]);
        this->testBoard[i][17]->addAdj(this->testBoard[i + 1][17]);
        this->testBoard[i][16]->addAdj(this->testBoard[i][17]);
    }
    this->testBoard[23][17]->addAdj(this->testBoard[24][17]);
    this->testBoard[23][16]->addAdj(this->testBoard[23][17]);

    for (int i = 8; i < 16; i++)
    {
        this->testBoard[15][i]->addAdj(this->testBoard[15][i + 1]);
        this->testBoard[16][i]->addAdj(this->testBoard[16][i + 1]);
        this->testBoard[15][i]->addAdj(this->testBoard[16][i]);
    }

    for (int i = 16; i < 19; i++)
    {
        this->testBoard[i][15]->addAdj(this->testBoard[i + 1][15]);
        this->testBoard[i][15]->addAdj(this->testBoard[i][16]);
    }
    this->testBoard[19][15]->addAdj(this->testBoard[19][16]);
    this->testBoard[17][18]->addAdj(this->testBoard[18][18]);

    for (int i = 17; i < 22; i++)
    {
        this->testBoard[17][i]->addAdj(this->testBoard[17][i + 1]);
        this->testBoard[18][i]->addAdj(this->testBoard[18][i + 1]);
    }

    this->testBoard[15][23]->addAdj(this->testBoard[16][23]);
    this->testBoard[16][23]->addAdj(this->testBoard[17][23]);
    this->testBoard[15][23]->addAdj(this->testBoard[15][24]);
    this->testBoard[17][23]->addAdj(this->testBoard[17][22]);

    // players put into their starting spaces!
    this->testBoard[17][0]->playersHere.push_back(Miss_Scarlett);
    this->testBoard[24][7]->playersHere.push_back(Colonel_Mustard);
    this->testBoard[0][6]->playersHere.push_back(Professor_Plum);
    this->testBoard[0][18]->playersHere.push_back(Mrs_Peacock);
    this->testBoard[9][24]->playersHere.push_back(Mr_Green);
    this->testBoard[15][24]->playersHere.push_back(Mrs_White);

    cout << "Board has been created & characters at their starting locations" << endl;

    return;
}


int gameBoard::rollDice()
{
    vector<int> Die1 = {1, 2, 3, 4, 5, 6};
    vector<int> Die2 = {1, 2, 3, 4, 5, 6};
    int Die1Result; 
    int Die2Result; 

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(Die1.begin(), Die1.end(), default_random_engine(seed));
    std::shuffle(Die2.begin(), Die2.end(), default_random_engine(seed));
    Die1Result = Die1[Die1.size() - 1];
    Die2Result = Die2[Die2.size() - 1];
    return (Die1Result + Die2Result);
}

void gameBoard::printBoard()
{
    std::cout << WHITE;
    std::cout << "    ";
    for (char x = 'A'; x <= 'Y'; x++)
    {
        std::cout << x << " ";
    }
    std::cout << endl;
    for (int x = 0; x < 53; x++)
    {
        std::cout << "-";
    }
    std::cout << endl;
    for (int x = 0; x < 25; x++)
    {
        if (x < 10)
            std::cout << " ";
        std::cout << x << "| ";
        for (int y = 0; y < 25; y++)
        {
            std::cout << WHITE;
            boardNode *tempNode = this->testBoard[y][x];
            if (tempNode == nullptr)
            {
                std::cout << "  ";
                continue;
            }
            switch (tempNode->spaceLocation)
            {
            case STUDY:
                std::cout << BLUE << "S";
                break;
            case HALL:
                std::cout << BLUE << "H";
                break;
            case LOUNGE:
                std::cout << BLUE << "N";
                break;
            case LIBRARY:
                std::cout << BLUE << "L";
                break;
            case DINING_ROOM:
                std::cout << BLUE << "D";
                break;
            case BILLIARD_ROOM:
                std::cout << BLUE << "I";
                break;
            case CONSERVATORY:
                std::cout << BLUE << "C";
                break;
            case BALLROOM:
                std::cout << BLUE << "B";
                break;
            case KITCHEN:
                std::cout << BLUE << "K";
                break;
            case NOT_ROOM:
                if (tempNode->playersHere.size() != 0)
                {
                    cout << YELLOW << tempNode->playersHere[0] + 1 << WHITE;
                }
                else
                {
                    std::cout << "O";
                }

                break;
            default:
                break;
            }
            std::cout << " ";
        }
        std::cout << endl;
        
    }
    std::cout << "Character Legend:\n" << "1: Miss Scarlett   2: Mr. Green   3: Colonel Mustard" << std::endl;
    std::cout << "4: Professor Plum   5: Mrs. Peacock   6: Mrs. White" << std::endl; 
    std::cout << std::endl;
    std::cout << "Room Legend:\n" << "S: Study   H: Hall   N: Lounge" << std::endl;
    std::cout << "L: Library   D: Dining Room   I: Billiard Room" << std::endl; 
    std::cout << "C: Conservatory   B: BallRoom   K: Kitchen" << std::endl; 
}

// moves player to desired location using breadth first search to find shortest distance

bool gameBoard::movement(int xCord, int yCord, int maxDistance, player *player)
{

    while (true)
    {
        
        boardNode *destination = this->testBoard[xCord][yCord];
        if(destination == nullptr)
        {
            printf("this is not a possible loction to move to, input another location:\n");
            return false;
        }
        boardNode *start = this->testBoard[player->xLocation][player->yLocation];
        boardNode *currLocation = this->testBoard[player->xLocation][player->yLocation];
        if (destination == currLocation)
        {
            cout << "You are already here" << endl;
            return false;
        }
        if (destination->adjSpaces.empty())
        {
            printf("this is not a possible loction to move to, input another location:\n");
            return false;
        }
        set<boardNode *> visited;
        vector<list<boardNode *>> queueLevel;
        queueLevel.resize(maxDistance);

        visited.insert(currLocation);
        queueLevel[0].push_back(currLocation);


        for (int i = 0; i < maxDistance; i++) // this allows the BFS to only look a certain distance away
        {

            while (!queueLevel[i].empty())
            {
                currLocation = queueLevel[i].front();
                queueLevel[i].pop_front();

                for (auto adj : currLocation->adjSpaces)
                {
                    if (!adj->isEmpty() && adj->spaceLocation == NOT_ROOM)
                    {
                        visited.insert(adj);
                        continue;
                    }
                    else if (adj == destination) // checks if the current node is the de
                    {
                        destination->addPlayer(player->playerNumber);
                        start->removePlayer(player->playerNumber);
                        player->xLocation = xCord;
                        player->yLocation = yCord;
                        cout << "you made it to your destination" << endl;
                        return true;
                    }

                    if (visited.find(adj) == visited.end() && !(i == maxDistance - 1))
                    {
                        visited.insert(adj);
                        queueLevel[i + 1].push_back(adj); // puts the next nodes to be searched in the next levels queue
                    }
                }
            }
        }

        cout << "node too far away, try a different location" << endl;
        return false;
    }
}

