/* 
 * File:   Record.h
 * Author: Andrew Bowser
 *
 * Created on November 1, 2024, 2:10 PM
 */

#ifndef RECORD_H
#define RECORD_H

class GameRecord {
public:
    int gamesPlayed;   // Number of games played
    int gamesWon;      
    // Default constructor
    GameRecord();

    // Function to update the record for a win
    void recordWin();

    // Function to display the game record
    void display() const;

    // Destructor
    ~GameRecord();

    // Friend class declaration
    friend class BlackJack;
};


#endif /* RECORD_H */

