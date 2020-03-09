#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <list>
#include "structure.h"

template <typename T>
void reenterInput(T&);
void readFile (std::list<Student>&, std::string);
double average (std::list<int>&, int);
double median (std::list<int>&, int);
double finalGrade (Student&, char);
void makeGroups (std::list<Student>&, std::list<Student>&);
void optionalInputValidation (char&, char, char);
void optionalInputValidation (char&, char, char, char);
void numberInputValidation (int&, int, int);
int randomNumber (int);
void generateGradesManually (Student*);
void createDataFile (int);
void sort (std::list<Student>&, std::list<Student>&, char);
void writeToFile(std::list<Student>&, char, std::string);

#endif