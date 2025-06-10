# 🎓📚 Student Record Manager Pro 🧑‍🎓
_A comprehensive C++ console system for efficient student data management, grade analysis, and performance tracking._

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)

## 📝 Project Description

**Student Record Manager Pro** is a powerful and user-friendly C++ console application designed for streamlined management of student academic records. Utilizing dynamic arrays for flexible data handling, it allows users to add, edit, and remove student profiles, manage their grades (which can be randomly generated or manually input), and perform insightful analyses. Key functionalities include calculating overall class averages, individual student averages, and identifying top-performing students. The system also features robust search capabilities, data persistence through file I/O, and error logging for reliability. Its colorful interface enhances user interaction and data presentation.

![Demo GIF](screenshots/1.gif)

## ✨ Key Features

*   👤 **Student Record Management**:
    *   Add new students to the system.
    *   Edit existing student information (e.g., name).
    *   Remove students from the records.
*   📝 **Grade Administration**:
    *   Assign or modify grades for students.
    *   Option for random generation of grades (typically within a defined range, e.g., 2.0-5.0).
*   📊 **Performance Analysis**:
    *   Calculate the overall average grade for all students.
    *   Compute individual average grades for each student.
    *   Identify and list students with the highest average grades.
*   🔍 **Student Search**: Efficiently search for specific students (e.g., by partial name, case-insensitive).
*   💾 **Data Persistence**:
    *   Save all student data (names, grades) to a primary data file (e.g., `data.txt`).
    *   Load student data from the file upon startup.
    *   Save a list of top-performing students to a separate file (e.g., `best_students.txt`).
*   🌈 **Colorful Console Interface**: Enhanced user experience with colored text for menus, highlights, and messages (Windows-specific).
*   📄 **Error Logging**: Logs operational errors to a file for easier debugging and system monitoring.
*   📋 **Interactive Menu**: User-friendly, menu-driven navigation for all functionalities.

## 🖼️ Screenshots

_Screenshots showcasing the main menu, student list, grade input, statistical outputs, and other key interface elements._

<p align="center">
  <img src="screenshots\1.jpg" width="300"/>
  <img src="screenshots\2.jpg" width="300"/>
  <img src="screenshots\3.jpg" width="300"/>
  <img src="screenshots\4.jpg" width="300"/>
  <img src="screenshots\5.jpg" width="300"/>
  <img src="screenshots\6.jpg" width="300"/>
  <img src="screenshots\7.jpg" width="300"/>
  <img src="screenshots\8.jpg" width="300"/>
  <img src="screenshots\9.jpg" width="300"/>
  <img src="screenshots\10jpg" width="300"/>
</p>


## ⚙️ System Requirements

*   **Operating System**: Windows (due to the use of `windows.h` for console color manipulation and `conio.h` for functions like `_getch()`).
*   **C++ Compiler**: Any modern C++ compiler that supports C++11 or newer (e.g., g++, MinGW, Clang, MSVC).
*   📄 **`utils.h` and `student.h` Header Files (User-Provided)**: This project **critically requires** two header files, `utils.h` and `student.h`, which are **not included in the repository and must be created by the user.** These files should contain necessary utility functions and the student data structure/logic, respectively. See the "Installation and Running" section for more details.

## 🛠️ Installation and Running

1.  **Clone the Repository**:
    ```bash
    git clone <repository-url>
    ```
    (Replace `<repository-url>` with the actual URL of your repository)

2.  **Navigate to the Project Directory**:
    ```bash
    cd <repository-directory>
    ```
    (Replace `<repository-directory>` with the name of the cloned folder)

3.  **Create `utils.h` and `student.h`**:
    Before compiling, you **must** create `utils.h` and `student.h` in the project's root directory.

    **Example content for `utils.h` (Illustrative):**
    ```cpp
    #ifndef UTILS_H
    #define UTILS_H

    #include <string>
    #include <windows.h> // For SetConsoleTextAttribute
    #include <conio.h>   // For _getch()
    #include <fstream>   // For logging
    #include <ctime>     // For timestamps in logs

    // Example: Console Color Codes
    const int CLR_DEFAULT = 7;
    const int CLR_MENU = 11;
    const int CLR_HIGHLIGHT = 14;
    const int CLR_ERROR = 12;

    void setColor(int color);
    void drawLine(char c = '-', int length = 50);
    void logError(const std::string& message, const std::string& logFilePath = "errors.log");
    void waitForKeyPress(const std::string& message = "Press any key to continue...");
    // Add other utility function declarations as needed by your main.cpp

    #endif // UTILS_H
    ```

    **Example content for `student.h` (Illustrative):**
    ```cpp
    #ifndef STUDENT_H
    #define STUDENT_H

    #include <string>
    #include <vector> // Assuming dynamic arrays are implemented with vectors

    // Example: Student Data Structure
    struct STUDENT {
        std::string name;
        std::vector<double> grades; // Or a fixed-size array if N_GRADES is constant
        double averageGrade;
        // Add other fields if necessary
    };

    // Function declarations related to student management
    void loadStudentsFromFile(std::vector<STUDENT>& students, const std::string& filePath);
    void saveStudentsToFile(const std::vector<STUDENT>& students, const std::string& filePath);
    void saveBestStudentsToFile(const std::vector<STUDENT>& students, const std::string& filePath, int topN = 3);
    void addStudent(std::vector<STUDENT>& students);
    void removeStudent(std::vector<STUDENT>& students, const std::string& nameToRemove);
    void editStudent(std::vector<STUDENT>& students, const std::string& nameToEdit);
    void displayAllStudents(const std::vector<STUDENT>& students);
    void calculateAverageGrades(std::vector<STUDENT>& students); // Calculates for all and individual
    void findBestStudents(const std::vector<STUDENT>& students);
    STUDENT* searchStudent(std::vector<STUDENT>& students, const std::string& searchTerm);
    void modifyGrades(STUDENT* student); // For a specific student
    void generateRandomGrades(STUDENT& student, int numGrades = 5, double minGrade = 2.0, double maxGrade = 5.0);
    // Add other student-related function declarations

    #endif // STUDENT_H
    ```
    *These are **examples**. You need to implement the functions declared here (either in these .h files if they are simple inline functions/templates, or more commonly in corresponding `.cpp` files like `utils.cpp` and `student.cpp` which you would then also need to compile and link).*

