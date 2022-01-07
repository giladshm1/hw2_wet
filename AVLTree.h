
#ifndef WET2_AVLTREE_H
#define WET2_AVLTREE_H

#include<functional>
#include <iostream>

template<typename T>
class AVLTree {
    //=========== public types ================
public:
    typedef T *AVLValue;
    typedef std::function<void(AVLValue)> Action;
    typedef std::function<void(AVLValue, int *, int)> ActionWithParam;
    typedef std::function<int(AVLValue)> Predicate;
    typedef std::function<int(AVLValue, AVLValue)> Comparator;

    //=========== private types ================
private:
    struct Node {
        Node(AVLValue value) : value(value), parent(NULL), leftSon(NULL), rightSon(NULL), height(0) {}

        AVLValue value;
        Node *parent;
        Node *leftSon, *rightSon;
        int height;
    };

    //=========== private fields ================
    Node *root;
    int size;
    Comparator comparator;

    //=========== public methods (API) ================
public:
    AVLTree() = default;

    AVLTree(Comparator comparator);

    virtual ~AVLTree();

    bool Add(AVLValue value);

    AVLValue Remove(AVLValue value); //returns the value deleted or NULL if not found

    void ForEach(Action action, int maxElements = -1);

    AVLValue Find(Predicate predicate);

    AVLValue Find(AVLValue value);

    AVLValue FindHighest();

    //void TreeToArray(Player **arr);

    void DeleteTree();

    void ForEachPreorder(Action action);

    void ForEachArray(int maxElements, int *arr, ActionWithParam action);

    //void ArrayToTree(Player **arr, int st, int end);

    int GetSize();

    void printBT(Action action, const std::string &prefix, const Node *node, bool isLeft);

    void printBT(Action action);

    Node *ArrayToTreeAuxInt(int *arr, int st, int end);

    //AVLTree<Player> *ArrayToTreeInt(int *arr, int st, int end);


    //=========== private methods ================
private:
    void IterateUpwards(Node *node);

    AVLValue RemoveSmallestNodeInTree(Node *node);

    Node *InternalFind(Predicate predicate);

    Node *InternalFind(AVLValue value);

    void DoLLRotation(Node *node);

    void DoRRRotation(Node *node);

    static int GetNodeHeight(Node *node);

    static int GetNodeBalance(Node *node);

    static void RecursiveForEach(Node *node, Action action, int *iterationsLeft);

    AVLValue InternalRemove(Node *node);

    //void TreeToArrayAux(Node *node, Player **arr, int *counter);

    void DeleteTreeAux(Node *node);

    void RecursiveForEachPreorder(Node *node, Action action);

    static void
    RecursiveForEachArray(Node *node, int *iterationsLeft, int *arr, int *index, ActionWithParam action);

    //static AVLTree<T>::Node *ArrayToTreeAux(Player **arr, int st, int end);
};


template<typename T>
AVLTree<T>::AVLTree(Comparator comparator):root(NULL), size(0), comparator(comparator) {}

template<typename T>
bool AVLTree<T>::Add(AVLValue value) {
    Node *node = new Node(value);

    if (NULL == root) {
        root = node;
        this->size += 1;
        return true;
    }

    Node *parentCurr = root;
    Node *curr = root;
    while (curr != NULL) {
        parentCurr = curr;
        if (comparator(parentCurr->value, value) < 0)
            curr = parentCurr->rightSon;
        else
            curr = parentCurr->leftSon;
    }
    //here curr is null, and parentCurr is the new father
    node->parent = parentCurr;
    if (comparator(parentCurr->value, value) < 0)
        parentCurr->rightSon = node;
    else
        parentCurr->leftSon = node;
    IterateUpwards(parentCurr);
    this->size += 1;
    return true;
}

template<typename T>
typename AVLTree<T>::AVLValue AVLTree<T>::Remove(AVLTree<T>::AVLValue value) {
    Node *curr = InternalFind(value);
    if (curr != NULL) {
        this->size -= 1;
    }
    return InternalRemove(curr);
}

