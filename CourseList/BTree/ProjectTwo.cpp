// Jacob Ard
// Project 2: Course List Application
// Templated BST implementation
// October 15, 2025

/*
* Course List program implements Course class, 
* generic Node and BST using templates 
*/

#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<fstream>
#include<sstream>

using namespace std;

/* TODO:
*			1) Refactor into seperate .HPP, .CPP, main files
*			2) Need to re-balance tree to maintain performance
*			3) Change prequisites from Vector<string> to Vector<Course>
*/

// Course class represents Course #, name and a list of prerequistites
class Course {
public:
	Course() {}
	Course(string courseNumber) : _courseNumber(courseNumber) {}
	Course(string courseNumber, string name) : _courseNumber(courseNumber), _name(name) {}
	Course(string courseNumber, string name, vector<string> prerequisites) :
		_courseNumber(courseNumber), _name(name), _prerequisites(prerequisites) {}

	string getCourseNumber() const { return this->_courseNumber; }
	void setCourseNumber(string courseNumber) { this->_courseNumber = courseNumber; }

	string getName() const { return this->_name; }
	void setName(string name) { this->_name = name; }

	vector<string> getPrerequisites() const { return this->_prerequisites; }
	void addPrerequisite(string prerequisite) { this->_prerequisites.push_back(prerequisite); }

	// overloaded comparison operators using the courseNumber 'key'
	bool operator<(const Course& rhs) const { return this->_courseNumber < rhs._courseNumber; }
	bool operator>(const Course& rhs) const { return this->_courseNumber > rhs._courseNumber; }
	bool operator==(const Course& rhs) const { return this->_courseNumber == rhs._courseNumber; }
	// compare string key to object's courseNumber (for convenience)
	bool operator==(const string& courseNum) const { return this->_courseNumber == courseNum; }

	// friend ostream method
	friend std::ostream& operator <<(std::ostream& os, const Course& course);

private:
	string _courseNumber;
	string _name;
	// TODO: make a Vector<Course>
	vector<string> _prerequisites; 
};

// friend ostream overload for in-order traversal printing
std::ostream& operator<<(std::ostream& os, const Course& course)
{
	return os << course._courseNumber << ", " << course._name << endl;
}

/*
* Note: I decided to implement Tree Node and BST structures
* using templates for a more generic, reusable data structure.
*
* This comes with a couple of requirements for any types to be used with this BST:
* T should overload comparison operators <, ==, >
* T should at least overload the ostream insertion << operator with a friend method:
*	this helps with printing the object during in-order traversal
*/

// Node structure for Binary Search Tree
template <typename T>
struct Node {
	// data can be of any type T
	T data;
	Node* left;
	Node* right;

	// default Node constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// initialize with data
	Node(T a_data) :
		Node() {
		data = a_data;
	}
};

// Templated Binary Search Tree
template<typename T>
class BinarySearchTree {
public:
	BinarySearchTree() : _root(nullptr) {}
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(T data);
	void Remove(T data);
	T Search(T data);
private:
	Node<T>* _root;

	void addNode(Node<T>* node, T data);
	void inOrder(Node<T>* node);
	Node<T>* removeNode(Node<T>* node, T data); 
	void destructRecursive(Node<T>* node); // for destructor 
};

// destructor
template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	// recursively deallocate nodes
	destructRecursive(_root);
}

// Prints BST objects during in-order traversal
template<typename T>
void BinarySearchTree<T>::InOrder()
{
	// pass root node to recursive inOrder method
	inOrder(_root);
}

// Inserts object into the BST
template<typename T>
void BinarySearchTree<T>::Insert(T data)
{
	// create root node if empty
	if (_root == nullptr) {
		_root = new Node<T>(data);
	}
	else {
		// root and new node to recursive addNode method
		addNode(_root, data);
	}
}

// Removes object from the BST
template<typename T>
void BinarySearchTree<T>::Remove(T data)
{
	// pass root node to recursive remove method
	removeNode(_root, data);
}


