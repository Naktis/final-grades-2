#include "containers.h"

void vectorContainer (char inputType, char finalType, char sortType, int strategy, char measure, char advanced, std::string fileName) {
    std::vector<Student> S, GS, BS; // All students (S), good students (GS), bad students (BS)
    S.reserve(10000000);            // Max capacity to avoid memory overallocation
    Timer t;

    // Read data
    if (inputType == 'r' || inputType == 'g') {
        readEnteredDataVector(S, inputType, finalType);
    } else {
        if (measure == 't') t.set();
        readFileVector(S, fileName, finalType);
        if (measure == 't') std::cout << "\n" << fileName << " failo skaitymas uztruko:\t" << t.elapsed() << "s\n";
    }
    S.shrink_to_fit();

    // Divide students into groups (from (S) to (S and GS))
    if (measure == 't') t.set();
    makeGroupsVector(S, GS, BS, strategy, advanced);
    if (measure == 't') std::cout << "Studentu grupavimas uztruko:\t\t\t" << t.elapsed() << "s\n";

    // Sort results
    if (measure == 't') t.set();
    strategy == 1 ? sortVector(BS, GS, sortType) : sortVector(S, GS, sortType);
    if (measure == 't') std::cout << "Rezultatu rusiavimas uztruko:\t\t\t" << t.elapsed() << "s\n";

    // Write the results of grouped students into separate files
    if (measure == 't') t.set();
    writeToFileVector(GS, finalType, "patenkinami.txt");
    if (measure == 't') std::cout << "Pazangiuju rezultatu irasymas uztruko:\t\t" << t.elapsed() << "s\n";

    if (measure == 't') t.set();
    strategy == 1 ?  writeToFileVector(BS, finalType, "nepatenkinami.txt"): writeToFileVector(S, finalType, "nepatenkinami.txt");
    if (measure == 't') std::cout << "Nepazangiuju rezultatu irasymas uztruko:\t" << t.elapsed() << "s\n";
}

void dequeContainer (char inputType, char finalType, char sortType, int strategy, char measure, std::string fileName) {
    std::deque<Student> S, GS, BS; // All students (S), good students (GS), bad students (BS)
    Timer t;

    // Read data
    if (inputType == 'r' || inputType == 'g') {
        readEnteredDataDeque(S, inputType, finalType);
    } else {
        if (measure == 't') t.set();
        readFileDeque(S, fileName, finalType);
        if (measure == 't') std::cout << "\n" << fileName << " failo skaitymas uztruko:\t" << t.elapsed() << "s\n";
    }    

    // Divide students into groups (from (S) to (S and GS))
    if (measure == 't') t.set();
    makeGroupsDeque(S, GS, BS, strategy);
    if (measure == 't') std::cout << "Studentu skirstymas uztruko:\t\t\t" << t.elapsed() << "s\n";

    // Sort results
    if (measure == 't') t.set();
    strategy == 1 ? sortDeque(BS, GS, sortType) : sortDeque(S, GS, sortType);
    if (measure == 't') std::cout << "Rezultatu rusiavimas uztruko:\t\t\t" << t.elapsed() << "s\n";
    
    // Write the results of grouped students into separate files
    if (measure == 't') t.set();
    writeToFileDeque(GS, finalType, "patenkinami.txt");
    if (measure == 't') std::cout << "Pazangiuju rezultatu irasymas uztruko:\t\t" << t.elapsed() << "s\n";

    if (measure == 't') t.set();
    strategy == 1 ? writeToFileDeque(BS, finalType, "nepatenkinami.txt") : writeToFileDeque(S, finalType, "nepatenkinami.txt");
    if (measure == 't') std::cout << "Nepazangiuju rezultatu irasymas uztruko:\t" << t.elapsed() << "s\n";
}

void listContainer (char inputType, char finalType, char sortType, int strategy, char measure, std::string fileName) {
    std::list<Student> S, GS, BS; // All students (S), good students (GS), bad students (BS)
    Timer t;

    // Read data
    if (inputType == 'r' || inputType == 'g') {
        readEnteredDataList(S, inputType, finalType);
    } else {
        if (measure == 't') t.set();
        readFileList(S, fileName, finalType);
        if (measure == 't') std::cout << "\n" << fileName << " failo skaitymas uztruko:\t" << t.elapsed() << "s\n";
    }

    // Divide students into groups (from (S) to (S and GS))
    if (measure == 't') t.set(); 
    makeGroupsList(S, GS, BS, strategy);
    if (measure == 't') std::cout << "Studentu skirstymas uztruko:\t\t\t" << t.elapsed() << "s\n";
    
    // Sort results
    if (measure == 't') t.set();
    strategy == 1 ? sortList(BS, GS, sortType) : sortList(S, GS, sortType);
    if (measure == 't') std::cout << "Rezultatu rusiavimas uztruko:\t\t\t" << t.elapsed() << "s\n";

    // Write the results of grouped students into separate files
    if (measure == 't') t.set();
    writeToFileList(GS, finalType, "patenkinami.txt");
    if (measure == 't') std::cout << "Pazangiuju rezultatu irasymas uztruko:\t\t" << t.elapsed() << "s\n";

    if (measure == 't') t.set();
    strategy == 1 ? writeToFileList(BS, finalType, "nepatenkinami.txt") : writeToFileList(S, finalType, "nepatenkinami.txt");
    if (measure == 't') std::cout << "Nepazangiuju rezultatu irasymas uztruko:\t" << t.elapsed() << "s\n";
}