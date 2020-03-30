#include "containers.h"

void vector (char inputType, char finalType, char sortType, int strategy) {
    std::vector<Student> S, GS, BS; // All students (S), good students (GS), bad students (BS)
    S.reserve(10000000);            // Max capacity to avoid memory overallocation

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
    makeGroupsVector(S, GS, BS, strategy);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "Studentu skirstymas uztruko: " << elapsed.count() << "s\n";

    // Sort results
    strategy == 1 ? sortVector(BS, GS, sortType) : sortVector(S, GS, sortType);

    // Write the results of grouped students into separate files
    writeToFileVector(GS, finalType, "patenkinami.txt");
    strategy == 1 ?  writeToFileVector(BS, finalType, "nepatenkinami.txt") : writeToFileVector(S, finalType, "nepatenkinami.txt");

}

void deque (char inputType, char finalType, char sortType, int strategy) {
    std::deque<Student> S, GS, BS; // All students (S), good students (GS), bad students (BS)

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
    makeGroupsDeque(S, GS, BS, strategy);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "Studentu skirstymas uztruko: " << elapsed.count() << "s\n";

    // Sort results
    strategy == 1 ? sortDeque(BS, GS, sortType) : sortDeque(S, GS, sortType);

    // Write the results of grouped students into separate files
    writeToFileDeque(GS, finalType, "patenkinami.txt");
    strategy == 1 ? writeToFileDeque(BS, finalType, "nepatenkinami.txt") : writeToFileDeque(S, finalType, "nepatenkinami.txt");
}

void list (char inputType, char finalType, char sortType, int strategy) {
    std::list<Student> S, GS, BS; // All students (S), good students (GS), bad students (BS)

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
    makeGroupsList(S, GS, BS, strategy);
    end = hrClock::now();
    elapsed = end - start;
    std::cout << "Studentu skirstymas uztruko: " << elapsed.count() << "s\n";

    // Sort results
    strategy == 1 ? sortList(BS, GS, sortType) : sortList(S, GS, sortType);

    // Write the results of grouped students into separate files
    writeToFileList(GS, finalType, "patenkinami.txt");
    strategy == 1 ? writeToFileList(BS, finalType, "nepatenkinami.txt") : writeToFileList(S, finalType, "nepatenkinami.txt");
}