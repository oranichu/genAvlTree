//
// Created by user on 06/05/2018.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "AvlTree.h"
#include "List.h"


class Bigger {
public:
    int operator()(int x1, int x2) {
        if (x1 == x2) {
            return EQUAL;
        }
        if (x1 < x2) {
            return GO_LEFT;
        }
        return GO_RIGHT;
    }
};

class PrintRankFunc {
public:
    void operator()(AvlNode<int, int> *current) {
        cout << current->getRank() << " ";
    }
};

class PrintHeightFunc {
public:
    void operator()(AvlNode<int, int> *current) {
        cout << current->getHeight() << " ";
    }
};

class AddInt {
    int val;
public:
    explicit AddInt(int val) : val(val) {}

    int operator()(int x, FuncOp t) {
        if (t == DEC) {
            return x - val;
        }
        return x + val;
    }

    int operator()(int x, int y, int z) {
        return x + y + z;
    }

};

class IntCmp {
public:
    bool operator()(int a, int b) {
        return a == b;
    }
};

int main() {
    List<int, IntCmp> intArr(-1);
    intArr.insert(4);
    intArr.insert(6);
    intArr.insert(3);
    cout << "-1, 3, 6, 4 :" << endl;
    intArr.printInt();
    Node<int>* p = intArr.find(6);
    cout << "6=" << p->getData() << endl;
    p = intArr.find(7);
    if(p == NULL){
        cout << "success" << endl;
    }
    intArr.destroy(6);
    cout << "-1, 3, 4 :" << endl;
    intArr.printInt();
    intArr.insert(6);
    intArr.destroy(4);
    cout << "-1, 6, 3 :" << endl;
    intArr.printInt();
    intArr.insert(4);
    if (intArr.destroy(9) == false){
        cout << "success" << endl;
    }

/*
    AvlTree<int,int, Bigger> tree;
    int n1 = 1 ;
    int n2 = 2 ;
    int n3 = 3 ;
    int n4 = 4 ;
    int n5 = 5 ;
    int n6 = 6 ;
    int n7 = 7 ;
    int n8 = 8;
    int n9 = 9 ;
    int n10 = 10 ;
    int n11 = 11 ;
    int n12 = 12 ;
    int n13 = 13 ;
    int n14 = 14;
    int n15 = 15 ;
    int n = 4 ;
    AddInt f1(4);

    tree.insert(1,1,AddInt(1));
    tree.insert(2,2,AddInt(2));
    tree.insert(3,3,AddInt(3));
    tree.insert(4,4,AddInt(4));
    tree.insert(5,5,AddInt(5));
    tree.insert(6,6,AddInt(6));
    tree.insert(7,7,AddInt(7));
    tree.insert(8,8,AddInt(8));
    tree.insert(9,9,AddInt(9));
    tree.insert(10,10,AddInt(10));
    tree.insert(11,11,AddInt(11));
    tree.insert(12,12,AddInt(12));
    tree.insert(13,13,AddInt(13));
    tree.insert(14,14,AddInt(14));
    tree.insert(15,15,AddInt(15));
    printRank(tree.getRoot(), NULL, false);


    //tree.removeNode(8,AddInt(8));
    tree.removeNode(1,AddInt(1));
    tree.removeNode(15,AddInt(15));

/*
    tree.removeNode(2,AddInt(2));
    tree.removeNode(4,AddInt(4));
    tree.removeNode(8,AddInt(8));
    tree.removeNode(3,AddInt(3));

*/
/*
    cout << "****************************" << endl ;
    printRank(tree.getRoot(), NULL, false);

*/
    return 0;
}