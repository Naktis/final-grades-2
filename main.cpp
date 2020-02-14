#include <iostream>
#include <iomanip>
#define N 50

struct Student {
    std::string name, surname;
    int hw, exam;
    double final;
};

double FinalGrade (int hw, int exam){
    return (0.4 * hw + 0.6 * exam);
}

void Print (Student S[], int n) {
    std::cout << S[n].surname << "\t" << S[n].name << "\t" << std::fixed << std::setprecision(2) << S[n].final << "\n";
}

int main () {
    Student *S = new Student[N];
    int nS = 0;

    char moreStudents = 'y', moreHw ='y';
    do {
        std::cout << "Studento pavarde, vardas, egzamino balas, namu darbu balai\n";
        std::cin >> S[nS].surname >> S[nS].name >> S[nS].exam;
        do {
            std::cin >> S[nS].hw;
            std::cout << "Ivesti daugiau namu darbu? (y/n)";
            std::cin >> moreHw;
         } while (moreHw != 'n');

        nS++;

        std::cout << "Ivesti dar vieno studento duomenis? (y/n)";
        std::cin >> moreStudents;
    } while (moreStudents != 'n');

    std::cout << "Pavarde\tVardas\tGalutinis (Vid.)\n";
    for (int i = 0; i < nS; i ++) {
        S[i].final = FinalGrade(S[i].hw, S[i].exam);
        Print(S, i);
    }

    return 0;
}