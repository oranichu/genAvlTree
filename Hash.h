//
// Created by shay-halimi on 08-Jun-18.
//

#ifndef GENTREE_HASH_H
#define GENTREE_HASH_H

#include "List.h"

template<typename T, typename CMP, typename GETKEY>
class Hash {
    int size;
    int occupancy;
    List<T, CMP> *arr;
    GETKEY getKey;

private:
    int hash(const T &data) {
        int key = getKey(data);
        return key % size;
    }

    void resize() {
        List<T, CMP> *tempArr = arr;
        arr = new List<T, CMP>(occupancy * 4);
        int place;
        Node<T> *curr;
        for (int i = 0; i < size; ++i) {
            curr = tempArr[i].getFirst();
            while (curr != NULL) {
                place = hash(curr->getData());
                arr[place].blindInsert(curr->getData());
                curr = curr->getNext();
            }
        }
        delete[] tempArr;
    }

public:
    Hash(T *array, int size) : size(size * 4), occupancy(size) {
        arr = new List<T, CMP>(size * 4);
        int place;
        for (int i = 0; i < size; ++i) {
            place = hash(*array);
            arr[place].blindInsert(*array);
            array++;
        }
    }

    ~Hash() {
        delete[] arr;
    }

    bool insert(const T& data){
        int place = hash(data);
        return arr[place].insert(data);
    }

    T& find(const T& data){
        int place = hash(data);
        return arr[place].find(data);
    }
};

#endif //GENTREE_HASH_H
