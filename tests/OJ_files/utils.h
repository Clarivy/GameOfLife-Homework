/**
 * @brief CLI for the game
 *
 * This part is derived from https://github.com/MarioTalevski/game-of-life and https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout
 *
 * @author Vincent Godin, Mario Talevski, Qingcheng Zhao
 *
 */
#ifndef GAMEOFLIFE_UTILS_H
#define GAMEOFLIFE_UTILS_H
#include <iostream>
#include <cstdlib>

#include <fstream>
#include <string>
#include <sstream>

enum class KeyCode
{
    // Controls:   1        2
    NONE,
    SAVE, // Save     S
    QUIT  // Esc     Esc
};

// Get keyboard without blocking
KeyCode GetKey()
{
    switch (std::cin.get())
    {
    case 's':
    case 'S':
        return KeyCode::SAVE;
    case 'q':
    case 'Q':
        return KeyCode::QUIT;
    default:
        return KeyCode::NONE;
    }
}

void clearScreen()
{
    
}

#endif // GAMEOFLIFE_UTILS_H