#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <deque>
#include "structure.h"

template <typename T>
void reenterInput(T&);
void readFile (std::deque<Student>&, std::string);
double average (int*, int);
double median (int*, int);
double finalGrade (Student*, char);
void makeGroups (std::deque<Student>&, std::deque<Student>&);
void optionalInputValidation (char&, char, char);
void optionalInputValidation (char&, char, char, char);
void numberInputValidation (int&, int, int);
int randomNumber (int);
void generateGradesManually (Student*);
void createDataFile (int);
void sort (std::deque<Student>&, std::deque<Student>&, char);
void writeToFile(std::deque<Student>&, char, std::string);

#endif