# Console Snake

A classic Snake game written in C++ that runs in the Windows console.

Steer the snake around the board, eat the fruit to grow longer and score points, and avoid hitting the walls or your own tail.

```
######################
#                    #
#                    #
#         F          #
#                    #
#       Ooo          #
#                    #
######################
Score: 10
```

## Features

- Snake grows and the score increases when you eat fruit
- Fruit spawns in a random free cell (never on the snake)
- Wall and self-collision detection
- Smooth, flicker-free redrawing (no screen clearing)
- Game Over screen with your final score

## Controls

| Key | Action     |
|-----|------------|
| `W` | Move up    |
| `A` | Move left  |
| `S` | Move down  |
| `D` | Move right |
| `X` | Quit       |

## Requirements

This game is **Windows-only**, because it uses `conio.h` and the Windows console API (`Windows.h`).

You need one of:
- Visual Studio (with the "Desktop development with C++" workload)
- MinGW-w64 (`g++`)

## Build and run

**Visual Studio**

1. Create a new *Console App* (C++) project.
2. Add `snake.cpp` to the project.
3. Press `Ctrl+F5` to build and run.

**MinGW / g++**

```bash
g++ snake.cpp -o snake.exe
snake.exe
```

Run it in a real console window (cmd or PowerShell). Keyboard input may not work in some IDE output panels or online compilers.

## How it works

The game runs in a simple loop:

1. `Draw()` prints the board, snake, fruit, and score
2. `Input()` reads the keyboard without blocking
3. `Logic()` moves the snake, checks collisions, and handles eating
4. `Sleep(100)` sets the game speed

To change the difficulty, edit the `Sleep(100)` value (lower is faster) or the `width` and `height` constants.

## License

MIT. See `LICENSE` for details.
