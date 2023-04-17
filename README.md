# Homework: Game Of Life

## Background

[**The Game of Life**](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) is a simple but profound game, created by one of the world greatest mathematician John Horton Conway. This game does not require player participation because all evolutionary processes are determined by the initial state and will proceed spontaneously. A common way to play with the Game of Life is to give it an initial state and watch how it evolves.

![https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life](pics/demo.gif)

## Rules

The universe of the Game of Life can simply considered as an infinite sheet of grid paper, in which each grid (or cell) is either alive or dead. The [original rules for the Game of Life](https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Rules) are reprinted below:

- **Underpopulation:** Any living cell with fewer than two living neighbors (the surrounding 8 cells) dies.

- **Survive:** Any living cell with two or three living neighbors lives on to the next generation.
- **Overpopulation:** Any living cell with more than three living neighbors dies.
- **Reborn:** Any dead cell with exactly 3 living neighbors comes to life.

![Moreno, Niandry. "A vector-based geographical cellular automata model to mitigate scale sensitivity and to allow objects' geometric transformation." (D:/AA-Study/2023-Spring/CS100_TA/Game of Life/GameOfLife-Homework/pics/rule.png).](./pics/rule.png)

There are many [variants of the Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Variations) , each with its own rules. Here are four of the most popular variants:

