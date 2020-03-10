#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <list>

#include "functions.h"

template <typename T>
void reenterInput(T& input) {
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> input;
}

// Functions which check if the input contains one of the asked options and asks to to reenter data, if it doesn't
void optionalInputValidation (char& input, char option1, char option2) {
    while (!(input == option1 || input == option2)) {
        std::cout << "Klaida. Pasirinkite viena is variantu (" << option1 << "/" << option2 << ") \n";
        reenterInput(input);
    }
}

// Overloaded function with 4 parameters
void optionalInputValidation (char& input, char option1, char option2, char option3) {
    while (!(input == option1 || input == option2 || input == option3)) {
        std::cout << "Klaida. Pasirinkite viena is variantu (" << option1 << "/" << option2  << "/" << option3 << ") \n";
        reenterInput(input);
    }
}

// Function which checks if the input is number-only and asks to reenter data, if it's not
void numberInputValidation (int& input, int lowest, int highest) {
    while (input < lowest || input > highest || std::cin.fail()) {
        std::cout << "Klaida. Pasirinkite skaiciu is intervalo [" << lowest << " ; " << highest << "] \n";
        reenterInput(input);
    }
}

void generateGradesManually (Student* S, char finalType) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count())); // Random number generator
    std::uniform_int_distribution<int> random10(1, 10);

    char moreGrades;
    std::list<int> HW;
    std::cout << "\nGeneruojami namu darbu balai.\n\n";
    do {
        HW.push_back(random10(mt));                      // Generate a random h.w. grade between 1 and 10
        std::cout << "Sugeneruotas balas: " << HW.back() << "\nGeneruoti dar viena n.d. bala? (t/n) ";
        std::cin >> moreGrades;
        optionalInputValidation(moreGrades, 't', 'n');
    } while (moreGrades == 't');

    S->exam = random10(mt);                                 // Generate a random exam grade between 1 and 10
    std::cout << "Sugeneruotas egzamino balas: " << S->exam << "\n";
    
    S->final = finalGrade(HW, S->exam, finalType);
}

void createDataFile (int numOfStudents) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count())); // Random number generator
    std::uniform_int_distribution<int> random10(1, 10);
    std::uniform_int_distribution<int> random20(1, 20);
    int numOfHW = random20(mt);                     // Generate the number of HW grades 

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

double average (std::list<int> &HW, int n) {
    double sum = 0;
    auto it = HW.begin();
    for (auto it = HW.begin(); it != HW.end(); it ++)
        sum += *(it);
    return (sum / n); // Division by zero isn't possible since the function can't be called when n = 0
}

double median (std::list<int> &HW, int n) {
    double m;
    HW.sort();                      // Sort values in ascending order

    auto it1 = HW.begin();          // Iterators for accessing middle values
    auto it2 = it1;
    std::advance(it1, n / 2 - 1);   // Move the iterator to the spot before the middle
    std::advance(it2, n / 2);       // Move the iterator to the middle spot

    n % 2 == 0 ? (m = 1.00 * (*it1 + *it2) / 2) : m = *it2; // Calculate median
    return m;
}

double finalGrade (std::list<int> &HW, int exam, char type){
    double hw;
    if (!HW.empty())  // Calculate the homework grade only if the homework list isn't empty
        type == 'm' ? hw = median(HW, HW.size()) : hw = average(HW, HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * exam);
}

