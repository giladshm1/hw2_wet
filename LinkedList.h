//
// Created by gilad on 09/01/2022.
//

#ifndef HW2_WET_LINKEDLIST_H
#define HW2_WET_LINKEDLIST_H

// Linked list operations in C++


#include <iostream>

using namespace std;

// Create a node

template<class T>
struct Node {
    T *data;
    int key;
    struct Node<T> *next;
};

template<class T>
void insertAtBeginning(struct Node<T> **head_ref, int key, T *new_data) {
    // Allocate memory to a node
    auto *new_node = (struct Node<T> *) malloc(sizeof(struct Node<T>));

    // insert the data
    new_node->key = key;
    new_node->data = new_data;
    new_node->next = (*head_ref);

    // Move head to new node
    (*head_ref) = new_node;
}

// Insert a node after a node
template<class T>
void insertAfter(struct Node<T> *prev_node, int key, T *new_data) {
    if (prev_node == NULL) {
        //cout << "the given previous node cannot be NULL";
        return;
    }

    auto *new_node = (struct Node<T> *) malloc(sizeof(struct Node<T>));
    new_node->key = key;
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

// Insert at the end
template<class T>
void insertAtEnd(struct Node<T> **head_ref, int key, T *new_data) {
    struct Node<T> *new_node = (struct Node<T> *) malloc(sizeof(struct Node<T>));
    struct Node<T> *last = *head_ref;

    new_node->key = key;
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) last = last->next;

    last->next = new_node;
}

// Delete a node
template<class T>
void deleteNode(struct Node<T> **head_ref, int key) {
    struct Node<T> *temp = *head_ref, *prev;

    if (temp != NULL && temp->key == key) {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    // Find the key to be deleted
    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    // If the key is not present
    if (temp == NULL) return;

    // Remove the node
    prev->next = temp->next;

    free(temp);
}

// Search a node
template<class T>
T *searchNode(struct Node<T> **head_ref, int key) {
    struct Node<T> *current = *head_ref;

    while (current != NULL) {
        if (current->key == key) return current->data;
        current = current->next;
    }
    return NULL;
}

// Print the linked list
template<class T>
void printList(struct Node<T> *node) {
    while (node != NULL) {
        cout << *(node->data) << " ";
        node = node->next;
    }
}

#endif //HW2_WET_LINKEDLIST_H
