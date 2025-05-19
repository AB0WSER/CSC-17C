/* 
 * File:   main.cpp
 * Author: Andrew Bowser
 * Created on November , 2024 at 1:03 PM
 *Purpose: CardClass.cpp
 */

using namespace std;
#include <iostream>
#include "BlackJack.h"

// Constructor to initialize the game
BlackJack::BlackJack(const string& playerName, float initialMoney) 
    : player(playerName, initialMoney), dealer("Dealer", 0), runningCount(0) {
    deck.shuffle();
    
    // Initialize card values in our tracker
    string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    for (const auto& rank : ranks) {
        cardCountTracker[rank] = 0;
    }

}


// Function to play the game
void BlackJack::play() {
    float bet;
    cout << "Enter your bet amount: ";
    cin >> bet;

    // Validate bet
    if (bet <= 0 || bet > player.getMoney()) {
        cout << "Invalid bet amount." << endl;
        return;
    }
    
    // Deal initial cards and update count
    Card card1 = deck.deal();
    player.addCard(card1);
    updateCardCount(card1);
    
    Card card2 = deck.deal();
    dealer.addCard(card2);
    updateCardCount(card2);
    
    Card card3 = deck.deal();
    player.addCard(card3);
    updateCardCount(card3);
    
    Card card4 = deck.deal();
    player.addCard(card4);
    updateCardCount(card4);

    player.showHand();
    cout << "Your score: " << player.calculateScore() << endl;
    displayCountAdvice();

    // Check for splitting pairs
    char splitChoice;
    if (player.isPair()) {
        cout << "You have a pair! Do you want to split? (Y/N): ";
        cin >> splitChoice;
        if (toupper(splitChoice) == 'Y') {
            Card secondCard = player.splitHand();
            Player<int> secondHand(player);
            secondHand.addCard(deck.deal());
            player.addCard(deck.deal());

            cout << "First hand:" << endl;
            player.showHand();
            cout << "Score: " << player.calculateScore() << endl;

            cout << "Second hand:" << endl;
            secondHand.showHand();
            cout << "Score: " << secondHand.calculateScore() << endl;
        }
    }

    // Check for doubling down
    char doubleDownChoice;
    cout << "Do you want to double down? (Y/N): ";
    cin >> doubleDownChoice;
    if (toupper(doubleDownChoice) == 'Y') {
        bet *= 2;
        player.addCard(deck.deal());
        cout << "You doubled down and received one card." << endl;
        player.showHand();
        cout << "Your score: " << player.calculateScore() << endl;
    }

    // Dealer logic
    while (dealer.calculateScore() < 17) {
        dealer.addCard(deck.deal());
    }

    // Show dealer's hand
    dealer.showHand();
    cout << "Dealer's score: " << dealer.calculateScore() << endl;

    // Determine winner
    int playerScore = player.calculateScore();
    int dealerScore = dealer.calculateScore();

    if (playerScore > 21) {
        cout << "You busted! Dealer wins!" << endl;
        player.updateMoney(-bet);
    } else if (dealerScore > 21 || playerScore > dealerScore) {
        cout << "You win!" << endl;
        player.updateMoney(bet);
        record.recordWin();
    } else if (playerScore == dealerScore) {
        cout << "It's a tie! No money won or lost." << endl;
    } else {
        cout << "Dealer wins!" << endl;
        player.updateMoney(-bet);
        }
    // When a hand ends, discard all cards
    auto discardHand = [this](Player<int>& p) {
        while (!p.hand.empty()) {
            Card c = p.hand.front();
            deck.discard(c);
            p.hand.pop_front();
        }
    };
    // At end of hand:
    discardHand(player);
    discardHand(dealer);
    
    // Display current money balance
    cout << "Your current balance: $" << player.getMoney() << endl;

    char countChoice;
    cout << "\nWould you like to see the current card count? (Y/N): ";
    cin >> countChoice;
    if (toupper(countChoice) == 'Y') {
        displayCountAdvice();
    }
    // Show discard pile status
    cout << "Cards in discard pile: " << deck.discardPileSize() << endl;
    if (deck.discardPileSize() > 0) {
    char reshuffleChoice;
    cout << "Would you like to reshuffle the discard pile into the deck? (Y/N): ";
    cin >> reshuffleChoice;
    if (toupper(reshuffleChoice) == 'Y') {
        deck.reshuffle();
        cout << "Deck has been reshuffled. " << deck.getRemainingCards() << " cards now available." << endl;
    }
}

    // Check if the player wants to play another hand
    char playAgain;
    cout << "Do you want to play another hand? (Y/N): ";
    cin >> playAgain;

    if (toupper(playAgain) == 'Y') {
        player.resetHand();
        dealer.resetHand();
        play(); // Recursively call the play function for another hand
    } else {
        cout << "Thank you for playing Blackjack!" << endl;
        record.display();
    }
}


// Update the count when a card is dealt
void BlackJack::updateCardCount(const Card& card) { 
    string rank = card.getRank();
    
    // Hi-Lo counting system values:
    if (rank == "2" || rank == "3" || rank == "4" || rank == "5" || rank == "6") {
        runningCount += 1;
        cardCountTracker[rank]++;
    }
    else if (rank == "10" || rank == "Jack" || rank == "Queen" || rank == "King" || rank == "Ace") {
        runningCount -= 1;
        cardCountTracker[rank]++;
    }
    // 7,8,9 are neutral (0)
}

// Display current count and betting advice
void BlackJack::displayCountAdvice() const {
    // Calculate true count (for shoe games)
    int remainingDecks = (deck.getRemainingCards() + 51) / 52; // Round up
    int trueCount = remainingDecks > 0 ? runningCount / remainingDecks : runningCount;
    
    cout << "\nCard Counting Info:" << endl;
    cout << "-------------------" << endl;
    cout << "Running count: " << runningCount << endl;
    if (remainingDecks > 1) {
        cout << "True count: " << trueCount << " (approx " << remainingDecks << " decks remaining)" << endl;
    }
    
    // Betting advice based on true count
    cout << "Betting advice: ";
    if (trueCount >= 3) {
        cout << "Count is favorable - consider increasing your bet!";
    } else if (trueCount <= -3) {
        cout << "Count is unfavorable - consider betting minimum.";
    } else {
        cout << "Count is neutral - standard betting strategy.";
    }
    cout << endl;
    
    // Optional: Show card distribution
    cout << "\nCards seen so far:" << endl;
    for (const auto& pair : cardCountTracker) {
        if (pair.second > 0) {
            cout << pair.first << ": " << pair.second << " ";
        }
    }
    cout << endl;
}

// Overloaded operator to display the game stats
ostream& operator<<(ostream& os, const BlackJack& game) {
    os << "Player: " << game.player.getMoney() << " | Games Played: " << game.record.gamesPlayed
       << " | Games Won: " << game.record.gamesWon;
    return os;
}

// Destructor
BlackJack::~BlackJack() {
    // Cleanup handled automatically
}