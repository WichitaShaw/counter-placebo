#include "BinarySearchTree.h"

#include <algorithm>

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

  std::cout << '\n';

  auto copyTree = testTree;
  for (auto check : { 3, 0, 33, 199, 35, 37 })
    std::cout << "Copy Tree: " << check << (copyTree.search(check) ? " found" : " unfound") << '\n';
  for (auto check : { 3, 0, 33, 199, 35, 37 })
    std::cout << "Test Tree: " << check << (testTree.search(check) ? " found" : " unfound") << '\n';

  std::cout << '\n';

  auto moveTree = std::move(testTree);
  for (auto check : { 3, 0, 33, 199, 35, 37 })
    std::cout << "Move Tree: " << check << (moveTree.search(check) ? " found" : " unfound") << '\n';
  for (auto check : { 3, 0, 33, 199, 35, 37 })
    std::cout << "Test Tree: " << check << (testTree.search(check) ? " found" : " unfound") << '\n';

  return;
}