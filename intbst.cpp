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
    Node* current = getNodeFor(value, root);
    if (!current) {

        return nullptr;
    }

    if (current->left) {
        current = current->left;
        while (current->right) {
            current = current->right;
        }
        return current;
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
    return predecessor;
}

int IntBST::getPredecessor(int value) const{
    Node* node = getPredecessorNode(value);
    if (node) {
        return node->info;
    } else {
        // Return 0 or -1 to indicate no predecessor
        return 0; 
    }
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
    Node *parent = nullptr;
    Node *current = root;

    // Find the node to be removed and its parent.
    while (current != nullptr && current->info != value) {
        parent = current;
        if (value < current->info) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        // Value not found in the tree.
        return false;
    }

    // Case 1: Removing a leaf node.
    if (current->left == nullptr && current->right == nullptr) {
        if (current != root) {
            if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete current;
    }
    // Case 2: Removing a node with one child.
    else if (current->left == nullptr || current->right == nullptr) {
        Node *child;
        if (current->left != nullptr) {
            child = current->left;
        } else {
            child = current->right;
        }

        if (current != root) {
            if (current == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            root = child;
        }
        delete current;
    }
    // Case 3: Removing a node with two children.
    else {
        Node *successor = current->right;
        Node *successorParent = current;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        if (successorParent != current) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }

        current->info = successor->info;
        delete successor;
    }
    return true;
} // REPLACE THIS NON-SOLUTION
