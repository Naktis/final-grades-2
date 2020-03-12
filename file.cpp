#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>
#include "file.h"

std::string getFileName () {
    bool badFile;
    std::string fileName;
    std::cout << "\nIveskite failo varda formatu failo_pav.txt\n";
    std::cin >> fileName;
    do {
        try {
            std::ifstream in (fileName);
            if (!in.good())         // Check if the data file exists
                throw 404;
            else {
                in.close();
                badFile = false;
            }
        } catch (int exception) {   // If it doesn't, let user reenter new file name
            badFile = true;
            std::cout << "Duomenu failas " << fileName << " neegzistuoja. Iveskite esamo failo varda:\n";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> fileName;
        }
    } while (badFile);
    return fileName;
}

void createDataFile (int numOfStudents) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count())); // Random number generator
    std::uniform_int_distribution<int> random10(1, 10);
    std::uniform_int_distribution<int> random20(1, 20);
    //int numOfHW = random20(mt);                     // Generate the number of HW grades 
    int numOfHW = 5;

    std::ostringstream fileName;
    fileName << "kursiokai" << numOfStudents << ".txt"; // Create data file name
    std::ofstream add (fileName.str());                 // Open data file

    // Print header text
    std::ostringstream row ("");
    row << std::setw(20) << std::left << "Vardas" << std::setw(21) << "Pavarde";

    for (int i = 1; i <= numOfHW; i ++) 
        row << "ND" << std::setw(8) << std::left << i;
    row << "Egz.\n";
    add << row.str();

    // Print student data text
    int lastGenerated = 0, grade;
    for (int i = 1; i <= numOfStudents; i ++) {
        row.str("");
        row << "Vardas" << std::setw(14) << std::left << i << "Pavarde" << std::setw(14) << std::left << i;
        for (int j = 0; j <= numOfHW; j ++) {
            grade = random10(mt);
            row << std::setw(10) << std::left << grade; // Generate an exam grade
            lastGenerated = grade;
        }
        row << "\n";
        add << row.str();
    }
    add.close();
}