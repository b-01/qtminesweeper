# QT Minesweeper

Minesweeper implementation written with C++ and QT. 

## How to build

On Linux based systems run `cmake_eclipse.sh` with either `Debug` or `Release`. Cmake then creates all the relevant build files under `build`.

To build the binary, navigate to `build/linux/(debug|release)/` and run `make`.

Binaries can then be found in the `bin` folder.


## How to use

Just start the `qtminesweeper` binary to run the game.

The purpose of the game is to open all the cells of the board which do not contain a bomb. You lose if you set off a bomb cell.

Every non-bomb cell you open will tell you the total number of bombs in the eight neighboring cells. Once you are sure that a cell contains a bomb, you can right-click to put a flag it on it as a reminder. You can quickly open all surrounding cells by middle-clicking on a cell. Be sure to mark all possible bomb locations or you will lose the game :wink:

To start a new game (or bandoning the current one), just click on the yellow face button.

### TLDR
- **left click**: open an unopened cell
- **right click**: mark an unopened cell as bomb (will not open on left/middle click)
- **middle click**: open all (8) surrounding cells

## Disclaimer

I've written this game years ago to replace [Gnome Mines](https://wiki.gnome.org/Apps/Mines) as it stopped working properly on my system at this time. Also wanted to try out UI programming using C++ and QT on Linux.

I will not povide a premade binary. The game might not work on your system. I do not update this repo.