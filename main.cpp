#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <algorithm> // Add this for transform
#include <cctype>    // Add this for tolower
#include "utils.h"
#include "student.h"

/*
The project assumes the creation of a student management system using structures.
Program in addition to the object-oriented system, it includes the operation of operating
on external files and the possibility of drawing numbers.
The program stores information about created structure objects inside dynamically
generated array. The size of the array is determined by the amount of data inside the data file
entrances. We control the number of lines of text in the file with the help of the cursor. The name is
retrieved via the getline() operation, which allows us to download the entire line of code at once (forces
us is to provide data to the program in the future in separate lines).

In addition, the program defines to us by means of a set of functions such operations as:
� supplementing array objects along with drawing values,
� determining the average value of all students' grades,
� determining how many students have an average higher than the general average (in this case
we use the previously designated function),
� displaying all data in a legible way,
� determining which of the students has the highest average and rewriting such a person
to the output file,
� displaying a specific student provided by the user
� (additionally) changing a specific grade for a specific student provided by the user

*/
using namespace std;

// Remove duplicate STUDENT structure definition since it's in student.h

float losuj()
{
	float tab[] = {2, 2.5, 3, 3.5, 4, 4.5, 5};
	int liczba = rand()%7;
	return tab[liczba];
}

void uzupelnij(ifstream &plik, STUDENT *tab, int N)
{
	for(int i=0; i<N; i++)
        {
	    float suma = 0;
	    getline(plik, tab[i].im_nazwisko);
	    if(tab[i].im_nazwisko.empty())
        {
            tab[i].im_nazwisko = "unknown";
        }

	    for(int j=0; j<5; j++)
	    {
		    tab[i].oceny[j] = losuj();
	        suma += tab[i].oceny[j];
	    }
	    tab[i].srednia_ocen = (float)suma/5;
    }
}

double srednia_ocen_studentow(STUDENT *tab, int N)
{
    if (N == 0) return 0.0;
    double suma = 0.0;
    int count = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<5; j++) {
            if(tab[i].oceny[j] >= 2.0 && tab[i].oceny[j] <= 5.0) {
                suma += tab[i].oceny[j];
                count++;
            }
        }
    }
    return count > 0 ? suma/count : 0.0;
}

int ilosc_uczniow_ze_srednia_powyzej_sredniej( STUDENT *tab, int N )
{
    int licznik = 0;
    for(int i=0; i<N; i++)
    {
		if(tab[i].srednia_ocen > srednia_ocen_studentow(tab, N))
			licznik++;
	}
	return licznik;
}

void wyswietl_uczniow(STUDENT *tab, int N) {
    try {
        Utils::setColor(Colors::LIGHT_BLUE);
        for(int i=0; i<N; i++) {
            if(!tab[i].im_nazwisko.empty() && tab[i].im_nazwisko != "unknown") {
                Utils::drawLine('-', 40);
                cout << "Student: " << tab[i].im_nazwisko << endl;
                cout << "Index: " << tab[i].indeks << endl;
                cout << "Year: " << tab[i].rok_studiow << endl;
                cout << "Grades: ";
                for(int j=0; j<5; j++) {
                    cout << fixed << setprecision(1) << tab[i].oceny[j] << " ";
                }
                cout << "\nAverage: " << fixed << setprecision(2) << tab[i].srednia_ocen << endl;
            }
        }
        Utils::drawLine('-', 40);
        Utils::setColor(Colors::WHITE);
    } catch(const exception& e) {
        Utils::logError("Error displaying students: " + string(e.what()));
    }
}

void najwyzsza_srednia(ofstream &plik2, STUDENT *tab, int N)
{
    if (N == 0) return;
    double max_srednia = tab[0].srednia_ocen;
    for (int i = 1; i < N; i++) {
        if(tab[i].srednia_ocen > max_srednia) {
            max_srednia = tab[i].srednia_ocen;
        }
    }
    cout << "\nStudents with highest average (" << fixed << setprecision(2) << max_srednia << "):\n";
    for(int i=0; i<N; i++) {
        if(fabs(tab[i].srednia_ocen - max_srednia) < 0.001) {
            cout << "\nStudent: " << tab[i].im_nazwisko;
            cout << "\nIndex: " << tab[i].indeks;
            cout << "\nYear: " << tab[i].rok_studiow;
            cout << "\nGrades: ";
            for(int j=0; j<5; j++) {
                cout << fixed << setprecision(1) << tab[i].oceny[j] << " ";
            }
            cout << "\nAverage: " << fixed << setprecision(2) << tab[i].srednia_ocen << endl;
            
            // Write to file
            plik2 << "\nStudent: " << tab[i].im_nazwisko;
            plik2 << "\nIndex: " << tab[i].indeks;
            plik2 << "\nYear: " << tab[i].rok_studiow;
            plik2 << "\nGrades: ";
            for(int j=0; j<5; j++) {
                plik2 << fixed << setprecision(1) << tab[i].oceny[j] << " ";
            }
            plik2 << "\nAverage: " << fixed << setprecision(2) << tab[i].srednia_ocen << "\n";
        }
    }
}

