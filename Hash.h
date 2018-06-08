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
    List<T, CMP>* arr;
    GETKEY getKey;

private:
    int hash(const T &data) {
        int key = getKey(data);
        return key%size;
    }

public:
    ~Hash(T *array, int size) : size(size * 4), occupancy(size) {
        arr = new List<T, CMP> (size * 4);
        int place;
        for (int i = 0; i < size; ++i) {
            place = hash(*array);
            arr[place].insert(*array);
            array++;
        }
    }
};

#endif //GENTREE_HASH_H
