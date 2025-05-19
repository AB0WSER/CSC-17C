/* 
 * File:   BlackJack.h
 * Author: Andrew
 *
 * Created on December , 2024, 1:15 PM
 */

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Deck.h"
#include "PlayerClass.h"
#include "Record.h"
#include <map>

class BlackJack {
protected:
    map<string, int> cardCountTracker; // Tracks cards seen for counting strategy
    int runningCount;
    Deck deck;              // Deck of cards used in the game
    Player<int> player;     // Player participating in the game
    Player<int> dealer;     // Dealer participating in the game
    GameRecord record;      // Game record for tracking stats

public:
    // Constructor to initialize the game
    BlackJack(const string& playerName, float initialMoney);

    // Function to play the game
    void play();

    // Overloaded operator to display the game stats
    friend ostream& operator<<(ostream& os, const BlackJack& game);
    
    void updateCardCount(const Card& card);  // Update count when card is dealt
    void displayCountAdvice() const;         // Show betting advice
   
    // Destructor
    ~BlackJack();
};


#endif /* BLACKJACK_H */

