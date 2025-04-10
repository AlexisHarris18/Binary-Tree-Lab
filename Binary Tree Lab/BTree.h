#include <iostream>
#include <memory>
using namespace std;

template <typename T>
struct Node {
    T data;
    shared_ptr<Node<T>> left;
    shared_ptr<Node<T>> right;
};

template <typename T>
class BTree {
public:
    void insert(const T& item);
    void remove(const T& item);
    void preOrder();
    void inOrder();
    void postOrder();
    int nodeCount();
    int leavesCount();

    shared_ptr<Node<T>> find(const T& item);
    shared_ptr<Node<T>> findRightMostNode(shared_ptr<Node<T>> ptr);
    shared_ptr<Node<T>> findParent(shared_ptr<Node<T>> ptr);

private:
    void preOrder(shared_ptr<Node<T>> ptr);
    void inOrder(shared_ptr<Node<T>> ptr);
    void postOrder(shared_ptr<Node<T>> ptr);
    void insert(const T& item, shared_ptr<Node<T>>& ptr);
    int nodeCount(shared_ptr<Node<T>> ptr);
    int leavesCount(shared_ptr<Node<T>> ptr);
    shared_ptr<Node<T>> find(const T& item, shared_ptr<Node<T>> ptr);
    void remove(shared_ptr<Node<T>>& ptr, const T& item);

    shared_ptr<Node<T>> root;
};

// Public insert
template <typename T>
void BTree<T>::insert(const T& item) {
    insert(item, root);
}

// Private insert
template <typename T>
void BTree<T>::insert(const T& item, shared_ptr<Node<T>>& ptr) {
    if (!ptr) {
        ptr = make_shared<Node<T>>(Node<T>{item});
    }
    else if (item < ptr->data) {
        insert(item, ptr->left);
    }
    else {
        insert(item, ptr->right);
    }
}

// Traversals
template <typename T>
void BTree<T>::preOrder() {
    preOrder(root);
    cout << endl;
}

template <typename T>
void BTree<T>::preOrder(shared_ptr<Node<T>> ptr) {
    if (!ptr) return;
    cout << ptr->data << " ";
    preOrder(ptr->left);
    preOrder(ptr->right);
}

template <typename T>
void BTree<T>::inOrder() {
    inOrder(root);
    cout << endl;
}

template <typename T>
void BTree<T>::inOrder(shared_ptr<Node<T>> ptr) {
    if (!ptr) return;
    inOrder(ptr->left);
    cout << ptr->data << " ";
    inOrder(ptr->right);
}

template <typename T>
void BTree<T>::postOrder() {
    postOrder(root);
    cout << endl;
}

template <typename T>
void BTree<T>::postOrder(shared_ptr<Node<T>> ptr) {
    if (!ptr) return;
    postOrder(ptr->left);
    postOrder(ptr->right);
    cout << ptr->data << " ";
}

// Node count
template <typename T>
int BTree<T>::nodeCount() {
    return nodeCount(root);
}

template <typename T>
int BTree<T>::nodeCount(shared_ptr<Node<T>> ptr) {
    if (!ptr) return 0;
    return 1 + nodeCount(ptr->left) + nodeCount(ptr->right);
}

// Leaves count
template <typename T>
int BTree<T>::leavesCount() {
    return leavesCount(root);
}

template <typename T>
int BTree<T>::leavesCount(shared_ptr<Node<T>> ptr) {
    if (!ptr) return 0;
    if (!ptr->left && !ptr->right) return 1;
    return leavesCount(ptr->left) + leavesCount(ptr->right);
}

// Find
template <typename T>
shared_ptr<Node<T>> BTree<T>::find(const T& item) {
    return find(item, root);
}

template <typename T>
shared_ptr<Node<T>> BTree<T>::find(const T& item, shared_ptr<Node<T>> ptr) {
    if (!ptr || ptr->data == item) return ptr;
    if (item < ptr->data) return find(item, ptr->left);
    return find(item, ptr->right);
}

// Find rightmost node
template <typename T>
shared_ptr<Node<T>> BTree<T>::findRightMostNode(shared_ptr<Node<T>> ptr) {
    if (!ptr) return nullptr;
    while (ptr->right) ptr = ptr->right;
    return ptr;
}

// Find parent
template <typename T>
shared_ptr<Node<T>> BTree<T>::findParent(shared_ptr<Node<T>> target) {
    if (!root || root == target) return nullptr;
    shared_ptr<Node<T>> parent = nullptr;
    shared_ptr<Node<T>> current = root;
    while (current && current != target) {
        parent = current;
        if (target->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return (current == target) ? parent : nullptr;
}

// Remove
template <typename T>
void BTree<T>::remove(const T& item) {
    remove(root, item);
}

template <typename T>
void BTree<T>::remove(shared_ptr<Node<T>>& ptr, const T& item) {
    if (!ptr) return;

    if (item < ptr->data) {
        remove(ptr->left, item);
    }
    else if (item > ptr->data) {
        remove(ptr->right, item);
    }
    else {
        if (!ptr->left) {
            ptr = ptr->right;
        }
        else if (!ptr->right) {
            ptr = ptr->left;
        }
        else {
            shared_ptr<Node<T>> maxNode = findRightMostNode(ptr->left);
            ptr->data = maxNode->data;
            remove(ptr->left, maxNode->data);
        }
    }
}