void konkretny_student(STUDENT *tab, int N) {
    string dane;
    cout << "Enter the name of the student to display: ";
    cin.ignore();
    getline(cin, dane);
    bool found = false;

    for(int i=0; i<N; i++) {
        // Case insensitive search
        string student_name = tab[i].im_nazwisko;
        string search_name = dane;
        // Convert both strings to lower case for comparison
        transform(student_name.begin(), student_name.end(), student_name.begin(), ::tolower);
        transform(search_name.begin(), search_name.end(), search_name.begin(), ::tolower);
        // Partial match search
        if(student_name.find(search_name) != string::npos) {
            found = true;
            cout << "\nStudent details:" << endl;
            cout << "Name: " << tab[i].im_nazwisko << endl;
            cout << "Index: " << tab[i].indeks << endl;
            cout << "Year: " << tab[i].rok_studiow << endl;
            cout << "Grades: ";
            for(int j=0; j<5; j++) {
                cout << fixed << setprecision(1) << tab[i].oceny[j] << " ";
            }
            cout << "\nAverage: " << fixed << setprecision(2) << tab[i].srednia_ocen << endl;
        }
    }
    if(!found) {
        cout << "Student not found!" << endl;
    }
}

void zmiana_ocen(STUDENT *tab, int N) {
    // Display all students first
    cout << "\nCurrent students:" << endl;
    for(int i=0; i<N; i++) {
        cout << i+1 << ". " << tab[i].im_nazwisko << " (Index: " << tab[i].indeks << ")" << endl;
    }

    string nazwisko;
    cout << "\nEnter student name to modify grades: ";
    cin.ignore();
    getline(cin, nazwisko);

    bool found = false;
    for(int i=0; i<N; i++) {
        // Case insensitive search
        string student_name = tab[i].im_nazwisko;
        string search_name = nazwisko;
        
        // Convert both strings to lower case for comparison
        transform(student_name.begin(), student_name.end(), student_name.begin(), ::tolower);
        transform(search_name.begin(), search_name.end(), search_name.begin(), ::tolower);
        
        // Partial match search
        if(student_name.find(search_name) != string::npos) {
            found = true;
            cout << "\nStudent found: " << tab[i].im_nazwisko << endl;
            cout << "Current grades: ";
            for(int j=0; j<5; j++) {
                cout << fixed << setprecision(1) << tab[i].oceny[j] << " ";
            }
            
            cout << "\nWhich grade do you want to change (1-5): ";
            int numer;
            cin >> numer;
            
            if(numer >= 1 && numer <= 5) {
                cout << "Enter new grade (2.0-5.0): ";
                float newGrade;
                cin >> newGrade;
                if(newGrade >= 2.0 && newGrade <= 5.0) {
                    tab[i].oceny[numer-1] = newGrade;
                    
                    // Recalculate average
                    float suma = 0;
                    for(int j=0; j<5; j++) {
                        suma += tab[i].oceny[j];
                    }
                    tab[i].srednia_ocen = suma/5;
                    cout << "\nGrade updated successfully!" << endl;
                    cout << "New grades: ";
                    for(int j=0; j<5; j++) {
                        cout << fixed << setprecision(1) << tab[i].oceny[j] << " ";
                    }
                    cout << "\nNew average: " << fixed << setprecision(2) << tab[i].srednia_ocen << endl;
                } else {
                    cout << "Invalid grade value! Grade must be between 2.0 and 5.0" << endl;
                }
            } else {
                cout << "Invalid grade number! Must be between 1 and 5" << endl;
            }
            break;
        }
    }
    
    if(!found) {
        cout << "Student not found!" << endl;
    }
}

