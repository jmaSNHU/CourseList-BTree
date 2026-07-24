#include "Btree.h"

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
void Node<T>::inOrder()
{
	int i;
	for (i = 0; i < this->numKeys; ++i) {
		if (!isLeafNode) {
			this->children[i]->inOrder();
		}
		std::cout << " " << this->keys[i];
	}
	if (!isLeafNode) {
		this->children[i]->inOrder();
	}
}

template<typename T>
T Node<T>::search(T key)
{
	int i = 0;
	while (i < this->numKeys && key > this->keys[i]) {
		++i;
	}

	if (i < this->numKeys && this->keys[i] == key) {
		return this->keys[i];
	}
	if (isLeafNode) {
		return T();
	}

	// recursively search this node's i'th child 
	return this->children[i]->search(key);
}

template<typename T>
void Node<T>::insertIfNotFull(T key)
{
	int i = this->numKeys - 1;

	if (isLeafNode) {
		// move keys right
		while (i >= 0 && this->keys[i] > key) {
			this->keys[i + 1] = this->keys[i];
			i--;
		}
		this->keys[i + 1] = key;
		++this->numKeys;
	} 
	else {
		// find the child to continue descending
		while (i >= 0 && this->keys[i] > key) {
			--i;
		}

		// check if a child node is full needs to be split
		if (this->children[i + 1]->numKeys == 2 * this->minDegree - 1) {
			this->split(i + 1, this->children[i + 1]);
			if (this->keys[i + 1] < key) {
				++i;
			}
		}
		this->children[i + 1]->insertIfNotFull(key);
	}
}

template<typename T>
void Node<T>::split(int index, Node<T>* child)
{
	// create a new node to hold the upper half of keys	
	Node<T>* newNode = new Node<T>(child->minDegree, child->isLeafNode);
	newNode->numKeys = this->minDegree - 1;

	//copy keys from child to new node
	for (int j = 0; j < this->minDegree - 1; ++j) {
		newNode->keys[j] = child->keys[j + this->minDegree];
	}

	if (!child->isLeafNode) {
		// copy child node's children to new node
		for (int j = 0; j < this->minDegree; ++j) {
			newNode->children[j] = child->children[j + this->minDegree];
		}
	}

	// shrink existing nodes number of keys
	child->numKeys = this->minDegree - 1;

	// shift parent (this) node's children to make room for new Node
	for (int j = this->numKeys; j >= index + 1; --j) {
		this->children[j + 1] = this->children[j];
	}
	// insert the new Node
	this->children[index + 1] = newNode;

	// shift parent (this) node's keys to accept key index from split node
	for (int j = this->numKeys - 1; j >= index; --j) {
		this->keys[j + 1] = this->keys[j];
	}
	this->keys[index] = child->keys[this->minDegree - 1];
	++this->numKeys;
}

template<typename T>
T BTree<T>::search(T key)
{
	// empty tree
	if (root == nullptr) return T();

	// recursively search
	return root->search(key);
}

template<typename T>
void BTree<T>::inOrder()
{
	if (root != nullptr) root->inOrder();
	std::cout << std::endl;
}

template<typename T>
void BTree<T>::insert(T key)
{
	if (this->root == nullptr) {
		this->root = new Node<T>(this->minDegree, true);
		this->root->keys[0] = key;
		this->root->numKeys = 1;
		return;
	}

	// handle split root
	if (this->root->numKeys == 2 * this->minDegree - 1) {
		Node<T>* newNode = new Node<T>(this->minDegree, false);
		newNode->children[0] = this->root;
		newNode->split(0, this->root);

		// determine which side of the split gets the new key
		int i = (newNode->keys[0] < key) ? 1 : 0;
		newNode->children[i]->insertIfNotFull(key);
		this->root = newNode;
	}
	else {
		this->root->insertIfNotFull(key);
	}
}