/*
* Course.h
* Jacob Ard
* CS-499 Capstone
* July 16, 2026
*/

#ifndef COURSE_H
#define COURSE_H

#include<iostream>
#include<vector>
#include<sstream>
#include<string>

using std::string;
using std::vector;

// Course class represents Course #, name and a list of prerequistites
class Course {
public:
	Course() {}
	Course(string courseNumber) : _courseNumber(courseNumber) {}
	Course(string courseNumber, string name) : _courseNumber(courseNumber), _name(name) {}
	Course(string courseNumber, string name, vector<Course> prerequisites) :
		_courseNumber(courseNumber), _name(name), _prerequisites(prerequisites) {}

	string getCourseNumber() const { return this->_courseNumber; }
	void setCourseNumber(string courseNumber) { this->_courseNumber = courseNumber; }

	string getName() const { return this->_name; }
	void setName(string name) { this->_name = name; }

	vector<Course> getPrerequisites() const { return this->_prerequisites; }
	void addPrerequisite(string prerequisite) { this->_prerequisites.push_back(prerequisite); }

	// overloaded comparison operators using the courseNumber 'key'
	bool operator<(const Course& rhs) const { return this->_courseNumber < rhs._courseNumber; }
	bool operator>(const Course& rhs) const { return this->_courseNumber > rhs._courseNumber; }
	bool operator==(const Course& rhs) const { return this->_courseNumber == rhs._courseNumber; }
	// compare string key to object's courseNumber (for convenience)
	bool operator==(const string& courseNum) const { return this->_courseNumber == courseNum; }

	// friend ostream method
	friend std::ostream& operator<<(std::ostream& os, const Course& course);

private:
	string _courseNumber;
	string _name;
	vector<Course> _prerequisites;
};

// friend ostream overload for in-order traversal printing
std::ostream& operator<<(std::ostream& os, const Course& course)
{
	return os << course._courseNumber << ", " << course._name << std::endl;
}

#endif