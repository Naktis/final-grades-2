#include "funVector.h"

void generateGradesManuallyVector (Student* S, char finalType) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count())); // Random number generator
    std::uniform_int_distribution<int> random10(1, 10);

    char moreGrades;
    std::vector<int> HW;
    std::cout << "\nGeneruojami namu darbu balai.\n\n";
    do {
        HW.push_back(random10(mt)); // Generate a random h.w. grade between 1 and 10
        std::cout << "Sugeneruotas balas: " << HW.back() << "\nGeneruoti dar viena n.d. bala? (t/n) ";
        std::cin >> moreGrades;
        optionalInputValidation(moreGrades, 't', 'n');
    } while (moreGrades == 't');

    int exam = random10(mt);        // Generate a random exam grade between 1 and 10
    std::cout << "Sugeneruotas egzamino balas: " << exam << "\n";
    
    // Calculate the final grade and add it to the structure
    S->final = finalGradeVector(HW, exam, finalType);
}

double averageVector (std::vector<int> &HW, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HW[i];
    return (sum / n); // Division by zero isn't possible since the function can't be called when n = 0
}

double medianVector (std::vector<int> &HW, int n) {
    double m;
    std::sort(HW.begin(), HW.end());
    n % 2 == 0 ? (m = 1.00 * (HW[n / 2 - 1] + HW[n / 2]) / 2) : m = HW[n / 2];
    return m;
}

double finalGradeVector (std::vector<int> &HW, int exam, char type) {
    double hw;
    if (!HW.empty())  // Calculate the homework grade only if the homework list isn't empty
        type == 'm' ? hw = medianVector(HW, HW.size()) : hw = averageVector(HW, HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * exam);
}

void readEnteredDataVector (std::vector<Student> &S, char inputType, char finalType) {
    char moreStudents = 'n';
    bool moreHW;
    int tempHW;       // Temporary homework grade for validation
    Student temp;     // Temporary structure to be filled in before pushing back to the vector
    std::vector<int> HW;
    int exam;
    do {
        moreHW = true;
        HW.clear();   // Empty the vector for new values

        std::cout << "\nStudento vardas ir pavarde:\n";
        std::cin >> temp.name >> temp.surname;

        if (inputType == 'g')
            generateGradesManuallyVector(&temp, finalType); // Generate homework and exam grades
        else {
            std::cout << "\nIveskite namu darbu balus, atskirtus paspaudus'enter'. Po paskutinio balo iveskite 0:\n";
            do {
                std::cin >> tempHW;
                numberInputValidation(tempHW, 0, 10);
                if (tempHW == 0)
                    moreHW = false;        // Terminate the loop, if 0 is entered
                else HW.push_back(tempHW); // Add the entered grade to the homework vector
            } while (moreHW);              // Continue the loop, if it's wanted to enter more h.w. grades
            HW.shrink_to_fit();

            std::cout << "\nEgzamino balas:\n";
            std::cin >> exam;
            numberInputValidation(exam, 1, 10);
            temp.final = finalGradeVector(HW, exam, finalType);
        }
        S.push_back(temp);                 // Add the structure to the vector of student data

        std::cout << "\nAr norite ivesti dar vieno studento duomenis? (t/n) ";
        std::cin >> moreStudents;
        optionalInputValidation(moreStudents, 't', 'n');
    } while (moreStudents == 't');
}

void readFileVector (std::vector<Student> &S, std::string fileName, char finalType) {
    std::ifstream fd (fileName);

    int numOfHW = 0;
    std::string header;
    std::getline(fd, header);            // Read the first line of the file
    std::istringstream firstRow (header);// Make it readable by copying it into a stringstream
    std::string str;
    while (firstRow >> str)              // Count the number of separate strings until the line reaches the end
        numOfHW ++;
    numOfHW -= 3;                        // Ignore the name, surname and exam strings

    Student temp;
    int tempHW, exam;
    std::string row;
    std::istringstream dataRow;
    std::vector<int> HW;
    HW.reserve(numOfHW);
    while (std::getline(fd, row)) {      // Continue reading until the end of file is reached (raised error flag)
        dataRow.clear();
        dataRow.str(row);
        dataRow >> temp.name >> temp.surname;
        HW.clear();                      // Empty the temporary homework vector and fill it with grades from the file
        for (int i = 0; i < numOfHW; i ++) {
            dataRow >> tempHW;
            HW.push_back(tempHW);
        }
        dataRow >> exam;
        temp.final = finalGradeVector(HW, exam, finalType);
        S.push_back(temp);               // Push the temporary structure to the vector of structures
    } 
    fd.close();
}

