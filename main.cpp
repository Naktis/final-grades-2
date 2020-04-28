#include "utility.h"

int main () {
    Timer t;

    // Select performance measurement
    char measure;
    std::cout << "Ar norite matuoti kiekvieno programos etapo trukme? (t/n)\n";
    std::cin >> measure;
    optionalInputValidation(measure, 't', 'n');

    // Select input type (read from a file, generate or enter grades manually)
    char inputType;
    std::cout << "\nPasirinkite studentu balu ivesties buda:\n";
    std::cout << "Skaitymas is failo:\t  f\nAtsitiktinis generavimas: g\nRankinis ivedimas:\t  r\n"; 
    std::cin >> inputType;
    optionalInputValidation(inputType, 'f', 'g', 'r');

    // Select optimization algorithms
    char advanced;
    std::cout << "\nAr norite naudoti studentu skirstyma spartinancius algoritmus? (t/n)\n";
    std::cin >> advanced;
    optionalInputValidation(advanced, 't', 'n');

    // Select final grade calculation method (median or average)
    char finalType;
    std::cout << "\nPasirinkite namu darbu skaiciavimo buda:";
    std::cout << "\nMediana:\tm\nVidurkis:\tv\n";
    std::cin >> finalType;
    optionalInputValidation(finalType, 'm', 'v');

    // Select data partition strategy
    int strategy;
    std::cout << "\nPasirinkite studentu skirstymo i kategorijas strategija: \n";
    std::cout << "Kurti du naujus konteinerius:\t1\nKurti viena nauja konteineri: \t2\n";
    std::cin >> strategy;
    numberInputValidation(strategy, 1, 2);

    // Select sorting type (alphabetically of by final grades)
    char sortType;
    std::cout << "\nPasirinkite rezultatu rusiavimo buda:\n";
    std::cout << "Abeceliskai pagal varda:\tv\nAbeceliskai pagal pavarde:\tp\nPagal galutini bala:\t\tb\n"; 
    std::cin >> sortType;
    optionalInputValidation(sortType, 'v', 'p', 'b');

    // Select file generation
    char fileCount = '1';       // Number of files to read
    std::string genFiles[5];    // Array of generated files' names
    if (inputType == 'f') {
        char newFiles;
        std::cout << "\nAr norite generuoti naujus duomenu failus? (t/n)\n";
        std::cin >> newFiles;
        optionalInputValidation(newFiles, 't', 'n');

        // Generate files
        if (newFiles == 't') {
            int mulitplier = 1;
            if (measure == 't') std::cout << "\nDuomenu failu generavimo trukme:\n";

            for (int i = 0 ; i < 5; i ++) {
                if (measure == 't') t.set();
                createDataFile(1000 * mulitplier, genFiles[i]);
                std::cout << genFiles[i];
                measure == 't' ? std::cout << " - " << t.elapsed() << "s \n" : std::cout << " sugeneruotas\n";
                mulitplier *= 10;
            }

            // Select the number of files to read
            std::cout << "\nKiek failu norite perskaityti? (t/n)\n";
            std::cout << "Visus sugeneruotus:\t5\nTik viena:\t\t1\n"; 
            std::cin >> fileCount;
            optionalInputValidation(fileCount, '5', '1');
        }
    }

    // Read, group, sort and print data
    std::string fileName;
    for (int i = 0; i < fileCount - '0'; i ++) {
        if (inputType == 'f')
            fileCount == '5' ? fileName = genFiles[i] : fileName = getFileName();

        if (measure == 't') t.set();
        
        utility(inputType, finalType, sortType, strategy, measure, advanced, fileName);

        if (measure == 't') std::cout << "Is viso:\t\t\t\t\t" << t.elapsed() << "s \n";
        if (fileCount == '5') std::cout << "(" << i + 1 << "/5)\n";
    }

    std::cout << "\nProgramos pabaiga\n";
    return 0;
}