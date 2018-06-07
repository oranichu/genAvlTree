#ifndef GENTREE_AVLTREE_H
#define GENTREE_AVLTREE_H

#include <iostream>

////////////////////////////////////
#include <string>

#define GO_LEFT (-1)
#define GO_RIGHT (1)
#define EQUAL (0)

using std::string;

using std::cout;
using std::endl;
///////////////////////////////////


typedef enum {
    LEFT, RIGHT
} Place;

int maxFunc(int x1, int x2) {
    if (x1 > x2) {
        return x1;
    }
    return x2;
}

template<typename T, typename U>
class AvlNode {
    T data;
    AvlNode<T, U> *father;
    AvlNode<T, U> *lSon;
    AvlNode<T, U> *rSon;
    int height;
    int rank;
    U sumRank;
public:
    AvlNode(const T &data,const U &sum) : data(data), father(NULL), lSon(NULL),
                             rSon(NULL), height(0), rank(1),sumRank(sum) {};

    void setData(const T &d) { data = d; }

    void setFather(AvlNode<T, U> *parent) { father = parent; }

    void setLeftSon(AvlNode<T, U> *left_son) { lSon = left_son; }

    void setRightSon(AvlNode<T, U> *right_son) { rSon = right_son; }

    const T &getData() {
        return data;
    }

    AvlNode<T, U> *getFather() const { return father; }

    AvlNode<T, U> *getLeftSon() const { return lSon; }

    AvlNode<T, U> *getRightSon() const { return rSon; }

    int getHeight() const { return height; }

    void setHeight(int h) { height = h; }

    int diff() const {
        if (lSon != NULL && rSon != NULL) {
            return lSon->height - rSon->height;
        }
        if (lSon != NULL) { //no right son
            return lSon->height + 1;
        }
        if (rSon != NULL) {
            return -1 - rSon->height; //no left son
        }
        return 0; //has no sons.
    }

    int getRank() const { return rank; };

    int getRankSum() const { return sumRank; };

    void setRank(int r) { rank = r; };

    void setRankSum(int s) { sumRank = s; };


};

template<typename T, typename U, typename CompareFunction>
class AvlTree {

private:
    AvlNode<T, U> *root;
    /** cmp function for the tree ,returns -1 if we want x1 to be on the left
     * son return 1 if we want x1 to be on the right side , and 0 if x1 == x2 */
    CompareFunction cmp;
    int size;

    AvlNode<T, U> *
    sortInsert(AvlNode<T, U> *current, AvlNode<T, U> *new_node) {
        // if x1 <= x2 of the cmp function we want the new node to be on the left
        if (cmp(new_node->getData(), current->getData()) <= EQUAL) {
            if (current->getLeftSon() == NULL) {
                //Left son doesn't exist found place to insert !
                makeSon(current, new_node, LEFT);
            } else { //Left son does exist,continue searching .
                // rec call to the function , but makes sure so update pointers.
                makeSon(current, sortInsert(current->getLeftSon(), new_node),
                        LEFT);
            }
        } else {
            if (current->getRightSon() == NULL) {
                //Right son doesn't exist found place to insert !
                makeSon(current, new_node, RIGHT);
            } else { //Right son does exist,continue searching .
                makeSon(current, sortInsert(current->getRightSon(), new_node),
                        RIGHT);
            }
        }
        updateHeight(current);
        current->setRank(current->getRank() + 1);
        return balance(current);
    }

    void makeSon(AvlNode<T, U> *father, AvlNode<T, U> *son, Place p) const {
        if (son != NULL) {
            son->setFather(father);
        }
        if (p == LEFT) {
            father->setLeftSon(son);
        } else { //p == RIGHT
            father->setRightSon(son);
        }
    }

    template<typename Func>
    //Function to determant what we want to do.
    void startInorder(AvlNode<T, U> *current, Func f) {
        if (current == NULL) {
            return;
        }
        startInorder(current->getLeftSon(), f);
        f(current);
        startInorder(current->getRightSon(), f);
    }

    template<typename Func>
    void startPreorder(AvlNode<T, U> *current, Func f) {
        if (current == NULL) {
            return;
        }
        f(current);
        startPreorder(current->getLeftSon(), f);
        startPreorder(current->getRightSon(), f);
    }

    template<typename Func>
    void startPostorder(AvlNode<T, U> *current, Func f) {
        if (current == NULL) {
            return;
        }
        startPostorder(current->getLeftSon(), f);
        startPostorder(current->getRightSon(), f);
        f(current);
    }

