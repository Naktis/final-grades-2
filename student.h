#pragma once

#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "validation.h"

class Student {
    private:
        std::string name, surname;
        double final;
    public:
        Student() : final(0) { };
        void setName(std::string);
        void setSurname(std::string);
        void setFinal(double);
        inline std::string getName() const { return name; }
        inline std::string getSurname() const { return surname; }
        inline double getFinal() const { return final; }
};