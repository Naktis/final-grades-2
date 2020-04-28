#include "Student.h"

// Copy constructor
Student::Student(const Student& origin) {
    name = origin.name;
    surname = origin.surname;
    final = origin.final;
}

Student::Student(std::string newName = "", std::string newSurname = "", double newFinal = 0) {
    name = newName;
    surname = newSurname;
    final = newFinal;
}

void Student::setName (std::string newName) {
    name = newName;
}

void Student::setSurname (std::string newSurname) {
    surname = newSurname;
}

void Student::setFinal (double newFinal) {
    final = newFinal;
}

void Student::setAll(std::string newName, std::string newSurname, double newFinal) {
    name = newName;
    surname = newSurname;
    final = newFinal;
}

// Copy assignment operator
Student& Student::operator=(const Student& origin) {
    if (&origin == this) return *this; // Self assignation check

    name = origin.name;
    surname = origin.surname;
    final = origin.final;
    return *this;
}