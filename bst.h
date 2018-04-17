#ifndef BST_H
#define BST_H

#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>

/**
 * A templated class for a Node in a search tree. The getters for
 * parent/left/right are virtual so that they can be overridden for future kinds
 * of search trees, such as Red Black trees, Splay trees, and AVL trees.
 */
template <typename Key, typename Value> class Node {
public:
  Node(const Key &key, const Value &value, Node<Key, Value> *parent);
  virtual ~Node();

  const std::pair<const Key, Value> &getItem() const;
  std::pair<const Key, Value> &getItem();
  const Key &getKey() const;
  const Value &getValue() const;
  Value &getValue();

  virtual Node<Key, Value> *getParent() const;
  virtual Node<Key, Value> *getLeft() const;
  virtual Node<Key, Value> *getRight() const;
  int getHeight() const;

  void setParent(Node<Key, Value> *parent);
  void setLeft(Node<Key, Value> *left);
  void setRight(Node<Key, Value> *right);
  void setValue(const Value &value);
  void setHeight(int height);

protected:
  std::pair<const Key, Value> mItem;
  Node<Key, Value> *mParent;
  Node<Key, Value> *mLeft;
  Node<Key, Value> *mRight;
  int mHeight;
};

/*
        -----------------------------------------
        Begin implementations for the Node class.
        -----------------------------------------
*/

/**
 * Explicit constructor for a node.
 */
template <typename Key, typename Value>
Node<Key, Value>::Node(const Key &key, const Value &value,
                       Node<Key, Value> *parent)
    : mItem(key, value), mParent(parent), mLeft(NULL), mRight(NULL),
      mHeight(1) {}

/**
 * Destructor, which does not need to do anything since the pointers inside of a
 * node are only used as references to existing nodes. The nodes pointed to by
 * parent/left/right are freed within the deleteAll() helper method in the
 * BinarySearchTree.
 */
template <typename Key, typename Value> Node<Key, Value>::~Node() {}

/**
 * A const getter for the item.
 */
template <typename Key, typename Value>
const std::pair<const Key, Value> &Node<Key, Value>::getItem() const {
  return mItem;
}

/**
 * A non-const getter for the item.
 */
template <typename Key, typename Value>
std::pair<const Key, Value> &Node<Key, Value>::getItem() {
  return mItem;
}

/**
 * A const getter for the key.
 */
template <typename Key, typename Value>
const Key &Node<Key, Value>::getKey() const {
  return mItem.first;
}

/**
 * A const getter for the value.
 */
template <typename Key, typename Value>
const Value &Node<Key, Value>::getValue() const {
  return mItem.second;
}

/**
 * A non-const getter for the value.
 */
template <typename Key, typename Value> Value &Node<Key, Value>::getValue() {
  return mItem.second;
}

/**
 * An implementation of the virtual function for retreiving the parent.
 */
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getParent() const {
  return mParent;
}

/**
 * An implementation of the virtual function for retreiving the left child.
 */
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getLeft() const {
  return mLeft;
}

/**
 * An implementation of the virtual function for retreiving the right child.
 */
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getRight() const {
  return mRight;
}

/**
 * A const getter for the height.
 */
template <typename Key, typename Value>
int Node<Key, Value>::getHeight() const {
  return mHeight;
}

/**
 * A setter for setting the parent of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value> *parent) {
  mParent = parent;
}

/**
 * A setter for setting the left child of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value> *left) {
  mLeft = left;
}

/**
 * A setter for setting the right child of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value> *right) {
  mRight = right;
}

/**
 * A setter for the value of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setValue(const Value &value) {
  mItem.second = value;
}

/**
 * A setter for the height of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) {
  mHeight = height;
}

/*
        ---------------------------------------
        End implementations for the Node class.
        ---------------------------------------
*/

/**
 * A templated unbalanced binary search tree.
 */
