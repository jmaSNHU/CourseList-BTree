/*
* BTree.cpp
* Jacob Ard
* CS-499 Capstone
* Algorithms & Data Structures Enhancement
* July 22, 2026
*/

#include "Btree.h"

/// <summary>
/// Node Constructor
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="minDegree"></param>
/// <param name="isLeafNode"></param>
template<typename T>
Node<T>::Node(int minDegree, bool isLeafNode)
{
	this->minDegree = minDegree;
	this->isLeafNode = isLeafNode;

	this->keys = new T[2 * minDegree - 1];
	this->children = new Node<T>*[2 * minDegree];
	this->numKeys = 0;
}

/// <summary>
/// Node Destructor
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
Node<T>::~Node()
{
	// free the dynamic keys array
	delete[] this->keys;
	if (!isLeafNode) {
		// delete child nodes
		for (int i = 0; i <= this->numKeys; ++i) {
			delete this->children[i];
		}
	}
	// free the dynamic child node array
	delete[] this->children;
}

/// <summary>
/// Performs in-order traversal
/// *Accepts a function(T) that is called on each
/// object in the BTree*
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="func"></param>
template<typename T>
void Node<T>::inOrder(const std::function<void(T&)>& func)
{
	int i;
	for (i = 0; i < this->numKeys; ++i) {
		// traverse children in order before printing
		if (!isLeafNode) {
			this->children[i]->inOrder(func);
		}
		// calls the passed function argument on this key T
		func(this->keys[i]);
	}
	// recursive traversal last childs subtree
	if (!isLeafNode) {
		this->children[i]->inOrder(func);
	}
}

/// <summary>
/// Perform Recursive  and returns a matching key T
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="key"></param>
/// <returns></returns>
template<typename T>
T Node<T>::(T key)
{
	int i = 0;
	// iterate through keys 
	while (i < this->numKeys && key > this->keys[i]) {
		++i;
	}

	// return the match
	if (i < this->numKeys && this->keys[i] == key) {
		return this->keys[i];
	}
	if (isLeafNode) {
		// return default T if not found
		return T();
	}

	// recursively  this node's i'th child 
	return this->children[i]->(key);
}

/// <summary>
/// Inserts a new key if space is available,
/// Splits child node if full
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="key"></param>
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

/// <summary>
/// Splits a child node into two and moves the median key
/// to the parent
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="index"></param>
/// <param name="child"></param>
template<typename T>
void Node<T>::split(int index, Node<T>* child)
{
	// create a new node to hold the upper half of keys	
	Node<T>* newNode = new Node<T>(child->minDegree, child->isLeafNode);
	newNode->numKeys = this->minDegree - 1;

	//copy keys from child to new node
	for (int i = 0; i < this->minDegree - 1; ++i) {
		newNode->keys[i] = child->keys[i + this->minDegree];
	}

	if (!child->isLeafNode) {
		// copy child node's children to new node
		for (int i = 0; i < this->minDegree; ++i) {
			newNode->children[i] = child->children[i + this->minDegree];
		}
	}

	// shrink existing nodes number of keys
	child->numKeys = this->minDegree - 1;

	// shift parent (this) node's children to make room for new Node
	for (int i = this->numKeys; i >= index + 1; --i) {
		this->children[i + 1] = this->children[i];
	}
	// insert the new Node
	this->children[index + 1] = newNode;

	// shift parent (this) node's keys to accept key index from split node
	for (int i = this->numKeys - 1; i >= index; --i) {
		this->keys[i + 1] = this->keys[i];
	}
	this->keys[index] = child->keys[this->minDegree - 1];
	++this->numKeys;
}

/// <summary>
/// Calls the Root Nodes recursve search method
/// Worst-case run time complexity of O(logn)
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="key"></param>
/// <returns></returns>
template<typename T>
T BTree<T>::search(T key)
{
	// empty tree
	if (root == nullptr) return T();

	// recursively search
	return root->search(key);
}

/// <summary>
/// Starts the In-Order traversal on the root node
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="func"></param>
template<typename T>
void BTree<T>::inOrder(const std::function<void(T&)>& func)
{
	if (root != nullptr) root->inOrder(func);
}

/// <summary>
/// Inserts a new Node into the B-Tree
/// Worst-case run time complexity of O(logn)
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="key"></param>
template<typename T>
void BTree<T>::insert(T key)
{
	// insert the root node
	if (this->root == nullptr) {
		this->root = new Node<T>(this->minDegree, true);
		this->root->keys[0] = key;
		this->root->numKeys = 1;
		return;
	}

	// split root if node is full
	if (this->root->numKeys == 2 * this->minDegree - 1) {
		Node<T>* newNode = new Node<T>(this->minDegree, false);
		newNode->children[0] = this->root;
		newNode->split(0, this->root);

		// determine which side of the split gets the new key
		int i = (newNode->keys[0] < key) ? 1 : 0;
		newNode->children[i]->insertIfNotFull(key);
		this->root = newNode;
	}
	// insert key in available node
	else {
		this->root->insertIfNotFull(key);
	}
}