template<typename T>
typename AVLTree<T>::AVLValue AVLTree<T>::InternalRemove(AVLTree<T>::Node *node) {
    if (NULL == node)
        return NULL;

    AVLValue value = node->value;
    Node *parentCurr = node->parent;
    bool theLastSonIsRight = parentCurr == NULL ? false : parentCurr->rightSon == node;
    if (node->height == 0) // The node to remove is a leaf
    {
        if (parentCurr)
            theLastSonIsRight ? parentCurr->rightSon = NULL : parentCurr->leftSon = NULL;
        else
            root = NULL;
        delete node;
        IterateUpwards(parentCurr);
        return value;
    }
    if (node->leftSon == NULL || node->rightSon == NULL) // The node to remove has one son
    {
        Node *son = node->leftSon == NULL ? node->rightSon : node->leftSon;
        if (parentCurr)
            theLastSonIsRight ? parentCurr->rightSon = son : parentCurr->leftSon = son;
        son->parent = parentCurr;
        if (NULL == parentCurr)
            root = son;
        delete node;
        IterateUpwards(parentCurr);
        return value;
    }
    //then have two sons
    node->value = RemoveSmallestNodeInTree(node->rightSon);
    return value;
}

template<typename T>
typename AVLTree<T>::AVLValue AVLTree<T>::RemoveSmallestNodeInTree(AVLTree<T>::Node *node) {
    Node *curr = node;
    while (curr->leftSon != NULL)
        curr = curr->leftSon;
    AVLValue value = curr->value;
    InternalRemove(curr);
    return value;
}

template<typename T>
void AVLTree<T>::ForEach(Action action, int maxElements) {
    int iterationsLeft = maxElements;
    RecursiveForEach(root, action, &iterationsLeft);
}

template<typename T>
void AVLTree<T>::RecursiveForEach(Node *node, Action action, int *iterationsLeft) {
    if (NULL == node || iterationsLeft == 0)
        return;

    RecursiveForEach(node->leftSon, action, iterationsLeft);
    if (*iterationsLeft == 0)
        return;

    action(node->value);
    (*iterationsLeft)--;
    RecursiveForEach(node->rightSon, action, iterationsLeft);
}

