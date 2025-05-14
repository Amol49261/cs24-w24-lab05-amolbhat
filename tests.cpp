
#include "card_list.h"
#include "card.h"
#include <cassert>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

using bst::BST;
using bst::playGame;

// Helper to capture printDeck output into a string for accurate testing later 
static std::string capturePrintDeck(BST &t) {
    std::ostringstream oss;
    auto old = std::cout.rdbuf(oss.rdbuf());
    t.printDeck();
    std::cout.rdbuf(old);
    return oss.str();
}

int main() {
    {
        BST t;
        assert(!t.contains(Card('c', "5")));
        assert(t.count(Card('c', "5")) == 0);
        
        t.insert(Card('c', "5"));
        assert(t.contains(Card('c', "5")));
        assert(t.count(Card('c', "5")) == 1);
        
        t.insert(Card('c', "5"));
        assert(t.count(Card('c', "5")) == 1);
        
        t.insert(Card('d', "1"));
        t.insert(Card('h', "10"));
        assert(t.contains(Card('d', "1")) && t.contains(Card('h', "10")));
        
        t.insert(Card('c', "a"));
        assert(t.contains(Card('c', "a")));
    }

    {
        BST t;
        t.remove(Card('c', "5"));
        assert(!t.contains(Card('c', "5")));
        
        t.insert(Card('d', "2"));
        t.remove(Card('d', "2"));
        assert(!t.contains(Card('d', "2")));
        
        t.insert(Card('h', "3"));
        t.remove(Card('d', "4"));
        assert(t.contains(Card('h', "3")));
        
        t = BST();
        t.insert(Card('c', "3"));
        t.insert(Card('a', "1"));
        t.insert(Card('e', "5"));
        t.remove(Card('c', "3"));
        assert(!t.contains(Card('c', "3")));
        
        t.remove(Card('a', "1"));
        assert(!t.contains(Card('a', "1")));
    }

    {
        BST t;
        std::vector<Card> seq = {{'c',"2"},{'c',"4"},{'c',"6"},{'c',"8"}};
        for (auto &c : seq) t.insert(c);
        
        auto n0 = t.findNode(Card('c', "2"));
        auto s0 = t.getSuccessor(n0);
        assert(s0 && s0->data == Card('c', "4"));
        
        auto n2 = t.findNode(Card('c', "6"));
        auto s2 = t.getSuccessor(n2);
        assert(s2 && s2->data == Card('c', "8"));
        
        auto p2 = t.getPredecessor(n2);
        assert(p2 && p2->data == Card('c', "4"));
        
        auto p0 = t.getPredecessor(n0);
        assert(p0 == nullptr);
        
        auto nl = t.findNode(Card('c', "8"));
        auto sl = t.getSuccessor(nl);
        assert(sl == nullptr);
    }

    {
        BST t;
        assert(capturePrintDeck(t).empty());
        
        t.insert(Card('d', "7"));
        assert(capturePrintDeck(t) == "d 7\n");
        
        t.insert(Card('c', "3"));
        t.insert(Card('h', "9"));
        {
            auto out = capturePrintDeck(t);
            assert(out.find("c 3\n") != std::string::npos);
            assert(out.find("d 7\n") != std::string::npos);
            assert(out.find("h 9\n") != std::string::npos);
        }
        
        t.remove(Card('d', "7"));
        assert(capturePrintDeck(t).find("d 7") == std::string::npos);
        
        t = BST();
        assert(capturePrintDeck(t).empty());
    }

    // Iterator tests 
    {
        BST t;
        assert(t.begin() == t.end());
        assert(t.rbegin() == t.rend());
        
        t.insert(Card('h',"2"));
        {
            auto it = t.begin();
            assert(*it == Card('h',"2"));
            ++it; assert(it == t.end());
            auto rit = t.rbegin();
            assert(*rit == Card('h',"2"));
            --rit; assert(rit == t.rend());
        }
        
        t.insert(Card('c',"3"));
        t.insert(Card('s',"1"));
        {
            std::vector<Card> v;
            for (auto it = t.begin(); it != t.end(); ++it)
                v.push_back(*it);
            assert((v == std::vector<Card>{Card('c',"3"),Card('s',"1"),Card('h',"2")}));
        }
        
        {
            std::vector<Card> v;
            for (auto it = t.rbegin(); it != t.rend(); --it)
                v.push_back(*it);
            assert((v == std::vector<Card>{Card('h',"2"),Card('s',"1"),Card('c',"3")}));
        }
        
        auto e = t.end(); ++e; assert(e == t.end());
        auto r = t.rend(); --r; assert(r == t.rend());
    }

    // playGame() function tests 
    {
        std::ofstream("x.txt") << "c 2\nh 5\n";
        std::ofstream("y.txt") << "h 5\ns 3\n";
        BST a,b;
        {
            std::ifstream if1("x.txt"), if2("y.txt");
            std::string ln; char s; std::string r;
            while (std::getline(if1,ln) && !ln.empty()) { std::istringstream is(ln); is>>s>>r; a.insert(Card(s,r)); }
            while (std::getline(if2,ln) && !ln.empty()) { std::istringstream is(ln); is>>s>>r; b.insert(Card(s,r)); }
        }
        
        std::ostringstream cap;
        auto old = std::cout.rdbuf(cap.rdbuf());
        playGame(a,b);
        std::cout.rdbuf(old);
        assert(cap.str().find("Alice picked matching card h 5")!=std::string::npos);
        
        BST c,d; c.insert(Card('s',"1")); d.insert(Card('d',"4"));
        cap.str(""); cap.clear(); std::cout.rdbuf(cap.rdbuf());
        playGame(c,d);
        std::cout.rdbuf(old);
        assert(cap.str().find("picked matching")==std::string::npos);
        
        BST e,f; f.insert(Card('c',"7"));
        cap.str(""); cap.clear(); std::cout.rdbuf(cap.rdbuf());
        playGame(e,f);
        std::cout.rdbuf(old);
        assert(cap.str().find("picked matching")==std::string::npos);
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
