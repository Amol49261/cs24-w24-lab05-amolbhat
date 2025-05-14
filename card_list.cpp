// card_list.cpp
// Author: Amol Bhat
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include <iostream>

namespace bst {

BST::BST() : root(nullptr) {}
BST::~BST() { destroy(root); }

void BST::destroy(Node* n) {
    if (!n) return;
    destroy(n->left);
    destroy(n->right);
    delete n;
}

void BST::insert(const Card& c) {
    if (!root) {
        root = new Node(c);
        return;
    }
    Node* cur = root;
    while (true) {
        if (c < cur->data) {
            if (cur->left)
                cur = cur->left;
            else { cur->left = new Node(c, cur); break; }
        } else if (cur->data < c) {
            if (cur->right)
                cur = cur->right;
            else { cur->right = new Node(c, cur); break; }
        } else {
            break;
        }
    }
}

bool BST::contains(const Card& c) const {
    return findNode(c) != nullptr;
}

int BST::count(const Card& c) const {
    return contains(c) ? 1 : 0;
}

BST::Node* BST::findNode(const Card& c) const {
    Node* cur = root;
    while (cur) {
        if (c < cur->data)      cur = cur->left;
        else if (cur->data < c) cur = cur->right;
        else                    return cur;
    }
    return nullptr;
}

BST::Node* BST::getSuccessor(Node* n) const {
    if (!n) return nullptr;
    if (n->right) {
        n = n->right;
        while (n->left) n = n->left;
        return n;
    }
    while (n->parent && n == n->parent->right)
        n = n->parent;
    return n->parent;
}

BST::Node* BST::getPredecessor(Node* n) const {
    if (!n) return nullptr;
    if (n->left) {
        n = n->left;
        while (n->right) n = n->right;
        return n;
    }
    while (n->parent && n == n->parent->left)
        n = n->parent;
    return n->parent;
}

void BST::remove(const Card& c) {
    Node* target = findNode(c);
    if (!target) return;

    auto transplant = [&](Node* u, Node* v) {
        if (!u->parent)
            root = v;
        else if (u == u->parent->left)
            u->parent->left  = v;
        else 
            u->parent->right = v;
        if (v) v->parent = u->parent;
    };

    if (!target->left) {
        transplant(target, target->right);
    } else if (!target->right) {
        transplant(target, target->left);
    } else {
        Node* succ = getSuccessor(target);
        if (succ->parent != target) {
            transplant(succ, succ->right);
            succ->right = target->right;
            succ->right->parent = succ;
        }
        transplant(target, succ);
        succ->left = target->left;
        succ->left->parent = succ;
    }
    delete target;
}

void BST::printDeck() const {
    for (auto it = begin(); it != end(); ++it)
        std::cout << *it << "\n";
}

BST::Iterator BST::begin() const {
    Node* n = root;
    while (n && n->left) n = n->left;
    return Iterator(n);
}
BST::Iterator BST::end()   const { return Iterator(nullptr); }
BST::Iterator BST::rbegin()const {
    Node* n = root;
    while (n && n->right) n = n->right;
    return Iterator(n);
}
BST::Iterator BST::rend()  const { return Iterator(nullptr); }

BST::Iterator::Iterator(Node* n) : current(n) {}

BST::Iterator& BST::Iterator::operator++() {
    // in-order successor
    if (!current) return *this;
    if (current->right) {
        Node* n = current->right;
        while (n->left) n = n->left;
        current = n;
    } else {
        Node* p = current->parent;
        Node* c = current;
        while (p && c == p->right) {
            c = p; p = p->parent;
        }
        current = p;
    }
    return *this;
}

BST::Iterator& BST::Iterator::operator--() {
    // reverse-order predecessor
    if (!current) return *this;
    if (current->left) {
        Node* n = current->left;
        while (n->right) n = n->right;
        current = n;
    } else {
        Node* p = current->parent;
        Node* c = current;
        while (p && c == p->left) {
            c = p; p = p->parent;
        }
        current = p;
    }
    return *this;
}

const Card& BST::Iterator::operator*() const {
    return current->data;
}
const Card* BST::Iterator::operator->() const {
    return &current->data;
}
bool BST::Iterator::operator==(const Iterator& o) const {
    return current == o.current;
}
bool BST::Iterator::operator!=(const Iterator& o) const {
    return current != o.current;
}

void playGame(BST& alice, BST& bob) {
    bool turnAlice = true;
    while (true) {
        bool matched = false;
        if (turnAlice) {
            for (auto it = alice.begin(); it != alice.end(); ++it) {
                if (bob.count(*it)) {
                    std::cout << "Alice picked matching card " << *it << "\n";
                    bob.remove(*it);
                    alice.remove(*it);
                    matched = true;
                    break;
                }
            }
        } else {
            for (auto it = bob.rbegin(); it != bob.rend(); --it) {
                if (alice.count(*it)) {
                    std::cout << "Bob picked matching card " << *it << "\n";
                    alice.remove(*it);
                    bob.remove(*it);
                    matched = true;
                    break;
                }
            }
        }
        if (!matched) break;
        turnAlice = !turnAlice;
    }

    std::cout << "\nAlice's cards:\n";  alice.printDeck();
    std::cout << "\nBob's cards:\n";    bob.printDeck();
}

} 
