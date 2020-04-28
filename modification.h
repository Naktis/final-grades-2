#pragma once

#include <vector>
#include <algorithm>
#include "student.h"

// Final grade calculation
double average (std::vector<int>&, int);
double median (std::vector<int>*, int);
double finalGrade (std::vector<int>&, int, char);

// Reordering functions
void makeGroups (std::vector<Student>&, std::vector<Student>&, std::vector<Student>&, int, char);
void sort (std::vector<Student>&, std::vector<Student>&, char);