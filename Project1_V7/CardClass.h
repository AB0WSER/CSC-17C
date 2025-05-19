/* 
 * File:   CardClass.h
 * Author: Andrew
 *
 * Created on November , 2024, 2:53 PM
 */


#ifndef CARDCLASS_H
#define CARDCLASS_H


#include <string>
using namespace std;

class Card {
protected:
    string suit;
    string rank;
    int value;

public:
    Card();
    Card(const string& s, const string& r, int v);
    string getSuit() const;
    string getRank() const;
    int getValue() const;
};

#endif /* CARDCLASS_H */