void displayMenu() {
    Utils::setColor(Colors::LIGHT_GREEN);
    Utils::drawLine('=');
    cout << "Available options:\n";
    cout << "1. Display all students\t\t2. Show average grades\n";
    cout << "3. Find best students\t\t4. Search for student\n";
    cout << "5. Modify grades\t\t6. Add new student\n";
    cout << "7. Remove student\t\t8. Edit student\n";
    cout << "9. Exit\n";
    Utils::drawLine('=');
    cout << "\nOption descriptions:\n";
    cout << "1 - Show complete list of students and grades\n";
    cout << "2 - Calculate and display average grades\n";
    cout << "3 - Find and display best students\n";
    cout << "4 - Search for a specific student\n";
    cout << "5 - Modify student grades\n";
    cout << "6 - Add a new student\n";
    cout << "7 - Remove a student\n";
    cout << "8 - Edit student information\n";
    Utils::setColor(Colors::WHITE);
}

void displayProgramInfo() {
    Utils::setColor(Colors::YELLOW);
    cout << "\nProgram features:\n";
    cout << "* Manage student records and grades\n";
    cout << "* Calculate statistics and averages\n";
    cout << "* Save best students to file\n";
    cout << "* Modify student grades\n";
    Utils::setColor(Colors::WHITE);
}

int main()
{
    srand(time(NULL));
    STUDENT *tab = nullptr;
    int N = 0;
    char choice;

    try {
        if (!loadStudentsFromFile(tab, N)) {
            Utils::logError("Failed to load student data!");
            // Create empty data file if it doesn't exist
            std::ofstream createFile("data.txt");
            createFile.close();
        }

        do {
            Utils::displayHeader();
            displayProgramInfo();
            displayMenu();

            cout << "\nEnter your choice (1-9): ";
            choice = _getch();

            switch(choice) {
                case '1':
                    // Display students
                    if(tab != nullptr) {
                        wyswietl_uczniow(tab, N);
                    } else {
                        cout << "No data loaded yet!" << endl;
                    }
                    break;
                case '2':
                    if(tab != nullptr) {
                        cout << "\nAverage grade for all students: " 
                             << fixed << setprecision(2) << srednia_ocen_studentow(tab, N) << endl;
                    } else {
                        cout << "No data loaded yet!" << endl;
                    }
                    break;
                case '3':
                    if(tab != nullptr) {
                        ofstream bestFile("best_students.txt");
                        najwyzsza_srednia(bestFile, tab, N);
                        bestFile.close();
                    } else {
                        cout << "No data loaded yet!" << endl;
                    }
                    break;
                case '4':
                    if(tab != nullptr) {
                        konkretny_student(tab, N);
                    } else {
                        cout << "No data loaded yet!" << endl;
                    }
                    break;
                case '5':
                    if(tab != nullptr) {
                        zmiana_ocen(tab, N);
                        saveStudentsToFile(tab, N);
                    } else {
                        cout << "No data loaded yet!" << endl;
                    }
                    break;
                case '6': {
                    if (addStudent(tab, N)) {
                        cout << "Student added successfully!" << endl;
                        saveStudentsToFile(tab, N);
                    }
                    break;
                }
                case '7': {
                    if(tab != nullptr) {
                        // Display current students first
                        cout << "\nCurrent students:\n";
                        for(int i = 0; i < N; i++) {
                            cout << (i+1) << ". " << tab[i].im_nazwisko 
                                 << " (Index: " << tab[i].indeks << ")" << endl;
                        }
                        
                        string indeks;
                        cout << "\nEnter student index to remove: ";
                        cin >> indeks;
                        if (removeStudent(tab, N, indeks)) {
                            cout << "Student removed successfully!" << endl;
                            saveStudentsToFile(tab, N);
                        } else {
                            cout << "Student not found or could not be removed!" << endl;
                        }
                    } else {
                        cout << "No data loaded yet!" << endl;
                    }
                    break;
                }
                case '8': {
                    string indeks;
                    cout << "Enter student index to edit: ";
                    cin >> indeks;
                    if (editStudent(tab, N, indeks)) {
                        cout << "Student updated successfully!" << endl;
                        saveStudentsToFile(tab, N);
                    }
                    break;
                }
                case '9':
                    Utils::setColor(Colors::LIGHT_RED);
                    cout << "\nExiting program...\n";
                    Utils::setColor(Colors::WHITE);
                    break;
                default:
                    cout << "\nInvalid option!\n";
            }
            if(choice != '9') {
                Utils::waitForKeyPress();
            }
        } while(choice != '9');
    } catch(const std::exception& e) {
        Utils::logError(e.what());
        delete[] tab;
        return 1;
    }
    delete[] tab;
    return 0;
}
