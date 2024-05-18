#include <cstdlib>
#include <locale.h>
#include <iostream>
#include <limits>

using namespace std;

template <typename T>
struct NodeTree {
    T value;
    struct NodeTree *left = nullptr, *right = nullptr; //! Should I change?
};

template <typename T>
void showTree(NodeTree <T> *raiz, int depth){ //? How can I make this better
    if (raiz == nullptr) {
        return;
    }
    
    // Print the current nodeTree with appropriate indentation
    for (int i = 0; i < depth; ++i) {
        cout << "    ";
    }
    cout << "  |---"; // Assuming 2 spaces for indentation
    
    cout << raiz->value << "\n";

    // Recursively call the function for left and right subtrees with increased depth
    showTree(raiz->left, (depth + 1));
    showTree(raiz->right, (depth + 1));
}

template <typename T>
void prefixado(NodeTree <T> *raiz) {
    // Verifify if its a valid nodeTree
    if (raiz == nullptr) {
        return;
    }

    cout << raiz->value << " ";
    prefixado(raiz->left);
    prefixado(raiz->right);
}

template <typename T>
void infixado(NodeTree <T> *raiz) {
    // Verifify if its a valid nodeTree
    if (raiz == nullptr) {
        return;
    }

    prefixado(raiz->left);
    cout << raiz->value << " ";
    prefixado(raiz->right);
}

template <typename T>
void posfixado(NodeTree <T> *raiz) {
    // Verifify if its a valid nodeTree
    if (raiz == nullptr) {
        return;
    }

    prefixado(raiz->left);
    prefixado(raiz->right);
    cout << raiz->value << " ";
}

template <typename T>
int descendents(NodeTree <T> *raiz) {
    // Verifify if its a valid nodeTree
    if (raiz == nullptr) {
        return 0;
    }

    return 1 + descendents(raiz->left) + descendents(raiz->right);
}

template <typename T>
bool insertNodeTree(NodeTree <T> *&raiz, T value) {
    // Verify if it is a valid raiz
    if (raiz == nullptr) {
        raiz = new NodeTree <T>;
        raiz->value = value;
        return true;
    }

    if (value < raiz->value) {
        return insert(raiz->left, value);
    } else {
        return insert(raiz->right, value);
    }
}

template <typename T>
bool deleteNodeTree(NodeTree<T> *&raiz, T value) { //? looh trough this function again
    // If nodeTree is a leaf
    if (raiz == nullptr) {
        return false; 
    }
    
    // NodeTree is found
    if (raiz->value == value) {
        // Case 1: NodeTree to delete is a leaf nodeTree
        if (raiz->left == nullptr && raiz->right == nullptr) {
            delete raiz;
            raiz = nullptr; // Update the pointer to null
            return true;
        }
        // Case 2: NodeTree to delete has only one child
        else if (raiz->left == nullptr) {
            NodeTree<T> *temp = raiz;
            raiz = raiz->right;
            delete temp;
            return true;
        }
        else if (raiz->right == nullptr) {
            NodeTree<T> *temp = raiz;
            raiz = raiz->left;
            delete temp;
            return true;
        }
        // Case 3: NodeTree to delete has two children
        else {
            // Find the in-order successor (or predecessor)
            NodeTree<T> *temp = raiz->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            // Replace the value of the nodeTree to delete with the value of the successor
            raiz->value = temp->value;
            // Delete the successor nodeTree recursively
            deleteNodeTree(raiz->right, temp->value);
            return true;
        }
    // NodeTree is not found
    } 
    else if (value < raiz->value) {
        return deleteNodeTree(raiz->left, value); // Search in the left subtree
    }
    else {
        return deleteNodeTree(raiz->right, value); // Search in the right subtree
    }
}


template <typename T>
void deleteTree(NodeTree <T> *&raiz) {
    if (raiz == nullptr) {
        return;
    }
    deleteTree(raiz->left);
    deleteTree(raiz->right);
    delete raiz;
    raiz = nullptr;
}   