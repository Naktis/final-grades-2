#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <deque>

#include "funDeque.h"
#include "validation.h"
#include "structure.h"

void generateGradesManuallyDeque (Student* S, char finalType) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count())); // Random number generator
    std::uniform_int_distribution<int> random10(1, 10);

    char moreGrades;
    std::deque<int> HW;
    std::cout << "\nGeneruojami namu darbu balai.\n\n";
    do {
        HW.push_back(random10(mt));                      // Generate a random h.w. grade between 1 and 10
        std::cout << "Sugeneruotas balas: " << HW.back() << "\nGeneruoti dar viena n.d. bala? (t/n) ";
        std::cin >> moreGrades;
        optionalInputValidation(moreGrades, 't', 'n');
    } while (moreGrades == 't');

    int exam = random10(mt);                                 // Generate a random exam grade between 1 and 10
    std::cout << "Sugeneruotas egzamino balas: " << exam << "\n";
    
    S->final = finalGradeDeque(HW, exam, finalType);
}

double averageDeque (std::deque<int> &HW, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HW[i];
    return (sum / n); // Division by zero isn't possible since the function can't be called when n = 0
}

double medianDeque (std::deque<int> &HW, int n) {
    double m;
    std::sort(HW.begin(), HW.end());
    n % 2 == 0 ? (m = 1.00 * (HW[n / 2 - 1] + HW[n / 2]) / 2) : m = HW[n / 2];
    return m;
}

double finalGradeDeque (std::deque<int> &HW, int exam, char type) {
    double hw;
    if (!HW.empty())  // Calculate the homework grade only if the homework list isn't empty
        type == 'm' ? hw = medianDeque(HW, HW.size()) : hw = averageDeque(HW, HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * exam);
}

void readEnteredDataDeque (std::deque<Student> &S, char inputType, char finalType) {
    char moreStudents = 'n';
    bool moreHW;
    int tempHW;       // Temporary homework value for validation
    Student temp;     // Temporary structure to be filled in before pushing back to the deque
    std::deque<int> HW;
    int exam;
    do {
        moreHW = true;
        HW.clear();                        // Empty the deque for new values

        std::cout << "\nStudento vardas ir pavarde:\n";
        std::cin >> temp.name >> temp.surname;

        if (inputType == 'g')
            generateGradesManuallyDeque(&temp, finalType);      // Generate homework and exam grades
        else {
            std::cout << "\nIveskite namu darbu balus, atskirtus paspaudus'enter'. Po paskutinio balo iveskite 0:\n";
            do {
                std::cin >> tempHW;
                numberInputValidation(tempHW, 0, 10);
                if (tempHW == 0)
                    moreHW = false;             // Terminate the loop, if 0 is entered
                else HW.push_back(tempHW); // Add the entered grade to the homework deque
            } while (moreHW);                   // Continue the loop, if it's wanted to enter more h.w. grades
            HW.shrink_to_fit();

            std::cout << "\nEgzamino balas:\n";
            std::cin >> exam;
            numberInputValidation(exam, 1, 10);
            temp.final = finalGradeDeque(HW, exam, finalType);
        }
        S.push_back(temp);                      // Add the structure to the deque of student data

        std::cout << "\nAr norite ivesti dar vieno studento duomenis? (t/n) ";
        std::cin >> moreStudents;
        optionalInputValidation(moreStudents, 't', 'n');
    } while (moreStudents == 't');
}

void readFileDeque (std::deque<Student> &S, std::string fileName, char finalType) {
    std::ifstream fd (fileName);

    int numOfHW = 0;
    std::string header;
    std::getline(fd, header);            // Read the first line of the file
    std::istringstream firstRow (header);// Make it readable by copying it into a stringstream
    std::string str;
    while (firstRow >> str)              // Count the number of separate strings until the line reaches the end
        numOfHW ++;
    numOfHW -= 3;                        // Ignore the name, surname and exam strings

    Student temp;
    int tempHW, exam;
    std::string row;
    std::istringstream dataRow;
    std::deque<int> HW;
    while (std::getline(fd, row)) {      // Continue reading until the end of file is reached (raised error flag)
        dataRow.str(row);
        dataRow >> temp.name >> temp.surname;
        HW.clear();                      // Empty the temporary homework deque and fill it with grades from the file
        for (int i = 0; i < numOfHW; i ++) {
            dataRow >> tempHW;
            HW.push_back(tempHW);
        }
        dataRow >> exam;
        temp.final = finalGradeDeque(HW, exam, finalType);
        S.push_back(temp);               // Push the temporary structure to the deque of structures
    }
	fd.close();
}

void makeGroupsDeque (std::deque<Student> &S, std::deque<Student> &GS) {
    // Sort students by their final grades
    std::sort(S.begin(), S.end(), [](Student &s1, Student &s2) {return s1.final < s2.final;}); 

    int numOfBadStudents = 0;
    while (S[numOfBadStudents].final < 5.0 && numOfBadStudents != S.size())  // Count the number of students with final grade < 5
        numOfBadStudents ++;

    std::copy(S.begin() + numOfBadStudents, S.end(), std::back_inserter(GS)); // Copy "good students" into another deque

    S.resize(numOfBadStudents);                 // Leave deque with the "bad students" data only
    S.shrink_to_fit();                          // Shrink it to save memory
}

void sortDeque (std::deque<Student> &S, std::deque<Student> &GS, char sortType) {
    if (sortType == 'v') {
        std::sort(S.begin(), S.end(), [](Student &s1, Student &s2) {return s1.name < s2.name;});
        std::sort(GS.begin(), GS.end(), [](Student &s1, Student &s2) {return s1.name < s2.name;});
    } else if (sortType == 'p') {
        std::sort(S.begin(), S.end(), [](Student &s1, Student &s2) {return s1.surname < s2.surname;});
        std::sort(GS.begin(), GS.end(), [](Student &s1, Student &s2) {return s1.surname < s2.surname;});
    }
}

void writeToFileDeque (std::deque<Student> &S, char finalType, std::string fileName) {
    std::ofstream fr (fileName);                // Open the results' file
    std::ostringstream row ("");                // Create empty row stringstream

    // Print header
    row << std::setw(20) << std::left << "Vardas" << std::setw(20) << "Pavarde" << "Galutinis ";
    fr << row.str();

    finalType == 'm' ? fr << "(Med.)\n" : fr << "(Vid.)\n";
    fr << "--------------------------------------------------------\n";

    // Print students' data
    for (int i = 0; i < S.size(); i ++) {
        row.str("");        // Empty the row stream and add single student's data
        row << std::setw(20) << std::left << S[i].name << std::setw(20) << S[i].surname
            << std::fixed << std::setprecision(2) << S[i].final << "\n";
        fr << row.str();    // Print the completed row
    }
    fr.close();             // Close the results' file
}