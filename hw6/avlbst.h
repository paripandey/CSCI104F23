#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void insertFix (AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node); // TODO
    virtual void removeFix (AVLNode<Key,Value>* node); // TODO
    virtual void rotateRight (AVLNode<Key,Value>* node);
    virtual void rotateLeft (AVLNode<Key,Value>* node);
    virtual AVLNode<Key, Value>* insertHelper(AVLNode<Key, Value>* root, const std::pair<const Key, Value>& keyValuePair);
    virtual void removeHelper(const Key& key);


};

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO

    AVLNode<Key,Value>* root = static_cast<AVLNode<Key, Value>*>(this->root_);
    root = insertHelper(root, new_item);

    this->root_ = root;

    AVLNode<Key,Value>* curr = static_cast<AVLNode<Key, Value>*>(this->internalFind(new_item.first));
    // curr->setHeight(this->height(curr));

    AVLNode<Key,Value>* parent = curr->getParent();
    int oldParentHeight = 0;
    int newParentHeight = 0;

    if (parent != NULL) {
        oldParentHeight = parent->getHeight();
        newParentHeight = this->height(parent);
    }

    if (oldParentHeight != newParentHeight) {
        insertFix(parent, curr);
    }
    
    
}


template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insertHelper(AVLNode<Key, Value>* root, const std::pair<const Key, Value>& keyValuePair)
{
    // TODO


    if (root == NULL) {
        AVLNode<Key, Value>* node = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        return node;
    }


    if (keyValuePair.first < root->getKey()) {
        root->Node<Key,Value>::setLeft(insertHelper(root->getLeft(), keyValuePair));
        root->getLeft()->Node<Key,Value>::setParent(root);

    }

    else if (keyValuePair.first > root->getKey()) {
        root->Node<Key,Value>::setRight(insertHelper(root->getRight(), keyValuePair));
        root->getRight()->Node<Key,Value>::setParent(root);
        
    }

    else {
        root->Node<Key,Value>::setValue(keyValuePair.second);
    }

    return root;
}


template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node) {

    
    // CHECKING IF THE PARENT OR THE GRANDPARENT IS NULL
    if (parent == NULL || parent->getParent() == NULL) {
        return;
    }

    AVLNode<Key,Value>* grandparent = parent->getParent();


    int gpOldHeight = grandparent->getHeight();
    int gpNewHeight = this->height(grandparent);


    // HAS THE GRANDPARENT'S HEIGHT CHANGED?
    if (gpOldHeight == gpNewHeight) {
        return;
    }

    // UPDATES THE GRANDPARENT's HEIGHT
    grandparent->setHeight(gpNewHeight);

    int gpLeftChildHeight = 0;
    int gpRightChildHeight = 0;

    if (grandparent->getLeft() != NULL) {
        grandparent->getLeft()->setHeight(this->height(grandparent->getLeft()));
         gpLeftChildHeight = grandparent->getLeft()->getHeight();
    }

    if (grandparent->getRight() != NULL) {
        grandparent->getRight()->setHeight(this->height(grandparent->getRight()));
        gpRightChildHeight = grandparent->getRight()->getHeight();
    }


    // CHECKS IF THE GRANDPARENT IS BALANCED
    if (abs(gpLeftChildHeight - gpRightChildHeight) <= 1) {    
        insertFix(grandparent, parent);
    }

    else {
        // WILL STORE THE GRANDPARENT'S CHILD OF GREATER HEIGHT
        AVLNode<Key,Value>* y = NULL;
        // TRACKS WHETHER THE LEFT CHILD OR THE RIGHT CHILD HAS THE GREATER HEIGHT
        int y_pos = -1;

        // WILL STORE THE PARENT'S CHILD OF GREATER HEIGHT
        // AVLNode<Key,Value>* x = NULL;
        
        // TRACKS WHETHER THE LEFT CHILD OR THE RIGHT CHILD HAS THE GREATER HEIGHT
        int x_pos = -1;
        
        // SIMPLY: y = parent;

        // FIND WHICH OF THE GRANDPARENT'S CHILDREN HAVE THE GREATER HEIGHT

        if (gpLeftChildHeight > gpRightChildHeight) {
            y = grandparent->getLeft();
            y_pos = 0; // LEFT CHILD
        }

        else {
            y = grandparent->getRight();
            y_pos = 1; // RIGHT CHILD
        }
        
        int pLeftChildHeight = 0;
        int pRightChildHeight = 0;

        if (parent->getLeft() != NULL) {
            pLeftChildHeight = parent->getLeft()->getHeight();
        }

        if (parent->getRight() != NULL) {
            pRightChildHeight = parent->getRight()->getHeight();
        }


        // DETERMINES WHICH OF PARENT'S CHILDREN HAS THE GREATER HEIGHT 
        if (pLeftChildHeight > pRightChildHeight) {
            //x = parent->getLeft();
            x_pos = 0; // LEFT CHILD
        }

        else {
            //x = parent->getRight();
            x_pos = 1; // RIGHT CHILD
        }

        
        // LEFT-LEFT ZIG-ZAG
        if (!y_pos && !x_pos) {
            rotateRight(grandparent);

        }

        // RIGHT-RIGHT ZIG-ZAG

        else if (y_pos && x_pos) {
            rotateLeft(grandparent);
        }

        // LEFT-RIGHT ZIG-ZAG

        else if (!y_pos && x_pos) {
            rotateLeft(y);
            // be careful of pointers changing
            rotateRight(grandparent);
        }

        // RIGHT-LEFT ZIG-ZAG
        else {
            // be careful of pointers changing
            rotateRight(y);
            rotateLeft(grandparent);
        }

        grandparent->setHeight(this->height(grandparent));
        y->setHeight(this->height(y));

    }
}



