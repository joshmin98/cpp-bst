#ifndef ROTATEBST_H
#define ROTATEBST_H

#include "bst.h"
#include "unordered_set"


template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value> {
public:
  bool sameKeys(const rotateBST<Key, Value> &t2) const;
  void transform(rotateBST<Key, Value> &t2) const;

protected:
  void leftRotate(Node<Key, Value> *r);
  void rightRotate(Node<Key, Value> *r);

private:
  void insertToHash(Node<Key, Value> *root, std::unordered_set<Key> &s);
};

template <typename Key, typename Value>
void rotateBST<Key, Value>::insertToHash(Node<Key, Value> *root,
                                         std::unordered_set<Key> &s) {
}

template <typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST<Key, Value> &t2) const {
  return false;
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST<Key, Value> &t2) const {
  return;
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value> *r) {
  // TODO
  Node<Key, Value> *parent = r->getParent();
  Node<Key, Value> *grandparent = parent->getParent();
  Node<Key, Value> *temp = grandparent->getRight();
  grandparent->setRight(temp->getLeft());
  temp->setLeft(grandparent);
  Node<Key, Value> *greatgrandparent = grandparent->getParent();
  if (greatgrandparent->getLeft() == grandparent) {
    greatgrandparent->setLeft(temp);
  } else {
    greatgrandparent->setRight(temp);
  }
  grandparent->setParent(temp);
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value> *r) {
  // TODO
}
#endif
