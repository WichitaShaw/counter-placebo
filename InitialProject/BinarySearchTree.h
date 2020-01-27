#pragma once

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
    BSTNodeType* newNode(const S& data) 
    {
      BSTNodeType* result = new BSTNodeType();
      result->value = data;
      return result;
    }


    BSTNodeType* insert(const S& data, BSTNodeType*& root)
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

    BSTNodeType* insert(const S& data)
    {
      return insert(data, pRoot);
    }


    bool search(const S& data, const BSTNodeType* root) const
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

    bool search(const S& data) const
    {
      return search(data, pRoot);
    }

  };


}