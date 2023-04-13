# Homework: Game Of Life

## Background

[**The Game of Life**](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) is a simple but profound game, created by one of the world greatest mathematician John Horton Conway. This game does not require player participation because all evolutionary processes are determined by the initial state and will proceed spontaneously. A common way to play with the Game of Life is to give it an initial state and watch how it evolves.

![https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life](D:/AA-Study/2023-Spring/CS100_TA/Game of Life/GameOfLife-Homework/pics/demo.gif)

## Rules

The universe of the Game of Life can simply considered as an infinite sheet of grid paper, in which each grid (or cell) is either alive or dead. The [original rules for the Game of Life](https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Rules) are reprinted below:

- **Underpopulation:** Any living cell with fewer than two living neighbors (the surrounding 8 cells) dies.

- **Survive: **Any living cell with two or three living neighbors lives on to the next generation.
- **Overpopulation:** Any living cell with more than three living neighbors dies.
- **Reborn: **Any dead cell with exactly 3 living neighbors comes to life.

![Moreno, Niandry. "A vector-based geographical cellular automata model to mitigate scale sensitivity and to allow objects' geometric transformation." (D:/AA-Study/2023-Spring/CS100_TA/Game of Life/GameOfLife-Homework/pics/rule.png).](./pics/rule.png)

There are many [variants of the Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Variations) , each with its own rules. Here are four of the most popular variants:

