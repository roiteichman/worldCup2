//
// Created by teich on 27/11/2022.
//

#ifndef MAIN23A1_CPP_AVL_TREE_H
#define MAIN23A1_CPP_AVL_TREE_H
#include <iostream>

const bool BY_ABILITY = true;
const bool BY_IDS = false;


template <class T>
class RankNode {
private:
    RankNode();

    T     m_data;
    RankNode* m_left;
    RankNode* m_right;
    RankNode* m_parent;
    int m_height;
    int m_weight;

public:
    RankNode(const T& value) : m_data(value), m_left(nullptr), m_right(nullptr), m_parent(nullptr), m_height(0), m_weight(1) {}
    ~RankNode() {}

    const T&  getValue () const { return m_data; }
    void      setValue(T data) {m_data=data; }
    void      setLeft (RankNode* left) { m_left = left; }
    RankNode*  getLeft () const { return m_left; }
    void      setRight (RankNode* right) { m_right = right; }
    RankNode*  getRight () const { return m_right; }
    void      setParent (RankNode* parent) { m_parent = parent; }
    RankNode*  getParent () const { return m_parent; }
    void      removeData () { m_data = nullptr; }
    void      setHeight (int maxHeight) { m_height = maxHeight;}
    int       getHeight () const {return m_height;}
    int       getWeight() const {return m_weight;}
    void      increaseWeight () {m_weight++;}
    void      decreaseWeight () {m_weight--;}
    void      updateWeight () {
        if (m_right && m_left) {
            m_weight = 1 + m_right->m_weight + m_left->m_weight;
            return;
        }
        if (m_right) {
            m_weight = 1 + m_right->m_weight;
            return;
        }
        if (m_left) {
            m_weight = 1 + m_left->m_weight;
            return;
        }
        if (!m_left && !m_right){
            m_weight = 1;
            return;
        }
    }

};

template <class T>
class RankTree {
public:
    explicit RankTree(bool orderBy=true, RankNode<T>* root = nullptr) : m_orderBy(orderBy), m_root(root) {}
    ~RankTree();

    bool insert(const T& value);

    void setMRoot(RankNode<T> *mRoot);

    RankNode<T>* getRoot() const { return m_root; }

    RankNode<T>* find(RankNode<T>* root, const T& value);
    RankNode<T> *findInt(RankNode<T> *root, int value) const;
    void remove(RankNode<T>* root, const T& value);

    void findNext(RankNode<T>* leaf);
    void findPrevious(RankNode<T>* leaf);


    int  height(const RankNode<T>* root) const;
    int maxHeight (const RankNode<T>* root) const;
    int  balanceFactor(RankNode<T>* root) const;
    void balanceTheTree(RankNode<T>* root);
    RankNode<T>* select(int k, RankNode<T>* root);
    int weightLeftSon(RankNode<T>* root);

    void rotateLeft (RankNode<T>* B);
    void rotateRight(RankNode<T>* C);

    void printInOrderByID  (RankNode<T>* root, int *const output, int& i) ; // Left, Parent, Right
    void printInOrder  (RankNode<T>* root, T *const output, int& i) ; // Left, Parent, Right
    RankNode<T> *sortedArrayToAVL(T* arr, int start, int end);
    void insertRankNodeByAbility(RankNode<T>* root, RankNode<T>* newNode);
    void insertRankNodeByIds(RankNode<T>* root, RankNode<T>* newNode);



private:
    bool m_orderBy;
    RankNode<T>* m_root;
    void deleteRankNode(RankNode<T>* node);
};

template <class T>
RankTree<T>::~RankTree() {
    if( m_root ) {
        deleteRankNode(m_root);
    }
}

template <class T>
void RankTree<T>::deleteRankNode(RankNode<T>* node) {
    if( node ) {
        deleteRankNode(node->getLeft());
        deleteRankNode(node->getRight());
        node->removeData();
        delete node; // Post Order Deletion
    }
}

template <class T>
bool RankTree<T>::insert(const T& value) {
    RankNode<T> *newNode;
    try {
        newNode = new RankNode<T>(value);
    } catch (const std::bad_alloc &e) {
        return true; // Out of memory
    }

    if (!m_root) { // Special case the tree is empty
        m_root = newNode;
    }
    else {
        if (m_orderBy)
            insertRankNodeByAbility(m_root, newNode);
        else
            insertRankNodeByIds(m_root, newNode);
    }
    return false;
}

