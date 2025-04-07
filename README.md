# 🐍 Snake Game

This repository contains an implementation of the classic Snake game developed in the C programming language.

## Description

Snake is a game where the player controls a snake moving around the screen. The objective is to collect as much food as possible (represented by a character on the screen) without colliding with the walls or the snake's own body. Each time the snake eats, it grows longer, increasing the game's difficulty.

## Features

- **Language:** C
- **Interface:** Console-based
- **Mechanics:**
  - Snake movement in four directions: up, down, left, and right.
  - Snake grows when it eats food.
  - Game ends upon collision with walls or itself.

## Requirements

- C compiler (e.g., GCC)
- Operating system compatible with console applications

## Installation and Execution

1. **Clone the repository:**

   ```bash
   git clone https://github.com/NicolasSerranoGarcia/Snake-game.git
2. **Compile the source code**

  Navigate to the project directory and compile the `snake.c` file:

  ```bash
  cd Snake-game
  gcc -o snake snake.c
  ```
3. **Run the game**
  After compiling, run the game with
  ```bash
    ./snake
  ```
4. **Controls**
- W: Move up

- S: Move down

- A: Move left

- D: Move right

- Q: Quit the game


## Contributions
Contributions are welcome! If you wish to improve this project, please follow these steps:

1. **Fork the repository**

2. **Create a new branch for your feature or fix:**

```bash
git checkout -b my-new-feature
```
3. **Make your changes and commit them:**

```bash
git commit -m 'Add new feature'
```
4. **Push your changes to my repository:**

```bash
git push origin 
```
