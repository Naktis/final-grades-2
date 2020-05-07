#pragma once

#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>
#include "person.h"

class Student : public Person {
    private:
        double final;
    public:
        // Constructors and a destructor
        Student() : final(0) { };
        Student(std::string newName, std::string newSurname, double newFinal);
        Student(const Student& origin) { setAll(origin.name, origin.surname, origin.final); } // Copy
        ~Student() { };

        // Set and get methods
        void setFinal(double newFinal) { final = newFinal; }
        void setAll(std::string, std::string, double);
        inline double getFinal() const { return final; }

        // Operators
        Student& operator = (const Student&); // Copy assignment operator
        bool operator == (const Student&);    // Can be used for != comparison
        double operator + (const Student& other) { return final + other.final; }
        double operator - (const Student& other) { return final - other.final; }
        double operator / (const Student& other) { return final / other.final; }

        friend std::istream& operator >> (std::istream&, Student&);
        friend std::ostream& operator << (std::ostream&, const Student&);

        // Comparison functions for sorting
        friend bool compareNames (const Student& A, const Student& B) {return A.name < B.name;}
        friend bool compareSurnames (const Student& A, const Student& B) {return A.surname < B.surname;}
        friend bool compareFinals (const Student& A, const Student& B) {return A.final < B.final;}

        void print() { std::cout << *this; }
};

// Declarations for global visibility of functions
extern bool compareNames(const Student&, const Student&);
extern bool compareSurnames(const Student&, const Student&);
extern bool compareFinals(const Student&, const Student&);