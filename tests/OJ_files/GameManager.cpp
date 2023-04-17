#include <iostream>
#include <fstream>
#include <cctype>
#include "GameManager.h"
#include "LifeCell.h"
#include "utils.h"

void GameManager::StartGame()
{
    clearScreen();
    PrintWelcomeMessage();
    // Load Map from file
    std::string filename;
    do
    {
        std::cout << "Please enter the world map to load: ";
        std::cin >> filename;
    } while (!LoadWorld(filename));
    std::cout << "World loaded successfully." << std::endl;
    while (!IsGameOver())
    {
        PrintWorld();
        std::cout << "Press Enter to continue, 's' to save the current world, and 'q' to quit." << std::endl;
        KeyCode option = GetKey();
        switch (option)
        {
        case KeyCode::SAVE:
            std::cout << "Please enter the filename to save to: ";
            std::cin >> filename;
            SaveWorld(filename);
            std::cout << "World saved successfully." << std::endl;
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

void GameManager::SaveWorld(std::ostream &os)
{
    os << m_world->GetWorldStr();
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
        LoadWorld(file);
        file.close();
        return true;
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
        return false;
    }
}
void GameManager::LoadWorld(std::istream &is)
{
    std::string line;
    int current_row = 0;
    int current_col = 0;
    while (std::getline(is, line))
    {
        current_col = 0;
        for (auto ch : line)
        {
            if (ch == '!')
                break;
            if (std::isspace(ch))
                continue;
            if (std::isdigit(ch))
            {
                m_world->SetCell(
                    current_row,
                    current_col, ch - '0');
            }
            else
            {
                int state = MAP_TO_STATE.at(ch);
                m_world->SetCell(
                    current_row,
                    current_col, state);
            }
            current_col++;
        }
        current_row++;
    }
}

void GameManager::PrintWelcomeMessage()
{
    std::cout << std::endl;
}

void GameManager::PrintWorld()
{
    std::cout << std::endl;
}