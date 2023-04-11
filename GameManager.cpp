#include <iostream>
#include <fstream>
#include "GameManager.h"
#include "LifeCell.h"
#include "utils.h"

void GameManager::StartGame()
{
    PrintWelcomeMessage();
    // Load Map from file
    std::string filename;
    do
    {
        std::cout << "Please enter the world map to load: ";
        std::cin >> filename;
    } while (!LoadWorld(filename));
    while (!IsGameOver())
    {
        PrintWorld();
        std::cout << "Press any key to continue..." << std::endl;
        KeyCode option = GetKey();
        switch (option)
        {
        case KeyCode::SAVE:
            std::cout << "Please enter the filename to save to: ";
            std::cin >> filename;
            SaveWorld(filename);
            break;
        case KeyCode::QUIT:
            ExitGame();
            break;
        default:
            UpdateGame();
            break;
        }
        clearScreen();
    }
}

void GameManager::UpdateGame()
{
    IncrementRoundCount();
    return m_world->Update();
}

void GameManager::SaveWorld(const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << m_world->GetWorldStr();
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}

void GameManager::ExitGame()
{
    SetGameOver(true);
    // std::cout << COLOR_RESET;
}

bool GameManager::LoadWorld(const std::string &filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        int current_row = 0;
        int current_col = 0;
        while (std::getline(file, line))
        {
            current_row++;
            current_col = 0;
            for (auto ch : line)
            {
                if (ch == '!')
                    break;
                m_world->SetCell(
                    current_row,
                    current_col,
                    ch);
                current_col++;
            }
        }
        file.close();
        std::cout << "World loaded successfully" << std::endl;
        return true;
    }
    std::cout << "Unable to open file" << std::endl;
    return false;
}

void GameManager::PrintWelcomeMessage()
{
    std::cout << "                         Game of Life - Edition for CS100 Homework" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Also known simply as life, " << std::endl;
    std::cout << "is a cellular automaton devised by the British mathematician John Horton Conway in 1970." << std::endl;
    std::cout << std::endl;
    std::cout << "Rules: " << COLOR_RED << m_world->GetRuleName() << COLOR_RESET << std::endl;
    std::cout << "The universe of the Game of life is an infinite two-dimensional orthogonal grid of square cells," << std::endl;
    std::cout << "each of which is in one of two possible states, life or dead. Every" << std::endl;
    std::cout << "cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent." << std::endl;
    std::cout << "At each step in time, the following transitions occur:" << std::endl;
    std::cout << "1. Any live cell with fewer than two live neighbours dies, as if caused by under-population." << std::endl;
    std::cout << "2. Any live cell with two or three live neighbours lives on to the next generation." << std::endl;
    std::cout << "3. Any live cell with more than three live neighbours dies, as if by over-population." << std::endl;
    std::cout << "4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction." << std::endl;
    std::cout << std::endl;
    std::cout << "O - living cell" << std::endl;
    std::cout << "R - RED cell" << std::endl;
    std::cout << "B - BLUE cell" << std::endl;
    std::cout << ". - dead cell" << std::endl;
    std::cout << std::endl;
}

void GameManager::PrintWorld()
{
    std::cout << "Current Round: " << GetRoundCount() << std::endl;
    for (auto ch : m_world->GetWorldStr())
    {
        switch(ch)
        {
        case BASE_CELL_ALIVE:
            std::cout << COLOR_GREEN << ch << COLOR_RESET;
            break;
        case COLOR_CELL_RED:
            std::cout << COLOR_RED << ch << COLOR_RESET;
            break;
        case COLOR_CELL_BLUE:
            std::cout << COLOR_BLUE << ch << COLOR_RESET;
            break;
        default:
            std::cout << ch;
            break;
        }
    }
}