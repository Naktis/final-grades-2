#ifndef LIST_H
#define LIST_H

#include <list>
#include "structure.h"

// Data generation
void generateGradesManuallyList (Student*, char);

// Final grade calculation
double averageList (std::list<int>&, int);
double medianList (std::list<int>&, int);
double finalGradeList (std::list<int> &, int, char);

// Data reading
void readEnteredDataList (std::list<Student> &, char, char);
void readFileList (std::list<Student>&, std::string, char);

// Other functions
void makeGroupsList (std::list<Student>&, std::list<Student>&);
void sortList (std::list<Student>&, std::list<Student>&, char);
void writeToFileList (std::list<Student>&, char, std::string);

#endif