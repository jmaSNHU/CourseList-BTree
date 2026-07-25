/*
* main.cpp
* Jacob Ard
* CS-499 Capstone
* Algorithms & Data Structures Enhancement
* July 24, 2026
* 
* This program loads Course information into a B-Tree data structure.
* Optionally accepts command line arguments for a provided CSV file.
* Menu Options:
* 1) Load courses into B-Tree
* 2) Print all course using in-order traversal
* 3) Search for a course by course number, print course info & prerequisites
* 9) Exit
*/

#include "BTree.h"
#include "BTree.cpp"
#include "Course.h"
#include <iostream>
#include <fstream>

/*
* static functions declarations for main:
* load courses, prereq courses
*/
// searches BTree for each prereq course number 
void updateCoursePrerequistites(BTree<Course>* courseBTree);

// reads from CSV file and inserts Course into B-Tree
void loadCourses(std::string filePath, BTree<Course>* bTree);

// program driver
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

	// Initialize a Course BTree with min degree 3
	BTree<Course>* bTree = new BTree<Course>(3);
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
		
		if (!(std::cin >> choice)) {
			std::cout << "Invalid input. Please enter a valid option 1-3, or 9.\n";
			// Clear error state and ignore bad input
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			continue; 
		}

		switch (choice) {
		case 1:
			// load each csv file passed to the program (or default file)
			for (std::string csv : csvFiles) {
				loadCourses(csv, bTree);
			}
			break;

		case 2:
			// print course list in order of course #
			std::cout << "Here is a sample schedule:\n\n";
			bTree->inOrder([](Course& course) {
				std::cout << course << std::endl;
				});
			break;

		case 3:
			std::cout << "What course do you want to know about? ";
			std::cin >> courseKey;
			// convert string to upper case 
			for (auto& c : courseKey)
				c = toupper(c);

			// search tree for matching course number
			course = bTree->search(courseKey);

			if (!course.getCourseNumber().empty()) {
				std::cout << course.getCourseNumber() << ", " << course.getName() << std::endl;
				std::cout << "Prerequisites:\n";
				auto prerequisites = course.getPrerequisites();
				// print each prereq course number
				for (int i = 0; i < prerequisites.size(); ++i) {
					std::cout << "\t\t" << prerequisites[i] << std::endl;
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

void loadCourses(std::string filePath, BTree<Course>* bTree) {

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
					// create & add prereq course object
					course.addPrerequisite(Course(row_data[i]));
					// add course number for validation
					prequisiteCourseNumbers.push_back(row_data[i]);
				}
			}

		}
		bTree->insert(course);
	}

	// validate and update nested prereq course objects with name
	// and prereq vectors
	updateCoursePrerequistites(bTree);

	inFile.close(); // close the file
}


void updateCoursePrerequistites(BTree<Course>* courseBTree) {
	// cancel validation if bTree pointer is null
	if (courseBTree == nullptr) {
		return;
	}

	// updates course prerequisites
	// this lambda function captures the bTree for use within inOrder() traversal
	const std::function<void(Course&)> updateCoursePreReq = [courseBTree](Course& course) {
		// gets a copy of Course's prerequisite Course vector
		std::vector<Course> prequistites = course.getPrerequisites();
		// loop through prereq vector
		for (auto& prereq : prequistites) {
			// search the bTree for the Course
			Course tmp = courseBTree->search(prereq);
			// copy the course if a match is found
			if (tmp == prereq)
				prereq = tmp; // default behavior performs a shallow copy
			else
				prereq.setName("Course Present In File");
			course.setPrerequisites(prequistites);
		}
		};
	// use lambda function in in-order traversal to update prereq course objects
	courseBTree->inOrder(updateCoursePreReq);
}