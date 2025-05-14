// card.cpp
// Author: Amol Bhat 
// Implementation of the classes defined in card.h

#include "card.h"
#include <map>

static int rankValue(const std::string &r) {
    if (r == "a") return 1;
    if (r == "j") return 11;
    if (r == "q") return 12;
    if (r == "k") return 13;
    return std::stoi(r);  
}

static int suitValue(char s) {
    switch (s) {
        case 'c': return 0;
        case 'd': return 1;
        case 's': return 2;
        case 'h': return 3;
    }
    return -1; 
}

bool Card::operator<(const Card &other) const {
    int sv = suitValue(suit);
    int osv = suitValue(other.suit);
    if (sv != osv) return sv < osv;
    return rankValue(rank) < rankValue(other.rank);
}

std::ostream& operator<<(std::ostream &os, const Card &c) {
    os << c.suit << ' ' << c.rank;
    return os;
}

bool Card::operator==(const Card &other) const {
    return suit == other.suit && rank == other.rank;
}

bool Card::operator!=(const Card &other) const {
    return !(*this == other);
}
