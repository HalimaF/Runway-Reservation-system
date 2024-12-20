#include "AVLTree.h"
#include <cstdio>
#include <cmath>
AVLTree::AVLTree(int minDifference) : root(nullptr), minTimeDifference(minDifference) {}

int AVLTree::height(Node* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int AVLTree::timeDifference(int t1, int t2) {
    int h1 = t1 / 100, m1 = t1 % 100;
    int h2 = t2 / 100, m2 = t2 % 100;
    return abs((h1 * 60 + m1) - (h2 * 60 + m2));
}

bool AVLTree::isValidInsertion(int key) {
    Node* current = root;
    while (current) {
        int diff = timeDifference(current->key, key);
        if (diff < minTimeDifference) return false;
        if (key < current->key) current = current->left;
        else current = current->right;
    }
    return true;
}

AVLTree::Node* AVLTree::insert(Node* node, int key) {
    if (!node) return new Node{ key, nullptr, nullptr, 1 };

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::addReservation(int key) {
    if (key / 100 >= 24 || key % 100 >= 60) {
        cout << "Error: Invalid time format. Please enter time in HHMM (24-hour format).\n";
        return;
    }
    if (!isValidInsertion(key)) {
        cout << "Error: Reservation time violates minimum time difference constraint.\n";
        return;
    }
    root = insert(root, key);
    cout << "Reservation added at: " << formatTime(key) << "\n";
}

AVLTree::Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

AVLTree::Node* AVLTree::maxValueNode(Node* node) {
    Node* current = node;
    while (current->right) current = current->right;
    return current;
}

AVLTree::Node* AVLTree::remove(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = remove(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void AVLTree::cancelReservation(int key) {
    Node* nodeToDelete = searchNode(root, key);
    if (!nodeToDelete) {
        cout << "Error: Reservation at " << formatTime(key) << " not found.\n";
        return;
    }
    root = remove(root, key);
    cout << "Reservation at " << formatTime(key) << " cancelled successfully.\n";
}

void AVLTree::minimumReservation() {
    if (!root) {
        cout << "No reservations available.\n";
        return;
    }
    Node* minNode = minValueNode(root);
    cout << "Minimum reservation time: " << formatTime(minNode->key) << "\n";
}

void AVLTree::maximumReservation() {
    if (!root) {
        cout << "No reservations available.\n";
        return;
    }
    Node* maxNode = maxValueNode(root);
    cout << "Maximum reservation time: " << formatTime(maxNode->key) << "\n";
}

AVLTree::Node* AVLTree::findNext(Node* node, int key) {
    Node* successor = nullptr;
    while (node) {
        if (key < node->key) {
            successor = node;
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return successor;
}

void AVLTree::nextLandingTime(int key) {
    Node* next = findNext(root, key);
    if (!next) {
        cout << "No later reservations found.\n";
        return;
    }
    cout << "Next landing time: " << formatTime(next->key) << "\n";
}

void AVLTree::planeLanded() {
    if (!root) {
        cout << "No reservations available.\n";
        return;
    }
    Node* earliest = minValueNode(root);
    cout << "Plane landed at: " << formatTime(earliest->key) << "\n";
    root = remove(root, earliest->key);
}

void AVLTree::searchReservation(int key) {
    Node* found = searchNode(root, key);
    if (found)
        cout << "Reservation found at: " << formatTime(found->key) << "\n";
    else
        cout << "No reservation found at the given time.\n";
}

AVLTree::Node* AVLTree::searchNode(Node* node, int key) {
    if (!node || node->key == key) return node;
    if (key < node->key)
        return searchNode(node->left, key);
    else
        return searchNode(node->right, key);
}

void AVLTree::inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << formatTime(root->key) << " ";
        inOrder(root->right);
    }
}

void AVLTree::displayReservations() {
    if (!root) {
        cout << "No reservations available.\n";
        return;
    }
    inOrder(root);
    cout << "\n";
}

string AVLTree::formatTime(int key) {
    int hours = key / 100;
    int minutes = key % 100;
    char buffer[6];
    sprintf_s(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);
    return string(buffer);
}

int AVLTree::rank(Node* node, int key) {
    if (!node) return 0;

    int currentRank = 0;

    if (key < node->key) {
        currentRank += rank(node->left, key);
    }
    else {
        if (node->left) {
            currentRank += getNodeCount(node->left);
        }
        if (node->key <= key) {
            currentRank++;
        }
        currentRank += rank(node->right, key);
    }
    return currentRank;
}

void AVLTree::rankOfReservation(int key) {
    if (!searchNode(root, key)) {
        cout << "Reservation not found for the given time.\n";
        return;
    }
    cout << "Reservations less than or equal to " << formatTime(key) << ": ";
    printReservations(root, key);
    cout << "\n";

    int rank = AVLTree::rank(root, key);
    cout << "Rank of reservation at " << formatTime(key) << ": " << rank << "\n";
}

void AVLTree::printReservations(Node* node, int key) {
    if (!node) return;

    if (node->key <= key) {
        printReservations(node->left, key);
        cout << formatTime(node->key) << " ";
        printReservations(node->right, key);
    }
    else {
        printReservations(node->left, key);
    }
}

int AVLTree::getNodeCount(Node* node) {
    if (!node) return 0;
    return 1 + getNodeCount(node->left) + getNodeCount(node->right);
}
