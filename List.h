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
    Node(const T& data) : data(data){}
    const T& getData(){ return data;}
    void setData(const T& data){this->data = data};
    Node<T>* getNext(){ return next;}
    void setNext(Node<T>* next){this->next = next;}
    Node<T>* getPrev(){ return prev;}
    void setPrev(Node<T>* prev){this->prev = prev;}
};

//not complete
template <typename T>
class List{
    Node<T>* head;
    int size;
public:
    List() : head(new Node()), size(0){} ////????/////
    ~List(){
        destroyList(head);
    }
    void destroyList(Node<T>* node){
        if(node==NULL){

        }
    }
};
#endif //PROJECT_LIST_H
