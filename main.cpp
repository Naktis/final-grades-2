#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>

struct Student {
    std::string name, surname;
    int exam;
    std::vector<int> HW;    // Vector of homework grades
};

double average (int* HW, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HW[i];
    return (sum / n); // Division by zero isn't possible since the function can't be called when n = 0
}

void quickSort (int* HW, int low, int high) {
    int i = low, j = high, temp, pivot = HW[j];
    // Swap elements to create a lower block of the array in which elements are
    // smaller and an upper block, where elements are larger than the pivot
    while (i <= j) {
        while (HW[i] < pivot)
            i++;
        while (HW[j] > pivot)
            j--;
        if (i <= j) {
            temp = HW[i];
            HW[i] = HW[j];
            HW[j] = temp;
            i++;
            j--;
        }
    }
    // Repeat quick sort with both upper and lower sides of the array, separated by the pivot
    if (j > low)
        quickSort(HW, low, j);
    if (i < high)
        quickSort(HW, i, high);
}

double median (int *HW, int n) {
    double m;
    quickSort(HW, 0, n-1);
    n % 2 == 0 ? (m = 1.00 * (*(HW + (n / 2) - 1) + *(HW + (n / 2))) / 2) : m = *(HW + (n / 2));
    return m;
}

double finalGrade (Student* S, char type){
    double hw;
    if (!S->HW.empty())  // Calculate the homework grade only if the homework array isn't empty
        type == 'm' ? hw = median(&S->HW[0], S->HW.size()) : hw = average(&S->HW[0], S->HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * S->exam);
}

// Function which checks if the input contains one of the asked options and asks to
// to reenter data, if it doesn't
void optionalInputValidation (char& input, char option1, char option2) {
    while (!(input == option1 || input == option2)) {
        std::cout << "Balas neirasytas. Pasirinkite viena is variantu (" << option1 << "/" << option2 << ") \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

// Function which checks if the input is number-only and asks to reenter data, if it's not
void numberInputValidation (int& input, int lowest, int highest) {
    while (input < lowest || input > highest || std::cin.fail()) {
        std::cout << "Balas neirasytas. Pasirinkite skaiciu is intervalo [" << lowest << " ; " << highest << "] \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

// Function which checks if the entered string contains any non-letter characters, according to the ASCII table.
// If it does, the user is asked to reenter data
void stringInputValidation (std::string &input) {
    bool onlyChars;
    do {
        onlyChars = true;
        for (int i = 0; i < input.length(); i ++)
            if (!((input[i] >= 65 && input[i] <= 90) || (input[i] >= 97 && input[i] <= 122))) {
                onlyChars = false;
                std::cout << "Zodis neirasytas, nes jame yra neleistinu simboliu. Iveskite zodi dar karta. \n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> input;
                break;
            }
    } while (!onlyChars);
}

void generateGrades (Student* S) {
    char moreGrades;
    std::cout << "\nGeneruojami namu darbu balai.\n\n";
    srand(time(NULL));  // Random seed
    do {
        S->HW.push_back((double)rand ()/ RAND_MAX * 9 + 1); // Generate a random h.w. grade between 1 and 10
        std::cout << "Sugeneruotas balas: " << S->HW.back() << "\nGeneruoti dar viena n.d. bala? (t/n) ";
        std::cin >> moreGrades;
        optionalInputValidation(moreGrades, 't', 'n');
    } while (moreGrades == 't');

    S->exam = (double)rand ()/ RAND_MAX * 9 + 1;            // Generate a random exam grade between 1 and 10
    std::cout << "Sugeneruotas egzamino balas: " << S->exam << "\n";
}

int main () {
    std::vector<Student> S;                    // Vector for entered student data
    char finalType;                            // Can be equal to 'm' (median) or 'v' (average)
    char moreStudents = 'n', isHWRandom = 'n'; // Variables for input validation
    bool moreHW;
    int tempHW;

    do {
        Student temp;                           // Temporary structure to be filled in before pushing back to the vector
        moreHW = true;
        std::cout << "\nStudento pavarde, vardas:\n";
        std::cin >> temp.surname;               // Read and validate student's surname and name
        stringInputValidation(temp.surname);
        std::cin >> temp.name;
        stringInputValidation(temp.name);
        
        std::cout << "\nAr norite n.d. ir egzamino balus generuoti atsitiktinai? (t/n) ";
        std::cin >> isHWRandom;                 // Read and validate if it's wanted to randomize grades
        optionalInputValidation(isHWRandom, 't', 'n');
        if (isHWRandom == 't')
            generateGrades(&temp);              // Generate homework and exam grades
        else {
            std::cout << "\nIveskite namu darbu balus, atskirtus paspaudus'enter'. Po paskutinio balo iveskite 0:\n";
            do {
                std::cin >> tempHW;             // Read and validate the entered homework grade
                numberInputValidation(tempHW, 0, 10);
                if (tempHW == 0)
                    moreHW = false;             // Terminate the loop, if 0 is entered
                else temp.HW.push_back(tempHW); // Add the entered grade to the homework vector
            } while (moreHW);                   // Continue the loop, if it's wanted to enter more h.w. grades
            std::cout << "\nEgzamino balas:\n";
            std::cin >> temp.exam;              // Read and validate the entered exam grade
            numberInputValidation(temp.exam, 1, 10);
        }
        S.push_back(temp);                      // Add the structure to the vector of student data

        std::cout << "\nAr norite ivesti dar vieno studento duomenis? (t/n) ";
        std::cin >> moreStudents;               // Read and validate if it's wanted to enter data of more students
        optionalInputValidation(moreStudents, 't', 'n');
    } while (moreStudents == 't');              // Continue the loop, if there's more student data
    S.shrink_to_fit();                          // Free unused space that the vector has reserved

    std::cout << "\nJeigu norite galutini bala skaiciuoti pagal namu darbu mediana, iveskite m, jeigu pagal vidurki - v. (m/v) ";
    std::cin >> finalType;                      // Read and validate the entered type of final grade (average or median)
    optionalInputValidation(finalType, 'm', 'v');

    // Calculate final grades and print results
    std::cout << "\nPavarde\t\tVardas\t\tGalutinis ";
    finalType == 'm' ? std::cout << "(Med.)\n" : std::cout << "(Vid.)\n" ;
    for (int i = 0; i < S.size(); i ++)
        std::cout << S[i].surname << "\t\t" << S[i].name << "\t\t" << std::fixed << std::setprecision(2) << finalGrade(&S[i], finalType) << "\n";
    return 0;
}