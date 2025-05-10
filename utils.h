#pragma once
#include <windows.h>
#include <string>
#include <iostream>

namespace Colors {
    const int WHITE = 7;
    const int LIGHT_BLUE = 11;
    const int LIGHT_GREEN = 10;
    const int LIGHT_RED = 12;
    const int YELLOW = 14;
}

namespace Utils {
    void setColor(int color);
    void logError(const std::string& error);
    void drawLine(char symbol = '-', int length = 80);
    void displayHeader();
    void waitForKeyPress();
}
