#ifndef ROTATEBST_H
#define ROTATEBST_H

#include "bst.h"
#include <iostream>
#include <unordered_set>
#include <cassert>

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value> {
public:
  bool sameKeys(const rotateBST<Key, Value> &t2) const;
  void transform(rotateBST<Key, Value> &t2) const;

protected:
  void leftRotate(Node<Key, Value> *r);
  void rightRotate(Node<Key, Value> *r);

private:
  void insertToHash(Node<Key, Value> *root, std::unordered_set<Key> &s) const;
  void updateHeight(Node<Key, Value> *root);
  void transformSubtree(rotateBST<Key, Value> &t2, Node<Key, Value> *root2,
                        Node<Key, Value> *root1) const;
};

template <typename Key, typename Value>
void rotateBST<Key, Value>::updateHeight(Node<Key, Value> *root) {
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

template <typename Key, typename Value>
void rotateBST<Key, Value>::insertToHash(Node<Key, Value> *root,
                                         std::unordered_set<Key> &s) const {
  if (!root) {
    return;
  }
  insertToHash(root->getLeft(), s);
  s.insert(root->getKey());
  insertToHash(root->getRight(), s);
}

template <typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST<Key, Value> &t2) const {
  Node<Key, Value> *root1 = this->mRoot;
  Node<Key, Value> *root2 = t2.mRoot;
  if (!root1 && !root2) {
    return true;
  }
  if ((root1 && !root2) || (!root1 && root2)) {
    return false;
  }
  std::unordered_set<Key> s1, s2;
  insertToHash(root1, s1);
  insertToHash(root2, s2);
  return (s1 == s2);
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::transformSubtree(rotateBST<Key, Value> &t2,
                                             Node<Key, Value> *root2,
                                             Node<Key, Value> *root1) const {
  if (root1 == NULL && root2 == NULL) {
    return;
  }
  if (root2->getLeft() == NULL) {
    while (root2->getKey() != root1->getKey()) {
      t2.rightRotate(root2);
      root2 = root2->getParent();
    }
  }
  else if (root2->getRight() == NULL) {
    while (root2->getKey() != root1->getKey()) {
      t2.leftRotate(root2);
      root2 = root2->getParent();
    }
  }

  transformSubtree(t2, root2->getRight(), root1->getRight());
  transformSubtree(t2, root2->getLeft(), root1->getLeft());
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST<Key, Value> &t2) const {
  if (!sameKeys(t2)) {
    return;
  }

  // Linearizing
  Node<Key, Value> *root = t2.mRoot;
  while (root != NULL) {
    while (root->getLeft() != NULL) {
      t2.rightRotate(root);
    }
    root = root->getRight();
  }

  // Moving root into position
  root = t2.mRoot;
  while (t2.mRoot->getKey() != this->mRoot->getKey()) {
    t2.leftRotate(root);
    root = t2.mRoot;
  }

  // Transforming subtrees
  transformSubtree(t2, root->getRight(), this->mRoot->getRight());
  transformSubtree(t2, root->getLeft(), this->mRoot->getLeft());
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value> *r) {
  if (r->getRight() == NULL) {
    return;
  }
  Node<Key, Value> *parent = r->getParent();
  Node<Key, Value> *newRoot = r->getRight();

  r->setRight(newRoot->getLeft());
  if (newRoot->getLeft() != NULL) {
    Node<Key, Value> *newRootLeft = newRoot->getLeft();
    newRootLeft->setParent(r);
  }

  newRoot->setLeft(r);
  r->setParent(newRoot);
  newRoot->setParent(parent);

  if (parent != NULL) {
    if (parent->getLeft() == r) {
      parent->setLeft(newRoot);
    } else {
      parent->setRight(newRoot);
    }
  } else {
    this->mRoot = newRoot;
  }

  this->updateHeight(r);
  return;
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value> *r) {
  if (r->getLeft() == NULL) {
    return;
  }
  Node<Key, Value> *parent = r->getParent();
  Node<Key, Value> *newRoot = r->getLeft();

  r->setLeft(newRoot->getRight());
  if (newRoot->getRight() != NULL) {
    Node<Key, Value> *newRootRight = newRoot->getRight();
    newRootRight->setParent(r);
  }

  newRoot->setRight(r);
  r->setParent(newRoot);
  newRoot->setParent(parent);

  if (parent != NULL) {
    if (parent->getLeft() == r) {
      parent->setLeft(newRoot);
    } else {
      parent->setRight(newRoot);
    }
  } else {
    this->mRoot = newRoot;
  }

  this->updateHeight(r);
  return;
}
#endif
