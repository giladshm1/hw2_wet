//
// Created by gilad on 05/01/2022.
//

#ifndef HW2_WET_HASHTABLE_H
#define HW2_WET_HASHTABLE_H

#include <iostream>
#include "AVLTree.h"


template<class T>
class HashTable {
    typedef std::function<int(T *, T *)> Comparator;

    int size;
    int current_size;
    static const int initial_size = 2;
    AVLTree<T> *table;
    Comparator comparator;

public:
    HashTable(Comparator comparator) : size(initial_size), current_size(0), comparator(comparator) {
        table = new AVLTree<T>[initial_size];

        if (table == NULL) {
            throw std::bad_alloc();
        }

        for (int i = 0; i < initial_size; ++i) {
            table[i] = AVLTree<T>(comparator);
        }
    }

    void insertItem(int key, T *value) {
        int index = hashFunction(key);
        table[index].Add(value);
        current_size++;

        if (size == current_size) {
            resize_table('l', 2);
        }
    }

    void deleteItem(int key, T *value) {
        int index = hashFunction(key);
        table[index].Remove(value);
        current_size--;

        if ((size / 4) == current_size) {
            resize_table('s', 2);
        }
    }

    T *findItem(int key, T *value) {
        int index = hashFunction(key);
        return table[index].Find(value);
    }

    int hashFunction(int key) {
        return (key % size);
    }

    void resize_table(char operation, int factor) {
        int prev_size = size;
        size = (operation == 'l' ? (size * factor) : (size / factor));
        auto new_table = new AVLTree<T>[size];
        if (new_table == NULL) {
            throw std::bad_alloc();
        }

        for (int i = 0; i < size; ++i)
            new_table[i] = AVLTree<T>(comparator);

        for (int i = 0; i < prev_size; ++i) {
            if (table[i].GetSize() != 0) {
                cloneTreeToNewHashTable(table[i], new_table);
                //TODO: delete the table[i] tree.
            }
        }

        //delete table;
        table = new_table;
    }

    void cloneTreeToNewHashTable(AVLTree<T> tree, AVLTree<T> *new_table) {
        //TODO: complete this function. we should use specific function that uses the
        // special key of each player that saved in the hash table.
    }

};

#endif //HW2_WET_HASHTABLE_H
