#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

struct Student {
    std::string name, surname;
    int exam;
    double final;
    std::vector<int> HW;                    // Vector of homework grades
};

void readFile (std::vector<Student> &S) {
    std::ifstream fd ("kursiokai.txt");     // Open the file of students' data
    int numOfHW = 0;

    if (fd.good()) {
        std::string firstLine;
        std::getline(fd, firstLine);        // Read the first line of the file
        std::stringstream ss (firstLine);   // Make it readable by copying it into a stringstream
        std::string str;
        while (ss >> str)                   // Count the number of separate strings until the line reaches the end
            numOfHW ++;
        numOfHW -= 3;                       // Ignore the name, surname and exam strings
    }

    Student temp;
    int tempHW;
    do {                                    // Read single student's data into a temporary structure
        fd >> temp.name >> temp.surname;
        temp.HW.clear();                    // Empty the temporary homework vector and fill it with grades from the file
        for (int i = 0; i < numOfHW; i ++) {
            fd >> tempHW;
            temp.HW.push_back(tempHW);
        }
        fd >> temp.exam;
        S.push_back(temp);                  // Push the temporary structure to the vector of structures
    } while (!fd.eof());                    // Continue reading until the end of file is reached
	fd.close();                             // Close the file
}

double average (int* HW, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HW[i];
    return (sum / n); // Division by zero isn't possible since the function can't be called when n = 0
}

double median (int *HW, int n) {
    double m;
    std::sort(HW, HW + n - 1);
    n % 2 == 0 ? (m = 1.00 * (*(HW + (n / 2) - 1) + *(HW + (n / 2))) / 2) : m = *(HW + (n / 2) - 1);
    return m;
}

double finalGrade (Student* S, char type){
    double hw;
    if (!S->HW.empty())  // Calculate the homework grade only if the homework vector isn't empty
        type == 'm' ? hw = median(&S->HW[0], S->HW.size()) : hw = average(&S->HW[0], S->HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * S->exam);
}

// Functions which check if the input contains one of the asked options and asks to to reenter data, if it doesn't
void optionalInputValidation (char& input, char option1, char option2) {
    while (!(input == option1 || input == option2)) {
        std::cout << "Klaida. Pasirinkite viena is variantu (" << option1 << "/" << option2 << ") \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

// Overloaded function with 4 parameters
void optionalInputValidation (char& input, char option1, char option2, char option3) {
    while (!(input == option1 || input == option2 || input == option3)) {
        std::cout << "Klaida. Pasirinkite viena is variantu (" << option1 << "/" << option2  << "/" << option3 << ") \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

// Function which checks if the input is number-only and asks to reenter data, if it's not
void numberInputValidation (int& input, int lowest, int highest) {
    while (input < lowest || input > highest || std::cin.fail()) {
        std::cout << "Klaida. Pasirinkite skaiciu is intervalo [" << lowest << " ; " << highest << "] \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

void generateGrades (Student* S) {
    char moreGrades;
    using hrClock = std::chrono::high_resolution_clock; // System clock for random seed
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count())); // Random number generator
    std::uniform_int_distribution<int> dist(1, 10);     // Data type and interval for a random number

    std::cout << "\nGeneruojami namu darbu balai.\n\n";
    do {
        S->HW.push_back(dist(mt));                      // Generate a random h.w. grade between 1 and 10
        std::cout << "Sugeneruotas balas: " << S->HW.back() << "\nGeneruoti dar viena n.d. bala? (t/n) ";
        std::cin >> moreGrades;
        optionalInputValidation(moreGrades, 't', 'n');
    } while (moreGrades == 't');

    S->exam = dist(mt);                                 // Generate a random exam grade between 1 and 10
    std::cout << "Sugeneruotas egzamino balas: " << S->exam << "\n";
}

void writeToFile(std::vector<Student> &S, char finalType) {
    std::ofstream fr ("rezultatai.txt");                // Open the results' file
    
    fr << "Vardas\t\t\tPavarde\t\t\tGalutinis ";        // Print header text
    finalType == 'm' ? fr << "(Med.)\n" : fr << "(Vid.)\n";
    for (int i = 0; i < S.size(); i ++)                 // Print students' names, surnames and final grades
        fr << std::setw(10) << std::left << S[i].name << "\t\t" << S[i].surname << "\t\t" << std::fixed << std::setprecision(2) << S[i].final << "\n";

    fr.close();                                         // Close the results' file
}

int main () {
    std::vector<Student> S;                    // Vector for student data
    char finalType;                            // Can be equal to 'm' (median) or 'v' (average)
    char inputType;                            // Can be equal to 'f' (file), 'g' (generate) or 'r' (manual)

    std::cout << "Pasirinkite studentu balu ivesties buda:\n";
    std::cout<< "Skaitymas is failo:\t  f\nAtsitiktinis generavimas: g\nRankinis ivedimas:\t  r\n"; 
    std::cin >> inputType;                      // Read and validate the entered input type
    optionalInputValidation(inputType, 'f', 'g', 'r');

    std::cout << "\nPasirinkite namu darbu skaiciavimo buda:";
    std::cout << "\nMediana:\tm\nVidurkis:\tv\n";
    std::cin >> finalType;                      // Read and validate the entered type of final grade
    optionalInputValidation(finalType, 'm', 'v');

    if (inputType == 'r' || inputType == 'g') {
        char moreStudents = 'n';                // Variables for input validation
        bool moreHW;
        int tempHW;
        Student temp;                           // Temporary structure to be filled in before pushing back to the vector
        do {
            moreHW = true;
            temp.HW.clear();                        // Empty the temporary student data vector

            std::cout << "\nStudento vardas ir pavarde:\n";
            std::cin >> temp.name >> temp.surname;  // Read and validate student's surname and name

            if (inputType == 'g')
                generateGrades(&temp);              // Generate homework and exam grades
            else {
                std::cout << "\nIveskite namu darbu balus, atskirtus paspaudus'enter'. Po paskutinio balo iveskite 0:\n";
                do {
                    std::cin >> tempHW;             // Read and validate the entered homework grade
                    numberInputValidation(tempHW, 0, 10);
                    if (tempHW == 0)
                        moreHW = false;             // Terminate the loop, if 0 is entered
                    else temp.HW.push_back(tempHW); // Add the entered grade to the homework vector
                } while (moreHW);                   // Continue the loop, if it's wanted to enter more h.w. grades
                temp.HW.shrink_to_fit();            // Free unused space that the vector has reserved
                std::cout << "\nEgzamino balas:\n";
                std::cin >> temp.exam;              // Read and validate the entered exam grade
                numberInputValidation(temp.exam, 1, 10);
            }
            S.push_back(temp);                      // Add the structure to the vector of student data

            std::cout << "\nAr norite ivesti dar vieno studento duomenis? (t/n) ";
            std::cin >> moreStudents;               // Read and validate if it's wanted to enter data of more students
            optionalInputValidation(moreStudents, 't', 'n');
        } while (moreStudents == 't');              // Continue the loop, if there's more student data
    } else readFile(S);                             // Read student data from a file
    S.shrink_to_fit();

    // Calculate final grades
    for (int i = 0; i < S.size(); i ++)
        S[i].final = finalGrade(&S[i], finalType);

    // Sort lines of student data alphabetically by the student's name
    std::sort(S.begin(), S.end(), [](Student &s1, Student &s2) {return s1.name < s2.name;});

    writeToFile(S, finalType);
    std::cout << "\nRezulatai irasyti i faila rezultatai.txt";
    return 0;
}