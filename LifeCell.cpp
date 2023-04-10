#include "LifeCell.h"
#include "GameSettings.h"

std::string CellColorised::GetStr()
{
    return std::string(IsAlive() ? (GetColor() == CellColor::RED ? "R" : "B") : ".");
}

void CellGenerations::SetGeneration(const int generation)
{
    m_generation = generation;
    if (m_generation == 0 || m_generation > MAX_GENERATIONS)
        SetAlive(CellState::DEAD);
    else
        SetAlive(CellState::ALIVE);
}

void CellGenerations::IncrementGeneration()
{
    SetGeneration(m_generation + 1);
}