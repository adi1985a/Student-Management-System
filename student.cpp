#include "student.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>       // Add this for fixed and setprecision

// Add declaration for losuj
extern float losuj();

bool saveStudentsToFile(STUDENT* tab, int N) {
    std::ofstream file("data.txt");
    if (!file) return false;

    for (int i = 0; i < N; i++) {
        file << tab[i].im_nazwisko << "\n"
             << tab[i].indeks << "\n"
             << tab[i].rok_studiow << "\n";
        for (int j = 0; j < 5; j++) {
            file << tab[i].oceny[j] << " ";
        }
        file << "\n";
    }
    return true;
}

bool loadStudentsFromFile(STUDENT*& tab, int& N) {
    std::ifstream file("data.txt");
    if (!file) return false;

    std::string line;
    std::vector<STUDENT> students;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            STUDENT s;
            s.im_nazwisko = line;
            
            if (std::getline(file, s.indeks) && 
                file >> s.rok_studiow) {
                file.ignore();
                
                std::string grades;
                std::getline(file, grades);
                std::istringstream iss(grades);
                
                float suma = 0;
                for (int j = 0; j < 5; j++) {
                    if (iss >> s.oceny[j]) {
                        suma += s.oceny[j];
                    } else {
                        s.oceny[j] = 2.0;
                        suma += 2.0;
                    }
                }
                s.srednia_ocen = suma / 5;
                students.push_back(s);
            }
        }
    }
    
    N = students.size();
    tab = new STUDENT[N];
    std::copy(students.begin(), students.end(), tab);
    
    return true;
}

bool addStudent(STUDENT*& tab, int& N) {
    STUDENT* newTab = new STUDENT[N + 1];
    std::copy(tab, tab + N, newTab);
    
    std::cout << "Enter student first name and last name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, newTab[N].im_nazwisko);
    
    std::cout << "Enter student index number: ";
    std::getline(std::cin, newTab[N].indeks);
    
    std::cout << "Enter study year (1-5): ";
    std::cin >> newTab[N].rok_studiow;

    // Validate year input
    while (newTab[N].rok_studiow < 1 || newTab[N].rok_studiow > 5) {
        std::cout << "Invalid year! Please enter a number between 1 and 5: ";
        std::cin >> newTab[N].rok_studiow;
    }

    float suma = 0;
    std::cout << "\nGenerating random grades...\n";
    for (int j = 0; j < 5; j++) {
        newTab[N].oceny[j] = losuj();
        suma += newTab[N].oceny[j];
        std::cout << "Grade " << (j+1) << ": " << std::fixed << std::setprecision(1) << newTab[N].oceny[j] << std::endl;
    }
    newTab[N].srednia_ocen = suma / 5;

    std::cout << "\nAdded student:" << std::endl;
    std::cout << "Name: " << newTab[N].im_nazwisko << std::endl;
    std::cout << "Index: " << newTab[N].indeks << std::endl;
    std::cout << "Year: " << newTab[N].rok_studiow << std::endl;

    delete[] tab;
    tab = newTab;
    N++;
    return true;
}

bool removeStudent(STUDENT*& tab, int& N, const std::string& indeks) {
    // First display all students
    std::cout << "\nCurrent students:\n";
    for(int i = 0; i < N; i++) {
        std::cout << "Index: " << tab[i].indeks << " - Name: " << tab[i].im_nazwisko << std::endl;
    }

    int idx = -1;
    for (int i = 0; i < N; i++) {
        if (tab[i].indeks == indeks) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return false;

    if (idx != -1) {
        std::cout << "Removing student: " << tab[idx].im_nazwisko << " (Index: " << tab[idx].indeks << ")\n";
    }

    STUDENT* newTab = new STUDENT[N - 1];
    for (int i = 0; i < idx; i++) newTab[i] = tab[i];
    for (int i = idx + 1; i < N; i++) newTab[i - 1] = tab[i];

    delete[] tab;
    tab = newTab;
    N--;
    return true;
}

bool editStudent(STUDENT* tab, int N, const std::string& indeks) {
    for (int i = 0; i < N; i++) {
        if (tab[i].indeks == indeks) {
            std::cout << "\nEditing student: " << tab[i].im_nazwisko << "\n";
            std::cout << "Current details:\n";
            std::cout << "Name: " << tab[i].im_nazwisko << "\n";
            std::cout << "Year: " << tab[i].rok_studiow << "\n";
            std::cout << "Grades: ";
            for(int j = 0; j < 5; j++) {
                std::cout << tab[i].oceny[j] << " ";
            }
            std::cout << "\n\n";

            std::cout << "Enter new name (or press enter to skip): ";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            if (!name.empty()) tab[i].im_nazwisko = name;

            std::cout << "Enter new study year (0 to skip): ";
            int year;
            std::cin >> year;
            if (year > 0) tab[i].rok_studiow = year;

            // Add grade editing option
            std::cout << "Do you want to edit grades? (y/n): ";
            char choice;
            std::cin >> choice;
            if(choice == 'y') {
                for(int j = 0; j < 5; j++) {
                    std::cout << "Enter grade " << (j+1) << ": ";
                    std::cin >> tab[i].oceny[j];
                }
            }
            return true;
        }
    }
    std::cout << "Student with index " << indeks << " not found!\n";
    return false;
}
