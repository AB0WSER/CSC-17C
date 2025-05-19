/* 
 * File:   main.cpp
 * Author: Andrew Bowser
 * Created on November , 2024 at 1:03 PM
 *Purpose: CardClass.cpp
 */


using namespace std;


#include "CardClass.h"
#include <iostream>

Card::Card() : suit(""), rank(""), value(0) {}
Card::Card(const string& s, const string& r, int v) : suit(s), rank(r), value(v) {}
string Card::getSuit() const { return suit; }
string Card::getRank() const { return rank; }
int Card::getValue() const { return value; }