template <class T>
void RankTree<T>::insertRankNodeByAbility(RankNode<T>* root, RankNode<T>* newNode) {
    // if the node exist we catch it from outside
    // Binary Search Tree insertion algorithm
    // comparing by the value of the pointer
    if(*(newNode->getValue()) < *(root->getValue()) ) {
        if(root->getLeft() ) // If there is a left child, keep searching
            insertRankNodeByAbility(root->getLeft(), newNode);
        else { // Found the right spot
            root->setLeft(newNode);
            newNode->setParent(root);
        }
    }
    else {
        if(root->getRight() ) // If there is a right child, keep searching
            insertRankNodeByAbility(root->getRight(), newNode);
        else {// Found the right spot
            root->setRight(newNode);
            newNode->setParent(root);
        }
    }
    root->setHeight(maxHeight(root));
    root->increaseWeight();
    balanceTheTree(root);
}

template <class T>
void RankTree<T>::insertRankNodeByIds(RankNode<T> *root, RankNode<T> *newNode) {
    // if the node exist we catch it from outside
    // Binary Search Tree insertion algorithm
    // comparing by the value of the pointer
    if(*(newNode->getValue()) > *(root->getValue()) ) {
        if(root->getRight() ) // If there is a left child, keep searching
            insertRankNodeByIds(root->getRight(), newNode);
        else { // Found the right spot
            root->setRight(newNode);
            newNode->setParent(root);
        }
    }
    else {
        if(root->getLeft() ) // If there is a right child, keep searching
            insertRankNodeByIds(root->getLeft(), newNode);
        else {// Found the right spot
            root->setLeft(newNode);
            newNode->setParent(root);
        }
    }
    root->setHeight(maxHeight(root));
    root->increaseWeight();
    balanceTheTree(root);
}

template<class T>
int RankTree<T>::maxHeight(const RankNode<T> *root) const {
    return (height(root->getLeft()) > height(root->getRight())) ? height(root->getLeft())+1 : height(root->getRight()) +1;
}


template <class T>
int RankTree<T>::height(const RankNode<T>* root) const {
    if (root){
        return root->getHeight();
    }
    return -1;
}

template<class T>
void RankTree<T>::balanceTheTree(RankNode<T> *root) {
    // AVL balancing algorithm - Based on slide 14 on tutorial 5 in data structures
    int balance = balanceFactor(root);
    if( balance > 1 ) { // left tree unbalanced
        if(balanceFactor(root->getLeft()) < 0 ) { // right child of left tree is the cause
            rotateLeft(root->getLeft()); // double rotation required - means LR rotate
            root->getLeft()->getLeft()->setHeight(maxHeight(root->getLeft()->getLeft())); // update the height of B after changing pointers
            root->getLeft()->setHeight(maxHeight(root->getLeft())); // update the height of A
        }
        rotateRight(root); // LL rotate
        root->setHeight(maxHeight(root)); // update height of C
        root->getParent()->setHeight(maxHeight(root->getParent())); // update height of A
    }
    else if( balance < -1 ) { // right tree unbalanced
        if(balanceFactor(root->getRight()) > 0 ) { // left child of right tree is the cause
            rotateRight(root->getRight()); // RL rotate
            root->getRight()->getRight()->setHeight(maxHeight(root->getRight()->getRight())); // update the height of B after changing pointers
            root->getRight()->setHeight(maxHeight(root->getRight())); // update the height of A
        }
        rotateLeft(root); // RR rotate
        root->setHeight(maxHeight(root)); // update height of C
        root->getParent()->setHeight(maxHeight(root->getParent())); // update height of A
    }
}

template <class T>
void RankTree<T>::rotateLeft (RankNode<T>* B) {
    RankNode<T>* A = B->getRight();
    B->setRight(A->getLeft());
    B->updateWeight();
    if (B->getRight())
        B->getRight()->setParent(B);
    A->setLeft(B);
    A->updateWeight();
    A->setParent(B->getParent());


    if(B->getParent() == nullptr ) {
        m_root = A;
    }
    else {
        if(B->getParent()->getLeft() == B ) {
            B->getParent()->setLeft(A);
        }
        else {
            B->getParent()->setRight(A);
        }
    }
    B->setParent(A);
}

