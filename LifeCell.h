#ifndef LIFECELL_H__
#define LIFECELL_H__
#include <string>
#include <vector>
#include <memory>
#include "GameSettings.h"

enum class CellState
{
    DEAD,
    ALIVE
};

enum class CellColor
{
    NONE,
    RED,
    BLUE
};

class CellBase
{

public:
    CellBase() = delete;

    CellBase(const int x, const int y, const CellState &state) : m_x(x), m_y(y), m_state(state) {}

    virtual ~CellBase() = default;

    // Getters
    bool IsAlive() { return m_state == CellState::ALIVE; }
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }

    // Setters
    void SetAlive(const CellState &state) { m_state = state; }

    // Convert to string for printing
    virtual std::string GetStr() { return std::string(IsAlive() ? " O " : " . "); }

private:
    int m_x, m_y;
    CellState m_state;
};

class CellColorised : public CellBase
{

public:
    CellColorised() = default;

    CellColorised(const int x, const int y, const CellState &state, const CellColor &color) : CellBase(x, y, state), m_color(color) {}

    virtual ~CellColorised() = default;

    // Getters
    CellColor GetColor() { return m_color; }

    // Convert to string for printing
    virtual std::string GetStr() override;

private:
    CellColor m_color;
};

class CellGenerations : public CellBase
{

public:
    CellGenerations() = default;

    CellGenerations(const int x, const int y, const CellState &state) : CellBase(x, y, state), m_generation(1) {}

    virtual ~CellGenerations() = default;

    // Getters
    int GetGeneration() { return m_generation; }

    // Setters
    void SetGeneration(const int generation);
    void IncrementGeneration();

private:
    int m_generation;
};

using CellPointer = std::shared_ptr<CellBase>;
using CellNeighbors = std::vector<CellPointer>;
using WorldMapRow = std::vector<CellPointer>;
using WorldMap2d = std::vector<WorldMapRow>;

#endif