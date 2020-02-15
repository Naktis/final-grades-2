#include <iostream>
#include <iomanip>
#define MAXS 50   // Maximum number of students
#define MAXHW 20  // Maximum number of homework grades

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
    n % 2 == 0 ? (m = *(HW + (n / 2) - 1) + *(HW + (n / 2)) / 2) : m = *(HW + (n / 2));
    return m;
}

void finalGrade (Student* S, int i, char type){
    int hw;
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

void numberInputValidation (int& input) {
    while (input < -1 || input > 10) {
        std::cout << "Pasirinkite skaiciu is intervalo [0 ; 10] ";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input;
    }
}

int main () {
    Student *S = new Student[MAXS];
    char finalType, moreStudents = 'y';
    int nS = 0;
    bool moreHW = true;

    do {
        std::cout << "Studento pavarde, vardas: ";
        std::cin >> S[nS].surname >> S[nS].name;
        std::cout << "Namu darbu balai, atskirti tarpais. Po paskutinio balo iveskite -1: ";
        do {
            std::cin >> S[nS].HW[S[nS].nHW];
            numberInputValidation(S[nS].HW[S[nS].nHW]);
            S[nS].HW[S[nS].nHW] == -1 ? moreHW = false : S[nS].nHW++;
        } while (moreHW);

        std::cout << "Egzamino balas: ";
        std::cin >> S[nS].exam;
        numberInputValidation(S[nS].exam);
        nS++;

        std::cout << "Ivesti dar vieno studento duomenis? (y/n) ";
        std::cin >> moreStudents;
        optionalInputValidation(moreStudents, 'y', 'n');
    } while (moreStudents != 'n');

    std::cout << "Jeigu norite galutini bala skaiciuoti pagal namu darbu mediana, iveskite m, jeigu pagal vidurki - v. (m/v) ";
    std::cin >> finalType;
    optionalInputValidation(finalType, 'm', 'v');

    std::cout << "\nPavarde\tVardas\tGalutinis ";
    finalType == 'm' ? std::cout << "(Med.)\n" : std::cout << "(Vid.)\n" ;
    for (int i = 0; i < nS; i ++) {
        finalGrade(S, i, finalType);
        std::cout << S[i].surname << "\t" << S[i].name << "\t" << std::fixed << std::setprecision(2) << S[i].final << "\n";
    }
    return 0;
}