- **Colorised**

  It follows the basic rules as described above with one addition: the living cells have different colors. When a cell is born, its color will be decided by the major color of its three living neighbors.

  The formal definition will be described later. More on [wiki](https://conwaylife.com/wiki/Colourised_Life).

- **Extended**

  It follows the basic rules as described above with one change: the size of a cell's neighborhood is extended to $k(k > 1)$. Consider any square with size $2k+1$, the centering cell will have all other cells in this square as its neighbors.

- **Weighted**

  It follows the **extended** rules as described above with one  addition: the neighbors are weighted, meaning that some neighbors might have more influence on it.

- **Generations:**

  It follows the **extended** rules as described above with one change: the living cells will not die immediately when overpopulation or underpopulation happens. Instead, the cells 'gets older' before the final death.

  The formal definition will be described later. More on [wiki](https://conwaylife.com/wiki/Generations).

## Try it Out!

The Game of Life has been studied extensively, and many interesting patterns have been discovered. Before starting your work, we strongly recommend you to first try this game out! You can play with it at [golly](https://golly.sourceforge.net/webapp/golly.html), and there are many amazing patterns you can find online. Here is a video in [YouTube](https://www.youtube.com/watch?v=C2vgICfQawE) and [BiliBili](https://www.bilibili.com/video/BV1PE411d7aR) about the Game of Life for your reference.

You will notice that some of the patterns are stable, meaning that they will continue to exist indefinitely, and some of them are even periodic, meaning that they will repeat themselves after a certain number of steps. Other patterns are unstable, meaning that they will eventually die out.  Here are some basic patterns:

![http://pi.math.cornell.edu/~lipa/mec/lesson6.html](D:/AA-Study/2023-Spring/CS100_TA/Game of Life/GameOfLife-Homework/pics/patterns.png)

## Your Task

Your task is to complete the implementation of our C++ version of the Game of Life with multiple rules. We have provided you a framework to help you get started. You need to implement all the functions in `LifeRuleStudent.cpp`. 

We have already wrote the base rule, `class LifeRuleBase`, left you to finish four variant rules listed above: `LifeRuleColorised`, `LifeRuleExtended`, `LifeRuleWeighted`, `LifeRuleGenerations`.  

There is no need for you to change other files. And since you can only submit `LifeRuleStudent.cpp` to OJ, any other change will not be considered.

### Framework

In real life, the game is often played on infinite number of grids. However, to simplify this homework, our game has fixed 25 \* 25 grids. The cells out of the grids will always be regarded as dead, and will never come to life.

For the original rules, a cell in grid can be described by three parameters: **x**, **y** and **state**: 

- $(x, y)$ represents the coordinate of this cell. $(x, y \in Z^+, 0 \leq x, y \leq 24)$
- State describes whether the cell is alive or dead. 

A cell is defined in `LifeCell.cpp`, called `CellBase`, with a smart pointer `CellPointer`.

In `class LifeRuleBase`, there are five functions. Here are the detailed explanation for two of them (for the rest of the functions, you can check the comments in files):

#### DetermineNextState

```cpp
CellPointer DetermineNextState(const CellPointer current, const CellNeighbors &neighbors)
```

This function will determine the next state of a cell, based on its current state and the number of lived `neighbors`. It applies the original rules. (对吗？)

- ***Parameters:***
  `current`: A `CellPointer`, indicating the current state of a cell.
  `neighbors`: a vector of `CellPointer`, containing all the neighbors of the cell we working on. We need to count the number of living cells in neighbors to determine the next state.


- ***Returns:***
  A `CellPointer`, indicating the next state of a cell.

#### GetNeighbors

```cpp
CellNeighbors GetNeighbors(const GameWorld *const game_world, const int x, const int y) const
```

It returns a vector containing all of the neighbors of the cell at $(x, y)$. For example, （？）

- ***Parameters:***
  `game_world`: Current world we are working in (You can imagine this as the grid paper we play the game on).
  `x`,` y`: Coordinate of the cell.

- ***Returns:***
  All neighbors of a cell at $(x, y)$.

### Rules Implementation Guide

#### LifeRuleColorised

The colorised rule is a variant of the original game. Now the living cells are all colored with one of the two different colors, red and blue. When a cell is born, its color will be decided by the major color of its three lived neighbors. 

Since the birth of a cell only happens when it has 3 living neighbors, and we only have 2 colors here, you don't need to worry about equality. 

- Please note that it should be implemented as `class LifeRuleColorised`.

##### Hint

- You may want to inherit `LifeRuleBase` and override its `DetermineNextState`.


#### LifeRuleExtended

The extended rule is a variant of the original game, where a cell's neighborhood is extended to 2. (i.e. All other 24 cells in a square of size $5 * 5$ are now neighbors of the centering cell).

- Please note that it should be implemented as `class LifeRuleExtended`.

##### Hint

- This can be done by overriding `GetNeighbors`.


#### LifeRuleWeighted

The weighted life rule is a variant of our extended game. Now the living cells are all weighted, meaning that some neighbors might have greater influences. So in detail, what you should do is:

1. For a living cell, calculate the sum of the weights of its neighbors. We call this "total influence".
2. **Underpopulation:** Any cells with a total influence of less than 4 dies.
3. **Survive: **Any living cell with $4 \leq $total influence $\leq 6 $ survives.
4. **Overpopulation:** Any live cell with weight more than 6 living neighbours dies.
5. **Reborn: **Any dead cell with exactly 6 living neighbors becomes alive.

The neighborhood of a cell $x$ can be now represented as the following matrix:

$$ \left\{\begin{matrix}   1 & 1 & 2& 1& 1\\  1 & 2 & 2& 2& 1\\ 2 & 2 & x& 2& 2 \\ 1 & 2 & 2& 2& 1 \\ 1 & 1 & 2& 1& 1\end{matrix}  \right\}\tag{2} $$

##### Hint

This can be done by overriding `DetermineNextState` in `LifeRuleExtended`.

#### LifeRuleGenerations

The generations rule is a variant of the original game. Now the live cells will not die immediately when overpopulation or underpopulation happens. Instead, the cells 'gets older' before the final death.

The detailed rules are as follows:

1.  A cell in state 0 ("dead") will switch to state 1 ("born") in the next state if it has 3 neighbors in state 1 ("alive").
2.  A cell in state 1 ("alive") will:

    - Remain in state 1 ("survive") in the next state if it has 2 or 3 neighbors in state 1 ("alive").
    - Otherwise, switch to state 2 ("aging") in the next state.

3.  A cell in state $m \geq 2$ will switch to state $m + 1$ in the next state. In particular, a cell in state $N$ will be reset to state 0 ("die").

In our game, $N = 8$.

- Please note that it should be implemented as `class LifeRuleGenerations`.

##### Hint

You may want to inherit `LifeRuleBase` and override its `DetermineNextState`.

### How to run

#### Compile the project

```bash
g++ -Wall -Wextra -o gof GameWorld.cpp GameManager.cpp LifeCell.cpp main.cpp LifeRuleStudent.cpp
```

#### Run the project

```bash
./gof <rule>
```

The program takes one argument: the rule you want to use. The rule can be `Base`, `Colorised`, `Extended`, `Weighted`, `Generations`.

Try to run with `./gof Base` and you can play with the original Game of Life.

### File Structure

This problem contains several files. You may need to read and understand some of them in order to complete the assignment. There are also some files that you can simply ignore. You don't need to understand every file to do this homework.

## Submission

You only need to submit `LifeRuleStudent.cpp` to OJ. 