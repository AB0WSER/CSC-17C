/* 
 * File:   main.cpp
 * Author: Andrew Bowser
 * Created on November , 2024 at 1:03 PM
 *Purpose: CardClass.cpp
 */

//System libraries

using namespace std;

#include "Record.h"
#include <iostream>
using namespace std;

// Default constructor
GameRecord::GameRecord() : gamesPlayed(0), gamesWon(0) {}

// Function to update the record for a win
void GameRecord::recordWin() {
    ++gamesPlayed;
    ++gamesWon;
}

// Function to display the game record
void GameRecord::display() const {
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
}

// Destructor
GameRecord::~GameRecord() {}