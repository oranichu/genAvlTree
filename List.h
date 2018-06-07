//
// Created by shay-halimi on 07-Jun-18.
//

#ifndef PROJECT_LIST_H
#define PROJECT_LIST_H

template <typename T>
class Node{
    T data;
    Node<T>* next;
    Node<T>* prev;
public:
    Node(const T& data) : data(data), next(NULL), prev(NULL){}
    const T& getData(){ return data;}
    void setData(const T& data){this->data = data;};
    Node<T>* getNext(){ return next;}
    void setNext(Node<T>* next){this->next = next;}
    Node<T>* getPrev(){ return prev;}
    void setPrev(Node<T>* prev){this->prev = prev;}
};

//not complete
template <typename T, typename CMP>
class List{
    Node<T>* head;
    int size;
public:
    List(const T& emptyValue) : head(new Node<T>(emptyValue)), size(0){}
    ~List(){
        destroyList(head);
    }
    void destroyList(Node<T>* node){
        if(node==NULL){
            return;
        }
        destroyList(node->getNext());
        delete node;
    }
    void insert(const T& data){
        Node<T>* node = new Node<T>(data);
        node->setNext(head->getNext());
        node->getPrev(head);
        head->setNext(node);
    }
    template <typename CMP>
    Node<T>* find(const T& data){
        Node<T>* curr = head;
        Node<T>* key = new Node<T>(data);
        while (CMP(curr, key) == false){
            curr = curr->getNext();
            if (curr == NULL){
                return NULL;
            }
        }
        delete key;
        return curr;
    }
    bool destroy(const T& data){
        Node<T>* node = find(data);
        if (node == NULL){
            return false;
        }
        Node<T>* prev = node->getPrev();
        node<T>* next = node->getNext();
        prev->setNext(next);
        if(next != NULL){
            next->setPrev(prev);
        }
        return true;
    }
};
#endif //PROJECT_LIST_H
