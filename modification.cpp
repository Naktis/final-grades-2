#include "modification.h"

double average (std::vector<int> &HW, int n) {
    double sum = 0;
    for (int i = 0; i < n; i ++)
        sum += HW[i];
    return (sum / n); // Division by zero isn't possible since the function can't be called when n = 0
}

double median (std::vector<int> &HW, int n) {
    double m;
    std::sort(HW.begin(), HW.end());
    n % 2 == 0 ? (m = 1.00 * (HW[n / 2 - 1] + HW[n / 2]) / 2) : m = HW[n / 2];
    return m;
}

double finalGrade (std::vector<int> &HW, int exam, char type) {
    double hw;
    if (!HW.empty())  // Calculate the homework grade only if the homework list isn't empty
        type == 'm' ? hw = median(HW, HW.size()) : hw = average(HW, HW.size());
    else hw = 0;
    return (0.4 * hw + 0.6 * exam);
}

void makeGroups (std::vector<Student> &S, std::vector<Student> &GS, std::vector<Student> &BS, int strategy, char advanced) {
    if (advanced == 't') {
        // Get a pivot which is located between good and bad students
        auto numOfBadStudents = std::partition (S.begin(), S.end(), [](Student &i){return (i.getFinal() < 5);});

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
        std::sort(S.begin(), S.end(), [](Student &s1, Student &s2) {return s1.getFinal() < s2.getFinal();}); 
        
        // Count the number of students with final grade < 5
        int numOfBadStudents = 0;
        while (S[numOfBadStudents].getFinal() < 5.0 && numOfBadStudents != S.size())
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

void sort (std::vector<Student> &S1, std::vector<Student> &S2, char sortType) {
    if (sortType == 'v') {          // Name sorting
        std::sort(S1.begin(), S1.end(), compareNames);
        std::sort(S2.begin(), S2.end(), compareNames);
    } else if (sortType == 'p') {   // Surname sorting
        std::sort(S1.begin(), S1.end(), compareSurnames);
        std::sort(S2.begin(), S2.end(), compareSurnames);
    } else {                        // Final grade sorting
        std::sort(S1.begin(), S1.end(), compareFinals);
        std::sort(S2.begin(), S2.end(), compareFinals);
    }
}