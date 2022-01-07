#include <iostream>
#include "HashTable.h"

template<typename T>
int Compare(T val1, T val2) {
    if (val1 < val2)
        return -1;
    if (val2 < val1)
        return 1;
    return 0;
}

int PtrIntComparator(AVLTree<int>::AVLValue num1, AVLTree<int>::AVLValue num2) {
    return Compare(*num1, *num2);
}

int main() {
    // array that contains keys to be mapped
    int a[] = {14, 13, 27, 8, 12, 18, 15};
    int n = sizeof(a) / sizeof(a[0]);

    // insert the keys into the hash table
    auto *h = new HashTable<int>(PtrIntComparator);
    for (int i = 0; i < n; i++)
        h->insertItem(a[i], &(a[i]));

    std::cout << "found:" << *(h->findItem(12, &(a[4])));

    // delete 12 from hash table
    h->deleteItem(12, &(a[4]));

    // display the Hash table
    //h.displayHash();

    return 0;
}
