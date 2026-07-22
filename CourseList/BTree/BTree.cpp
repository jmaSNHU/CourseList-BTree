#include "BTree.h"

template<typename T>
Node<T>::Node(int minDegree, bool isLeafNode)
{
	this->minDegree = minDegree;
	this->isLeafNode = isLeafNode;

	this->keys = new T[2 * minDegree - 1];
	this->children = new Node<T>*[2 * minDegree];
	this->numKeys = 0;
}

template<typename T>
Node<T>::~Node()
{
	delete[] this->keys;
	if (!isLeafNode) {
		for (int i = 0; i <= this->numKeys; ++i) {
			delete this->children[i];
		}
	}
	delete[] this->children;
}

template<typename T>
void BTree<T>::traverse()
{
	if (root != nullptr) root->traverse();
	std::cout << std::endl;
}

template<typename T>
void Node<T>::inOrder()
{
	int i;
	for (i = 0; i < this->numKeys; ++i) {
		if (!isLeafNode) {
			this->children[i]->inOrder();
			std::cout << " " << this->keys[i];
		}
	}
	if (!isLeafNode) {
		this->children->inOrder();
	}
}

template<typename T>
Node<T>* BTree<T>::search(T key)
{
	// empty tree
	if (root == nullptr) return nullptr;

	// recursively search
	root->search(key);
}