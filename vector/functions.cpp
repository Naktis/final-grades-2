#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

#include "functions.h"

void readFile (std::vector<Student> &S, std::string fileName) {
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
    temp.HW.reserve(numOfHW);

    int tempHW;
    std::string row;
    std::stringstream dataRow;
    while (std::getline(fd, row)) {         // Continue reading until the end of file is reached (raised error flag)
        dataRow.str(row);
        dataRow >> temp.name >> temp.surname;
        temp.HW.clear();                    // Empty the temporary homework vector and fill it with grades from the file
        for (int i = 0; i < numOfHW; i ++) {
            dataRow >> tempHW;
            temp.HW.push_back(tempHW);
        }
        dataRow >> temp.exam;
        S.push_back(temp);                  // Push the temporary structure to the vector of structures
    }
	fd.close();
}

double average (int* HW, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HW[i];
    return (sum / n); // Division by zero isn't possible since the function can't be called when n = 0
}

double median (int *HW, int n) {
    double m;
    std::sort(HW, HW + n);
    n % 2 == 0 ? (m = 1.00 * (HW[n / 2 - 1] + HW[n / 2]) / 2) : m = HW[n / 2];
    return m;
}

double finalGrade (Student* S, char type){
    double hw;
    if (!S->HW.empty())  // Calculate the homework grade only if the homework vector isn't empty
        type == 'm' ? hw = median(&S->HW[0], S->HW.size()) : hw = average(&S->HW[0], S->HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * S->exam);
}

void makeGroups (std::vector<Student> &S, std::vector<Student> &GS) {
    // Sort students by their final grades
    std::sort(S.begin(), S.end(), [](Student &s1, Student &s2) {return s1.final < s2.final;}); 

    int numOfBadStudents = 0;
    while (S[numOfBadStudents].final < 5.0)     // Count the number of students with final grade < 5
        numOfBadStudents ++;

    GS.reserve(S.size() - numOfBadStudents);    // Increase required capacity for the "good students" vector
    std::copy(S.begin() + numOfBadStudents, S.end(), std::back_inserter(GS)); // Copy "good students" into another vector

    S.resize(numOfBadStudents);                 // Leave vector with the "bad students" data only
    S.shrink_to_fit();                          // Shrink it to save memory
}

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

void generateGradesManually (Student* S) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count())); // Random number generator
    std::uniform_int_distribution<int> random10(1, 10);

    char moreGrades;
    std::cout << "\nGeneruojami namu darbu balai.\n\n";
    do {
        S->HW.push_back(random10(mt));                      // Generate a random h.w. grade between 1 and 10
        std::cout << "Sugeneruotas balas: " << S->HW.back() << "\nGeneruoti dar viena n.d. bala? (t/n) ";
        std::cin >> moreGrades;
        optionalInputValidation(moreGrades, 't', 'n');
    } while (moreGrades == 't');

    S->exam = random10(mt);                                 // Generate a random exam grade between 1 and 10
    std::cout << "Sugeneruotas egzamino balas: " << S->exam << "\n";
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

void sort (std::vector<Student> &S, std::vector<Student> &GS, char sortType) {
    if (sortType == 'v') {
        std::sort(S.begin(), S.end(), [](Student &s1, Student &s2) {return s1.name < s2.name;});
        std::sort(GS.begin(), GS.end(), [](Student &s1, Student &s2) {return s1.name < s2.name;});
    } else if (sortType == 'p') {
        std::sort(S.begin(), S.end(), [](Student &s1, Student &s2) {return s1.surname < s2.surname;});
        std::sort(GS.begin(), GS.end(), [](Student &s1, Student &s2) {return s1.surname < s2.surname;});
    }
}

void writeToFile(std::vector<Student> &S, char finalType, std::string fileName) {
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