# CourseListBTree
Artifact enhancement for CS-300's Course List Program Using a B-Tree Implementation.

## Background
This C++ program is derived from the final project for CS-300: Design and Analysis of Data Structures and Algorithms. The purpose of this project was to demonstrate my ability to correctly implement a fundamental computer science data structure and apply it to a practical problem. The original project requirements were to write a program that reads a CSV file containing course data, which includes fields for Course Number, Course Name, and a list of prerequisite courses. The program must also be able to print all courses in alphanumeric order by course ID and search the data structure for a single course. I was given a choice to implement one of three data structures: Binary Search Tree, Hashmap, or Vector. A Binary Search Tree, or BST, was a natural choice for this solution because it typically includes an in-order traversal method that satisfies the sorting requirement, while Hashmaps are inherently unordered and Vectors would require a less efficient sort operation after loading the initial data structure.

## Enhancement

I chose to enhance this artifact by implementing a B-Tree data structure to replace my original BST implementation. One reason I chose this approach is that my original BST class lacks a rebalance function. As BSTs grow in height and size, their performance degrades toward a worst-case O(n) runtime complexity. To prevent this and maintain an average O(log n) complexity for search, insert, and delete operations, they must be periodically rebuilt. I decided to implement a B-Tree because it is inherently self-balancing and therefore guarantees a worst-case runtime complexity of O(log n). B-Trees differ from BSTs in that each node can hold multiple keys and multiple children rather than two, which is determined by a minimum degree factor. The trade-off is that the implementation of B-Tree operations is much more complex than the BST. For example, the B-Tree maintains balance with a function that splits full child nodes and moves the median key to the parent node.

## Instructions 

Run or deploy the program from Visual Studio or compile in Unix enivronments with the GCC compiler, e.g.:

```g++ main.cpp BTree.cpp```

```./a.out```

<img width="572" height="941" alt="CLI" src="https://github.com/user-attachments/assets/214f7a86-3a01-4bca-9444-026965daa227" />