    AvlNode<T, U> *recFind(AvlNode<T, U> *current, T key) {
        if (current == NULL) {
            return NULL;
        }
        if (cmp(key, current->getData()) == EQUAL) {
            return current;
        }
        if (cmp(key, current->getData()) == GO_LEFT) {
            return recFind(current->getLeftSon(), key);
        }
        return recFind(current->getRightSon(), key);
    }

    AvlNode<T, U> *balance(AvlNode<T, U> *node) {
        int balance = node->diff();
        if (balance > 1) {
            if (node->getLeftSon()->diff() >= 0) {
                return llRotation(node);
            } else {
                return lrRotation(node);
            }
        } else if (balance < -1) {
            if (node->getRightSon()->diff() > 0) {
                return rlRotation(node);
            } else {
                return rrRotation(node);
            }
        }
        // Tree is balanced , return original root  .
        return node;
    }

    AvlNode<T, U> *rightRotation(AvlNode<T, U> *node) {
        AvlNode<T, U> *tempA = node->getLeftSon();
        tempA->setFather(node->getFather());
        makeSon(node, node->getLeftSon()->getRightSon(), LEFT);
        makeSon(tempA, node, RIGHT);
        updateHeight(node);
        updateHeight(tempA);
        updateRank(node);
        updateRank(tempA);
        return tempA;
    }

    AvlNode<T, U> *leftRotation(AvlNode<T, U> *node) {
        AvlNode<T, U> *tempA = node->getRightSon();
        tempA->setFather(node->getFather());
        makeSon(node, node->getRightSon()->getLeftSon(), RIGHT);
        makeSon(tempA, node, LEFT);
        updateHeight(node);
        updateHeight(tempA);
        updateRank(node);
        updateRank(tempA);
        return tempA;
    }

    void updateHeight(AvlNode<T, U> *node) {
        int leftSonH = -1, rightSonH = -1;
        if (node->getLeftSon() != NULL) {
            leftSonH = node->getLeftSon()->getHeight();
        }
        if (node->getRightSon() != NULL) {
            rightSonH = node->getRightSon()->getHeight();
        }
        node->setHeight(maxFunc(leftSonH, rightSonH) + 1);
    }

    void updateRank(AvlNode<T, U> *node) {
        int rightSonR = 0 , leftSonR= 0 ;
        if (node->getLeftSon() != NULL) {
            leftSonR = node->getLeftSon()->getRank();
        }
        if (node->getRightSon() != NULL) {
            rightSonR = node->getRightSon()->getRank();
        }
        node->setRank(1 + rightSonR + leftSonR);
    }

    AvlNode<T, U> *llRotation(AvlNode<T, U> *node) {
        return rightRotation(node);
    }

    AvlNode<T, U> *lrRotation(AvlNode<T, U> *node) {
        node->setLeftSon(leftRotation(node->getLeftSon()));
        return rightRotation(node);
    }

    AvlNode<T, U> *rlRotation(AvlNode<T, U> *node) {
        node->setRightSon(rightRotation(node->getRightSon()));
        return leftRotation(node);
    }

    AvlNode<T, U> *rrRotation(AvlNode<T, U> *node) {
        return leftRotation(node);
    }

    AvlNode<T, U> *findMinReplace(AvlNode<T, U> *current) const {
        if (current == NULL) {
            return NULL;
        }
        while (current->getLeftSon() != NULL) {
            current = current->getLeftSon();
        }
        return current;
    }

    AvlNode<T, U> *
    removeTwoSons(AvlNode<T, U> *current, AvlNode<T, U> *bad_node) {
        if (cmp(bad_node->getData(), current->getData()) == EQUAL) {
            AvlNode<T, U> *replace_node = findMinReplace(
                    bad_node->getRightSon());
            current->setData(replace_node->getData());
            makeSon(current,
                    removeOneOrNoSons(current->getRightSon(), replace_node,
                                      RIGHT), RIGHT);
        } else if (cmp(bad_node->getData(), current->getData()) == GO_LEFT) {
            // rec call to the function , but makes sure so update pointers.
            makeSon(current,
                    removeTwoSons(current->getLeftSon(), bad_node),
                    LEFT);
        } else { //go right.
            makeSon(current,
                    removeTwoSons(current->getRightSon(), bad_node),
                    RIGHT);
        }
        updateHeight(current);
        current->setRank(current->getRank() - 1);
        return balance(current);
    }