template <typename Key, typename Value> class BinarySearchTree {
public:
  BinarySearchTree();          // TODO
  virtual ~BinarySearchTree(); // TODO
  int height();                // TODO
  bool isBalanced();           // TODO
  bool isBalancedHelper(Node<Key, Value> *root);
  virtual void insert(const std::pair<const Key, Value> &keyValuePair); // TODO
  virtual void remove(const Key &key);                                  // TODO
  void clear();                                                         // TODO
  void print() const;

private:
  void updateHeight(Node<Key, Value> *root);

public:
  /**
   * An internal iterator class for traversing the contents of the BST.
   */
  class iterator {
  public:
    iterator(Node<Key, Value> *ptr);
    iterator();

    std::pair<const Key, Value> &operator*();
    std::pair<const Key, Value> *operator->();

    bool operator==(const iterator &rhs) const;
    bool operator!=(const iterator &rhs) const;
    iterator &operator=(const iterator &rhs);

    iterator &operator++();

  protected:
    Node<Key, Value> *mCurrent;
  };

public:
  iterator begin();
  iterator end();
  iterator find(const Key &key) const;

protected:
  Node<Key, Value> *internalFind(const Key &key) const; // TODO
  Node<Key, Value> *getSmallestNode() const;            // TODO
  void printRoot(Node<Key, Value> *root) const;

protected:
  Node<Key, Value> *mRoot;
};

/*
        ---------------------------------------------------------------
        Begin implementations for the BinarySearchTree::iterator class.
        ---------------------------------------------------------------
*/

/**
 * Explicit constructor that initializes an iterator with a given node pointer.
 */
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key, Value> *ptr)
    : mCurrent(ptr) {}

/**
 * A default constructor that initializes the iterator to NULL.
 */
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator() : mCurrent(NULL) {}

/**
 * Provides access to the item.
 */
template <typename Key, typename Value>
std::pair<const Key, Value> &BinarySearchTree<Key, Value>::iterator::
operator*() {
  return mCurrent->getItem();
}

/**
 * Provides access to the address of the item.
 */
template <typename Key, typename Value>
std::pair<const Key, Value> *BinarySearchTree<Key, Value>::iterator::
operator->() {
  return &(mCurrent->getItem());
}

/**
 * Checks if 'this' iterator's internals have the same value
 * as 'rhs'
 */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::
operator==(const BinarySearchTree<Key, Value>::iterator &rhs) const {
  return this->mCurrent == rhs.mCurrent;
}

/**
 * Checks if 'this' iterator's internals have a different value
 * as 'rhs'
 */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::
operator!=(const BinarySearchTree<Key, Value>::iterator &rhs) const {
  return this->mCurrent != rhs.mCurrent;
}

/**
 * Sets one iterator equal to another iterator.
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &
BinarySearchTree<Key, Value>::iterator::
operator=(const BinarySearchTree<Key, Value>::iterator &rhs) {
  this->mCurrent = rhs.mCurrent;
  return *this;
}

/**
 * Advances the iterator's location using an in-order traversal.
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &
BinarySearchTree<Key, Value>::iterator::operator++() {
  if (mCurrent->getRight() != NULL) {
    mCurrent = mCurrent->getRight();
    while (mCurrent->getLeft() != NULL) {
      mCurrent = mCurrent->getLeft();
    }
  } else if (mCurrent->getRight() == NULL) {
    Node<Key, Value> *parent = mCurrent->getParent();
    while (parent != NULL && mCurrent == parent->getRight()) {
      mCurrent = parent;
      parent = parent->getParent();
    }
    mCurrent = parent;
  }
  return *this;
}

/*
        -------------------------------------------------------------
        End implementations for the BinarySearchTree::iterator class.
        -------------------------------------------------------------
*/

/*
        -----------------------------------------------------
        Begin implementations for the BinarySearchTree class.
        -----------------------------------------------------
*/

