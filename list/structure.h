#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <list>

struct Student {
    std::string name, surname;
    int exam;
    double final;
    std::list<int> HW; // Vector of homework grades
};

#endif