template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    removeHelper(key);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeHelper(const Key& key) {

    
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    
    // THE KEY WAS NOT FOUND
    if (curr == NULL) {
        return;
    }
    
    curr->setHeight(BinarySearchTree<Key,Value>::height(curr));



    // THE NODE WITH THE GIVEN KEY HAS 2 CHILDREN; SWAP WITH ITS SUCCESSOR
    if ((curr->getLeft() != NULL) && (curr->getRight() != NULL)) {
        AVLNode<Key,Value>* successor = static_cast<AVLNode<Key,Value>*>(this->successor(curr));
        successor->setHeight(BinarySearchTree<Key,Value>::height(successor));
        nodeSwap(curr, successor);
    }

    

    AVLNode<Key, Value>* parent = curr->getParent();


    BinarySearchTree<Key,Value>::removeHelper(key);

    if (parent != NULL) {
        parent->setHeight(this->height(parent));
    }

    removeFix(parent);

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* node) {
    if (node == NULL) {
        return;
    }

    int leftChildHeight = 0;
    int rightChildHeight = 0;

    if (node->getLeft() != NULL) {
        leftChildHeight = node->getLeft()->getHeight();
    }

    if (node->getRight() != NULL) {
        rightChildHeight = node->getRight()->getHeight();
    }

    if (abs(leftChildHeight - rightChildHeight) > 1) {

        AVLNode<Key,Value>* y = NULL;
        AVLNode<Key,Value>* x = NULL;
        AVLNode<Key,Value>* parent = node->getParent();

        // check for zig-zig
        if (leftChildHeight > rightChildHeight) {
            y = node->getLeft();
        }

        else if (leftChildHeight < rightChildHeight) {
            y = node->getRight();
        }

        int yLeftChildHeight = 0;
        int yRightChildHeight = 0;

        if (y->getLeft() != NULL) {
            yLeftChildHeight = y->getLeft()->getHeight();
        }

        if (y->getRight() != NULL) {
            yRightChildHeight = y->getRight()->getHeight();
        }

        if (yLeftChildHeight > yRightChildHeight) {
            x = y->getLeft();

            if (y == node->getLeft()) {
                rotateRight(node);
            }

            else {
                rotateRight(y);
                rotateLeft(node);
            }
        }

        else if (yLeftChildHeight < yRightChildHeight) {
            x = y->getRight();

            if (y == node->getRight()) {
                rotateLeft(node);
            }

            else {
                rotateLeft(y);
                rotateRight(node);
            }

        }

        else {

            if (y == node->getLeft() && y->getLeft() != NULL) {
                rotateRight(node);
            }

            else if (y == node->getRight() && y->getRight() != NULL) {
                rotateLeft(node);
            }

            else if (y == node->getLeft()) {
                rotateLeft(y);
                rotateRight(node);
            }

            else {
                rotateRight(y);
                rotateLeft(node);
            }

        }

        removeFix(parent);

    }

    else if (node->getHeight() != this->height(node)) {
        node->setHeight(this->height(node));
        removeFix(node->getParent());
    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* node) {

/*
 Define a right rotation as taking a left child, making it
the parent and making the original parent the new right
child
*/

    AVLNode<Key, Value>* y = node->getLeft();


    if (node->getParent() == NULL) {
        this->root_ = y;
    }

    else if (node->getKey() < node->getParent()->getKey()) {
        node->getParent()->Node<Key,Value>::setLeft(y);
    }

    else {
        node->getParent()->Node<Key,Value>::setRight(y);
    }
    
    y->Node<Key,Value>::setParent(node->getParent());
    node->Node<Key,Value>::setParent(y);
    node->Node<Key,Value>::setLeft(y->getRight());
    if (y->getRight() != NULL) {
        y->getRight()->Node<Key,Value>::setParent(node);
    }
    
    y->Node<Key,Value>::setRight(node);

   node->setHeight(BinarySearchTree<Key,Value>::height(node));
    y->setHeight(BinarySearchTree<Key,Value>::height(y));
    
    //y->getLeft()->setHeight(BinarySearchTree<Key,Value>::height(y->getLeft()));

    //this->print();

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* node) {


    AVLNode<Key, Value>* y = node->getRight();

    if (node->getParent() == NULL) {
       this->root_ = y;
    }

    else if (node->getKey() < node->getParent()->getKey()) {
        node->getParent()->Node<Key,Value>::setLeft(y);
    }

    else {
        node->getParent()->Node<Key,Value>::setRight(y);
    }

    y->Node<Key,Value>::setParent(node->getParent());
    node->Node<Key,Value>::setParent(y);
    node->Node<Key,Value>::setRight(y->getLeft());

    if (y->getLeft() != NULL) {
        y->getLeft()->Node<Key,Value>::setParent(node);
    }

    y->Node<Key,Value>::setLeft(node);

    node->setHeight(BinarySearchTree<Key,Value>::height(node));
    y->setHeight(BinarySearchTree<Key,Value>::height(y));
    //y->getRight()->setHeight(BinarySearchTree<Key,Value>::height(y->getRight()));
    //this->print();


}


#endif
