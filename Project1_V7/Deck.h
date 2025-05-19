
/* 
 * File:   Deck.h
 * Author: Andrew
 *
 * Created on November 3, 2024, 1:10 PM
 */


#include "CardClass.h"
#include <stack>
#include <set>

#ifndef DECK_H
#define DECK_H


class Deck : public Card {
protected:
    static const int SIZE = 52;// Total number of cards in a deck
    Card cards[SIZE];          // Array to hold all cards
    int top;                   // Index of the top card in the deck
    set<string> dealtCards;    // To track unique card strings
    stack<Card> discardPile;

public:
    // Constructor to initialize the deck
    Deck();

    // Function to shuffle the deck
    void shuffle();

    // Function to deal a card from the deck
    Card deal();
    // Used for map with card counting
    int getRemainingCards() const { return SIZE - top; }
    void discard(const Card& card);
    void reshuffle(); // Combine discard pile back into deck
    int discardPileSize() const;  // Declaration
    // Destructor
    ~Deck();
};
#endif /* DECK_H */

