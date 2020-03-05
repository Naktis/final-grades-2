#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

#include "structure.h"
#include "functions.h"

int main () {
    using hrClock = std::chrono::high_resolution_clock;
    std::vector<Student> S;                    // Vector for all student data
    std::vector<Student> HL, LL;               // Vectors of high level (HL) and low level (LL) students
    char finalType;                            // Can be equal to 'm' (median) or 'v' (average)
    char inputType;                            // Can be equal to 'f' (file), 'g' (generate) or 'r' (manual)
    S.reserve(10000000);

    double createTime[5];
    double readTime, sortTime, printTime;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;
    std::string fileName;

    char newFiles;
    std::cout << "Ar norite generuoti naujus duomenu failus? (t/n)\n";
    std::cin >> newFiles;
    optionalInputValidation(newFiles, 't', 'n');
    if (newFiles == 't') {
        int mulitplier = 1;
        std::cout << "\nDuomenu failu generavimo trukme:\n";
        for (int i = 0 ; i < 5; i ++) {
            start = hrClock::now();
            createDataFile(1000 * mulitplier);
            std::cout << 1000 * mulitplier << " studentu - ";
            mulitplier *= 10;
            end = hrClock::now();
            elapsed = end - start;
            createTime[i] = elapsed.count();
            std::cout << createTime[i] << "s \n";
        }
    }

    std::cout << "\nPasirinkite studentu balu ivesties buda:\n";
    std::cout << "Skaitymas is failo:\t  f\nAtsitiktinis generavimas: g\nRankinis ivedimas:\t  r\n"; 
    std::cin >> inputType;                      // Read and validate the entered input type
    optionalInputValidation(inputType, 'f', 'g', 'r');

    if (inputType == 'f') {
        bool badFile;
        std::cout << "\nIveskite failo varda formatu failo_pav.txt\n";
        std::cin >> fileName;
        do {
            try {
                std::ifstream in (fileName);
                if (!in.good())                     // Check if the data file exists
                    throw 404;
                else {
                    in.close();
                    badFile = false;
                }
            } catch (int exception) {               // If it doesn't, let user choose another input option
                badFile = true;
                std::cout << "Duomenu failas " << fileName << " neegzistuoja. Iveskite esamo failo varda:\n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> fileName;
            }
        } while (badFile);
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
                generateGradesManually(&temp);              // Generate homework and exam grades
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
    } else readFile(S, fileName);                             // Read student data from a file
    S.shrink_to_fit();

    // Calculate final grades
    for (int i = 0; i < S.size(); i ++)
        S[i].final = finalGrade(S[i], finalType);

    start = hrClock::now(); 
    makeGroups(S, HL, LL);
    end = hrClock::now();
    elapsed = end - start;
    sortTime = elapsed.count();
    std::cout << "\nStudentu rusiavimas uztruko: " << sortTime << "s\n";

    // Sort lines of student data alphabetically by the student's name
    std::sort(HL.begin(), HL.end(), [](Student &s1, Student &s2) {return s1.name < s2.name;});
    std::sort(LL.begin(), LL.end(), [](Student &s1, Student &s2) {return s1.name < s2.name;});

    start = hrClock::now(); 
    writeToFile(HL, finalType, "patenkinami.txt");
    end = hrClock::now();
    elapsed = end - start;
    sortTime = elapsed.count();
    std::cout << "\nLaiminguju rezultatu irasymas uztruko: " << sortTime << "s";

    start = hrClock::now(); 
    writeToFile(LL, finalType, "nepatenkinami.txt");
    end = hrClock::now();
    elapsed = end - start;
    sortTime = elapsed.count();
    std::cout << "\nNeaiminguju rezultatu irasymas uztruko: " << sortTime << "s\n";
    return 0;
}