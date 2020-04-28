#include "iodata.h"

std::string getFileName () {
    bool badFile;
    std::string fileName;
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
        } catch (int exception) {   // If it doesn't, let user reenter a new file name
            badFile = true;
            std::cout << "Duomenu failas " << fileName << " neegzistuoja. Iveskite esamo failo varda:\n";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> fileName;
        }
    } while (badFile);              // Repeat until existing file name is entered
    return fileName;
}

void createDataFile (int numOfStudents, std::string& fileName) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(1, 10); // Generates a number from 1 to 10
    std::uniform_int_distribution<int> random20(1, 20); //                    from 1 to 20

    int numOfHW = random20(mt);         // Generate the number of HW grades 

    std::ostringstream fileNameStream;  // Create the name of the file
    fileNameStream << "kursiokai" << numOfStudents << ".txt";
    fileName = fileNameStream.str();
    std::ofstream add (fileName);

    // Print header text
    std::ostringstream row ("");        // Empty row to be filled in with header data
    row << std::setw(20) << std::left << "Vardas" << std::setw(21) << "Pavarde";
    for (int i = 1; i <= numOfHW; i ++)
        row << "ND" << std::setw(8) << std::left << i;
    row << "Egz.\n";
    add << row.str();                   // Print out the row

    // Print student data
    for (int i = 1; i <= numOfStudents; i ++) {
        row.str("");                    // Empty the row and fill it with single student's data
        row << "Vardas" << std::setw(14) << std::left << i << "Pavarde" << std::setw(14) << std::left << i;
        for (int j = 0; j <= numOfHW; j ++)
            row << std::setw(10) << std::left << random10(mt);
        row << "\n";
        add << row.str();
    }
    add.close();
}

void readFile (std::vector<Student> &S, std::string fileName, char finalType) {
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
    std::string row, tempName, tempSurname;
    std::istringstream dataRow;
    std::vector<int> HW;
    HW.reserve(numOfHW);
    while (std::getline(fd, row)) {  // Continue reading until the end of file is reached (raised error flag)
        dataRow.clear();
        dataRow.str(row);
        dataRow >> tempName >> tempSurname;

        HW.clear();                  // Empty the temporary homework vector and fill it with grades from the file
        for (int i = 0; i < numOfHW; i ++) {
            dataRow >> tempHW;
            HW.push_back(tempHW);
        }
        dataRow >> exam;
        temp.setAll(tempName, tempSurname, finalGrade(HW, exam, finalType));
        S.push_back(temp);           // Push the temporary structure to the vector of structures
    } 
    fd.close();
}

void generateGradesManually (Student* S, char finalType) {
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
    S->setFinal(finalGrade(HW, exam, finalType));
}

void readEnteredData (std::vector<Student> &S, char inputType, char finalType) {
    char moreStudents = 'n';
    bool moreHW;
    int tempHW;       // Temporary homework grade for validation
    Student temp;     // Temporary structure to be filled in before pushing back to the vector
    std::vector<int> HW;
    int exam;
    std::string tempName, tempSurname;
    do {
        moreHW = true;
        HW.clear();   // Empty the vector for new values

        std::cout << "\nStudento vardas ir pavarde:\n";
        std::cin >> tempName >> tempSurname;
        temp.setAll(tempName, tempSurname, 0);

        if (inputType == 'g')
            generateGradesManually(&temp, finalType); // Generate homework and exam grades
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
            temp.setFinal(finalGrade(HW, exam, finalType));
        }
        S.push_back(temp);                 // Add the structure to the vector of student data

        std::cout << "\nAr norite ivesti dar vieno studento duomenis? (t/n) ";
        std::cin >> moreStudents;
        optionalInputValidation(moreStudents, 't', 'n');
    } while (moreStudents == 't');
}

void writeToFile (std::vector<Student> &S, char finalType, std::string fileName) {
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
        row << std::setw(20) << std::left << S[i].getName() << std::setw(20) << S[i].getSurname()
            << std::fixed << std::setprecision(2) << S[i].getFinal() << "\n";
        fr << row.str();    // Print the completed row
    }
    fr.close();
}