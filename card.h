// card.h
// Author: Your name
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
#include <ostream>

class Card {

public:
    char suit;
    std::string rank;

    Card() = default;
    Card(char s, const std::string &r) : suit(s), rank(r) {}

    bool operator<(const Card &other) const;
    bool operator==(const Card &other)const;
    bool operator!=(const Card &other) const;

};

std::ostream& operator<<(std::ostream &os, const Card &c);

#endif
