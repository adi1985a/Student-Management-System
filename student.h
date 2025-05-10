#pragma once
#include <string>
#include <fstream>
#include <vector>

struct STUDENT {
    std::string im_nazwisko;
    std::string indeks;
    int rok_studiow;
    double oceny[5];
    double srednia_ocen;
};

bool saveStudentsToFile(STUDENT* tab, int N);
bool loadStudentsFromFile(STUDENT*& tab, int& N);
bool addStudent(STUDENT*& tab, int& N);
bool removeStudent(STUDENT*& tab, int& N, const std::string& indeks);
bool editStudent(STUDENT* tab, int N, const std::string& indeks);

void najwyzsza_srednia(std::ofstream& plik2, STUDENT* tab, int N);
