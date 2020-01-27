#include "BinarySearchTree.h"

#include <iostream>

using namespace js;

void main()
{
  BinarySearchTree<int> testTree;

  testTree.insert(0);
  testTree.insert(15);
  testTree.insert(101);
  testTree.insert(35);
  testTree.insert(37);
  testTree.insert(56);

  for (auto check : { 3, 0, 33, 199, 35, 37 })
    std::cout << check << (testTree.search(check) ? " found" : " unfound") << '\n';
  return;
}