//Search returns T data if found, empty T if not found
//Requires that T overload the <, ==, > operators
template<typename T>
T BinarySearchTree<T>::Search(T data)
{
	// start at root node
	Node<T>* currNode = _root;
	while (currNode != nullptr) {
		// return if data is equal to node's data
		if (currNode->data == data) {
			return currNode->data;
		}
		// else traverse left subtree if data is less than currNodes' data
		else if (data < currNode->data) {
			currNode = currNode->left;
		}
		// else travese right subtree if data is greater than currNode
		else {
			currNode = currNode->right;
		}
	}
	return T(); // return empty data if not found
}

// Inserts a new object <T> into the BST
template<typename T>
void BinarySearchTree<T>::addNode(Node<T>* node, T data)
{
	
	// if node is larger then add to left
	if (data < node->data) {
		// check for left node, add leaf if empty
		if (node->left == nullptr) {
			node->left = new Node<T>(data);
		}
		else {
			// continue recursing left side
			addNode(node->left, data);
		}
	}
	// add to the right side
	else {
		// add right leaf if empty
		if (node->right == nullptr) {
			node->right = new Node<T>(data);
		}
		else {
			// continue recursing right side
			addNode(node->right, data);
		}
	}
}

// Prints in-order traversal of BST
// Requires overloaded ostream << operator for T
template<typename T>
void BinarySearchTree<T>::inOrder(Node<T>* node)
{
	// base case
	if (node == nullptr) {
		return;
	}

	// recursively traverse left subtree
	this->inOrder(node->left);
	cout << node->data;
	// traverse right subtree
	this->inOrder(node->right);
}

// Recursively search and remove an object <T> from the tree
template<typename T>
Node<T>* BinarySearchTree<T>::removeNode(Node<T>* node, T data)
{
	// base case
	if (node == nullptr) {
		return node;
	}

	// check for match and if so, remove left node using recursive call 
	if (node->data > data) {
		node->left = this->removeNode(node->left, data);
	}
	// check for match and if so, remove right node using recursive call
	else if (node->data < data) {
		node->right = this->removeNode(node->right, data);
	}

	// matching node
	else {
		// no children
		// if left node = nullptr && right node = nullptr delete node 
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			return nullptr;
		}
		// one left child
		else if (node->left != nullptr && node->right == nullptr) {
			Node<T>* tmp = node->left;
			delete node;
			return tmp;
		}
		// one right child
		else if (node->left == nullptr && node->right != nullptr) {
			Node<T>* tmp = node->right;
			delete node;
			return tmp;
		}
		// multiple children
		else {
			// tmp successor node
			Node<T>* successor = node->right;
			// traverse left side of succ node
			while (successor != nullptr && successor->left != nullptr) {
				successor = successor->left;
			}
			// copy successor data
			node->data = successor->data;
			// remove original successor node
			node->right = this->removeNode(node->right, successor->data);
		}

	}

	return node;
}

// recursively delete left and right subtrees
template<typename T>
void BinarySearchTree<T>::destructRecursive(Node<T>* node)
{
	if (node != nullptr) {
		// recursively delete left nodes
		destructRecursive(node->left);
		// recursively delete right nodes
		destructRecursive(node->right);
		delete node; // deallocate leaf node
	}
}

/*
* static functions for main:
* load data, prereq course validation
*/

// iterates through a vector of prereq course numbers
// searches BST for each prereq course number 
// takes nlogn time validate the BST.
void validateCoursePrerequisites(vector<string> prequisiteCourseNumbers, BinarySearchTree<Course>* courseBst) {
	// cancel validation if bst pointer is null
	if (courseBst == nullptr) {
		return;
	}
	// validate prerequisites
	for (string prereq : prequisiteCourseNumbers) {
		// make sure the prereq course exists
		Course searchCourse = courseBst->Search(prereq);
		if (searchCourse.getCourseNumber().empty()) {
			cerr << "Error: Prerequisite course " << prereq << " not found\n";
			// delete and reallocate bst ??
			//delete courseBst;
			//courseBst = new BinarySearchTree<Course>();
		}
	}
}

