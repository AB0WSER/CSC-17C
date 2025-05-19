/* 
 * File:   main.cpp
 * Author: Andrew Bowser
 * Created on November , 2024 at 1:03 PM
 *Purpose: CardClass.cpp
 */

//System libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "Deck.h"
#include <algorithm>
#include <ctime>


// Constructor to initialize the deck
Deck::Deck() : top(0) {
    srand(static_cast<unsigned>(time(0)));//for rand function
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    int index = 0;
    for (const string& suit : suits) {
        for (int i = 0; i < 13; ++i) {
            cards[index++] = Card(suit, ranks[i], values[i]);
        }
    }
}

// Function to shuffle the deck
void Deck::shuffle() {
    // If we're low on cards, reshuffle discard pile first
    if ((SIZE - top) < 10 && !discardPile.empty()) {
        reshuffle();
        return;
    }

    // Fisher-Yates shuffle algorithm
    for (int i = SIZE - 1; i > top; --i) {
        // Generate random index between top and i
        int j = top + rand() % (i - top + 1);
        
        // Swap cards[i] and cards[j]
        Card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

// Function to deal a card from the deck
Card Deck::deal() {
    if (top < SIZE) {
        Card c = cards[top++];
        string cardID = c.getRank() + " of " + c.getSuit();

        if (dealtCards.find(cardID) != dealtCards.end()) {
            throw logic_error("Duplicate card dealt!"); // Optional: for error checking
        }

        dealtCards.insert(cardID);
        return c;
    } else {
        throw out_of_range("No cards left in the deck");
    }
}
void Deck::discard(const Card& card) {
    // Remove from dealtCards set first
    string cardID = card.getRank() + " of " + card.getSuit();
    dealtCards.erase(cardID);
    
    // Add to discard pile
    discardPile.push(card);
}

void Deck::reshuffle() {
    // Only reshuffle if we have cards in discard pile
    if (discardPile.empty()) return;
    
    cout << "Reshuffling " << discardPile.size() << " cards from discard pile..." << endl;
    
    // Move cards from discard pile back to main deck
    while (!discardPile.empty()) {
        if (top > 0) {
            cards[--top] = discardPile.top(); // Add to bottom of deck
        }
        discardPile.pop();
    }
    
    // Shuffle the deck
    shuffle();
}

int Deck::discardPileSize() const {
    return discardPile.size();
}
// Destructor
Deck::~Deck() {
    // No dynamic memory used, so no special cleanup required
}