#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

#include "structure.h"
#include "functions.h"

int main () {
    std::vector<Student> S, GS; // All students' (S) and "the good students"' (GS) data vectors
    S.reserve(10000000);        // Max capacity to avoid memory overallocation

    // Timer properties
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Select file generation
    char newFiles;
    std::cout << "Ar norite generuoti naujus duomenu failus? (t/n)\n";
    std::cin >> newFiles;
    optionalInputValidation(newFiles, 't', 'n');

    // Generate files
    if (newFiles == 't') {
        int mulitplier = 1;
        std::cout << "\nDuomenu failu generavimo trukme:\n";
        for (int i = 0 ; i < 5; i ++) {
            start = hrClock::now();
            createDataFile(1000 * mulitplier);
            std::cout << "kursiokai" << 1000 * mulitplier << ".txt - ";
            mulitplier *= 10;
            end = hrClock::now();
            elapsed = end - start;
            std::cout << elapsed.count() << "s \n";
        }
    }

    // Select input type (read from a file, generate or enter grades manually)
    char inputType;
    std::cout << "\nPasirinkite studentu balu ivesties buda:\n";
    std::cout << "Skaitymas is failo:\t  f\nAtsitiktinis generavimas: g\nRankinis ivedimas:\t  r\n"; 
    std::cin >> inputType;
    optionalInputValidation(inputType, 'f', 'g', 'r');

    // Get the name of the student data file
    std::string fileName;
    if (inputType == 'f') {
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
    }

    // Select sorting type (alphabetically of by final grades)
    char sortType;
    std::cout << "\nPasirinkite rezultatu rusiavimo buda:\n";
    std::cout << "Abeceliskai pagal varda:\tv\nAbeceliskai pagal pavarde:\tp\nPagal galutini bala:\t\tb\n"; 
    std::cin >> sortType;
    optionalInputValidation(sortType, 'v', 'p', 'b');

    // Select final grade calculation method (median or average)
    char finalType;
    std::cout << "\nPasirinkite namu darbu skaiciavimo buda:";
    std::cout << "\nMediana:\tm\nVidurkis:\tv\n";
    std::cin >> finalType;
    optionalInputValidation(finalType, 'm', 'v');

    // Enter/generate grades manually
    if (inputType == 'r' || inputType == 'g') {
        char moreStudents = 'n';
        bool moreHW;
        int tempHW;       // Temporary homework value for validation
        Student temp;     // Temporary structure to be filled in before pushing back to the vector
        do {
            moreHW = true;
            temp.HW.clear();                        // Empty the vector for new values

            std::cout << "\nStudento vardas ir pavarde:\n";
            std::cin >> temp.name >> temp.surname;

            if (inputType == 'g')
                generateGradesManually(&temp);      // Generate homework and exam grades
            else {
                std::cout << "\nIveskite namu darbu balus, atskirtus paspaudus'enter'. Po paskutinio balo iveskite 0:\n";
                do {
                    std::cin >> tempHW;
                    numberInputValidation(tempHW, 0, 10);
                    if (tempHW == 0)
                        moreHW = false;             // Terminate the loop, if 0 is entered
                    else temp.HW.push_back(tempHW); // Add the entered grade to the homework vector
                } while (moreHW);                   // Continue the loop, if it's wanted to enter more h.w. grades
                temp.HW.shrink_to_fit();

                std::cout << "\nEgzamino balas:\n";
                std::cin >> temp.exam;
                numberInputValidation(temp.exam, 1, 10);
            }
            S.push_back(temp);                      // Add the structure to the vector of student data

            std::cout << "\nAr norite ivesti dar vieno studento duomenis? (t/n) ";
            std::cin >> moreStudents;
            optionalInputValidation(moreStudents, 't', 'n');
        } while (moreStudents == 't');
    } else {
        start = hrClock::now();
        readFile(S, fileName);                   // Read student data from a file
        end = hrClock::now();
        elapsed = end - start;
        std::cout << "\nFailo skaitymas uztruko: " << elapsed.count() << "s\n";
    }
    S.shrink_to_fit();

    // Calculate final grades
    for (int i = 0; i < S.size(); i ++)
        S[i].final = finalGrade(&S[i], finalType);

    // Divide students into groups (from (S) to (S and GS))
    start = hrClock::now(); 
    makeGroups(S, GS);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "\nStudentu skirstymas uztruko: " << elapsed.count() << "s\n";

    // Sort results
    sort(S, GS, sortType);

    // Write "the good students"' results into a file
    start = hrClock::now(); 
    writeToFile(GS, finalType, "patenkinami.txt");
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "\nLaiminguju rezultatu irasymas uztruko: " << elapsed.count() << "s";

    // Write "the bad students"' results into a file
    start = hrClock::now(); 
    writeToFile(S, finalType, "nepatenkinami.txt");
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "\nNeaiminguju rezultatu irasymas uztruko: " << elapsed.count() << "s\n";

    std::cout << "Programos pabaiga\n";
    return 0;
}