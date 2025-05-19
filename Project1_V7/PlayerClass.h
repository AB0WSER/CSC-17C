/* 
 * File:   PlayerClass.h
 * Author: Andrew
 *
 * Created on December 15, 2024, 1:11 PM
 */

#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include <list>
#include <stdexcept>
#include <algorithm> // for count_if, find_if, min_element
#include <iostream>    // for cout in showHand
#include "CardClass.h"

using namespace std;

template <typename T>
class Player {
protected:
    string name;         // Name of the player
    T score;             // Player's score (templated for flexibility)
    float money;         // Player's money balance

public:
    list<Card> hand;   // Cards held by the player
    // Constructor to initialize player with a name
    Player(const string& name, float initialMoney) 
        : name(name), score(0), money(initialMoney) {}

    // Function to add a card to the player's hand
    void addCard(const Card& card) {
        hand.push_back(card);
    }

    // Function to calculate the player's score
    T calculateScore() const {
        T total = 0;

        // Use count_if to count Aces
        int aces = count_if(hand.begin(), hand.end(), [](const Card& card) {
            return card.getRank() == "Ace";
        });

        for (const Card& card : hand) {
            total += card.getValue();
        }

        while (total > 21 && aces-- > 0) total -= 10;
        return total;
    }

    void showHand() const {
    // Show current hand
    cout << name << "'s hand:" << endl;
    for (const Card& card : hand) {
        cout << card.getRank() << " of " << card.getSuit() << endl;
    }

    // 🔍 find_if: Checks for any Ace in the hand
    auto it = find_if(hand.begin(), hand.end(), [](const Card& card) {
        return card.getRank() == "Ace";
    });
    if (it != hand.end()) {
        cout << "Your hand contains at least one Ace!" << endl;
    }

    // 🪙 min_element: Finds the lowest value card
    auto minIt = min_element(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
        return a.getValue() < b.getValue();
    });
    if (minIt != hand.end()) {
        cout << "Lowest card in your hand: " << minIt->getRank() << " of " << minIt->getSuit() << endl;
    }

    //Copies the list of cards to a new list
    list<Card> copiedHand;
    copy(hand.begin(), hand.end(), back_inserter(copiedHand));

    //Swaps copied hand with a temp hand 
    list<Card> tempHand = hand;
    swap(tempHand, copiedHand);

    //Sorts the copied hand (requires random access, so we use vector)
    vector<Card> sortedVec(copiedHand.begin(), copiedHand.end());
    sort(sortedVec.begin(), sortedVec.end(), [](const Card& a, const Card& b) {
        return a.getValue() < b.getValue();
    });

    cout << "\nSorted hand (by card value):" << endl;
    for (const Card& card : sortedVec) {
        cout << card.getRank() << " of " << card.getSuit() << " (" << card.getValue() << ")" << endl;
    }
}
    

    // Function to update money balance
    void updateMoney(float amount) {
        money += amount;
    }

    // Function to get current money balance
    float getMoney() const {
        return money;
    }

    // Function to reset the player's hand
    void resetHand() {
        hand.clear();
        score = 0;
    }

    // Check if the hand is a pair
    bool isPair() const {
         if (hand.size() != 2) return false;

        auto it = hand.begin();
        string firstRank = it->getRank();
        ++it;
        string secondRank = it->getRank();

        return firstRank == secondRank;
    }

    // Function to split the hand (returns the second card)
    Card splitHand() {
        if (isPair()) {
            auto it = hand.begin();
            advance(it, 1);                 // Move iterator to second card
            Card secondCard = *it;
            hand.erase(it);                 // Erase the second card
            return secondCard;
        } else {
            throw logic_error("Cannot split a non-pair hand");
        }
    }

    // Destructor
    ~Player() {}
};
#endif /* PLAYERCLASS_H */