void loadCourses(string filePath, BinarySearchTree<Course>* bst) {

	cout << "Loading CSV file " << filePath << endl;

	ifstream inFile(filePath);
	// verify the file is open
	if (!inFile.is_open()) {
		std::cerr << "Error opening file: " << filePath << endl;
		return;
	}

	// tmp vector for validating prereqs after parsing the whole file
	vector<string> prequisiteCourseNumbers;
	string line;
	// read each line of the file...
	while (getline(inFile, line)) {
		stringstream ss(line);
		string field;
		vector<string> row_data;

		// read each comma seperated field on the line...
		while (getline(ss, field, ',')) {
			if (!field.empty()) {
				row_data.push_back(field);
			}
		}

		// create course objects
		Course course;
		for (int i = 0; i < row_data.size(); ++i) {
			switch (i) {
			case 0: // first field course #
				course.setCourseNumber(row_data[i]);
				break;
			case 1: // second field course name
				course.setName(row_data[i]);
				break;
			default: // prerequisites
				// check for empty field
				if (!row_data[i].empty()) {
					// add prerequisite to course object
					course.addPrerequisite(row_data[i]);
					// add course number for validation
					prequisiteCourseNumbers.push_back(row_data[i]);
				}
			}

		}
		bst->Insert(course);
	}

	inFile.close(); // close the file

	// checks if course exists for all prereq course #s
	validateCoursePrerequisites(prequisiteCourseNumbers, bst);
}

int main(int argc, char* argv[]) {

	// process command line arguments
	vector<string> csvFiles;
	string defaultFileName = "CS 300 ABCU_Advising_Program_Input.csv";
	string courseKey;
	switch (argc) {
	// use default filename if user passes no args
	case 1:
		csvFiles.push_back(defaultFileName);
		break;
	default:
		// loop through multiple fileName args, starting at 1
		for (int i = 1; i < argc; ++i) {
			csvFiles.push_back(argv[i]);
		}
		break;
	}

	// Define a binary search tree to hold all Courses
	BinarySearchTree<Course>* bst = new BinarySearchTree<Course>();
	Course course;

	cout << "Welcome to course planner." << endl;
	int choice = 0;
	while (choice != 9) {
		cout << endl;
		cout << "  1. Load Data Structure." << endl;
		cout << "  2. Print Course List." << endl;
		cout << "  3. Print Course." << endl;
		cout << "  9. Exit" << endl;
		cout << "\nWhat would you like to do? ";
		cin >> choice;

		switch (choice) {
		case 1:
			// load each csv file passed to the program (or default file)
			for (string csv : csvFiles) {
				loadCourses(csv, bst);
			}
			break;

		case 2:
			// print course list in order of course #
			cout << "Here is a sample schedule:\n\n";
			bst->InOrder();
			break;

		case 3:
			cout << "What course do you want to know about? ";
			cin >> courseKey;
			// convert string to upper case 
			for (auto& c : courseKey)
				c = toupper(c);

			// search tree for matching course number
			course = bst->Search(courseKey);

			if (!course.getCourseNumber().empty()) {
				cout << course.getCourseNumber() << ", " << course.getName() << endl;
				cout << "Prerequisites: ";
				auto prerequisites = course.getPrerequisites();
				// print each prereq course number
				for (int i = 0; i < prerequisites.size(); ++i) {
					cout << prerequisites[i];
					if (i < prerequisites.size() - 1)
						cout << ", ";
				}
				cout << endl;
			}
			else {
				cout << "Course Number " << courseKey << " not found." << endl;
			}
			break;

		case 9: // exit
			break;
		default: // invalid input
			cout << choice << " is not a valid option." << endl;
		}

	}

	cout << "Thank you for using the course planner!" << endl;
	return 0;
}