template <class T>
void RankTree<T>::rotateRight(RankNode<T>* C) {
    // Rotate node
    RankNode<T>* A = C->getLeft();
    C->setLeft(A->getRight());
    C->updateWeight();
    if (C->getLeft())
        C->getLeft()->setParent(C);
    A->setRight(C);
    A->updateWeight();

    // Adjust tree
    if(C->getParent() == nullptr ) {
        m_root = A;
        A->setParent(nullptr);
    }
    else {
        if(C->getParent()->getLeft() == C ) {
            C->getParent()->setLeft(A);
        }
        else {
            C->getParent()->setRight(A);
        }
        A->setParent(C->getParent());
    }

    C->setParent(A);
}

template <class T>
int  RankTree<T>::balanceFactor(RankNode<T>* root) const {
    int balance = 0;
    if( root ) {
        balance = height(root->getLeft()) - height(root->getRight());
    }
    return balance;
}

template<class T>
void RankTree<T>::findNext(RankNode<T> *leaf) {
    RankNode<T> *next = leaf;
    if (leaf->getRight() && leaf->getLeft()){
        leaf->getValue()->setClosestLeft(leaf->getLeft()->getValue().get());
        leaf->getLeft()->getValue()->setClosestRight(leaf->getValue().get());
        leaf->getValue()->setClosestRight(leaf->getRight()->getValue().get());
        leaf->getRight()->getValue()->setClosestLeft(leaf->getValue().get());
        return;}
    if (!(next->getParent())){
        return;
    }
    while (next->getParent()->getRight() == next) {
        next = next->getParent();
        if (!(next->getParent())){
            // means that we got to the root
            break;
        }
    }
    if(next->getParent()) {
        leaf->getValue()->setClosestRight(&(*next->getParent()->getValue()));
        next->getParent()->getValue()->setClosestLeft(&(*leaf->getValue()));
    }
}



template<class T>
void RankTree<T>::findPrevious(RankNode<T> *leaf) {
    RankNode<T> *next = leaf;
    if (!(next->getParent()) || (leaf->getRight() && leaf->getLeft())){
        return;
    }
    while (next->getParent()->getLeft() == next) {
        next = next->getParent();
        if (!(next->getParent())){
            // means that we got to the root
            break;
        }
    }
    if(next->getParent()) {
        leaf->getValue()->setClosestLeft(&(*next->getParent()->getValue()));
        next->getParent()->getValue()->setClosestRight(&(*leaf->getValue()));
    }
}

template <class T>
void RankTree<T>::printInOrderByID(RankNode<T>* root, int *const output, int& i) {
    if( root ) {
        printInOrderByID(root->getLeft(), output, i);  // Left
        output[i]=root->getValue()->getID(); // Parent
        i++;
        printInOrderByID(root->getRight(), output, i); // Right
    }
}

template <class T>
void RankTree<T>::printInOrder(RankNode<T>* root, T* const output, int& i) {
    if( root ) {
        printInOrder(root->getLeft(), output, i);  // Left
        output[i] = root->getValue(); // Parent
        i++;
        printInOrder(root->getRight(), output, i); // Right
    }
}


// Depth-First Search
template <class T>
RankNode<T>* RankTree<T>::find(RankNode<T>* root, const T& value) {
    bool byIDs = false;
    if (m_orderBy == byIDs){
        return findInt(root, value->getID());
    }
    if( root ) {
        //std::cout << root->getValue() << std::endl;
        if(root->getValue() == value )
            return root; // Found
        else if( *value < *(root->getValue()) )
            return find(root->getLeft(), value);
        else
            return find(root->getRight(), value);
    }

    return nullptr;
}
template <class T>
RankNode<T>* RankTree<T>::findInt(RankNode<T>* root, int value) const{
    if( root ) {
        //std::cout << root->getValue() << std::endl;
        if(root->getValue()->getID() == value )
            return root; // Found
        else if( value < root->getValue()->getID() )
            return findInt(root->getLeft(), value);
        else
            return findInt(root->getRight(), value);
    }

    return nullptr;
}