- **Colorised**

  It follows the basic rules as described above with one addition: the living cells have different colors. When a cell is born, its color will be decided by the major color of its three living neighbors.

  The formal definition will be described later. More on [wiki](https://conwaylife.com/wiki/Colourised_Life).

- **Extended**

  It follows the basic rules as described above with one change: the size of a cell's neighborhood is extended. Consider any square with size $2k+1$, the centering cell will have all other cells in this square as its neighbors. For example, extended to a 5 \* 5 square, (i.e all 24 cells around a cell are now its neighbor, the cell itself is not included in its neighborhood).

  ![https://conwaylife.com/wiki/Moore_neighbourhood](pics/extended.png)

  The formal definition will be described later. More on [wiki](https://conwaylife.com/wiki/Gallery_of_neighbourhoods/Images).

- **Weighted**

  It follows the **extended** rules as described above with one addition: the neighbors are weighted, meaning that some neighbors might have more influence on it. More on [wiki](https://conwaylife.com/forums/viewtopic.php?f=11&t=935)

- **Generations:**

  It follows the **original** rules as described above with one change: the living cells will not die immediately when overpopulation or underpopulation happens. Instead, the cells 'gets older' before the final death.

  The formal definition will be described later. More on [wiki](https://conwaylife.com/wiki/Generations).

## Try it Out!

The Game of Life has been studied extensively, and many interesting patterns have been discovered. Before starting your work, we strongly recommend you to first try this game out! You can play with it at [golly](https://golly.sourceforge.net/webapp/golly.html), and there are many amazing patterns you can find online. Here is a video in [YouTube](https://www.youtube.com/watch?v=C2vgICfQawE) and [BiliBili](https://www.bilibili.com/video/BV1PE411d7aR) about the Game of Life for your reference.

You will notice that some of the patterns are stable, meaning that they will continue to exist indefinitely, and some of them are even periodic, meaning that they will repeat themselves after a certain number of steps. Other patterns are unstable, meaning that they will eventually die out. Here are some basic patterns:

<img src="pics/patterns.png" alt="http://pi.math.cornell.edu/~lipa/mec/lesson6.html" style="height:300px;" /> <img src="pics/patterns2.png" alt="http://pi.math.cornell.edu/~lipa/mec/lesson6.html" style="height:300px;" />

## Your Task

The Game of Life is a very simple game, but it has been shown to be capable of producing complex and interesting patterns. In fact, there are entire websites and books dedicated to the study of the Game of Life.

Your task is to complete the implementation of our C++ version of the Game of Life with multiple rules. We have provided you a framework to help you get started. You need to implement all the functions in `LifeRuleStudent.cpp`.

We have provided you with a framework to help you get started. You can refer to [How-to-Run](#how-to-run) to play with the game.

Rules should be implemented as classes. You need to think about how to design the class structure, and the inheritance relationship between different rules.

We have already wrote the base rule, `class LifeRuleBase`, left you to finish four variant rules listed above: `LifeRuleColorised`, `LifeRuleExtended`, `LifeRuleWeighted`, `LifeRuleGenerations`.

Here is the description:

- `LifeRuleBase`: We have provided for you. This is the original Game of Life, contains the basic code for implementing a rule in the Game of Life.
- `LifeRuleColorised`: **You need to complete it**. In this variant, the live cells have different colors.
- `LifeRuleExtended`: _You need to complete it_. In this variant, the size of a cell's neighborhood is extended.
- `LifeRuleWeighted`: **You need to complete it**. In this variant, neighbors are weighted.
- `LifeRuleGenerations`: **You need to complete it**. In this variant, the cells 'get older' before eventually dying.

To make sure the homework compile, every rule should be a subclass of `LifeRuleBase`. There is no need for you to change other files. And since you can only submit `LifeRuleStudent.cpp` to OJ, any other change will not be considered.

### Framework

In real life, the game is often played on infinite number of grids. However, to simplify this homework, our game has fixed 25 \* 25 grids. The cells out of the grids will always be regarded as dead, and will never come to life.

For the original rules, a cell in grid can be described by three parameters: **x**, **y** and **state**:

- $(x, y)$ represents the coordinate of this cell. $(x, y \in Z^+, 0 \leq x, y \leq 24)$
- State describes whether the cell is alive or dead.

A cell is defined in `LifeCell.cpp`, called `class LifeCell`, with a smart pointer `CellPointer`.

A class of any rules have two key functions `DetermineNextState`, `GetNeighbors`. You may want to reuse some of those while some of them rewrote.

Here is the definition of the three functions:

#### DetermineNextState

```cpp
void DetermineNextState(const CellPointer current, const CellNeighbors &neighbors) const
```

This function will determine the next state of a cell, based on its current state and the number of lived `neighbors`. It applies the original rules. (对吗？)

- **_Parameters:_**

  `current`: A `CellPointer`, pointing to a cell to be updated

  `neighbors`: a vector of `CellPointer`, containing all the neighbors of the cell we working on. You need to count the number of living cells in neighbors to determine the next state.

#### GetNeighbors

```cpp
CellNeighbors GetNeighbors(const GameWorld *const game_world, const int x, const int y) const
```

It returns a vector containing all of the neighbors of the cell at $(x, y)$. For example, （？）

- **_Parameters:_**

  `game_world`: Current world we are working in (You can imagine this as the grid paper we play the game on).

  `x`,` y`: Coordinate of the cell.

- **_Returns:_**

  All neighbors of a cell at $(x, y)$.

### Rules Implementation Guide

#### Colorised Rule

The colorised rule is a variant of the original game. Now the living cells are all colored with one of the two different colors, red and blue. When a cell is born, its color will be decided by the major color of its three lived neighbors.

Since the birth of a cell only happens when it has 3 living neighbors, and we only have 2 colors here, you don't need to worry about equality.

- Please note that it should be implemented as `class LifeRuleColorised`.

##### Hint

- You may want to inherit `LifeRuleBase` and override its `DetermineNextState`.

#### Extended Rule

The extended rule is a variant of the original game, where a cell's neighborhood is extended to 2. (i.e. All other 24 cells in a square of size $5 * 5$ are now neighbors of the centering cell).

- Please note that it should be implemented as `class LifeRuleExtended`.

##### Hint

- This can be done by overriding `GetNeighbors`.

#### Weighted Rule

The weighted life rule is a variant of our extended game. Now the living cells are all weighted, meaning that some neighbors might have greater influences. So in detail, what you should do is:

1. For a living cell, calculate the sum of the weights of its neighbors. We call this "total influence".
2. **Underpopulation:** Any cells with a total influence of less than 4 dies.
3. **Survive:** Any living cell with $4 \leq $total influence $\leq 6 $ survives.
4. **Overpopulation:** Any live cell with weight more than 6 living neighbours dies.
5. **Reborn:** Any dead cell with exactly 6 living neighbors becomes alive.

The neighborhood of a cell $x$ can be now represented as the following matrix:

$$ \begin{matrix} 1 & 1 & 2& 1& 1\\ 1 & 2 & 2& 2& 1\\ 2 & 2 & x& 2& 2 \\ 1 & 2 & 2& 2& 1 \\ 1 & 1 & 2& 1& 1\end{matrix}\tag{2} $$

##### Hint

This can be done by overriding `DetermineNextState` in `LifeRuleExtended`.

#### Generations Rule

The generations rule is a variant of the original game. Now the live cells will not die immediately when overpopulation or underpopulation happens. Instead, the cells 'gets older' before the final death.

The detailed rules are as follows:

1.  A cell in state 0 ("dead") will switch to state 1 ("born") in the next state if it has exactly 3 neighbors that is **not** in state 0 ("dead").
2.  A cell in state 1 ("alive") will:

    - Remain in state 1 ("survive") in the next state if it has 2 or 3 neighbors in state 1 ("alive").
    - Otherwise, switch to state 2 ("aging") in the next state.

3.  A cell in state $m \geq 2$ will switch to state $m + 1$ in the next state. In particular, a cell in state $N$ will be reset to state 0 ("die").

In our game, $N = 8$.

- Please note that it should be implemented as `class LifeRuleGenerations`.

##### Hint

You may want to inherit `LifeRuleBase` and override its `DetermineNextState`.

### Cell state and map representation

#### Cell State

The cell class `LifeCell` is defined in `LifeCell.cpp`. It has three attributes: **x**, **y** and **state**. However, to support different rules, the state is not only a 'dead' or 'alive' state, but a integer state. The state of a cell can be one of the following:

- 0: dead
- 1: alive
- 2: red (colorised rule)
- 3: blue (colorised rule)

Or the state can be the generation of the cell in generations rule, in which case the state can be any integer from 0 to 8.

Your implementation of the rules should be able to handle the state transition between these states, it is guaranteed in all test cases that

- The state of a cell will never be negative.
- In the base rule, extended rule and weighted rule, the state of a cell will only be 0 or 1.
- In the colorised rule, the state of a cell will only be 0, 2 or 3.
- In the generations rule, the state of a cell will only be 0, 1 or 2 to 8.

#### Map File

Our game world can be represented by a map file. In these homework, we use a simple `.cells` file to store the initial state of the game. 

We provide some example files in the `map` folder, you can refer to [How-to-Run](#how-to-run) to see how to load the map file. 

You don't need to load the map by yourself, our framework have already implemented the map loading function. In case you want to edit the map file, here is a brief introduction of the file format:

The file format is similar to [plain text format](https://conwaylife.com/wiki/Plaintext) for simpilicity. However, to support different rules, we have made some changes to the file format.


> ##### This part can be ignored if you don't want to edit the map file.
> ###### Comments start with a '!' and are ignored
>
> ###### Cells are represented by a 'O' or '.' (alive or dead respectively)
>
> ###### 'R' and 'B' represent red and blue cells in colorised rule (it is ignored in other rules, and not supported officially by golly).
> ###### Numbers represent the generation of the cell in generations rule (it is ignored in other rules, and not supported officially by golly).

### How to run

#### Compile the project

In Windows, you can run with:

```bash
g++ -Wall -Wextra -o gof.exe GameWorld.cpp GameManager.cpp LifeCell.cpp main.cpp LifeRuleStudent.cpp
```

In Linux or MacOS, you can run with:

```bash
g++ -Wall -Wextra -o gof GameWorld.cpp GameManager.cpp LifeCell.cpp main.cpp LifeRuleStudent.cpp
```

#### Run the project

```bash
./gof <rule>
```

The program takes one argument, which is the rule you want to use. The rule can be `Base`, `Colorised`, `Extended`, `Weighted`, `Generations`.

Try to run with `./gof base` and you can play with the original Game of Life.

Then, you can select a map from `map/` and play with it. We have provided different maps for different rules.

For example, you can run with `./gof colorised`, then load the map 'map/colorised.cells'.

You can find more maps at the [wiki](https://conwaylife.com/wiki/) and play with them at [golly](https://golly.sourceforge.net/webapp/golly.html).

### File Structure

This problem contains several files. You may need to read and understand some of them in order to complete the assignment. There are also some files that you can simply ignore. **You don't need to understand every line to finish this homework**.

## Submission

You only need to submit `LifeRuleStudent.cpp` to OJ.