void makeGroupsVector (std::vector<Student> &S, std::vector<Student> &GS, std::vector<Student> &BS, int strategy, char advanced) {
    if (advanced == 't') {
        // Get a pivot which is located between good and bad students
        auto numOfBadStudents = std::partition (S.begin(), S.end(), [](Student &i){return (i.final < 5);});

        // Copy good students into their vector
        GS.reserve(S.end() - numOfBadStudents);
        std::copy(numOfBadStudents, S.end(), std::back_inserter(GS));

        // Copy bad students or resize the whole students' vector
        if (strategy == 1) {
            BS.reserve(numOfBadStudents - S.begin());
            std::copy(S.begin(), numOfBadStudents, std::back_inserter(BS));
            S.clear();
        } else S.resize(numOfBadStudents - S.begin()); // Leave the main vector with the "bad students" data only
    } else {
        // Sort students by their final grades
        std::sort(S.begin(), S.end(), [](Student &s1, Student &s2) {return s1.final < s2.final;}); 

        // Count the number of students with final grade < 5
        int numOfBadStudents = 0;
        while (S[numOfBadStudents].final < 5.0 && numOfBadStudents != S.size())
            numOfBadStudents ++;

        // Copy good students into their vector
        GS.reserve(S.size() - numOfBadStudents);
        std::copy(S.begin() + numOfBadStudents, S.end(), std::back_inserter(GS));

        // Copy bad students or resize the whole students' vector
        if (strategy == 1) {
            BS.reserve(numOfBadStudents);
            std::copy(S.begin(), S.begin() + numOfBadStudents, std::back_inserter(BS));
            S.clear();
        } else S.resize(numOfBadStudents); // Leave the main vector with the "bad students" data only
    }
    S.shrink_to_fit();
}

void sortVector (std::vector<Student> &S1, std::vector<Student> &S2, char sortType) {
    if (sortType == 'v') {
        std::sort(S1.begin(), S1.end(), [](Student &s1, Student &s2) {return s1.name < s2.name;});
        std::sort(S2.begin(), S2.end(), [](Student &s1, Student &s2) {return s1.name < s2.name;});
    } else if (sortType == 'p') {
        std::sort(S1.begin(), S1.end(), [](Student &s1, Student &s2) {return s1.surname < s2.surname;});
        std::sort(S2.begin(), S2.end(), [](Student &s1, Student &s2) {return s1.surname < s2.surname;});
    } else {
        std::sort(S1.begin(), S1.end(), [](Student &s1, Student &s2) {return s1.final < s2.final;});
        std::sort(S2.begin(), S2.end(), [](Student &s1, Student &s2) {return s1.final < s2.final;});
    }
}

void writeToFileVector (std::vector<Student> &S, char finalType, std::string fileName) {
    std::ofstream fr (fileName);
    std::ostringstream row ("");

    // Print header
    row << std::setw(20) << std::left << "Vardas" << std::setw(20) << "Pavarde" << "Galutinis ";
    fr << row.str();

    finalType == 'm' ? fr << "(Med.)\n" : fr << "(Vid.)\n";
    fr << "--------------------------------------------------------\n";

    // Print students' data
    for (int i = 0; i < S.size(); i ++) {
        row.str("");        // Empty the row stream and add single student's data
        row << std::setw(20) << std::left << S[i].name << std::setw(20) << S[i].surname
            << std::fixed << std::setprecision(2) << S[i].final << "\n";
        fr << row.str();    // Print the completed row
    }
    fr.close();
}