template<class T>
void RankTree<T>::remove(RankNode<T>* root, const T &value){

    RankNode<T>* willDeleted = find(root, value);
    if(!willDeleted)
        return;
    RankNode<T>* parent = willDeleted->getParent();

    bool removed = false;

    // 1: if is a leaf - height==0
    if (!height(willDeleted)) {
        // if is not a root
        if (parent){
            if (willDeleted == parent->getLeft()) {
                // after recursion the leaf is smaller than the parent but he is a right son of him
                parent->setLeft(nullptr);
                // if parent now is leaf
                if (!parent->getRight()){
                    parent->setHeight(0);
                }
            } else {
                parent->setRight(nullptr);
                // if parent now is leaf
                if (!parent->getLeft()){
                    parent->setHeight(0);
                }
            }
        }
            // if is the last junction in tree reset the tree, pointer to nullptr
        else
            m_root= nullptr;
        removed = true;
    }
    else if(willDeleted->getLeft() == nullptr || willDeleted->getRight() == nullptr) {
        RankNode<T> *singleSon;

        // 2: if it has a single son
        if (willDeleted->getLeft() == nullptr) {
            singleSon = willDeleted->getRight();
        } else if (willDeleted->getRight() == nullptr) {
            singleSon = willDeleted->getLeft();
        }
        if (parent) {
            if (willDeleted == parent->getLeft()) {
                // if willDeleted is a left son
                parent->setLeft(singleSon);
                singleSon->setParent(parent);
            } else {
                parent->setRight(singleSon);
                singleSon->setParent(parent);
            }
        }
        else {
            singleSon->setParent(parent);
            m_root = singleSon;
            removed = true;
        }
        willDeleted->setRight(nullptr);
        willDeleted->setLeft(nullptr);
        removed = true;
    }

    if (removed) {
        willDeleted->setParent(nullptr);
        deleteRankNode(willDeleted);
        while (parent) {
            parent->decreaseWeight();
            balanceTheTree(parent);
            parent = parent->getParent();
        }
    }

    // 3: if it is an internal junction
    if (!removed) {
        // searching for the next junction one step right and all the way down to the left
        RankNode<T>* nextJunction = willDeleted->getRight();
        //bool hasLeftSon = false;
        while (nextJunction->getLeft()) {
            nextJunction = nextJunction->getLeft();
            //hasLeftSon = true;
        }
        //change between the nodes
        willDeleted->setValue(nextJunction->getValue());
        nextJunction->setValue(value);
        remove(nextJunction, value);
    }
}


template <class T>
RankNode<T>* RankTree<T>::sortedArrayToAVL(T* arr, int start, int end)
{
    //Base Case
    if (start > end)
        return NULL;

    //Get the middle element and make it root
    int mid = (start + end)/2;
    RankNode<T> *root;
    try {
        root = new RankNode<T>(arr[mid]);
    }
    catch (const std::bad_alloc& e){
        return nullptr;
    }


    int height=0;
    //Recursively build the left subtree and make it left child of root
    root->setLeft(sortedArrayToAVL(arr, start, mid - 1));
    if(root->getLeft()) {
        root->getLeft()->setParent(root);
        height = root->getLeft()->getHeight()+1;
    }
    //Recursively build the right subtree and make it right child of root
    root->setRight(sortedArrayToAVL(arr, mid + 1, end));
    if(root->getRight()) {
        root->getRight()->setParent(root);
        height = height>root->getRight()->getHeight()+1 ? height : root->getRight()->getHeight()+1;
    }
    root->setHeight(height);
    return root;
}

template<class T>
void RankTree<T>::setMRoot(RankNode<T> *mRoot) {
    m_root = mRoot;
}

template<class T>
RankNode<T> *RankTree<T>::select(int k, RankNode<T>* root) {
    if (weightLeftSon(root)==k-1){
        return root;
    }
    else if(weightLeftSon(root)>k-1){
        root = root->getLeft();
        select(k, root);
    }
    else{
        int newK = k-weightLeftSon(root);
        root = root->getRight();
        select(newK, root);
    }
}
template<class T>
int RankTree<T>::weightLeftSon(RankNode<T>* root) {
    if (root->getLeft()){
        return root->getLeft()->getWeight();
    }
    else{
        return 0;
    }
}

#endif //MAIN23A1_CPP_AVL_TREE_H