4.  **Compile the Program**:
    Open a terminal (like Command Prompt or PowerShell) in the project directory.
    **Example using g++ (MinGW):**
    ```bash
    g++ main.cpp utils.cpp student.cpp -o student_management.exe -static-libgcc -static-libstdc++
    ```
    *(This assumes you have `utils.cpp` and `student.cpp` for implementations. If all logic is in headers, then `g++ main.cpp -o student_management.exe ...` might suffice, but this is less common for larger projects).*

5.  **Prepare `data.txt` (Optional but Recommended)**:
    You can pre-populate a file named `data.txt` (or whatever your primary data file is named, potentially defined in `utils.h` or a new `constants.h`) with student names, one per line. If the file doesn't exist, the program might be designed to create it or prompt for initial data.

6.  **Run the Application**:
    After successful compilation, execute the generated program:
    ```bash
    ./student_management.exe
    ```
    or simply in CMD:
    ```bash
    student_management.exe
    ```

## ▶️ How to Use

Upon launching, the application will present a main menu with numbered options. Enter the number corresponding to your desired action:

1.  **Display all students**: Lists all students currently in the system along with their grades and average.
2.  **Show average grades**: Displays the overall class average and individual student averages.
3.  **Find best students**: Identifies and shows the top-performing students (e.g., top 3 by average grade). This list might also be saved to `best_students.txt`.
4.  **Search for a student**: Allows you to search for a student by name (case-insensitive, partial matches often supported).
5.  **Modify grades**: Select a student and manually change their grades or trigger random grade generation for them.
6.  **Add new student**: Prompts for the new student's name and initializes their record (possibly with empty or randomly generated grades).
7.  **Remove student**: Allows you to select and delete a student's record from the system.
8.  **Edit student**: Allows modification of a student's details (e.g., name).
9.  **Exit**: Saves data (if applicable) and terminates the application.

*Data is typically saved to `data.txt` upon exiting or via a dedicated save option, and top student lists might be updated in `best_students.txt`.*

## 💡 Technical Details & Program Logic

*   **Dynamic Data Structures**: Uses dynamic arrays (likely `std::vector` in C++) to store student records, allowing for a variable number of students.
*   **`STUDENT` Structure/Class**: Defined in `student.h`, this holds individual student data like name, a collection of grades, and calculated average.
*   **`utils.h`**: Contains utility functions such as `setColor()` for console colors, `drawLine()` for UI formatting, `logError()` for writing to an error log, and `waitForKeyPress()` for pausing execution.
*   **File I/O**: Employs C++ file streams (`fstream`) to read and write student data to `data.txt` and `best_students.txt`. The format can be plain text or a more structured format.
*   **Grade Generation**: Random grades (e.g., floating-point numbers between 2.0 and 5.0) are generated using C++'s random number utilities.
*   **Search Algorithm**: Implements a search function (e.g., linear search) that can handle partial and case-insensitive name matching.
*   **Error Handling**: Basic error logging, for instance, if data files cannot be opened.

## 🤝 Contributing

Contributions to the **Student Record Manager Pro** are highly valued! If you have suggestions for new functionalities, UI enhancements, or code improvements:

1.  Fork the repository.
2.  Create a new branch for your changes: `git checkout -b feature/your-improvement-idea`
3.  Implement your changes and commit them: `git commit -m "Enhancement: Implement your improvement idea"`
4.  Push your changes to your branch: `git push origin feature/your-improvement-idea`
5.  Open a Pull Request.

Please ensure your contributions are well-documented and align with the project's coding conventions.

## ✍️ Author

**Adrian Lesniak**
_C++ Developer & System Design Enthusiast_

## 📃 License

This project is licensed under the **MIT License**.
The full text of the license is available at: [https://opensource.org/licenses/MIT](https://opensource.org/licenses/MIT)

---
🚀 _Empowering education through efficient data management!_
