/*
* BTree.h
* Jacob Ard
* CS-499 Capstone
* July 16, 2026
*/


#ifndef B_TREE_H
#define B_TREE_H

/// <summary>
/// Templated Node class for B-Tree
/// Nodes contain multiple keys and child nodes
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class Node {
public:
	Node(int minDegree, bool isLeafNode); //constructor
	~Node(); // destructor

	void inOrder(); // performs inorder traversal and prints node data
	Node<T>* search(T key); // search by key returns matching Node pointer
	void insertIfNotFull(T key); // inserts key in the correct node
	void split(int index, Node<T>* child); // splits a full child node

private:
	T* keys; // array of keys
	Node<T>**; // array of child node pointers

	int numKeys; // number of keys used to allocate keys array
	bool isLeafNode; // returns true if node has no children
	int minDegree; // minimum degree

	friend class Node<T>; // grants Nodes' access to privte members
};



#endif // !B_TREE_H
