# Canfield
 A simplified C++ console version of the game Canfield.
 
 This repository contains several container files (list, list iterator, stack, queue) as well as files to play the game Canfield.  Compiling in linux after download: 'make' and then ./canfield to play.    
 
 
 
 Canfield (simplified)
 
Setup:
Type of Deck	= Standard 52 card Deck
Deck is the top left pile.
Reserve	located directly under Deck. Thirteen cards here with top card face up. Top card available for play to Foundations or Tableau.
Tableau	Four piles to the right of Foundations (T0 T1 T2 T3). One card is dealt face up on to each pile. Tableaus are built down from 13 to 1.  You can move an entire Tableau to another Tableau or move the cards from Tableau, one by one, to a Foundation.  These prompts are provided for the player.

Foundations	are the four piles on the left (F0 F1 F2 F3). These are empty and player must move a '1' from either a Tableau, Deck, or Reserve and build up to 13 from there.  

Goal:  Move all cards to the Foundation piles.

Rules:

Cards in the Tableau are built in descending order (13 to 1).  An empty slot in the Tableau is filled automatically from the Reserve. If the Reserve is empty, an empty slot can be filled by any card or group of cards in sequence.

Deck can be redealt as many times needed until player wins or quits/exits the game.

Foundations are built up in ascending order (1-13).  Cards can be moved from Deck, Reserve, or a Tableau one at a time.  

Each card in the Foundation piles scores one point.  

A score of 52 wins the game.  This will give the player the option of choosing to play again or quit and exit the game.
