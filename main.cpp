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

class PrintRankFunc {
public:
    void operator()(AvlNode<int,int> *current) {
        cout << current->getRank() << " ";
    }
};

class PrintHeightFunc {
public:
    void operator()(AvlNode<int,int> *current) {
        cout << current->getHeight() << " ";
    }
};

class AddInt {
    int val ;
public:
     explicit AddInt(int val) :val(val){}
    int operator()(int x,FuncOp t){
        if (t==DEC) {
            return x-val ;
        }
        return x+val ;
    }
    int operator() (int x,int y){
        return x+y - val  ;
    }
    int operator()(int x,int y,int z){
        return x+y+z ;
    }

};
int main() {

    AvlTree<int,int, Bigger> tree;
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
    int n = 4 ;
    AddInt f1(4);

    tree.insert(n8,n,AddInt(4));
    tree.insert(n9,n,AddInt(1));
    tree.insert(n11,n,f1);
    tree.insert(n12,n,f1);
    tree.insert(n3,n,f1);
    tree.insert(n1,n,AddInt(1));
    tree.insert(n2,n,f1);
    tree.insert(n4,n,AddInt(0));
    tree.insert(n15,n,f1);
    tree.insert(n5,n,f1);
    tree.insert(n6,n,f1);
    tree.insert(n7,n,f1);
    tree.insert(n13,n,f1);
    tree.insert(n14,n,AddInt(9));
    tree.insert(n10,n,f1);
/*
    tree.removeNode(n8,f1);
    tree.removeNode(n1,f1);

    tree.removeNode(n2,f1);
    tree.removeNode(n4,f1);
    tree.removeNode(n8,f1);
    tree.removeNode(n3,f1);
*/



    printTree(tree.getRoot(), NULL, false);
    cout << "****************************" << endl ;
    printRank(tree.getRoot(), NULL, false);


    return 0;
}