#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "structure.h"

template <typename T>
void reenterInput(T&);
void readFile (std::vector<Student>&);
double average (int*, int);
double median (int*, int);
double finalGrade (Student*, char);
void optionalInputValidation (char&, char, char);
void optionalInputValidation (char&, char, char, char);
void numberInputValidation (int&, int, int);
void generateGrades (Student*);
void writeToFile(std::vector<Student>&, char);

#endif