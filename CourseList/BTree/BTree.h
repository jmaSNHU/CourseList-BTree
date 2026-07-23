/*
* BTree.h
* Jacob Ard
* CS-499 Capstone
* July 16, 2026
*/


#ifndef B_TREE_H
#define B_TREE_H

#include<iostream>


// forward declaration of types so the compiler knows they exist
// this is needed BTree to be a friend of the Node class
// Node and BTree objects must share the same type
template<typename T> class Node;
template<typename T> class BTree;


/// <summary>
/// Templated Node class for B-Tree
/// Nodes contain multiple keys and child nodes
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class Node {
public:
	Node(int minDegree, bool isLeafNode);  // constructor
	~Node();							   // destructor

	void inOrder();						   // performs inorder traversal and prints node data
	Node<T>* search(T key);				   // search by key returns matching Node pointer
	void insertIfNotFull(T key);		   // inserts key in the correct node
	void split(int index, Node<T>* child); // splits a full child node

	// grants other Nodes access to private members
	friend class BTree<T>;

private:
	T* keys;		 // array of keys
	Node<T>** children;		 // array of child node pointers

	int numKeys;	 // number of keys used to allocate keys array
	bool isLeafNode; // returns true if node has no children
	int minDegree;   // minimum degree


};

template<typename T>
class BTree {
public:
	BTree(int minDegree) : root(nullptr), minDegree(minDegree) {}
	~BTree() { delete root; }

	void inOrder();
	Node<T>* search(T key);
	void insert(T key);
private:
	Node<T>* root;
	int minDegree;
};




#endif // !B_TREE_H
