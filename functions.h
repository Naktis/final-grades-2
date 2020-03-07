#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "structure.h"

template <typename T>
void reenterInput(T&);
void readFile (std::vector<Student>&, std::string);
double average (int*, int);
double median (int*, int);
double finalGrade (Student*, char);
void makeGroups (std::vector<Student>&, std::vector<Student>&);
void optionalInputValidation (char&, char, char);
void optionalInputValidation (char&, char, char, char);
void numberInputValidation (int&, int, int);
int randomNumber (int);
void generateGradesManually (Student*);
void createDataFile (int);
void sort (std::vector<Student>&, std::vector<Student>&, char);
void writeToFile(std::vector<Student>&, char, std::string);

#endif