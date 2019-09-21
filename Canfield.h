/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     canfield.h
  Last updated:  September 2018
  Description:   Implementation of the card game of Canfield using 
                 stacks and queues.
**********************************************************************/

#ifndef CANFIELD_H
#define CANFIELD_H

#include "Queue.h"
#include "Stack.h"

const int NUM_CARDS = 52, NUM_SUITS = 4, NUM_RANKS = 13;

class Canfield 
{
private:

    Queue deck;
    Stack reserve;
    Stack foundation[NUM_SUITS], 
          tableau[NUM_SUITS];
    int   waste, score=0;
    bool  quit;
    char  from, 
          to;
    int   fromId, 
          toId;

public:
    // Default constructor
    Canfield();

    // Destructor
    ~Canfield();

    // The main loop of the game.
    void play();

private:

    // Empty all the data structures
    void emptyAll();

    // Starting a new game. It must reset all the data structures,
    // generate a new set of 52 random cards and place them in the
    // appropriate places in the game.
    void newGame();

    // creates a new pack of cards and shuffles them
    void newShuffledPack(int *newDeck);

    // Prints the choices of actions for the player.
    void printMenu();

    // Performs an action based on the user's choice.
    void performAction(char answer);

    // Displays the entire content of the game.
    void printGame();

    // Deals one card from the deck.
    void deal();

    // Performs one move.
    void move();

    //Repeats the same move one more time.
    void repeatMove();

    // Determines what card is to be moved. Accessor method.
    int getCard();

    // Checks if the requested movement is possible. Accessor method.
    bool checkMove(int card);

    // Removes the card to be moved. Mutator method.
    void removeCard();

    // Adds the card or the entire tableau to its new destination. 
    // Mutator method.
    void addCard(int card);

    // Checking for an empty tableau, move reserve card to tableau.
    void checkTableau();

    // Called when score == NUM_CARDS.
    void  wonGame();
};

#endif
