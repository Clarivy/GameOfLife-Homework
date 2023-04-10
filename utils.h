// Author: Mario Talevski
#include <iostream>
#include <cstdlib>

#include <fstream>
#include <string>
#include <sstream>

// Move OS defines up here to be used in different places
#if defined(_WIN32) || defined(WIN32) || defined(__MINGW32__) || defined(__BORLANDC__)
#define OS_WIN
// WINDOWS COLORS
#define COLOR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED)
#define COLOR_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)

#define COLOR_BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE)

#define COLOR_RESET SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)

#elif defined(linux) || defined(__CYGWIN__)
#define OS_LINUX

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

#elif (defined(__APPLE__) || defined(__OSX__) || defined(__MACOS__)) && defined(__MACH__) // To ensure that we are running on a mondern version of macOS
#define OS_MAC

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

#endif

#if defined(OS_WIN)
#include <windows.h> // Use for windows
#else
#include <unistd.h>
#endif

enum class KeyCode
{
    // Controls:   1        2
    NONE,
    SAVE,  // Save     S
    QUIT   // Esc     Esc
};

// Get keyboard without blocking
KeyCode GetKey()
{
    char ch = getchar();
    switch (ch)
    {
    case 's':
    case 'S':
        return KeyCode::SAVE;
    case 27:
        return KeyCode::QUIT;
    default:
        return KeyCode::NONE;
    }
}

const int gridSize = 25;
void printGrid(bool gridOne[gridSize + 1][gridSize + 1]);
void determineState(bool gridOne[gridSize + 1][gridSize + 1]);
void clearScreen(void);

int main()
{

    // system( "color A" );//LGT green
    std::cout << COLOR_GREEN;
    clearScreen();
    bool gridOne[gridSize + 1][gridSize + 1] = {};
    int x, y, n;
    std::string nc;
    std::string start;
    if (start == "y" || start == "Y")
    {
        while (true)
        {
            printGrid(gridOne);
            determineState(gridOne);
            Sleep(200);
            clearScreen();
        }
    }
    else
    {
        std::cout << COLOR_RESET;
        clearScreen();
        return 0;
    }
}

void clearScreen(void)
{
// Tested and working on Ubuntu and Cygwin
#if defined(OS_WIN)
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    if (hStdOut == INVALID_HANDLE_VALUE)
        return;

    /* Get the number of cells in the current buffer */
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count);

    /* Fill the entire buffer with the current colors and attributes */
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count);

    SetConsoleCursorPosition(hStdOut, homeCoords);

#elif defined(OS_LINUX) || defined(OS_MAC)
    std::cout << "\033[2J;"
              << "\033[1;1H"; // Clears screen and moves cursor to home pos on POSIX systems
#endif
}

void compareGrid(bool gridOne[gridSize + 1][gridSize + 1], bool gridTwo[gridSize + 1][gridSize + 1])
{
    for (int a = 0; a < gridSize; a++)
    {
        for (int b = 0; b < gridSize; b++)
        {
            gridTwo[a][b] = gridOne[a][b];
        }
    }
}
