#include <iostream>
#include "HashTable.h"
#include "UnionFind.h"
#include "LinkedList.h"


int PtrIntComparator(AVLTree<int>::AVLValue num1, AVLTree<int>::AVLValue num2) {
    return Compare(*num1, *num2);
}

int main() {
    /*
    struct Node<int> *head = NULL;

    int n1 = 1, n2 = 2, n3 = 3, n4 = 4, n5 = 5;
    insertAtEnd(&head, &n1);
    insertAtBeginning(&head, &n2);
    insertAtBeginning(&head, &n3);
    insertAtEnd(&head, &n4);
    insertAfter(head->next, &n5);

    cout << "Linked list: ";
    printList(head);

    int item_to_find = 3;
    if (searchNode(&head, &item_to_find)) {
        cout << endl << item_to_find << " is found";
    } else {
        cout << endl << item_to_find << " is not found";
    }

    cout << "\nAfter deleting an element: ";
    deleteNode(&head, &n3);
    printList(head);

    if (searchNode(&head, &item_to_find)) {
        cout << endl << item_to_find << " is found";
    } else {
        cout << endl << item_to_find << " is not found";
    }
*/

    UnionFind* uf = new UnionFind(5);
    Group *g1 = uf->Find(2);
    Group *g2 = uf->Find(3);
    uf->Union(g1, g2);
    Group *g3 = uf->Find(2);
    Group *g4 = uf->Find(3);
    uf->Union(g3, g4);
    Group *g5 = uf->Find(3);
    Group *g6 = uf->Find(4);






    // array that contains keys to be mapped
    int a[] = {14, 13, 27, 8, 12, 18, 15};
    int n = sizeof(a) / sizeof(a[0]);

    // insert the keys into the hash table
    auto *h = new HashTable<int>();
    for (int i = 0; i < n; i++)
        h->insertItem(a[i], &(a[i]));

    if (h->findItem(12) != NULL) {
        cout << endl << "found";
    } else {
        cout << endl << "not found";
    }

    // delete 12 from hash table
    h->deleteItem(12);

    if (h->findItem(12) != NULL) {
        cout << endl << "found";
    } else {
        cout << endl << "not found";
    }

    // display the Hash table
    //h.displayHash();

    return 0;
}
