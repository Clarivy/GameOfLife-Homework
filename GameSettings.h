#ifndef GAMESETTING_H__
#define GAMESETTING_H__

#include <set>


// For base rule save and laod
#define BASE_CELL_ALIVE 'O'
#define BASE_CELL_DEAD '.'

// For base rule states
const std::set BASE_CELL_SURVIVE = {2, 3};
const std::set BASE_CELL_BIRTH = {3};

#define BASE_CELL_BLUE 'B'
#define BASE_CELL_RED 'R'
#define BASE_CELL_DEAD '.'


// For generations rule
#define MAX_GENERATIONS 8

#endif