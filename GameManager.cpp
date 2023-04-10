#include <iostream>
#include <fstream>
#include "GameManager.h"
#include "LifeSprite.h"
#include "utils.h"

void GameManager::StartGame()
{
    PrintWelcomeMessage();
    // Load Map from file
    std::string filename;
    std::cin >> filename;
    LoadWorld(filename);
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
            if (!UpdateGame())
            {
                std::cout << "Game has ended." << std::endl;
                ExitGame();
            }
            break;
        }
        clearScreen();
    }
}

bool GameManager::UpdateGame()
{
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
    std::cout << COLOR_RESET;
    clearScreen();
}

void GameManager::LoadWorld(const std::string &filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        int current_row = 0;
        int current_col = 0;
        while (std::getline(file, line))
        {
            current_col = 0;
            for (auto ch : line)
            {
                if (ch == '!')
                    break;
                m_world->SetSprite(
                    current_row,
                    current_col,
                    ch);
                current_col++;
            }
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
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
    std::cout << "Rules" << std::endl;
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
    std::cout << ". - dead cell" << std::endl;
    std::cout << std::endl;
}

void GameManager::PrintWorld()
{
    std::cout << m_world->GetWorldStr();
}