#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class AVLTree {
private:
    struct Node {
        int key;        
        Node* left;
        Node* right;
        int height;
    };
    Node* root;
    int minTimeDifference; 
    Node* insert(Node* node, int key);
    Node* remove(Node* root, int key);
    Node* minValueNode(Node* node);
    Node* maxValueNode(Node* node);
    Node* findNext(Node* node, int key);
    Node* searchNode(Node* node, int key);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    int height(Node* node);
    int getBalance(Node* node);
    void inOrder(Node* root);
    int rank(Node* node, int key);
    bool isValidInsertion(int key);
    int timeDifference(int t1, int t2);

public:
    AVLTree(int minDifference);
    void addReservation(int key);
    void cancelReservation(int key);
    void displayReservations();
    void minimumReservation();
    void maximumReservation();
    void nextLandingTime(int key);
    void searchReservation(int key);
    void planeLanded();
    void rankOfReservation(int key);
    void printReservations(Node* node, int key);
    int getNodeCount(Node* node);
    string formatTime(int key);   

};

#endif
