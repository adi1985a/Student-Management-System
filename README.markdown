# Student Management System

## Description
A C++ console application for managing student records using dynamic arrays. Supports adding, editing, removing students, grade management, calculating averages, and identifying top performers. Features a colorful interface and error logging. Created by Adrian Lesniak.

## Features
- Add, edit, and remove students
- Manage student grades (randomly generated or modified)
- Calculate overall and individual grade averages
- Identify students with highest averages
- Search for specific students
- Save/load student data to/from `data.txt`
- Save best students to `best_students.txt`
- Colorful console interface

## Requirements
- C++ compiler (e.g., g++)
- Header files: `utils.h` and `student.h` (not provided)
- Windows OS (uses `windows.h` and `conio.h`)

## Installation
1. Clone the repository:
   ```bash
   git clone <repository-url>
   ```
2. Ensure `utils.h` and `student.h` are in the project directory.
3. Compile the program:
   ```bash
   g++ main.cpp -o student_management
   ```

## Usage
1. Create a `data.txt` file with student names (one per line) or let the program create it.
2. Run the program:
   ```bash
   ./student_management
   ```
3. Choose options 1-9 from the menu:
   - 1: Display all students
   - 2: Show average grades
   - 3: Find best students
   - 4: Search for a student
   - 5: Modify grades
   - 6: Add new student
   - 7: Remove student
   - 8: Edit student
   - 9: Exit
4. Results are saved to `data.txt` and `best_students.txt`.

## Notes
- Requires `utils.h` for functions like `setColor()`, `drawLine()`, `logError()`, and `waitForKeyPress()`.
- Requires `student.h` for `STUDENT` structure and functions like `loadStudentsFromFile()`, `addStudent()`, `removeStudent()`, and `editStudent()`.
- Grades are randomly generated (2.0-5.0) or manually modified.
- Case-insensitive partial name search for students.

## Author
Adrian Lesniak

## License
MIT License