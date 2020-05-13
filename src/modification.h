#pragma once

#include <vector>
#include <algorithm>
#include "student.h"

// Final grade calculation
double average (std::vector<int>&);
double median (std::vector<int>&);
double finalGrade (std::vector<int>&, int, char);

// Data reordering
void makeGroups (std::vector<Student>&, std::vector<Student>&);
void sort (std::vector<Student>&, std::vector<Student>&, char);