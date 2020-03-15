#include <iostream>
#include <chrono>

#include "validation.h" // optionalInputValidation functions
#include "containers.h" // vector, list and deque functions
#include "file.h"       // createDataFile function

int main () {
    // Timer properties
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Select a std container
    char container;
    std::cout << "Pasirinkite konteineri darbui su duomenimis: \n";
    std::cout << "std::vector:\tv\nstd::list:\tl\nstd::deque:\td\n";
    std::cin >> container;
    optionalInputValidation(container, 'v', 'l', 'd');

    // Select file generation
    char newFiles;
    std::cout << "\nAr norite generuoti naujus duomenu failus? (t/n)\n";
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

    // Call the function of the chosen container to read, modify and print data
    if (container == 'v')
        vector(inputType, finalType, sortType);
    else if (container == 'd')
        deque(inputType, finalType, sortType);
    else list(inputType, finalType, sortType);

    std::cout << "Programos pabaiga\n";
    return 0;
}