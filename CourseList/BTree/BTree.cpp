#include "BTree.h"

template<typename T>
void BTree<T>::traverse()
{
	if (root != nullptr) root->traverse();
	std::cout << std::endl;
}

template<typename T>
Node<T>* BTree<T>::search(T key)
{
	// empty tree
	if (root == nullptr) return nullptr;

	// recursively search
	root->search(key);
}