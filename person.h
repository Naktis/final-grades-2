#pragma once

class Person {
    protected:
        std::string name, surname;
    public:
        virtual void print() = 0;

        void setName(std::string newName) { name = newName; }
        void setSurname(std::string newSurname) { surname = newSurname; }
        inline std::string getName() const { return name; }
        inline std::string getSurname() const { return surname; }
};