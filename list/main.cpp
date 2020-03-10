#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <chrono>

#include "structure.h"
#include "functions.h"

int main () {
    std::list<Student> S, GS; // All students' (S) and "the good students"' (GS) data lists

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

    // Read data
    if (inputType == 'r' || inputType == 'g') {
        readEnteredData(S, inputType, finalType);
    } else {
        std::string fileName = getFileName();
        start = hrClock::now();
        readFile(S, fileName, finalType);
        end = hrClock::now();
        elapsed = end - start;
        std::cout << "\nFailo skaitymas uztruko: " << elapsed.count() << "s\n";
    }

    // Divide students into groups (from (S) to (S and GS))
    start = hrClock::now(); 
    makeGroups(S, GS);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "Studentu skirstymas uztruko: " << elapsed.count() << "s\n";

    // Sort results
    sort(S, GS, sortType);

    // Write the results of grouped students into separate files
    writeToFile(GS, finalType, "patenkinami.txt");
    writeToFile(S, finalType, "nepatenkinami.txt");

    std::cout << "\nProgramos pabaiga\n";
    return 0;
}