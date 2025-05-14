// card_list.h
// Author: Amol Bhat
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <iterator>

namespace bst {

class BST {
public:
    struct Node {
        Card data;
        Node *left, *right, *parent;
        Node(const Card &c, Node* p = nullptr): data(c), left(nullptr), right(nullptr), parent(p) {}
    };

    Node* findNode(const Card& c) const;
    Node* getSuccessor(Node* n) const;
    Node* getPredecessor(Node* n) const;

    BST();
    ~BST();

    void insert(const Card& c);
    bool contains(const Card& c) const;
    void remove(const Card& c);
    int  count(const Card& c) const;
    void printDeck() const;

    class Iterator {
    public:
        using value_type        = Card;
        using reference         = const Card&;
        using pointer           = const Card*;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator(Node* n = nullptr);
        Iterator& operator++();    // successor
        Iterator& operator--();    // predecessor
        reference operator*() const;
        pointer   operator->() const;
        bool      operator==(const Iterator&) const;
        bool      operator!=(const Iterator&) const;

    private:
        Node* current;
    };

    Iterator begin()  const;
    Iterator end()    const;
    Iterator rbegin() const;
    Iterator rend()   const;

private:
    Node* root;
    void  destroy(Node* n);
};

void playGame(BST& alice, BST& bob);

} 

#endif 
