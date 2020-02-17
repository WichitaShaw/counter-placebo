#pragma once

#include <iostream>

//debug
//#define DEBUG

namespace js
{

  template <typename S>
  struct BSTNode 
  {

    BSTNode* left = nullptr;
    BSTNode* right = nullptr;
    S value;

  };


  template <typename S>
  class BinarySearchTree
  {
    using BSTNodeType = BSTNode<S>;

    BSTNodeType* pRoot = nullptr;

  public:
    BinarySearchTree() = default;
    ~BinarySearchTree();

    BinarySearchTree(const BinarySearchTree& rhs);
    BinarySearchTree& operator=(const BinarySearchTree<S>& rhs);

    BinarySearchTree(BinarySearchTree&& rhs);
    BinarySearchTree& operator=(BinarySearchTree&& rhs);

  public:
    BSTNodeType* newNode(const S& data);
    BSTNodeType* copySubTree(const BSTNodeType* root);
    void deleteSubTree(BSTNodeType*& root);
    BSTNodeType* insert(const S& data);
    bool search(const S& data) const;

  private:
    BSTNodeType* insert(const S& data, BSTNodeType*& root);
    bool search(const S& data, const BSTNodeType* root) const;

  };


  template <typename S>
  BinarySearchTree<S>::~BinarySearchTree()
  {
    deleteSubTree(pRoot);
  }


  template <typename S>
  BinarySearchTree<S>::BinarySearchTree(const BinarySearchTree& rhs)
  {
    pRoot = copySubTree(rhs.pRoot);
  }


  template <typename S>
  BinarySearchTree<S>& BinarySearchTree<S>::operator=(const BinarySearchTree& rhs)
  {
    deleteSubTree(pRoot);
    pRoot = copySubTree(rhs.pRoot);
    return *this;
  }


  template <typename S>
  BinarySearchTree<S>::BinarySearchTree(BinarySearchTree&& rhs)
  {
    pRoot = rhs.pRoot;
    rhs.pRoot = nullptr;
  }


  template <typename S>
  BinarySearchTree<S>& BinarySearchTree<S>::operator=(BinarySearchTree&& rhs)
  {
    deleteSubTree(pRoot);
    pRoot = rhs.pRoot;
    rhs.pRoot = nullptr;
    return *this;
  }


  template <typename S>
  BSTNode<S>* BinarySearchTree<S>::newNode(const S& data)
  {
    BSTNodeType* result = new BSTNodeType();
    result->value = data;
    return result;
  }


  template <typename S>
  BSTNode<S>* BinarySearchTree<S>::copySubTree(const BSTNodeType* root)
  {
    if (!root)
      return nullptr;
    auto* result = newNode(root->value);
    result->left = copySubTree(root->left);
    result->right = copySubTree(root->right);
    return result;
  }


  template <typename S>
  void BinarySearchTree<S>::deleteSubTree(BSTNodeType*& root)
  {
    if (!root)
      return;

    auto*& left = root->left;
    auto*& right = root->right;

#ifdef DEBUG
    std::cout << "deleting value: " << root->value << '\n';
#endif

    delete root;

    deleteSubTree(left);
    deleteSubTree(right);
  }


  template <typename S>
  BSTNode<S>* BinarySearchTree<S>::insert(const S& data, BSTNodeType*& root) //private
  {
    if (!root)
    {
      root = newNode(data);
      root->value = data;
      return root;
    }
    else if (data <= root->value)
      return insert(data, root->left);

    else
      return insert(data, root->right);
  }

  template <typename S>
  BSTNode<S>* BinarySearchTree<S>::insert(const S& data) //public
  {
    return insert(data, pRoot);
  }


  template <typename S>
  bool BinarySearchTree<S>::search(const S& data, const BSTNodeType* root) const
  {
    if (!root)
      return false;

    if (root->value == data)
      return true;

    if (data < root->value)
    {
      if (!root->left)
        return false;
      return search(data, root->left);
    }

    if (!root->right)
      return false;
    return search(data, root->right);
  }
  
  template <typename S>
  bool BinarySearchTree<S>::search(const S& data) const
  {
    return search(data, pRoot);
  }

}