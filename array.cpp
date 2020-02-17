#include <iostream>
#include <iomanip>
#include <ctime>
#define MAXS 200   // Maximum number of students
#define MAXHW 50  // Maximum number of homework grades

struct Student {
    std::string name, surname;
    int exam;
    double final;
    int HW[MAXHW];  // An array of homework grades
    int nHW = 0;    // Amount of homework grades
};

double average (int* HW, int n) {
    if (n) {
        double sum = 0;
        for (int i = 0; i < n; i ++)
            sum += HW[i];
        return (sum / n);
    }
    else return 0;
}

void quickSort (int* HW, int low, int high) {
    int i = low, j = high, temp, pivot = HW[j];
    
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
    if (j > low)
        quickSort(HW, low, j);
    if (i < high)
        quickSort(HW, i, high);
}

double median (int* HW, int n) {
    double m;
    quickSort(HW, 0, n);
    n % 2 == 0 ? (m = 1.00 * (*(HW + (n / 2) - 1) + *(HW + (n / 2))) / 2) : m = *(HW + (n / 2));
    return m;
}

void finalGrade (Student* S, int i, char type){
    double hw;
    type == 'm' ? hw = median(S[i].HW, S[i].nHW) : hw = average(S[i].HW, S[i].nHW);
    S[i].final = (0.4 * hw + 0.6 * S[i].exam);
}

void optionalInputValidation (char& input, char option1, char option2) {
    while (!(input == option1 || input == option2)) {
        std::cout << "Pasirinkite viena is variantu (" << option1 << "/" << option2 << ") ";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

void numberInputValidation (int& input, int lowest, int highest) {
    while (input < lowest || input > highest || std::cin.fail()) {
        std::cout << "Pasirinkite skaiciu is intervalo [" << lowest << " ; " << highest << "] ";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

void generateGrades (Student* S, int i) {
    char moreGrades;
    std::cout << "\nGeneruojami namu darbu balai.\n\n";
    srand(time(NULL));
    do {
        S[i].HW[S[i].nHW] = (double)rand ()/ RAND_MAX * 9 + 1;
        std::cout << "Sugeneruotas balas: " << S[i].HW[S[i].nHW] << "\nGeneruoti dar viena n.d. bala? (t/n) ";
        S[i].nHW ++;
        std::cin >> moreGrades;
        optionalInputValidation(moreGrades, 't', 'n');
    } while (moreGrades == 't');

    S[i].exam = (double)rand ()/ RAND_MAX * 9 + 1;
    std::cout << "Sugeneruotas egzamino balas: " << S[i].exam << "\n";
}

int main () {
    Student *S = new Student[MAXS];
    char finalType, moreStudents = 'n', isHWRandom = 'n';
    int nS = 0, tempHW;
    bool moreHW;

    do {
        moreHW = true;
        std::cout << "\nStudento pavarde, vardas:\n";
        std::cin >> S[nS].surname >> S[nS].name;

        std::cout << "\nAr norite n.d. ir egzamino balus generuoti atsitiktinai? (t/n) ";
        std::cin >> isHWRandom;
        optionalInputValidation(isHWRandom, 't', 'n');
        if (isHWRandom == 't')
            generateGrades(S, nS);
        else {
            std::cout << "\nIveskite namu darbu balus, atskirtus paspaudus'enter'. Po paskutinio balo iveskite 0:\n";
            do {
                std::cin >> tempHW;
                numberInputValidation(tempHW, 0, 10);
                if (tempHW == 0)
                    moreHW = false;
                else {
                    S[nS].HW[S[nS].nHW] = tempHW;
                    S[nS].nHW++;
                }
            } while (moreHW);
            std::cout << "\nEgzamino balas:\n";
            std::cin >> S[nS].exam;
            numberInputValidation(S[nS].exam, 1, 10);
        }
        nS++;
        std::cout << "\nAr norite ivesti dar vieno studento duomenis? (t/n) ";
        std::cin >> moreStudents;
        optionalInputValidation(moreStudents, 't', 'n');
    } while (moreStudents == 't');

    std::cout << "\nJeigu norite galutini bala skaiciuoti pagal namu darbu mediana, iveskite m, jeigu pagal vidurki - v. (m/v) ";
    std::cin >> finalType;
    optionalInputValidation(finalType, 'm', 'v');

    std::cout << "\nPavarde\t\tVardas\t\tGalutinis ";
    finalType == 'm' ? std::cout << "(Med.)\n" : std::cout << "(Vid.)\n" ;
    for (int i = 0; i < nS; i ++) {
        finalGrade(S, i, finalType);
        std::cout << S[i].surname << "\t\t" << S[i].name << "\t\t" << std::fixed << std::setprecision(2) << S[i].final << "\n";
    }
    delete[] S;
    return 0;
}