# So Long

![C](https://img.shields.io/badge/language-C-blue.svg)

A 2D game engine and mini-game built with the MiniLibX graphics library.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Game Controls](#game-controls)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Challenges and Solutions](#challenges-and-solutions)
- [Contributing](#contributing)
- [License](#license)

## Overview

So Long is a simple 2D game where the player navigates through a map, collecting items and avoiding enemies, with the goal of reaching the exit. This project demonstrates skills in graphics programming, game logic implementation, and efficient memory management in C.

## Features

- Custom map parsing and validation
- Smooth graphics rendering using MiniLibX
- Player movement and collision detection
- Item collection mechanic
- Enemy AI with random movement
- Win/lose conditions
- Animated sprites
- Move counter display

## Requirements

- GCC compiler
- Make
- MiniLibX library
- X11 include files (for Linux)

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/g-garibotti/so_long.git
   ```
2. Navigate to the project directory:
   ```
   cd so_long
   ```
3. Compile the project:
   ```
   make
   ```

## Usage

Run the game with a map file:

```
./so_long maps/map1.ber
```

## Game Controls

- Move Up: `W` or `↑`
- Move Down: `S` or `↓`
- Move Left: `A` or `←`
- Move Right: `D` or `→`
- Quit Game: `ESC` or close window

## Project Structure

- `main.c`: Entry point and game initialization
- `game_loop.c`: Main game loop and event handling
- `map_parser.c` & `map_reader.c`: Map loading and validation
- `map_solver.c`: Map solvability checker
- `render.c`: Graphics rendering functions
- `player.c` & `enemy.c`: Player and enemy logic
- `collision.c`: Collision detection
- `textures.c`: Texture loading and management
- `game_update.c`: Game state updates
- `game_exit.c`: Cleanup and exit handling

## Technical Details

### Map Parsing and Validation
- Maps are loaded from `.ber` files
- Validation checks for rectangular shape, enclosed walls, and required elements
- Flood fill algorithm ensures map solvability

### Graphics Rendering
- Utilizes MiniLibX for efficient rendering
- Implements double buffering for smooth animations
- Supports custom textures for all game elements

### Game Logic
- Implements a state machine for game flow
- Uses delta time for consistent game speed across different systems
- Efficient collision detection using grid-based checks

### Memory Management
- Careful allocation and deallocation to prevent memory leaks
- Use of static variables to optimize performance

## Challenges and Solutions

1. **Challenge**: Efficient map parsing and validation
   **Solution**: Implemented a two-pass system: first pass for basic structure, second for detailed validation and flood fill

2. **Challenge**: Smooth animations with MiniLibX
   **Solution**: Utilized double buffering and frame-based animation system

3. **Challenge**: Balancing game difficulty
   **Solution**: Implemented configurable enemy movement patterns and adjustable game speed

