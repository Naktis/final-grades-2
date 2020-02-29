#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "structure.h"
#include "functions.h"

int main () {
    std::vector<Student> S;                    // Vector for student data
    char finalType;                            // Can be equal to 'm' (median) or 'v' (average)
    char inputType;                            // Can be equal to 'f' (file), 'g' (generate) or 'r' (manual)

    std::cout << "Pasirinkite studentu balu ivesties buda:\n";
    std::cout<< "Skaitymas is failo:\t  f\nAtsitiktinis generavimas: g\nRankinis ivedimas:\t  r\n"; 
    std::cin >> inputType;                      // Read and validate the entered input type
    optionalInputValidation(inputType, 'f', 'g', 'r');

    if (inputType == 'f') {
        try {
            std::ifstream in ("kursiokai.txt");
            if (!in.good())                     // Check if data file exists
                throw 404;
            else in.close();
        } catch (int exception) {               // If it doesn't, let user choose another input option
            std::cout << "Duomenu failas neegzistuoja. Pasirinkite kita varianta (g/r)\n";
            reenterInput(inputType);
            optionalInputValidation(inputType, 'g', 'r');
        }
    }

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
    return 0;
}