/*
* Course.h
* Jacob Ard
* CS-499 Capstone
* July 16, 2026
*/

// TODO: 1) Add comments to all methods and classes
//       2) Refactor Vector<string> to Vector<Course> 

#ifndef COURSE_H
#define COURSE_H

#include<iostream>
#include<vector>
#include<sstream>
#include<string>

// Course class represents Course #, name and a list of prerequistites
class Course {
public:
	Course() {}
	Course(std::string courseNumber) : _courseNumber(courseNumber) {}
	Course(std::string courseNumber, std::string name) : _courseNumber(courseNumber), _name(name) {}
	Course(std::string courseNumber, std::string name, std::vector<std::string> prerequisites) :
		_courseNumber(courseNumber), _name(name), _prerequisites(prerequisites) {}

	std::string getCourseNumber() const { return this->_courseNumber; }
	void setCourseNumber(std::string courseNumber) { this->_courseNumber = courseNumber; }

	std::string getName() const { return this->_name; }
	void setName(std::string name) { this->_name = name; }

	std::vector<std::string> getPrerequisites() const { return this->_prerequisites; }
	void addPrerequisite(std::string prerequisite) { this->_prerequisites.push_back(prerequisite); }

	// overloaded comparison operators using the courseNumber 'key'
	bool operator<(const Course& rhs) const { return this->_courseNumber < rhs._courseNumber; }
	bool operator>(const Course& rhs) const { return this->_courseNumber > rhs._courseNumber; }
	bool operator==(const Course& rhs) const { return this->_courseNumber == rhs._courseNumber; }
	// compare string key to object's courseNumber (for convenience)
	bool operator==(const std::string& courseNum) const { return this->_courseNumber == courseNum; }

	// friend ostream method
	friend std::ostream& operator<<(std::ostream& os, const Course& course);

private:
	std::string _courseNumber;
	std::string _name;
	std::vector<std::string> _prerequisites;
};

// friend ostream overload for in-order traversal printing
std::ostream& operator<<(std::ostream& os, const Course& course)
{
	return os << course._courseNumber << ", " << course._name << std::endl;
}

#endif