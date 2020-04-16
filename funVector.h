#pragma once

#include <vector>
#include "student.h"

// Data generation
void generateGradesManuallyVector (Student*);

// Final grade calculation
double averageVector (std::vector<int>&, int);
double medianVector (std::vector<int>*, int);
double finalGradeVector (std::vector<int>&, int, char);

// Data reading
void readEnteredDataVector (std::vector<Student>&, char, char);
void readFileVector (std::vector<Student>&, std::string, char);

// Other functions
void makeGroupsVector (std::vector<Student>&, std::vector<Student>&, std::vector<Student>&, int, char);
void sortVector (std::vector<Student>&, std::vector<Student>&, char);
void writeToFileVector (std::vector<Student>&, char, std::string);