# Puzzle Game
This is a puzzle game implemented in C++ using the SDL2 library. The game consists of a 4x4 puzzle grid with numbered tiles that can be moved to solve the puzzle. The game generates a random initial puzzle configuration and the player must rearrange the tiles to return them to their original order.

## Prerequisites
1. [SDL2](https://www.libsdl.org/) (Simple DirectMedia Layer) library for rendering the puzzle.
2. [SLDL2 TTF](https://github.com/libsdl-org/SDL_ttf) (TrueType Support) library for rendering text.

## Building and Running
A compiled executable for Windows is provided in this repository. To run the game on Windows, simply double-click on the `puzzle.exe` file. Make sure that the provided dll files, and font file are present in the directory with the executable.

To compile the code for Linux, you will need to change the entry point function from `WinMain` to `main`. You can then follow the following steps:

1. Install the SDL2 library and the SDL2 TTF library.
2. Clone this repository to your local machine.
3. Navigate to the root directory of the repository.
4. Remove the dll files (optional).
5. Run the following command to build the program:
```
g++ puzzle.cpp -o puzzle -lSDL2 -lSDL2_ttf
```
6. Run the following command to run the program:
```
./puzzle
```
## Controls
The controls for the game are as follows:

* Use the WASD keys or the arrow keys to move a tile.
* Press Escape to pause the game.
* On the escape menu or the game won menu, pressing Space will generate a new game.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
* A small portion of the code for this program was generated by the [GPT language model](https://chat.openai.com/).
