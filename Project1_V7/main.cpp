/* 
 * File:   main.cpp
 * Author: Andrew Bowser
 * Created on November 27, 2024 at 1:03 PM
 *Purpose: Project 2 V4
 */

//System libraries
#include <iostream>

using namespace std;

// User libraries
#include "BlackJack.h" 
//Global Constants only
//Conversions/Math/Physics Constants like PI/Speed of Light, etc...

//Function Prototypes 

//Execution Begins Here

int main(int argc, char** argv) {
   string playerName;
    float initialMoney;

    cout << "Welcome to Blackjack!" << endl;
    cout << "Enter your name: ";
    cin >> playerName;
    cout << "Enter the amount of money you want to start with: $";
    cin >> initialMoney;

    // Start the Blackjack game
    BlackJack game(playerName, initialMoney);
    game.play();

    // Display final stats
    cout << "Final stats: " << endl;
    cout << game << endl;

    return 0;
}