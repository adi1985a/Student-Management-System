#include "utils.h"
#include <fstream>
#include <conio.h>

namespace Utils {
    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void logError(const std::string& error) {
        std::ofstream logFile("error_log.txt", std::ios::app);
        logFile << "[ERROR] " << error << std::endl;
        logFile.close();
    }

    void drawLine(char symbol, int length) {
        std::string line(length, symbol);
        std::cout << line << std::endl;
    }

    void displayHeader() {
        system("cls");
        setColor(Colors::LIGHT_BLUE);
        drawLine('*');
        std::cout << "\t\tStudent Management System v2.0" << std::endl;
        std::cout << "\t\tCreated by Adrian Lesniak" << std::endl;
        drawLine('*');
        setColor(Colors::WHITE);
    }

    void waitForKeyPress() {
        std::cout << "\nPress any key to continue..." << std::endl;
        _getch();
    }
}
