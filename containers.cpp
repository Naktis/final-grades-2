#include "containers.h"

void vector (char inputType, char finalType, char sortType) {
    std::vector<Student> S, GS; // All students' (S) and "the good students"' (GS) data vectors
    S.reserve(10000000);        // Max capacity to avoid memory overallocation

    // Timer properties
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Read data
    if (inputType == 'r' || inputType == 'g') {
        readEnteredDataVector(S, inputType, finalType);
    } else {
        std::string fileName = getFileName();
        start = hrClock::now();
        readFileVector(S, fileName, finalType);
        end = hrClock::now();
        elapsed = end - start;
        std::cout << "\nFailo skaitymas uztruko: " << elapsed.count() << "s\n";
    }
    S.shrink_to_fit();

    // Divide students into groups (from (S) to (S and GS))
    start = hrClock::now(); 
    makeGroupsVector(S, GS);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "Studentu skirstymas uztruko: " << elapsed.count() << "s\n";

    // Sort results
    sortVector(S, GS, sortType);

    // Write the results of grouped students into separate files
    writeToFileVector(GS, finalType, "patenkinami.txt");
    writeToFileVector(S, finalType, "nepatenkinami.txt");
}

void deque (char inputType, char finalType, char sortType) {
    std::deque<Student> S, GS; // All students' (S) and "the good students"' (GS) data deques

    // Timer properties
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Read data
    if (inputType == 'r' || inputType == 'g') {
        readEnteredDataDeque(S, inputType, finalType);
    } else {
        std::string fileName = getFileName();
        start = hrClock::now();
        readFileDeque(S, fileName, finalType);
        end = hrClock::now();
        elapsed = end - start;
        std::cout << "\nFailo skaitymas uztruko: " << elapsed.count() << "s\n";
    }

    // Divide students into groups (from (S) to (S and GS))
    start = hrClock::now(); 
    makeGroupsDeque(S, GS);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "\nStudentu skirstymas uztruko: " << elapsed.count() << "s\n";

    // Sort results
    sortDeque(S, GS, sortType);

    // Write the results of grouped students into separate files
    writeToFileDeque(GS, finalType, "patenkinami.txt");
    writeToFileDeque(S, finalType, "nepatenkinami.txt");
}

void list (char inputType, char finalType, char sortType) {
    std::list<Student> S, GS; // All students' (S) and "the good students"' (GS) data lists

    // Timer properties
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed;

    // Read data
    if (inputType == 'r' || inputType == 'g') {
        readEnteredDataList(S, inputType, finalType);
    } else {
        std::string fileName = getFileName();
        start = hrClock::now();
        readFileList(S, fileName, finalType);
        end = hrClock::now();
        elapsed = end - start;
        std::cout << "\nFailo skaitymas uztruko: " << elapsed.count() << "s\n";
    }

    // Divide students into groups (from (S) to (S and GS))
    start = hrClock::now(); 
    makeGroupsList(S, GS);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "Studentu skirstymas uztruko: " << elapsed.count() << "s\n";

    // Sort results
    sortList(S, GS, sortType);

    // Write the results of grouped students into separate files
    writeToFileList(GS, finalType, "patenkinami.txt");
    writeToFileList(S, finalType, "nepatenkinami.txt");
}