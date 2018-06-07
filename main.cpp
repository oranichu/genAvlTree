//
// Created by user on 06/05/2018.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "AvlTree.h"


class Bigger {
public:
    int operator()(int x1, int x2) {
        if (x1==x2) {
            return EQUAL ;
        }
        if (x1<x2) {
            return  GO_LEFT ;
        }
        return GO_RIGHT ;
    }
};

class PrintDataFunc {
public:
    void operator()(AvlNode<int> *current) {
        cout << current->getData() << " ";
    }
};

class PrintHeightFunc {
public:
    void operator()(AvlNode<int> *current) {
        cout << current->getHeight() << " ";
    }
};

int main() {

    AvlTree<int, Bigger> tree;
    int n1 = 15 ;
    int n2 = 14 ;
    int n3 = 13 ;
    int n4 = 12 ;
    int n5 = 11 ;
    int n6 = 10 ;
    int n7 = 9 ;
    int n8 = 8;
    int n9 = 7 ;
    int n10 = 6 ;
    int n11 = 5 ;
    int n12 = 4 ;
    int n13 = 3 ;
    int n14 = 2;
    int n15 = 1 ;

    tree.insert(n1);
    tree.insert(n2);
    tree.insert(n3);
    tree.insert(n4);
    tree.insert(n5);
    tree.insert(n6);
    tree.insert(n7);
    tree.insert(n8);
    tree.insert(n9);
    tree.insert(n10);
    tree.insert(n11);
    tree.insert(n12);
    tree.insert(n13);
    tree.insert(n14);
    tree.insert(n15);


    printTree(tree.getRoot(), NULL, false);

    return 0;
}