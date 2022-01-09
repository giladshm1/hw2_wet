//
// Created by gilad on 05/01/2022.
//

#ifndef HW2_WET_HASHTABLE_H
#define HW2_WET_HASHTABLE_H

#include <iostream>
#include "LinkedList.h"


template<class T>
class HashTable {
    static const int initial_size = 2; //maybe another size

    int size;
    int current_size;
    Node<T> **table;

public:
    HashTable() : size(initial_size), current_size(0) {
        table = new Node<T> *[initial_size];

        if (table == NULL) {
            throw std::bad_alloc();
        }

        for (int i = 0; i < initial_size; ++i) {
            table[i] = NULL;
        }
    }

    void insertItem(int key, T *value) {
        int index = hashFunction(key);
        insertAtBeginning(&(table[index]), key, value);
        current_size++;

        if (size == current_size) {
            resize_table('l', 2);
        }
    }

    void deleteItem(int key) {
        int index = hashFunction(key);
        deleteNode(&(table[index]), key);
        current_size--;

        if ((size / 4) == current_size) {
            resize_table('s', 2);
        }
    }

    T *findItem(int key) {
        int index = hashFunction(key);
        return searchNode(&(table[index]), key);
    }

    int hashFunction(int key) {
        return (key % size);
    }

    void resize_table(char operation, int factor) {
        int prev_size = size;
        size = (operation == 'l' ? (size * factor) : (size / factor));
        auto new_table = new Node<T> *[size];
        if (new_table == NULL) {
            throw std::bad_alloc();
        }

        for (int i = 0; i < size; ++i)
            new_table[i] = NULL;

        for (int i = 0; i < prev_size; ++i) {
            if (table[i] != NULL) {
                cloneListToNewHashTable(table[i], new_table);
                //TODO: delete the table[i] list.
            }
        }

        delete[] table;
        table = new_table;
    }

    void cloneListToNewHashTable(Node<T> *list, Node<T> **new_table) {
        struct Node<T> *current = list;

        while (current != NULL) {
            insertAtBeginning(&(new_table[hashFunction(current->key)]), current->key, current->data);
            current = current->next;
        }
    }
};

#endif //HW2_WET_HASHTABLE_H
