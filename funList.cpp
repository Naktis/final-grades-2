#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <list>

#include "funList.h"
#include "validation.h"
#include "structure.h"

void generateGradesManuallyList (Student* S, char finalType) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10);

    char moreGrades;
    std::list<int> HW;
    std::cout << "\nGeneruojami namu darbu balai.\n\n";
    do {
        HW.push_back(random10(mt)); // Generate a random h.w. grade
        std::cout << "Sugeneruotas balas: " << HW.back() << "\nGeneruoti dar viena n.d. bala? (t/n) ";
        std::cin >> moreGrades;
        optionalInputValidation(moreGrades, 't', 'n');
    } while (moreGrades == 't');

    int exam = random10(mt);       // Generate a random exam grade
    std::cout << "Sugeneruotas egzamino balas: " << exam << "\n";
    
    // Calculate the final grade and add it to the structure
    S->final = finalGradeList(HW, exam, finalType);
}

double averageList (std::list<int> &HW, int n) {
    double sum = 0;
    auto it = HW.begin();
    for (auto it = HW.begin(); it != HW.end(); it ++)
        sum += *(it);
    return (sum / n); // Division by zero isn't possible since the function can't be called when n = 0
}

double medianList (std::list<int> &HW, int n) {
    double m;
    HW.sort();                      // Sort values in ascending order

    auto it1 = HW.begin();          // Iterators for accessing middle values
    auto it2 = it1;
    std::advance(it1, n / 2 - 1);   // Move the iterator to the spot before the middle
    std::advance(it2, n / 2);       // Move the iterator to the middle spot

    n % 2 == 0 ? (m = 1.00 * (*it1 + *it2) / 2) : m = *it2; // Calculate median
    return m;
}

double finalGradeList (std::list<int> &HW, int exam, char type){
    double hw;
    if (!HW.empty())  // Calculate the homework grade only if the homework list isn't empty
        type == 'm' ? hw = medianList(HW, HW.size()) : hw = averageList(HW, HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * exam);
}

void readEnteredDataList (std::list<Student> &S, char inputType, char finalType) {
    char moreStudents = 'n';
    bool moreHW;
    int tempHW;       // Temporary homework grade for validation
    std::list<int> HW;
    Student temp;     // Temporary structure to be filled in before pushing back to the list
    int exam;
    do {
        moreHW = true;
        HW.clear();   // Empty the list for new values

        std::cout << "\nStudento vardas ir pavarde:\n";
        std::cin >> temp.name >> temp.surname;

        if (inputType == 'g')
            generateGradesManuallyList(&temp, finalType); // Generate homework and exam grades
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
            std::cin >> exam;
            numberInputValidation(exam, 1, 10);
            temp.final = finalGradeList(HW, exam, finalType);
        }
        S.push_back(temp);                      // Add the structure to the list of student data

        std::cout << "\nAr norite ivesti dar vieno studento duomenis? (t/n) ";
        std::cin >> moreStudents;
        optionalInputValidation(moreStudents, 't', 'n');
    } while (moreStudents == 't');
}

void readFileList (std::list<Student> &S, std::string fileName, char finalType) {
    std::ifstream fd (fileName);

    int numOfHW = 0;
    std::string header;
    std::getline(fd, header);            // Read the first line of the file
    std::stringstream firstRow (header); // Make it readable by copying it into a stringstream
    std::string str;
    while (firstRow >> str)              // Count the number of separate strings until the line reaches the end
        numOfHW ++;
    numOfHW -= 3;                        // Ignore the name, surname and exam strings

    Student temp;
    int tempHW, exam;
    std::string row;
    std::stringstream dataRow;
    std::list<int> HW;
    while (std::getline(fd, row)) { // Continue reading until the end of file is reached (raised error flag)
        dataRow.clear();
        dataRow.str(row);
        dataRow >> temp.name >> temp.surname;
        HW.clear();                 // Empty the temporary homework list and fill it with grades from the file
        for (int i = 0; i < numOfHW; i ++) {
            dataRow >> tempHW;
            HW.push_back(tempHW);
        }
        dataRow >> exam;
        temp.final = finalGradeList(HW, exam, finalType);
        S.push_back(temp);          // Push the temporary structure to the list of structures
    }
	fd.close();
}

void makeGroupsList (std::list<Student> &S, std::list<Student> &GS) {
    // Sort students by their final grades
    S.sort([](Student &s1, Student &s2) {return s1.final < s2.final;});

    // Count the number of students with final grade < 5
    int numOfBadStudents = 0;
    auto it = S.begin();
    while (it->final < 5.0 && it != S.end()) {
            numOfBadStudents ++;
            it ++;
    }

    GS.assign(it, S.end());        // Copy good students' data to another list
    S.resize(numOfBadStudents);    // Leave the list with the "bad students" data only
}

void sortList (std::list<Student> &S, std::list<Student> &GS, char sortType) {
    if (sortType == 'v') {
        S.sort([](Student &s1, Student &s2) {return s1.name < s2.name;});
        GS.sort([](Student &s1, Student &s2) {return s1.name < s2.name;});
    } else if (sortType == 'p') {
        S.sort([](Student &s1, Student &s2) {return s1.surname < s2.surname;});
        GS.sort([](Student &s1, Student &s2) {return s1.surname < s2.surname;});
    }
}

void writeToFileList (std::list<Student> &S, char finalType, std::string fileName) {
    std::ofstream fr (fileName);
    std::ostringstream row ("");

    // Print header
    row << std::setw(20) << std::left << "Vardas" << std::setw(20) << "Pavarde" << "Galutinis ";
    fr << row.str();

    finalType == 'm' ? fr << "(Med.)\n" : fr << "(Vid.)\n";
    fr << "--------------------------------------------------------\n";

    // Print students' data
    auto it = S.begin();
    for (auto it = S.begin(); it != S.end(); it ++) {
        row.str("");        // Empty the row stream and add single student's data
        row << std::setw(20) << std::left << it->name << std::setw(20) << it->surname
            << std::fixed << std::setprecision(2) << it->final << "\n";
        fr << row.str();    // Print the completed row
    }
    fr.close();
}