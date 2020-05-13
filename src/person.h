#pragma once

class Person {
    protected:
        std::string name, surname;
    public:
        virtual void print() = 0;
        virtual void setName(std::string newName) = 0;
        virtual void setSurname(std::string newSurname) = 0;
        virtual inline std::string getName() const = 0;
        virtual inline std::string getSurname() const = 0;
};