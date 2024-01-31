// intbst.cpp
// Implements class IntBST
// Gavin Cao, 1/29/24

#include "intbst.h"

#include <iostream>
using std::cout;


IntBST::IntBST():root(nullptr) { 
    
}


IntBST::~IntBST() {
    clear(root);
}

void IntBST::clear(Node *n) {
        if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}


bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    } else {
        return insert(value, root);
    }
}

bool IntBST::insert(int value, Node *n) {
    if (value < n->info) {
        if (!n->left) {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        } else {
            return insert(value, n->left);
        }
    } else if (value > n->info) {
        if (!n->right) {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        } else {
            return insert(value, n->right);
        }
    }

    return false;
}

void IntBST::printPreOrder() const {
    printPreOrder(root); 
}
void IntBST::printPreOrder(Node *n) const {
    if (n) {
        cout << n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->info << " ";
        printInOrder(n->right);
    }
}

void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << " ";
    }
}

int IntBST::sum() const {
    return sum(root); // REPLACE THIS NON-SOLUTION
}

int IntBST::sum(Node *n) const {
    if (!n) return 0;
    return n->info + sum(n->left) + sum(n->right); // REPLACE THIS NON-SOLUTION
}

int IntBST::count() const {
    return count(root);// REPLACE THIS NON-SOLUTION
}

int IntBST::count(Node *n) const {
    if (!n) return 0;
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n == nullptr) {
        return nullptr;
    } 
    if (value == n->info) {
        return n;
    } 
    if (value < n->info) {
        return getNodeFor(value, n->left);
    } else {
        return getNodeFor(value, n->right);
    }
}

bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr; // REPLACE THIS NON-SOLUTION
}


IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* node = getPredecessorNode(value);
    return node
}

int IntBST::getPredecessor(int value) const{
    Node* current = getNodeFor(value, root);
    if (!current) return 0;


    if (current->left) {
        current = current->left;
        while (current->right) {
            current = current->right;
        }
        return current->info;
    }

    Node* predecessor = nullptr;
    Node* ancestor = root;
    while (ancestor != current) {
        if (current->info > ancestor->info) {
            predecessor = ancestor;
            ancestor = ancestor->right;
        } else {
            ancestor = ancestor->left;
        }
    }
    return predecessor->data; // REPLACE THIS NON-SOLUTION
}

IntBST::Node* IntBST::getSuccessorNode(int value) const{
        Node* current = getNodeFor(value, root);
    if (current == nullptr) {
        return nullptr;
    }
    
    if (current->right != nullptr) {
        Node* temp = current->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }

    Node* successor = nullptr;
    Node* ancestor = root;
    while (ancestor != current) {
        if (current->info < ancestor->info) {
            successor = ancestor; 
            ancestor = ancestor->left;
        } else {
            ancestor = ancestor->right;
        }
    }
    return successor;
}

int IntBST::getSuccessor(int value) const{
    Node* successorNode = getSuccessorNode(value);
    if (successorNode) {
        return successorNode->info;
    } else {

        return 0;
    } // REPLACE THIS NON-SOLUTION
}

bool IntBST::remove(int value){
    Node* toDelete = getNodeFor(value, root);
    if (toDelete == nullptr) {
        // Value not found in the tree.
        return false;
    }

    if (toDelete->left == nullptr && toDelete->right == nullptr) {
        if (toDelete != root) {
            if (toDelete->parent->left == toDelete) {
                toDelete->parent->left = nullptr;
            } else {
                toDelete->parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete toDelete;
    }

    else if (toDelete->left == nullptr || toDelete->right == nullptr) {
        Node* child = (toDelete->left) ? toDelete->left : toDelete->right;
        if (toDelete != root) {
            if (toDelete == toDelete->parent->left) {
                toDelete->parent->left = child;
            } else {
                toDelete->parent->right = child;
            }
            child->parent = toDelete->parent;
        } else {
            root = child;
            root->parent = nullptr;
        }
        delete toDelete;
    }

    else {
        Node* successor = getSuccessorNode(toDelete->info);
        int val = successor->info;
        remove(successor->info);
        toDelete->info = val;
    }
    return true;
} // REPLACE THIS NON-SOLUTION
