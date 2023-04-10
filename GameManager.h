#ifndef GAMEMANAGER_H__
#define GAMEMANAGER_H__
#include <string>
#include "GameWorld.h"

/**
 * A simple ASCII interface for the Game of Life
 *
 **/

class GameManager
{
public:
    GameManager() = delete;
    ~GameManager() = default;
    GameManager(const GameManager &) = delete;

    GameManager(const std::shared_ptr<GameWorld> &world) : m_world(world) {}
    
    // Functionalities of the game

    /**
     * Starts the game
     */
    void StartGame();

    /**
     * Updates the game
     *
     * @return true if the game has changed, false otherwise
     */
    bool UpdateGame();

    /**
     * Saves the current world to a file
     *
     * @param filename The name of the file to save to
     */
    void SaveWorld(const std::string &filename);

    /**
     * Exits the game
     */
    void ExitGame();

    /**
     * Loads a world from a .cells file
     * The format of the file is as follows:
     * Comments start with a ! and are ignored
     * Cells are represented by a O or . (alive or dead respectively)
     *
     * @param filename The name of the file to load
     */
    void LoadWorld(const std::string &filename);

    
    // For interface

    /**
     * Print welcome message
     */
    void PrintWelcomeMessage();

    /**
     * Print the current world
     */
    void PrintWorld();

    void SetGameOver(bool isGameOver) { this->isGameOver = isGameOver; }
    bool IsGameOver() { return isGameOver; }

private:
    std::shared_ptr<GameWorld> m_world;
    bool isGameOver = false;
};

#endif