#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <list>
#include "structure.h"

// Input validation
template <typename T>
void reenterInput(T&);

void optionalInputValidation (char&, char, char);
void optionalInputValidation (char&, char, char, char);
void numberInputValidation (int&, int, int);

// Data generation
void generateGradesManually (Student*, char);
void createDataFile (int);

// Final grade calculation
double average (std::list<int>&, int);
double median (std::list<int>&, int);
double finalGrade (std::list<int> &, int, char);

// Data reading
void readEnteredData (std::list<Student> &, char, char);
std::string getFileName();
void readFile (std::list<Student>&, std::string, char);

// Other functions
void makeGroups (std::list<Student>&, std::list<Student>&);
void sort (std::list<Student>&, std::list<Student>&, char);
void writeToFile (std::list<Student>&, char, std::string);

#endif