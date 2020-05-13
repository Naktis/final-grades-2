#include "Student.h"

Student::Student(std::string newName, std::string newSurname, double newFinal = 0) { 
    setAll(newName, newSurname, newFinal); 
}

void Student::setAll(std::string newName, std::string newSurname, double newFinal) {
    name = newName;
    surname = newSurname;
    final = newFinal;
}

// Copy assignment operator
Student& Student::operator = (const Student& origin) {
    if (&origin == this) return *this; // Self assignment check

    name = origin.name;
    surname = origin.surname;
    final = origin.final;
    return *this;
}

bool Student::operator == (const Student& other) {
    return (name == other.name && surname == other.surname && final == other.final);
}

std::istream& operator >> (std::istream& in, Student& s) {
    in >> s.name >> s.surname >> s.final;
    return in;
}

std::ostream& operator << (std::ostream& out, const Student& s) {
    out << std::setw(20) << std::left << s.name << std::setw(20) << s.surname
        << std::fixed << std::setprecision(2) << s.final << "\n";
    return out; 
}