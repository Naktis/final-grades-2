#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>

struct Student {
    std::string name, surname;
    int exam;
    double final;
    std::vector<int> HW; // Vector of homework grades
};

#endif