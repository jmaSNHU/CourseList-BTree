/*
* BTree.h
* Jacob Ard
* CS-499 Capstone
* Algorithms & Data Structures Enhancement
* July 16, 2026
*/


#ifndef B_TREE_H
#define B_TREE_H

#include<functional>
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
struct Node {
	Node(int minDegree, bool isLeafNode);  
	~Node();							  

	// performs inorder traversal and calls the provided function
	void inOrder(const std::function<void(T&)>& func); 
	// search by key returns matching Node pointer
	T search(T key);				   
	// inserts key in the correct node
	void insertIfNotFull(T key);	
	// splits a full child node
	void split(int index, Node<T>* child); 

	T* keys;		    // array of keys
	Node<T>** children; // array of child node pointers

	int numKeys;	    // number of keys used to allocate keys array
	bool isLeafNode;    // returns true if node has no children
	int minDegree;      // minimum degree
};

template<typename T>
class BTree {
public:
	BTree(int minDegree) : root(nullptr), minDegree(minDegree) {}
	~BTree() { delete root; }

	// Initiates recursive in-order traversal on the root node
	void inOrder(const std::function<void(T&)>& func);
	// Initiates recursive search on the root node
	T search(T key);
	// Inserts a new key T
	void insert(T key);
private:
	Node<T>* root;
	int minDegree;
};




#endif // !B_TREE_H
