#pragma once

#include <string>
#include <chrono>
#include <iostream>

class Student {
    private:
        std::string name, surname;
        double final;
    public:
        Student() : final(0) { };
        Student(std::string, std::string, double);
        Student(const Student&);            // Copy constructor

        ~Student() { };

        void setName(std::string);
        void setSurname(std::string);
        void setFinal(double);
        void setAll(std::string, std::string, double);
        inline std::string getName() const { return name; }
        inline std::string getSurname() const { return surname; }
        inline double getFinal() const { return final; }

        Student& operator=(const Student&); // Copy assignment operator
};