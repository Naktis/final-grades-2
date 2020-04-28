#pragma once

#include <random>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "modification.h"
#include "validation.h"

std::string getFileName();
void createDataFile (int, std::string&);
void readFile (std::vector<Student>&, std::string, char);
void generateGradesManually (Student*, char);
void readEnteredData (std::vector<Student>&, char, char);
void writeToFile (std::vector<Student>&, char, std::string);