/**
 * Default constructor for a BinarySearchTree, which sets the root to NULL.
 */
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() {
  mRoot = NULL;
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() {
  clear();
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const {
  printRoot(mRoot);
  std::cout << "\n";
}

/**
 * Returns an iterator to the "smallest" item in the tree
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() {
  BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
  return begin;
}

/**
 * Returns an iterator whose value means INVALID
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() {
  BinarySearchTree<Key, Value>::iterator end(NULL);
  return end;
}

/**
 * Returns an iterator to the item with the given key, k
 * or the end iterator if k does not exist in the tree
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key &key) const {
  Node<Key, Value> *curr = internalFind(key);
  BinarySearchTree<Key, Value>::iterator it(curr);
  return it;
}

/**
 * An method to return the height of the BST.
 */
template <typename Key, typename Value>
int BinarySearchTree<Key, Value>::height() {
  if (mRoot == NULL) {
    return 0;
  }
  return mRoot->getHeight();
}

/**
 * Helper method for isBalanced()
 */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value> *root) {
  int leftHeight, rightHeight;
  if (root == NULL) {
    return true;
  }
  Node<Key, Value> *left = root->getLeft();
  Node<Key, Value> *right = root->getRight();
  if (left == NULL) {
    leftHeight = 0;
  } else {
    leftHeight = left->getHeight();
  }
  if (right == NULL) {
    rightHeight = 0;
  } else {
    rightHeight = right->getHeight();
  }
  if (abs(leftHeight - rightHeight) <= 1 && isBalancedHelper(root->getLeft()) &&
      isBalancedHelper(root->getRight())) {
    return true;
  }
  return false;
}

/**
 * An method to checks if the BST is balanced. This method returns true if and
 * only if the BST is balanced.
 */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() {
  return isBalancedHelper(mRoot);
}

/**
 * A method used to calculate the height of subtrees.
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::updateHeight(Node<Key, Value> *root) {
  while (root != NULL) {
    Node<Key, Value> *right = root->getRight();
    Node<Key, Value> *left = root->getLeft();
    int rightHeight, leftHeight;
    if (right == NULL) {
      rightHeight = 0;
    } else {
      rightHeight = right->getHeight();
    }
    if (left == NULL) {
      leftHeight = 0;
    } else {
      leftHeight = left->getHeight();
    }
    if (leftHeight > rightHeight) {
      root->setHeight(leftHeight + 1);
    } else {
      root->setHeight(rightHeight + 1);
    }
    root = root->getParent();
  }
}

/**
 * An insert method to insert into a Binary Search Tree. The tree will not
 * remain balanced when inserting.
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(
    const std::pair<const Key, Value> &keyValuePair) {
  if (internalFind(keyValuePair.first) != NULL) {
    return;
  }

  if (mRoot == NULL) {
    mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
    return;
  }

  Node<Key, Value> *newNode =
      new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
  Node<Key, Value> *it = mRoot;
  while (it != NULL) {
    if (newNode->getKey() > it->getKey()) {
      if (it->getRight() == NULL) {
        newNode->setParent(it);
        it->setRight(newNode);
        break;
      }
      it = it->getRight();
    } else if (newNode->getKey() < it->getKey()) {
      if (it->getLeft() == NULL) {
        newNode->setParent(it);
        it->setLeft(newNode);
        break;
      }
      it = it->getLeft();
    }
  }
  updateHeight(it);
}

/**
 * An remove method to remove a specific key from a Binary Search Tree. The tree
 * may not remain balanced after removal.
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key &key) {
  // Case 0: Node not in tree
  Node<Key, Value> *removeNode = internalFind(key);
  if (removeNode == NULL) {
    return;
  }

  // Case 1: Leaf Node
  if (removeNode->getLeft() == NULL && removeNode->getRight() == NULL) {
    Node<Key, Value> *parent = removeNode->getParent();
    if (parent == NULL) {
      delete removeNode;
      mRoot = NULL;
      return;
    }

    if (parent->getLeft() == removeNode) {
      parent->setLeft(NULL);
    } else {
      parent->setRight(NULL);
    }

    delete removeNode;
    updateHeight(parent);
  }

  // Case 2: One left child
  else if (removeNode->getRight() == NULL) {
    Node<Key, Value> *parent = removeNode->getParent();
    Node<Key, Value> *newChild = removeNode->getLeft();
    if (parent != NULL) {
      if (parent->getRight() == removeNode) {
        parent->setRight(newChild);
      } else {
        parent->setLeft(newChild);
      }
    } else {
      mRoot = newChild;
    }

    newChild->setParent(parent);

    delete removeNode;
    if (parent != NULL) {
      updateHeight(parent);
    }
  }

  // Case 3: One right child
  else if (removeNode->getLeft() == NULL) {
    Node<Key, Value> *parent = removeNode->getParent();
    Node<Key, Value> *newChild = removeNode->getRight();
    if (parent != NULL) {
      if (parent->getRight() == removeNode) {
        parent->setRight(newChild);
      } else {
        parent->setLeft(newChild);
      }
    } else {
      mRoot = newChild;
    }

    newChild->setParent(parent);

    delete removeNode;
    if (parent != NULL) {
      updateHeight(parent);
    }
  }

  // Case 4: Two children
  else {
    Node<Key, Value> *pred = removeNode->getLeft();
    while (pred->getRight() != NULL) {
      pred = pred->getRight();
    }

    Node<Key, Value> *removeNodeParent = removeNode->getParent();
    Node<Key, Value> *predParent = pred->getParent();

    predParent->setRight(NULL);
    Node<Key, Value> *newRoot = new Node<Key, Value>(
        pred->getKey(), pred->getValue(), removeNodeParent);
    newRoot->setRight(removeNode->getRight());
    newRoot->setLeft(removeNode->getLeft());
    if (removeNodeParent != NULL) {
      if (removeNodeParent->getRight() == removeNode) {
        removeNodeParent->setRight(newRoot);
      } else {
        removeNodeParent->setLeft(newRoot);
      }
    }
    Node<Key, Value> *left = removeNode->getLeft();
    Node<Key, Value> *right = removeNode->getRight();
    if (left != NULL) {

      left->setParent(newRoot);
    }
    if (right != NULL) {

      right->setParent(newRoot);
    }
    newRoot->setParent(removeNodeParent);
    delete removeNode;

    if (predParent->getRight() == pred) {
      predParent->setRight(pred->getLeft());
    } else {
      predParent->setLeft(pred->getLeft());
    }

    if (newRoot->getParent() == NULL) {
      mRoot = newRoot;
    }

    delete pred;
    if (newRoot == mRoot) {
      updateHeight(newRoot);
    }
    updateHeight(predParent);
  }
}

/**
 * A method to remove all contents of the tree and reset the values in the tree
 * for use again.
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear() {
  Node<Key, Value> *removeNode = getSmallestNode();
  while (removeNode != NULL) {
    remove(removeNode->getKey());
    removeNode = getSmallestNode();
  }
  mRoot = NULL;
}

/**
 * A helper function to find the smallest node in the tree.
 */
template <typename Key, typename Value>
Node<Key, Value> *BinarySearchTree<Key, Value>::getSmallestNode() const {
  // DONE
  Node<Key, Value> *smallest = mRoot;
  while (smallest != NULL) {
    smallest = smallest->getLeft();
  }
  return smallest;
}

/**
 * Helper function to find a node with given key, k and
 * return a pointer to it or NULL if no item with that key
 * exists
 */
template <typename Key, typename Value>
Node<Key, Value> *
BinarySearchTree<Key, Value>::internalFind(const Key &key) const {
  // DONE
  Node<Key, Value> *it = mRoot;
  while (it != NULL) {
    if (key > it->getKey()) {
      it = it->getRight();
    } else if (key < it->getKey()) {
      it = it->getLeft();
    } else {
      return it;
    }
  }
  return NULL;
}

/**
 * Helper function to print the tree's contents
 */
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot(Node<Key, Value> *root) const {
  if (root != NULL) {
    std::cout << "[";
    printRoot(root->getLeft());
    std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
    printRoot(root->getRight());
    std::cout << "]";
  }
}

/*
        ---------------------------------------------------
        End implementations for the BinarySearchTree class.
        ---------------------------------------------------
*/

#endif
