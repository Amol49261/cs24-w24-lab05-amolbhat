// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>       
#include "card.h"

using namespace std;

int main(int argv, char** argc){
    if (argv < 3){
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argc[1]);
    ifstream cardFile2(argc[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail() ){
        cout << "Could not open file " << argc[2];
        return 1;
    }

    set<Card> alice, bob;
    char suit;
    string rank;

    while (getline(cardFile1, line) && (line.length() > 0)) {
        istringstream iss(line);
        iss >> suit >> rank;
        alice.emplace(suit, rank);
    }
    cardFile1.close();

    while (getline(cardFile2, line) && (line.length() > 0)) {
        istringstream iss(line);
        iss >> suit >> rank;
        bob.emplace(suit, rank);
    }
    cardFile2.close();

    bool turnAlice = true;
    while (true){
        bool foundMatch = false;

        if (turnAlice){
            for (auto it = alice.begin(); it != alice.end(); ++it){
                if (bob.count(*it)){
                    cout << "Alice picked matching card " << *it << '\n';
                    bob.erase(*it);
                    alice.erase(it);
                    foundMatch = true;
                    break;
                }
            }
        } else {
            for (auto rit = bob.rbegin(); rit != bob.rend(); ++rit){
                if (alice.count(*rit)){
                    cout << "Bob picked matching card " << *rit << '\n';
                    alice.erase(*rit);
                    auto lit = next(rit).base();  
                    bob.erase(lit);
                    foundMatch = true;
                    break;
                }
            }
        }

        if (!foundMatch)
            break;   // no more matches so end the game 

        turnAlice = !turnAlice;
    }

    //Any remianing cards are being signaled to print here 
    cout << "\nAlice's cards:\n";
    for (auto &c : alice) cout << c << '\n';

    cout << "\nBob's cards:\n";
    for (auto &c : bob)   cout << c << '\n';

    return 0;
}
