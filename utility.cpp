#include "utility.h"

void utility (char inputType, char finalType, char sortType, int strategy, char measure, char advanced, std::string fileName) {
    std::vector<Student> S, GS, BS; // All students (S), good students (GS), bad students (BS)
    S.reserve(10000000);            // Max capacity to avoid memory overallocation
    Timer t;

    // Read data
    if (inputType == 'r' || inputType == 'g') {
        readEnteredData(S, inputType, finalType);
    } else {
        if (measure == 't') t.set();
        readFile(S, fileName, finalType);
        if (measure == 't') std::cout << "\n" << fileName << " failo skaitymas uztruko:\t" << t.elapsed() << "s\n";
    }
    S.shrink_to_fit();

    // Divide students into groups (from (S) to (S and GS) or (BS and GS))
    if (measure == 't') t.set();
    makeGroups(S, GS, BS, strategy, advanced);
    if (measure == 't') std::cout << "Studentu grupavimas uztruko:\t\t\t" << t.elapsed() << "s\n";

    // Sort results
    if (measure == 't') t.set();
    strategy == 1 ? sort(BS, GS, sortType) : sort(S, GS, sortType);
    if (measure == 't') std::cout << "Rezultatu rusiavimas uztruko:\t\t\t" << t.elapsed() << "s\n";

    // Write the results of grouped students into separate files
    if (measure == 't') t.set();
    writeToFile(GS, finalType, "patenkinami.txt");
    if (measure == 't') std::cout << "Pazangiuju rezultatu irasymas uztruko:\t\t" << t.elapsed() << "s\n";

    if (measure == 't') t.set();
    strategy == 1 ?  writeToFile(BS, finalType, "nepatenkinami.txt"): writeToFile(S, finalType, "nepatenkinami.txt");
    if (measure == 't') std::cout << "Nepazangiuju rezultatu irasymas uztruko:\t" << t.elapsed() << "s\n";
}