    AvlNode<T, U> *
    removeOneOrNoSons(AvlNode<T, U> *current, AvlNode<T, U> *bad_node,
                      Place p) {
        if (cmp(bad_node->getData(), current->getData()) == EQUAL) {
            AvlNode<T, U> *temp = (p == LEFT) ? current->getLeftSon()
                                              : current->getRightSon();
            delete (current);
            return temp;
        }
        if (cmp(bad_node->getData(), current->getData()) == GO_LEFT) {
            // rec call to the function , but makes sure so update pointers.
            makeSon(current,
                    removeOneOrNoSons(current->getLeftSon(), bad_node, p),
                    LEFT);
        } else { //go right.
            makeSon(current,
                    removeOneOrNoSons(current->getRightSon(), bad_node, p),
                    RIGHT);
        }
        updateHeight(current);
        current->setRank(current->getRank() - 1);
        return balance(current);
    }

public:
    AvlTree() : root(NULL), size(0) {};

    ~AvlTree() {
        if (root == NULL) {
            return;
        }
        treeDestroy(root);
    }

    AvlNode<T, U> *getRoot() const { return root; }

    int getSize() const {
        return size;
    }

    void insert(const T &data,const U &sum) {
        AvlNode<T, U> *new_node = new AvlNode<T, U>(data,sum);
        size++;
        if (root == NULL) {
            root = new_node;
            return;
        }
        root = sortInsert(root, new_node);

    }

    AvlNode<T, U> *find(const T &key) {
        return recFind(root, key);
    }

    template<typename Func>
    void inorder(Func f) {
        startInorder(root, f);
    }

    template<typename Func>
    void preorder(Func f) {
        startPreorder(root, f);
    }

    template<typename Func>
    void postorder(Func f) {
        startPostorder(root, f);
    }

    bool removeNode(const T &key) {
        AvlNode<T, U> *node_to_remove = find(key);
        if (node_to_remove == NULL) {
            return false;
        }
        if (node_to_remove->getLeftSon() != NULL &&
            node_to_remove->getRightSon() != NULL) {
            root = removeTwoSons(root, node_to_remove);
        } else if (node_to_remove->getLeftSon() != NULL) {
            root = removeOneOrNoSons(root, node_to_remove, LEFT);
        } else if (node_to_remove->getRightSon() != NULL) {
            root = removeOneOrNoSons(root, node_to_remove, RIGHT);
        } else { //for no sons it's same case as one son.
            root = removeOneOrNoSons(root, node_to_remove, LEFT);
        }
        size--;
        return true;
    }

    void treeDestroy(AvlNode<T, U> *node) {
        if (node == NULL) {
            return;
        }
        treeDestroy(node->getLeftSon());
        treeDestroy(node->getRightSon());
        delete (node);
    }

//////////////////////////////////////////////////////////////
    void printCheck(AvlNode<T, U> *node) {
        while (node->getLeftSon() != NULL) {
            cout << node->getData() << " ";
            node = node->getLeftSon();
        }
        cout << endl;
        while (node != root) {
            cout << node->getData() << " ";
            node = node->getFather();
        }
    }

};

/////////////////////////////////////////////////////////////
struct Trunk {
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p) {
    if (p == NULL)
        return;
    showTrunks(p->prev);
    cout << p->str;
}

// Recursive function to print binary tree. It uses inorder traversal
// call as printTree(root, NULL, false);
void printTree(AvlNode<int, int> *root, Trunk *prev, bool isLeft) {
    if (root == NULL)
        return;

    string prev_str = " ";
    Trunk *trunk = new Trunk(prev, prev_str);
    printTree(root->getLeftSon(), trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft) {
        trunk->str = ".---";
        prev_str = "  |";
    } else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->getData() << endl;
    if (prev)
        prev->str = prev_str;

    trunk->str = "  |";
    printTree(root->getRightSon(), trunk, false);
}

void printRank(AvlNode<int, int> *root, Trunk *prev, bool isLeft) {
    if (root == NULL)
        return;

    string prev_str = " ";
    Trunk *trunk = new Trunk(prev, prev_str);
    printRank(root->getLeftSon(), trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft) {
        trunk->str = ".---";
        prev_str = "  |";
    } else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->getRank() << endl;
    if (prev)
        prev->str = prev_str;

    trunk->str = "  |";
    printRank(root->getRightSon(), trunk, false);
}
///////////////////////////////////////////////////////////////////////



#endif //GENTREE_AVLTREE_H
