/*
* Course.h
* Jacob Ard
* CS-499 Capstone
* July 16, 2026
* 
*/


#ifndef COURSE_H
#define COURSE_H

#include<iostream>
#include<vector>
#include<sstream>
#include<string>

/// <summary>
/// Course class represents Course #, name and a list of prerequistites
/// </summary>
class Course {
public:
	// Constructors
	Course() {}
	Course(std::string courseNumber) : _courseNumber(courseNumber) {}
	Course(std::string courseNumber, std::string name) : _courseNumber(courseNumber), _name(name) {}
	Course(std::string courseNumber, std::string name, std::vector<Course> prerequisites) :
		_courseNumber(courseNumber), _name(name), _prerequisites(prerequisites) {}

	// Getters and Setters for courseNumber, name, and prerequisites
	std::string getCourseNumber() const { return this->_courseNumber; }
	void setCourseNumber(std::string courseNumber) { this->_courseNumber = courseNumber; }

	std::string getName() const { return this->_name; }
	void setName(std::string name) { this->_name = name; }

	std::vector<Course> getPrerequisites() const { return this->_prerequisites; }
	void addPrerequisite(Course prerequisite) { this->_prerequisites.push_back(prerequisite); }
	void setPrerequisites(std::vector<Course> prerequisites) { this->_prerequisites = prerequisites; }

	// overloaded comparison operators using the courseNumber 'key'
	bool operator<(const Course& rhs) const { return this->_courseNumber < rhs._courseNumber; }
	bool operator>(const Course& rhs) const { return this->_courseNumber > rhs._courseNumber; }
	bool operator==(const Course& rhs) const { return this->_courseNumber == rhs._courseNumber; }
	// compare string key to object's courseNumber (for convenience)
	bool operator==(const std::string& courseNum) const { return this->_courseNumber == courseNum; }

private:
	std::string _courseNumber;
	std::string _name;
	std::vector<Course> _prerequisites;
};

// friend ostream overload for in-order traversal printing
std::ostream& operator<<(std::ostream& os, const Course& course)
{
	return os << course.getCourseNumber() << " - " << course.getName();
}

#endif