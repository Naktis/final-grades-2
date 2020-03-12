#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <deque>
#include "structure.h"

// Data generation
void generateGradesManuallyDeque (Student*);

// Final grade calculation
double averageDeque (std::deque<int>&, int);
double medianDeque (std::deque<int>*, int);
double finalGradeDeque (std::deque<int>&, int, char);

// Data reading
void readEnteredDataDeque (std::deque<Student>&, char, char);
void readFileDeque (std::deque<Student>&, std::string, char);

// Other functions
void makeGroupsDeque (std::deque<Student>&, std::deque<Student>&);
void sortDeque (std::deque<Student>&, std::deque<Student>&, char);
void writeToFileDeque (std::deque<Student>&, char, std::string);

#endif