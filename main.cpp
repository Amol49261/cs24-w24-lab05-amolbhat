// Feb 14: This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "card.h"
#include "card_list.h"

using namespace std;
using bst::BST;
using bst::playGame;

int main(int argv, char** argc) {
    if (argv < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argc[1]);
    ifstream cardFile2(argc[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file " << argc[2];
        return 1;
    }

    BST alice, bob;
    char suit;
    string rank;

    while (getline(cardFile1, line) && (line.length() > 0)) {
        istringstream iss(line);
        iss >> suit >> rank;
        alice.insert(Card(suit, rank));
    }
    cardFile1.close();

    while (getline(cardFile2, line) && (line.length() > 0)) {
        istringstream iss(line);
        iss >> suit >> rank;
        bob.insert(Card(suit, rank));
    }
    cardFile2.close();

    playGame(alice, bob);

    return 0;
}
