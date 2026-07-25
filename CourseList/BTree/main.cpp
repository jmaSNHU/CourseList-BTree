#include "BTree.h"
#include "BTree.cpp"
#include "Course.h"
#include <iostream>
#include <fstream>

/*
* static functions for main:
* load data, prereq course validation
*/

// iterates through a vector of prereq course numbers
// searches BST for each prereq course number 
// takes nlogn time validate the BST.
void validateCoursePrerequisites(std::vector<std::string> prequisiteCourseNumbers, BTree<Course>* courseBst) {
	// cancel validation if bst pointer is null
	if (courseBst == nullptr) {
		return;
	}
	// validate prerequisites
	for (std::string prereq : prequisiteCourseNumbers) {
		// make sure the prereq course exists
		Course searchCourse = courseBst->search(prereq);
		if (searchCourse.getCourseNumber().empty()) {
			std::cerr << "Error: Prerequisite course " << prereq << " not found\n";
			// delete and reallocate bst ??
			//delete courseBst;
			//courseBst = new BinarySearchTree<Course>();
		}
	}
}

void loadCourses(std::string filePath, BTree<Course>* bst) {

	std::cout << "Loading CSV file " << filePath << std::endl;

	std::ifstream inFile{ filePath };
	// verify the file is open
	if (!inFile.is_open()) {
		std::cerr << "Error opening file: " << filePath << std::endl;
		return;
	}

	// tmp vector for validating prereqs after parsing the whole file
	std::vector<std::string> prequisiteCourseNumbers;
	std::string line;
	// read each line of the file...
	while (std::getline(inFile, line)) {
		std::stringstream ss(line);
		std::string field;
		std::vector<std::string> row_data;

		// read each comma seperated field on the line...
		while (std::getline(ss, field, ',')) {
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
		bst->insert(course);
	}

	inFile.close(); // close the file

	// checks if course exists for all prereq course #s
	validateCoursePrerequisites(prequisiteCourseNumbers, bst);
}

int main(int argc, char* argv[]) {

	// process command line arguments
	std::vector<std::string> csvFiles;
	std::string defaultFileName = "CS 300 ABCU_Advising_Program_Input.csv";
	std::string courseKey;
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
	BTree<Course>* bst = new BTree<Course>(3);
	Course course;

	std::cout << "Welcome to course planner." << std::endl;
	int choice = 0;
	while (choice != 9) {
		std::cout << std::endl;
		std::cout << "  1. Load Data Structure." << std::endl;
		std::cout << "  2. Print Course List." << std::endl;
		std::cout << "  3. Print Course." << std::endl;
		std::cout << "  9. Exit" << std::endl;
		std::cout << "\nWhat would you like to do? ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			// load each csv file passed to the program (or default file)
			for (std::string csv : csvFiles) {
				loadCourses(csv, bst);
			}
			break;

		case 2:
			// print course list in order of course #
			std::cout << "Here is a sample schedule:\n\n";
			bst->inOrder();
			break;

		case 3:
			std::cout << "What course do you want to know about? ";
			std::cin >> courseKey;
			// convert string to upper case 
			for (auto& c : courseKey)
				c = toupper(c);

			// search tree for matching course number
			course = bst->search(courseKey);

			if (!course.getCourseNumber().empty()) {
				std::cout << course.getCourseNumber() << ", " << course.getName() << std::endl;
				std::cout << "Prerequisites: ";
				auto prerequisites = course.getPrerequisites();
				// print each prereq course number
				for (int i = 0; i < prerequisites.size(); ++i) {
					std::cout << prerequisites[i];
					if (i < prerequisites.size() - 1)
						std::cout << ", ";
				}
				std::cout << std::endl;
			}
			else {
				std::cout << "Course Number " << courseKey << " not found." << std::endl;
			}
			break;

		case 9: // exit
			break;
		default: // invalid input
			std::cout << choice << " is not a valid option." << std::endl;
		}

	}

	std::cout << "Thank you for using the course planner!" << std::endl;
	return 0;
}