template<typename T>
typename AVLTree<T>::AVLValue AVLTree<T>::Find(AVLTree<T>::Predicate predicate) {
    Node *findRes = InternalFind(predicate);
    if (NULL == findRes)
        return NULL;
    return findRes->value;
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::InternalFind(AVLTree<T>::Predicate predicate) {
    Node *curr = root;
    while (curr != NULL) {
        if (predicate(curr->value) == 0)
            return curr;
        if (predicate(curr->value) < 0)
            curr = curr->leftSon;
        else
            curr = curr->rightSon;
    }
    return NULL;
}

template<typename T>
typename AVLTree<T>::AVLValue AVLTree<T>::Find(AVLTree<T>::AVLValue value) {
    Node *findRes = InternalFind(value);
    if (NULL == findRes)
        return NULL;
    return findRes->value;
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::InternalFind(AVLTree<T>::AVLValue value) {
    return InternalFind([=](AVLValue currValue) { return comparator(value, currValue); });
}

template<typename T>
AVLTree<T>::~AVLTree() {

}

template<typename T>
int AVLTree<T>::GetSize() {
    return this->size;
}

template<typename T>
typename AVLTree<T>::AVLValue AVLTree<T>::FindHighest() {
    if (this->root == NULL) {
        return NULL;
    }

    Node *temp = this->root;
    while (temp->rightSon != NULL) {
        temp = temp->rightSon;
    }
    return temp->value;
}

static int MaxInt(int a, int b) {
    return a > b ? a : b;
}

/*
template<typename T>
void AVLTree<T>::TreeToArray(Player **arr) {
    if (this->root == NULL) {
        return;
    }

    int *counter = new int();
    *counter = 0;
    TreeToArrayAux(this->root, arr, counter);
    delete counter;
}


template<typename T>
void AVLTree<T>::TreeToArrayAux(Node *node, Player **arr, int *counter) {
    if (node == NULL) {
        return;
    }

    if (node->leftSon != NULL) {
        TreeToArrayAux(node->leftSon, arr, counter);
    }

    arr[*counter] = node->value;
    (*counter)++;

    if (node->rightSon != NULL) {
        TreeToArrayAux(node->rightSon, arr, counter);
    }
}*/

template<typename T>
void AVLTree<T>::ForEachPreorder(Action action) {
    RecursiveForEachPreorder(root, action);
}

template<typename T>
void AVLTree<T>::RecursiveForEachPreorder(Node *node, Action action) {
    if (NULL == node)
        return;

    RecursiveForEachPreorder(node->leftSon, action);
    RecursiveForEachPreorder(node->rightSon, action);
    action(node->value);
}

template<typename T>
void AVLTree<T>::ForEachArray(int maxElements, int *arr, ActionWithParam action) {
    int iterationsLeft = maxElements;
    int index = 0;
    RecursiveForEachArray(root, &iterationsLeft, arr, &index, action);
}

template<typename T>
void
AVLTree<T>::RecursiveForEachArray(Node *node, int *iterationsLeft, int *arr, int *index, ActionWithParam action) {
    if (NULL == node || iterationsLeft == 0)
        return;

    RecursiveForEachArray(node->leftSon, iterationsLeft, arr, index, action);
    if (*iterationsLeft == 0)
        return;

    action(node->value, arr, *index);
    (*index)++;

    (*iterationsLeft)--;
    RecursiveForEachArray(node->rightSon, iterationsLeft, arr, index, action);
}

/*
template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::ArrayToTreeAux(Player **arr, int st, int end) {
    if (st > end) {
        return NULL;
    }

    int middle = (st + end) / 2;
    Node *left_son = ArrayToTreeAux(arr, st, middle - 1);
    Node *right_son = ArrayToTreeAux(arr, middle + 1, end);

    Node *temp = new Node(arr[middle]);
    temp->leftSon = left_son;
    temp->rightSon = right_son;

    if (left_son != NULL) {
        left_son->parent = temp;
    }
    if (right_son != NULL) {
        right_son->parent = temp;
    }

    if (left_son == NULL && right_son == NULL) {
        temp->height = 0;
    }
    if (left_son != NULL && right_son == NULL) {
        temp->height = left_son->height + 1;
    }
    if (left_son == NULL && right_son != NULL) {
        temp->height = right_son->height + 1;
    }
    if (left_son != NULL && right_son != NULL) {
        temp->height = MaxInt(left_son->height, right_son->height) + 1;
    }

    return temp;
}

template<typename T>
void AVLTree<T>::ArrayToTree(Player **arr, int st, int end) {
    Node *temp = ArrayToTreeAux(arr, st, end);
    this->DeleteTreeAux(this->root);
    this->root = temp;
    this->size = end + 1;
}*/

template<typename T>
void AVLTree<T>::DeleteTreeAux(Node *node) {
    if (node == NULL) {
        return;
    }

    DeleteTreeAux(node->leftSon);
    DeleteTreeAux(node->rightSon);
    delete node;
}

template<typename T>
void AVLTree<T>::DeleteTree() {
    DeleteTreeAux(this->root);
}

template<typename T>
void AVLTree<T>::IterateUpwards(Node *node) {
    while (node != NULL) {
        node->height = 1 + MaxInt(GetNodeHeight(node->leftSon), GetNodeHeight(node->rightSon));
        if (GetNodeBalance(node) > 1) // Left Rotation
        {
            if (GetNodeBalance(node->leftSon) >= 0) // LL Rotation
            {
                DoLLRotation(node);
            } else // LR Rotation
            {
                Node *nodeToUpdateHeight = node->leftSon;
                DoRRRotation(node->leftSon);
                DoLLRotation(node);
                nodeToUpdateHeight->height =
                        1 + MaxInt(GetNodeHeight(node->leftSon), GetNodeHeight(node->rightSon));
            }
        } else if (GetNodeBalance(node) < -1) // Right Rotation
        {
            if (GetNodeBalance(node->rightSon) <= 0) // RR Rotation
            {
                DoRRRotation(node);
            } else // RL Rotation
            {
                Node *nodeToUpdateHeight = node->rightSon;
                DoLLRotation(node->rightSon);
                DoRRRotation(node);
                nodeToUpdateHeight->height =
                        1 + MaxInt(GetNodeHeight(node->leftSon), GetNodeHeight(node->rightSon));
            }
        } else {
            if (NULL == (node->parent))
                root = node;
            node = node->parent;
        }
    }
}

template<typename T>
void AVLTree<T>::DoLLRotation(AVLTree::Node *node) {
    Node *B = node;
    Node *A = node->leftSon;
    Node *A_r = A->rightSon;
    // The Rotation
    A->rightSon = B;
    A->parent = B->parent;
    if (A->parent != NULL)
        (B->parent->leftSon) == B ? A->parent->leftSon = A : A->parent->rightSon = A;
    B->parent = A;
    B->leftSon = A_r;
    if (A_r != NULL)
        A_r->parent = B;
}

template<typename T>
void AVLTree<T>::DoRRRotation(AVLTree::Node *node) {
    Node *B = node;
    Node *A = node->rightSon;
    Node *A_l = A->leftSon;
    // The Rotation
    A->leftSon = B;
    A->parent = B->parent;
    if (A->parent != NULL)
        (B->parent->leftSon) == B ? A->parent->leftSon = A : A->parent->rightSon = A;
    B->parent = A;
    B->rightSon = A_l;
    if (A_l != NULL)
        A_l->parent = B;
}

template<typename T>
int AVLTree<T>::GetNodeHeight(Node *node) {
    return NULL == node ? -1 : node->height;
}

template<typename T>
int AVLTree<T>::GetNodeBalance(Node *node) {
    /*if (NULL == node)
        return 0;*/
    return GetNodeHeight(node->leftSon) - GetNodeHeight(node->rightSon);
}


template<typename T>
void AVLTree<T>::printBT(Action action, const std::string &prefix, const Node *node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "|---" : "\\---");

        // print the value of the node
        //std::cout << *(node->value) << std::endl;
        action(node->value);
        std::cout << std::endl;

        // enter the next tree level - left and right branch
        printBT(action, prefix + (isLeft ? "|    " : "     "), node->rightSon, true);
        printBT(action, prefix + (isLeft ? "|    " : "     "), node->leftSon, false);
    }
}

template<typename T>
void AVLTree<T>::printBT(Action action) {
    if (NULL == root)
        std::cout << "The tree is empty.";
    else
        printBT(action, "", root, false);
}

/*
template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::ArrayToTreeAuxInt(int *arr, int st, int end) {
    if (st > end) {
        return NULL;
    }

    int middle = (st + end) / 2;
    Node *left_son = ArrayToTreeAux(arr, st, middle - 1);
    Node *right_son = ArrayToTreeAux(arr, middle + 1, end);

    Node *temp = new Node(arr[middle]);
    temp->leftSon = left_son;
    temp->rightSon = right_son;

    temp->height = MaxInt(left_son->height, right_son->height) + 1;

    left_son->parent = temp;
    right_son->parent = temp;

    return temp;
}*/

/*
template<typename T>
AVLTree<Player> *AVLTree<T>::ArrayToTreeInt(int *arr, int st, int end) {
    Node *temp = ArrayToTreeAux(arr, st, end);
    AVLTree<T> *res = new AVLTree<T>();
    res->root = temp;
    return res;
}
*/

#endif //WET2_AVLTREE_H