void readEnteredData(std::list<Student> &S, char inputType, char finalType) {
    char moreStudents = 'n';
    bool moreHW;
    int tempHW;       // Temporary homework value for validation
    std::list<int> HW;
    Student temp;     // Temporary structure to be filled in before pushing back to the list
    do {
        moreHW = true;
        HW.clear();                        // Empty the list for new values

        std::cout << "\nStudento vardas ir pavarde:\n";
        std::cin >> temp.name >> temp.surname;

        if (inputType == 'g')
            generateGradesManually(&temp, finalType); // Generate homework and exam grades
        else {
            std::cout << "\nIveskite namu darbu balus, atskirtus paspaudus'enter'. Po paskutinio balo iveskite 0:\n";
            do {
                std::cin >> tempHW;
                numberInputValidation(tempHW, 0, 10);
                if (tempHW == 0)
                    moreHW = false;             // Terminate the loop, if 0 is entered
                else HW.push_back(tempHW);      // Add the entered grade to the homework list
            } while (moreHW);                   // Continue the loop, if it's wanted to enter more h.w. grades

            std::cout << "\nEgzamino balas:\n";
            std::cin >> temp.exam;
            numberInputValidation(temp.exam, 1, 10);
            temp.final = finalGrade (HW, temp.exam, finalType);
        }
        S.push_back(temp);                      // Add the structure to the list of student data

        std::cout << "\nAr norite ivesti dar vieno studento duomenis? (t/n) ";
        std::cin >> moreStudents;
        optionalInputValidation(moreStudents, 't', 'n');
    } while (moreStudents == 't');
}

std::string getFileName() {
    std::string fileName;
    bool badFile;
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

void readFile (std::list<Student> &S, std::string fileName, char finalType) {
    std::ifstream fd (fileName);

    int numOfHW = 0;
    std::string header;
    std::getline(fd, header);               // Read the first line of the file
    std::stringstream firstRow (header);    // Make it readable by copying it into a stringstream
    std::string str;
    while (firstRow >> str)                 // Count the number of separate strings until the line reaches the end
        numOfHW ++;
    numOfHW -= 3;                           // Ignore the name, surname and exam strings

    Student temp;
    int tempHW;
    std::string row;
    std::stringstream dataRow;
    std::list<int> HW;
    while (std::getline(fd, row)) {         // Continue reading until the end of file is reached (raised error flag)
        dataRow.str(row);
        dataRow >> temp.name >> temp.surname;
        HW.clear();                    // Empty the temporary homework list and fill it with grades from the file
        for (int i = 0; i < numOfHW; i ++) {
            dataRow >> tempHW;
            HW.push_back(tempHW);
        }
        dataRow >> temp.exam;
        temp.final = finalGrade(HW, temp.exam, finalType);
        S.push_back(temp);                  // Push the temporary structure to the list of structures
    }
	fd.close();
}

void makeGroups (std::list<Student> &S, std::list<Student> &GS) {
    // Sort students by their final grades
    S.sort([](Student &s1, Student &s2) {return s1.final < s2.final;});

    int numOfBadStudents = 0;
    auto it = S.begin();
    while (it->final < 5.0) {      // Count the number of students with final grade < 5
            numOfBadStudents ++;
            it ++;
    }

    GS.assign(it, S.end());        // Copy good students' data to the list
    S.resize(numOfBadStudents);    // Leave the list with the "bad students" data only
}

void sort (std::list<Student> &S, std::list<Student> &GS, char sortType) {
    if (sortType == 'v') {
        S.sort([](Student &s1, Student &s2) {return s1.name < s2.name;});
        GS.sort([](Student &s1, Student &s2) {return s1.name < s2.name;});
    } else if (sortType == 'p') {
        S.sort([](Student &s1, Student &s2) {return s1.surname < s2.surname;});
        GS.sort([](Student &s1, Student &s2) {return s1.surname < s2.surname;});
    }
}

void writeToFile(std::list<Student> &S, char finalType, std::string fileName) {
    std::ofstream fr (fileName);                // Open the results' file
    std::ostringstream row ("");                // Create empty row stringstream

    // Print header
    row << std::setw(20) << std::left << "Vardas" << std::setw(20) << "Pavarde" << "Galutinis ";
    fr << row.str();

    finalType == 'm' ? fr << "(Med.)\n" : fr << "(Vid.)\n";
    fr << "--------------------------------------------------------\n";

    auto it = S.begin();
    // Print students' data
    for (auto it = S.begin(); it != S.end(); it ++) {
        row.str("");        // Empty the row stream and add single student's data
        row << std::setw(20) << std::left << it->name << std::setw(20) << it->surname
            << std::fixed << std::setprecision(2) << it->final << "\n";
        fr << row.str();    // Print the completed row
    }
    fr.close();             // Close the results' file
}